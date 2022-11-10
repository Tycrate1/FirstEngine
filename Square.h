#ifndef SQUARE_CLASS_H
#define SQUARE_CLASS_H

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Square {
public:
	//Indices
	GLuint indices[6];

	VAO vao;

	Square(float width, float height, float x, float y, float r, float g, float b);

	void draw();
	//TODO: Make a delete function
};

#endif