#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f, 
	};

	float rect_vertices[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f, 
		-0.5f, 0.5f, 0.0f ,
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	const char* vertexShaderSrc =
		"#version 330 core \n "
		"layout (location = 0) in vec3 aPos; \n"
		"void main(){ gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); } ";


	const char* fragmentShaderSrc =
		"#version 330 core \n"
		"out vec4 FragColor; \n"
		"void main() { FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); }";

	// 1. 绑定顶点数组对象
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// 2. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
	glCompileShader(fragmentShader);


	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


#if 0
	// 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
#endif


	// 4. 设定顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	// ..:: 绘制代码（渲染循环中） :: ..
#if 0
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0)
	glBindVertexArray(0);
#endif


	while (!glfwWindowShouldClose(window))
	{

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	std::cin.get();
}

