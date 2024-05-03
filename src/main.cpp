#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl2.h>

#include <SDL.h>
#include <GL/gl3w.h>

#include <iostream>
// #include "engine/rendering/shader.cpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FRAME_RATE 120

// Destroys the window and displays an error message.
int destroyWindow(SDL_Window *windowPtr, SDL_GLContext context, const char *message) {
	printf("Error: %s", message);
	if (context != NULL)
		SDL_GL_DeleteContext(context);
	if (windowPtr != NULL)
	    SDL_DestroyWindow(windowPtr);
    SDL_Quit();
	return 1;
}

int main(int argc, char* args[]) {
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
    	return 1;

    window = SDL_CreateWindow("Hello Cube",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
	);

	if (window == NULL)
		return destroyWindow(window, NULL, "Window failed to create");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (context == NULL)
        return destroyWindow(window, context, "Context failed to create");
    gl3wInit();
    ImGuiContext *guiContext = ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	ImGui_ImplSDL2_InitForOpenGL(window, context);
	ImGui_ImplOpenGL3_Init();

	ImGui::StyleColorsDark();
    
	SDL_Event windowEvent;
	uint32_t previous_time = SDL_GetTicks64();
	uint32_t current_time;
	float delta_time;
	float delta_time_target = (1.0 / (float)FRAME_RATE);
	while (true) {
		current_time = SDL_GetTicks64();
		if (SDL_PollEvent(&windowEvent)) {
			ImGui_ImplSDL2_ProcessEvent(&windowEvent);
			if (windowEvent.type == SDL_QUIT) 
				break;
		}
		delta_time = (float)(current_time - previous_time) / 1000;
		if (delta_time >= delta_time_target) {
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame();
			ImGui::NewFrame();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			SDL_GL_SwapWindow(window);
			previous_time = current_time;
		}
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext(guiContext);

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
    SDL_Quit();
	return 0;
}