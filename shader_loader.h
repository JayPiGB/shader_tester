#pragma once
#include<glad/glad.h>
struct ShaderLoader {
	char* loadShaderSourceFromFile(const char* path);
	bool buildShaderProgram();
};
