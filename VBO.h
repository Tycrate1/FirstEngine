#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO {
public:
	//Id is the vbo object
	GLuint ID;
	VBO(GLfloat* vertices, GLsizeiptr size);
	VBO();

	void Bind();
	void Unbind();
	void Delete();
};

#endif