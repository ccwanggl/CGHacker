#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

struct ShaderSource
{
	std::string vectexShader;
	std::string fragmentShader;
};

enum class ShaderType
{
	NONE=-1,
	VERTEX=0,
	FRAGMENT=1
};

static ShaderSource ParseShader(const std::string& filepath)
{
	std::fstream file(filepath);
	std::string line;

	ShaderType type = ShaderType::NONE;
	std::stringstream ss[2];

	while (std::getline(file, line))
	{
		if (line.find("shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[static_cast<int>(type)] << line << "\n";
		}

	}

	return { ss[0].str(), ss[1].str() };

}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//TODO(guoliang): Error Handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile shader!" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl; 
		std::cout << message << std::endl;

		glDeleteShader(id);

		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vs, const std::string& fs)
{
	unsigned int program = glCreateProgram();
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vs);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fs);


	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}


int main()
{
	GLFWwindow* window{ nullptr };

	if (!glfwInit())
	{
		std::cout << "GLFW init failed!" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "Hello Triangle", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initalize GLAD" << std::endl;
		return -1;
	}

	{
		float vertices[] = {
			0.5f, 0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f ,
		};

		unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		VertexArray va;
		VertexBuffer vb(vertices, 4 * 3 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		ShaderSource src = ParseShader("res/shaders/basic.shader");
		unsigned int program = CreateShader(src.vectexShader, src.fragmentShader);


		while (!glfwWindowShouldClose(window))
		{
			glUseProgram(program);
			va.Bind();
			ib.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);


			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glDeleteProgram(program);

	}
		glfwTerminate();

	return 0;
}

