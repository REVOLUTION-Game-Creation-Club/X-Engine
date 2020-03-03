#pragma once
#pragma region INCLUDE / NAMESPACES
#include "Xpch.h"
#include "XCore.h"
#include "XEngine/EventSystem/Event.h"
#pragma endregion
namespace XEngine
{
	#pragma region WINDOWS PROPS STRUCT
	struct WindowProps
	{
		// Windows Title
		std::string Title;
		// Postive Window Width
		unsigned int Width;
		// Postive Window Height
		unsigned int Height;
		// Setting Title, Width, Height variables
		WindowProps(const std::string& title = "X-Engine", unsigned int width = 1920, unsigned int height = 1080) :Title(title), Width(width), Height(height) {}
	};
	#pragma endregion
	#pragma region WINDOW CLASS
	class XENGINE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {}
		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		static Window* Create(const WindowProps& props = WindowProps());
	};
	#pragma endregion
}