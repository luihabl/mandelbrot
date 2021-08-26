#include <tinysdl.h>

using namespace TinySDL;

int main(int argc, char *argv[]) {

    int screen_w = 512, screen_h = 256;
    
    SDL_Window * window = Window::init("Window Title", screen_w, screen_h);
    Mat4x4 window_projection = LinAlg::ortho(0, (float) screen_w, (float) screen_h, 0, -1, 1);
    
    BatchRenderer renderer;
    renderer.setup();

    Shader shader = Shader::default_sprite_shaders();
    shader.use().set_mat4x4("projection", window_projection); 

    Texture sprite_tex = Texture::from_file("sprite.png");

    SDL_Event event; 
    bool quit = false;
    while(!quit) {
        while (SDL_PollEvent(&event) != 0) if (event.type == SDL_QUIT) quit = true;

        Graphics::viewport(screen_w, screen_h);
        Graphics::clear(Color::black);

        renderer.set_texture(&sprite_tex);
        renderer.draw_tex({50.0f, 150.0f});

        renderer.render();
        SDL_GL_SwapWindow(window);
    }
    
    return 0;
}