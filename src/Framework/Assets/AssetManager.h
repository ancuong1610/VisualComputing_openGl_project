#pragma once
#include <ShaderProgram.h>
#include <memory>
#include <libheaders.h>
#include <unordered_map>
#include <memory>
#include <OBJLoader.h>
class AssetManager
{
private:
	std::unordered_map<std::string, std::unique_ptr<ShaderProgram>> m_shaders;

public:

	//factory functions
	static std::unique_ptr<ShaderProgram> createShaderProgram(const std::string& vspath, const std::string& fspath);

	//member functions
	ShaderProgram* getShaderProgram(const std::string& name);
	void addShaderProgram(const std::string& name, std::unique_ptr<ShaderProgram>&& shader);
	bool removeShaderProgram(const std::string& name);

};

