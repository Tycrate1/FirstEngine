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

// Screen Size
const unsigned int width = 800;
const unsigned int height = 800;

int main() {
	//Init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Vertices
	GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 0.0f,	0.0f, 0.0f, //Lower left corner
		-0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 0.0f,	0.0f, 1.0f, //Upper left corner
		 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 0.0f,	1.0f, 1.0f, //Upper right corner
		 0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 0.0f,	1.0f, 0.0f  //Lower right corner
	};
	//Indices
	GLuint indices[] =
	{
		0, 2, 1, //Upper triangle
		0, 3, 2 //Lower triangle
	};

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

	// VAO/VBO/EBO
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//Texture
	Texture popCat("RubixCube.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);

	//Camera Object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

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
		popCat.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//Swap Buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//Delete everything from memory
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popCat.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}