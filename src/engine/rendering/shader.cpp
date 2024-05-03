#include "shader.hpp"
#include <GL/gl3w.h>
#include <string>

#define GLSL(src) "#version 330 core\n" #src

using Roguelike::Shader;

const char* defaultVertexSource = GLSL(
	in vec3 position;
	in vec3 color;
	in vec2 texcoord;

	out vec3 Color;
	out vec2 Texcoord;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 proj;

	void main()
	{
		Color = color;
		Texcoord = texcoord;
		gl_Position = proj * view * model * vec4(position, 1.0);
	}
);

const char* defaultFragmentSource = GLSL(
	in vec3 Color;

	out vec4 outColor;

	void main()
	{
		outColor = vec4(Color, 1.0);
	}
);

Shader::Shader(const char* vertexPath = "", const char* fragmentPath = "") {
    // Define default shader behavior

}