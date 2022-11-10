#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "Texture.h"
#include "Camera.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include "Square.h"

// Screen Size
const unsigned int width = 800;
const unsigned int height = 800;

int main() {
	//Init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenglTutorial", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	// Shaders
	Shader shaderProgram("default.vert", "default.frag");

	Square sq(0.5f, 0.5f, 1, -1, 144, 238, 144);

	//Texture
	//Texture popCat("RubixCube.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	//popCat.texUnit(shaderProgram, "tex0", 0);

	//Camera Object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	//basicly delta time
	glfwSwapInterval(1);

	//Loop
	while (!glfwWindowShouldClose(window)) {
		//Clear Screen
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		//Camera
		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		//Drawing Object
		//popCat.Bind();
		sq.draw();

		//Swap Buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//Delete everything from memory
	//TODO: Call the delete function for the vao, vbo, and ebo
	//popCat.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}