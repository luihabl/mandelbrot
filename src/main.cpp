#include <tinysdl.h>
#include <string>

#include <glad/glad.h>

#include "shaders/shaders.h"

using namespace TinySDL;
typedef Vec<double, 2> DVec2;

int main(int argc, char *argv[]) {

    int screen_w = 512, screen_h = 256;
    
    SDL_Window * window = Window::init("Window Title", screen_w, screen_h);
    Mat4x4 window_projection = LinAlg::ortho(0, (float) screen_w, (float) screen_h, 0, -1, 1);
    // Mat4x4 window_projection = Mat4x4::identity;
    
    BatchRenderer renderer;
    renderer.setup();

    Shader mandelbrot_shader = Shader::from_source(MB::vertex_src, MB::frag_src);
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

    SDL_Event event; 
    bool quit = false;
    while(!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) quit = true;
            if (event.type == SDL_WINDOWEVENT) {
                if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    Window::get_drawable_size(&screen_w, &screen_h);
                    mandelbrot_shader.set_mat4x4("projection", LinAlg::ortho(0, (float) screen_w, (float) screen_h, 0, -1, 1)); 
                    mandelbrot_shader.set_vec2("window_size", {(float) screen_w, (float) screen_h});
                }
            }
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
        SDL_GL_SwapWindow(window);
    }
    
    return 0;
}