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

	while (!glfwWindowShouldClose(window))
	{

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	std::cin.get();
}