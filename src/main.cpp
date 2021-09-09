#include <tinysdl.h>
#include <string>

#include "shaders/shaders.h"
#include "gui.h"

#include "imgui.h" 
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#define CONTROL_FLOAT(var, vmin, vmax) ImGui::SliderFloat(#var, &var, vmin, vmax, "%.3f");

using namespace TinySDL;
typedef Vec<double, 2> DVec2;

int main(int argc, char *argv[]) {

    // Setup --------------------------------------------------------------------------------------------------------------

    int screen_w = 960, screen_h = 580;
    
    SDL_Window * window = Window::init("Mandelbrot explorer", screen_w, screen_h);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    Mat4x4 window_projection = LinAlg::ortho(0, (float) screen_w, (float) screen_h, 0, -1, 1);
    
    BatchRenderer renderer;
    renderer.setup();

    MB::GUI gui(window, Window::get_context());
    gui.setup();

    // Shaders ------------------------------------------------------------------------------------------------------------

    auto& colormaps = MB::get_colormaps();
    std::vector<const char*> cm_labels;
    for (auto [label, src] : colormaps)
    {
        cm_labels.push_back(label);
    }

    
    std::string frag_src = MB::get_frag_src();

    int current_cm = 0;
    Shader shader = Shader::from_source(MB::get_vertex_src(),  (frag_src + colormaps[current_cm].src).c_str());

    // Shaders ------------------------------------------------------------------------------------------------------------


    int max_iter = 600;
    bool is_clicking = false;
    IVec2 mouse_pos = {0, 0};
    IVec2 mouse_initial_pos = {0, 0};
    IVec2 iter_range = { 0, 200 };
    double zoom = 200.0;
    DVec2 current_offset = {-580 / zoom, -290 / zoom};
    float scale_exp = 1.0f;

    // Setting uniforms ----------------------------------------------------------------------------------------------------

    shader.use().set_mat4x4("projection", window_projection);
    shader.set_dvec2("window_size", {(double) screen_w, (double) screen_h});
    shader.set_dvec2("offset", current_offset);
    shader.set_double("zoom", zoom);
    shader.set_double("radius", 4.0);
    shader.set_float("scale_exp", scale_exp);
    shader.set_int("min_iter_range", iter_range[0]);
    shader.set_int("max_iter_range", iter_range[1]);

   
    SDL_Event event; 
    bool quit = false;
    while(!quit) {

        // Getting inputs -------------------------------------------------------------------------------------------------

        while (SDL_PollEvent(&event) != 0) {
            
            gui.process_event(&event);

            if (event.type == SDL_QUIT) quit = true;
            
            if (event.type == SDL_WINDOWEVENT) {
                if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    Window::get_drawable_size(&screen_w, &screen_h);
                    shader.set_mat4x4("projection", LinAlg::ortho(0, (float) screen_w, (float) screen_h, 0, -1, 1));
                    shader.set_vec2("window_size", {(float) screen_w, (float) screen_h});
                }
            }

            if(gui.io().WantCaptureMouse) break;

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                is_clicking = true;
                SDL_GetMouseState(&mouse_initial_pos[0], &mouse_initial_pos[1]);
            }
            else if(event.type == SDL_MOUSEBUTTONUP) {
                is_clicking = false;
                DVec2 delta_offset = (mouse_initial_pos.cast_to<double>() - mouse_pos.cast_to<double>()) / zoom;
                current_offset = current_offset + delta_offset;
            }
            
            if(event.type == SDL_MOUSEWHEEL)
            {
                double old_zoom = zoom;

                if (event.wheel.y < 0)
                    zoom *= 0.95;

                if (event.wheel.y > 0)
                    zoom *= 1.05;

                SDL_GetMouseState(&mouse_pos[0], &mouse_pos[1]);

                current_offset = current_offset + (1.0/old_zoom - 1.0/zoom) * mouse_pos.cast_to<double>();

                shader.set_double("zoom", zoom);
                shader.set_dvec2("offset", current_offset);
            }

        } 


        if(is_clicking){
            SDL_GetMouseState(&mouse_pos[0], &mouse_pos[1]);
            DVec2 delta_offset = (mouse_initial_pos.cast_to<double>() - mouse_pos.cast_to<double>()) / zoom;
            shader.set_dvec2("offset", current_offset + delta_offset);
        }

        // Drawing set ---------------------------------------------------------------------------------------------------

        Graphics::viewport(screen_w, screen_h);
        Graphics::clear(Color::black);

        renderer.draw_rect_fill({0, 0, (float)screen_w, (float)screen_h}, Color::white);

        
        // GUI ------------------------------------------------------------------------------------------------------------

        gui.start_frame();
               
        ImGui::SetNextWindowBgAlpha(0.5f);
        ImGui::Begin("Mandelbrot set parameters");                          

        ImGui::Text("Zoom: %.3ex\t\t%.1f FPS", zoom, ImGui::GetIO().Framerate);

        if(ImGui::SliderFloat("Scale exponent", &scale_exp, 0.0f, 2.0f, "%.3f"))
        {
            shader.set_float("scale_exp", scale_exp);
        }

        if(ImGui::SliderInt2("Iteration range", &iter_range[0], 0, max_iter, "%d iter."), ImGuiSliderFlags_AlwaysClamp)
        {

            iter_range[0] = std::clamp(iter_range[0], 0, iter_range[1]);
            
            shader.set_int("min_iter_range", iter_range[0]);
            shader.set_int("max_iter_range", iter_range[1]);
        }

        
        if(ImGui::Combo("Colormap", &current_cm, cm_labels.data(), (int)cm_labels.size()))
        {
            shader.del();
            shader = Shader::from_source(MB::get_vertex_src(),  (frag_src + colormaps[current_cm].src).c_str());
            shader.use();

            shader.set_int("min_iter_range", iter_range[0]);
            shader.set_int("max_iter_range", iter_range[1]);
            shader.set_float("scale_exp", scale_exp);
            shader.set_dvec2("offset", current_offset);
            shader.set_mat4x4("projection", LinAlg::ortho(0, (float) screen_w, (float) screen_h, 0, -1, 1));
            shader.set_vec2("window_size", {(float) screen_w, (float) screen_h});
            shader.set_double("radius", 4.0);
            shader.set_double("zoom", zoom);
        }

        ImGui::End();

        
        // Rendering ------------------------------------------------------------------------------------------------------
        
        renderer.render();
        gui.render();

        SDL_GL_SwapWindow(window);
    }

    return 0;
}