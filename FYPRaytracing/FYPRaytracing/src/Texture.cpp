#include "Texture.h"
#include "vendor/stb_image/stb_image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Texture::Texture(const std::string& path)
{
	m_directory = path;
	m_buffer = nullptr;
	m_width = 0;
	m_height = 0;
	m_bitsPerPixel = 0;
	m_rendererId = 0;

	stbi_set_flip_vertically_on_load(1);
	m_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bitsPerPixel, 4);

	glGenTextures(1, &m_rendererId);
	glBindTexture(GL_TEXTURE_2D, m_rendererId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer);
	glGenerateMipmap(GL_TEXTURE_2D);

	if (m_buffer)
		stbi_image_free(m_buffer);
}

void Texture::Bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_rendererId);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::GetWidth()
{
	return m_width;
}

int Texture::GetHeight()
{
	return m_height;
}

int Texture::GetBitsPerPixel()
{
	return m_bitsPerPixel;
}

unsigned char* Texture::GetBufferPtr()
{
	return m_buffer;
}
