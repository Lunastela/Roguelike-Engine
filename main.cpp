#include <SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include <iostream>

#define GLSL(src) "#version 150 core\n" #src

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

float vertices[] = {
     0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
};

const char* vertexSource = GLSL(
	in vec2 position;
	in vec3 color;

	out vec3 Color;

	void main()
	{
		Color = color;
		gl_Position = vec4(position, 0.0, 1.0);
	}
);

const char* fragmentSource = GLSL(
	in vec3 Color;

	out vec4 outColor;

	void main()
	{
		outColor = vec4(Color, 1.0);
	}
);

void setupRenderCalls() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Create Shader Program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
		5 * sizeof(float), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
		5 * sizeof(float), (void*)(2 * sizeof(float)));
}

// Destroys the window and displays a message
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
 
 	window = SDL_CreateWindow("Hello Triangle",
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

	setupRenderCalls();

	SDL_Event windowEvent;
	while (true) {
		if (SDL_PollEvent(&windowEvent)) {
			if (windowEvent.type == SDL_QUIT) 
				break;
		}
		SDL_GL_SwapWindow(window);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	return 0;
}