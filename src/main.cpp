#include <tinysdl.h>
#include <string>

#include "shaders/shaders.h"

#include "imgui.h" 
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#define CONTROL_FLOAT(var, vmin, vmax) ImGui::SliderFloat(#var, &var, vmin, vmax, "%.3f");

using namespace TinySDL;
typedef Vec<double, 2> DVec2;

int main(int argc, char *argv[]) {

    int screen_w = 512, screen_h = 256;
    
    SDL_Window * window = Window::init("Mandelbrot explorer", screen_w, screen_h);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    Mat4x4 window_projection = LinAlg::ortho(0, (float) screen_w, (float) screen_h, 0, -1, 1);
    // Mat4x4 window_projection = Mat4x4::identity;
    
    BatchRenderer renderer;
    renderer.setup();

    auto& colormaps = MB::get_colormaps();
    std::vector<const char*> cm_labels;
    for (auto [label, src] : colormaps)
    {
        cm_labels.push_back(label);
    }

    
    std::string frag_src = MB::get_frag_src();

    int current_cm = 0;
    Shader mandelbrot_shader = Shader::from_source(MB::get_vertex_src(),  (frag_src + colormaps[current_cm].src).c_str());
    // Shader sprite_shader = Shader::default_sprite_shaders();



    // Texture sprite_tex = Texture::from_file("sprite.png");
    bool is_clicking = false;
    IVec2 mouse_pos = {0, 0};
    IVec2 mouse_initial_pos = {0, 0};
    
    double zoom = 120.0;
    DVec2 current_offset = {-256 / zoom, -128 / zoom};


    mandelbrot_shader.use().set_mat4x4("projection", window_projection); 
    mandelbrot_shader.set_dvec2("window_size", {(double) screen_w, (double) screen_h});
    mandelbrot_shader.set_dvec2("offset", current_offset);
    mandelbrot_shader.set_double("zoom", zoom);


    mandelbrot_shader.set_double("radius", 4.0);

    float scale_exp = 1.0f;
    mandelbrot_shader.set_float("scale_exp", scale_exp);

    // int max_iter = 200;
    // mandelbrot_shader.set_int("max_iter", max_iter);


    int max_iter = 600;
    IVec2 iter_range = {0, 200};
    mandelbrot_shader.set_int("min_iter_range", iter_range[0]);
    mandelbrot_shader.set_int("max_iter_range", iter_range[1]);

    // Setup Dear Imgui stuff goes here ----

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io; 

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(window, Window::get_context());
    ImGui_ImplOpenGL3_Init("#version 460");


    ImGui::GetStyle().FrameRounding = 4.0f;
    ImGui::GetStyle().GrabRounding = 4.0f;
    
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);



    SDL_Event event; 
    bool quit = false;
    while(!quit) {
        while (SDL_PollEvent(&event) != 0) {
            ImGui_ImplSDL2_ProcessEvent(&event);

            if (event.type == SDL_QUIT) quit = true;
            if (event.type == SDL_WINDOWEVENT) {
                if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    Window::get_drawable_size(&screen_w, &screen_h);
                    mandelbrot_shader.set_mat4x4("projection", LinAlg::ortho(0, (float) screen_w, (float) screen_h, 0, -1, 1)); 
                    mandelbrot_shader.set_vec2("window_size", {(float) screen_w, (float) screen_h});
                }
            }

            if(io.WantCaptureMouse) break;

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

                mandelbrot_shader.set_double("zoom", zoom);
                mandelbrot_shader.set_dvec2("offset", current_offset);
            }

        } 


        if(is_clicking){
            SDL_GetMouseState(&mouse_pos[0], &mouse_pos[1]);
            DVec2 delta_offset = (mouse_initial_pos.cast_to<double>() - mouse_pos.cast_to<double>()) / zoom;
            mandelbrot_shader.set_dvec2("offset", current_offset + delta_offset);
        }

        Graphics::viewport(screen_w, screen_h);
        Graphics::clear(Color::black);

        renderer.draw_rect_fill({0, 0, (float)screen_w, (float)screen_h}, Color::white);

        renderer.render();



                // Draw Dear Imgui stuff goes here ----
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        ImGui::SetNextWindowBgAlpha(0.5f);
        ImGui::Begin("Mandelbrot set parameters");                          

        ImGui::Text("Zoom: %.3ex\t\t%.1f FPS", zoom, ImGui::GetIO().Framerate);

        if(ImGui::SliderFloat("Scale exponent", &scale_exp, 0.0f, 2.0f, "%.3f"))
        {
            mandelbrot_shader.set_float("scale_exp", scale_exp);
        }

        if(ImGui::SliderInt2("Iteration range", &iter_range[0], 0, max_iter, "%d iter."), ImGuiSliderFlags_AlwaysClamp)
        {

            iter_range[0] = std::clamp(iter_range[0], 0, iter_range[1]);
            
            mandelbrot_shader.set_int("min_iter_range", iter_range[0]);
            mandelbrot_shader.set_int("max_iter_range", iter_range[1]);
        }

        
        if(ImGui::Combo("Colormap", &current_cm, cm_labels.data(), (int)cm_labels.size()))
        {
            Log::debug("changed!");

            mandelbrot_shader.del();
            mandelbrot_shader = Shader::from_source(MB::get_vertex_src(),  (frag_src + colormaps[current_cm].src).c_str());
            mandelbrot_shader.use();

            mandelbrot_shader.set_int("min_iter_range", iter_range[0]);
            mandelbrot_shader.set_int("max_iter_range", iter_range[1]);
            mandelbrot_shader.set_float("scale_exp", scale_exp);
            mandelbrot_shader.set_dvec2("offset", current_offset);
            mandelbrot_shader.set_mat4x4("projection", LinAlg::ortho(0, (float) screen_w, (float) screen_h, 0, -1, 1)); 
            mandelbrot_shader.set_vec2("window_size", {(float) screen_w, (float) screen_h});
            mandelbrot_shader.set_double("radius", 4.0);
            mandelbrot_shader.set_double("zoom", zoom);
        }


        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



        SDL_GL_SwapWindow(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    
    return 0;
}