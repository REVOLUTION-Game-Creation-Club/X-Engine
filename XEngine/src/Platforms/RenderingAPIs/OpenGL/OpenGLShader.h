#pragma once
#include "XEngine/GraphicsSystem/Shader.h"
#include <glm/glm.hpp>
typedef unsigned int GLenum;
namespace XEngine
{
	class OpenGLShader : public Shader
	{
	public:
		// Defined in Source File
		OpenGLShader(const std::string& path);
		OpenGLShader(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
		virtual ~OpenGLShader();
		void Bind() const override;
		void Unbind() const override;
		void UploadUniformInt(const std::string name, int value);
		void UploadUniformFloat(const std::string name, float value);
		void UploadUniformFloat2(const std::string name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string name, const glm::vec4& values);
		void UploadUniformMat3(const std::string name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string name, const glm::mat4& matrix);
		virtual const std::string& GetName() const override
			{ return shaderName; }
	private:
		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		std::string shaderName;
		uint32_t shaderRendererID;
	};
}