#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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

	std::string vertexShaderSrc =
		"#version 330 core \n "
		"layout (location = 0) in vec3 aPos; \n"
		//"void main(){ gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); } ";
		"void main(){ gl_Position = vec4(aPos, 1.0); } ";


	std::string fragmentShaderSrc =
		"#version 460 core \n"
		"layout(location=0) out vec4 FragColor; \n"
		"void main() { FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); }";

	// 1. 绑定顶点数组对象
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// 2. 把我们的顶点数组复制到一个顶点缓冲中，供 OpenGL 使用

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int program = CreateShader(vertexShaderSrc, fragmentShaderSrc);
	// 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// 4. 设定顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	while (!glfwWindowShouldClose(window))
	{
		glUseProgram(program);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(program);

	glfwTerminate();

	std::cin.get();
}

