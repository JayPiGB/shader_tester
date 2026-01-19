#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>

#include "shader_loader.h"

float quadVertices[] = {
	-1, 1, 0,
	-1, -1, 0,
	1, 1, 0,
	1, -1, 0
};

GLushort indices[] = {
	0, 1, 2,
	1, 2, 3
};

int main() {
	if (!glfwInit()) {
		std::cout << "GLFW initializaiton error" << std::endl;
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(640, 380, "Shader Tester", NULL, NULL);
	if (!window) {
		std::cout << "Window creation error" << std::endl;
		return 1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Loading opengl error!" << std::endl;
		return 1;
	}

	GLuint quadVAO;
	glGenVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);

	GLuint triangleBuff;
	glGenBuffers(1, &triangleBuff);
	glBindBuffer(GL_ARRAY_BUFFER, triangleBuff);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, 0);

	GLuint elementBuff;
	glGenBuffers(1, &elementBuff);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuff);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glClearColor(0, 0, 0, 1);

	ShaderLoader sl;
	sl.buildShaderProgram();

	while (!glfwWindowShouldClose(window)) {
		int widht, height;
		glfwGetWindowSize(window, &widht, &height);
		glViewport(0, 0, widht, height);

		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(quadVAO);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
