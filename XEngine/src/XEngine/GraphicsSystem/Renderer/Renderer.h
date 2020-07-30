#pragma once
#include "XEngine/GraphicsSystem/Camera.h"
#include "XEngine/GraphicsSystem/Shader.h"
#include "XEngine/GraphicsSystem/Renderer/RendererAPI.h"
#include "XEngine/GraphicsSystem/Renderer/RenderCommand.h"
namespace XEngine
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void BeginScene(OrthographicCamera& camera);
		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));
		static void EndScene();
		static RendererAPI::API GetAPI() 
			{ return RendererAPI::GetAPI(); }
	private:
		struct SceneData
			{ glm::mat4 ViewProjectionMatrix; };
		static Scope<SceneData> rendererSceneData;
	};
}