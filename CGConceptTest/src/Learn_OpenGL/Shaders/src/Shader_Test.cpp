#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


int main()
{
	GLFWwindow* window;

	if (!glfwInit())
	{
		// test
	}

	window = glfwCreateWindow(800, 600, "Shaders", nullptr, nullptr);
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

	std::cout << glGetString(GL_VERSION) << std::endl;


	while (!glfwWindowShouldClose(window))
	{

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	std::cin.get();
}