#define GLEW_STATIC

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int destroyWindow(SDL_Window *windowPtr, SDL_GLContext context, const char *message) {
	fprintf(stderr, message);
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
 
 	window = SDL_CreateWindow("Hello Window",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
	);

	if (window == NULL)
		return destroyWindow(window, NULL, "Window failed to create");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (context == NULL)
        return destroyWindow(window, context, "Context failed to create");
	SDL_GL_SetSwapInterval(1); 

	GLenum err;
    glewExperimental = GL_TRUE;
    err = glewInit();
    if (err != GLEW_OK)
        return destroyWindow(window, context, "GLEW failed to initialize");

	SDL_Event windowEvent;
	while (true) {
		if (SDL_PollEvent(&windowEvent)) {
			if (windowEvent.type == SDL_QUIT) 
				break;
		}
		SDL_GL_SwapWindow(window);
	}
	return 0;
}