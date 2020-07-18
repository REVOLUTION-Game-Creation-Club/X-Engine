#pragma once
#include <string>
#include <glm/glm.hpp>
#include <unordered_map>
namespace XEngine
{
	class Shader
	{
	public:
		virtual ~Shader() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetInt(const std::string& name, const int value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;
		virtual const std::string& GetName() const = 0;
		static Ref<Shader> Create(const std::string& path);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
	private:
		uint32_t shaderRendererID;
	};
	class ShaderLibrary
	{
	public:
		// Defined in source file
		void Add(Ref<Shader>& shader, const std::string& name);
		void Add(Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& path);
		Ref<Shader> Load(const std::string& path, const std::string& name);
		Ref<Shader>Get(const std::string& name);
		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> libraryShaders;
	};
}