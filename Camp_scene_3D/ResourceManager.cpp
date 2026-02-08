#include "ResourceManager.h"

std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, BasicTexture> ResourceManager::Textures;

Shader& ResourceManager::LoadShader(const char* vertexPath, const char* fragmentPath, std::string name) {
	Shader s(vertexPath, fragmentPath);
	Shaders[name] = s;
	return Shaders.at(name);
}

Shader& ResourceManager::GetShader(std::string name) {
	return Shaders.at(name);
}

BasicTexture& ResourceManager::LoadTexture(const char* filePath, bool alpha, std::string name) {
	BasicTexture t;
	t.Generate(filePath);
	Textures[name] = t;
	return Textures.at(name);
}

BasicTexture& ResourceManager::GetTexture(std::string name) {
	return Textures.at(name);
}

void ResourceManager::Clear() {
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.ID);
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);
}