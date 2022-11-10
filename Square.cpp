#include "Square.h"

Square::Square(float width, float height, float x, float y, float r, float g, float b) : indices{ 0, 2, 1, 0, 3, 2 } {
	float xCords = width / 2;
	float yCords = height / 2;

	GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS      /   TexCoord  //
		-xCords + x, -yCords + y, 0.0f,     r / 255, g / 255,  b / 255,	0.0f, 0.0f, //Lower left corner
		-xCords + x,  yCords + y, 0.0f,     r / 255, g / 255,  b / 255,	0.0f, 0.0f, //Upper left corner
		 xCords + x,  yCords + y, 0.0f,     r / 255, g / 255,  b / 255,	0.0f, 0.0f, //Upper right corner
		 xCords + x, -yCords + y, 0.0f,     r / 255, g / 255,  b / 255,	0.0f, 0.0f  //Lower right corner
	};

	vao.Bind();

	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

void Square::draw() {
	vao.Bind();
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

//TODO: Make a delete function