#pragma once
#include "Textures/stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	static unsigned int loadTexture(char const* path);
};
