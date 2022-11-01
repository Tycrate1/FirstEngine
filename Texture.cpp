#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
	// Type of texture
	type = texType;
	// numcolch is the color chanels for the image
	int widthImg, heightImg, numColCh;
	//flips the image so its facing the right way
	stbi_set_flip_vertically_on_load(true);
	// Stores the image file in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	//Opengl texture object
	glGenTextures(1, &ID);
	//assigns texture
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	//type of algorithm that makes image smaller or bigger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//configures repeat
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//for clamp to border
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(texType, GL_TEXTURE_BORDER_COLOR, flatColor);

	//assigns image to object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);

	//clears and unbinds
	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	//gets uniform location from shader program
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	//sets value of the uniform
	glUniform1i(texUni, 0);
}

//binds
void Texture::Bind() {
	glBindTexture(type, ID);
}

//unbinds
void Texture::Unbind() {
	glBindTexture(type, 0);
}

//deletes
void Texture::Delete() {
	glDeleteTextures(1, &ID);
}