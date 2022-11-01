#include "VBO.h"

//Creates a VBO for an object you want to draw
VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

//binds
void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

//unbinds
void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//deletes
void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}