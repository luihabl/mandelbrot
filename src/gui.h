#include <tinysdl.h>

#include "imgui.h" 
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"


namespace MB
{
	class GUI
	{
	public:
		GUI(SDL_Window* window, SDL_GLContext* context);
		~GUI();
		void setup();
		void render();
		void process_event(SDL_Event* event);
		void start_frame();

		ImGuiIO& io();

	private:
		SDL_Window* window;



	};



}

