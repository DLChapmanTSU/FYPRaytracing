#pragma once
#include <string>

class Texture
{
private:
	int m_width;
	int m_height;
	int m_bitsPerPixel;
	std::string m_directory;
	unsigned char* m_buffer;
	unsigned int m_rendererId;
public:
	Texture(const std::string& path);
	void Bind(unsigned int slot = 0);
	void Unbind();
	int GetWidth();
	int GetHeight();
	int GetBitsPerPixel();
	unsigned char* GetBufferPtr();
};