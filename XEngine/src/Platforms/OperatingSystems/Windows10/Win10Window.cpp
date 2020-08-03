// Source file for Win10Window class functions, configured for Windows 10, also derived from window class
#include "Xpch.h"
#include "wtypes.h"
#include "XEngine/InputSystem/Input.h"
#include "XEngine/EventSystem/KeyEvent.h"
#include "XEngine/EventSystem/MouseEvent.h"
#include "XEngine/EventSystem/ApplicationEvent.h"
#include "XEngine/GraphicsSystem/Renderer/Renderer.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGlContext.h"
#include "Platforms/OperatingSystems/Windows10/Win10Window.h"
namespace XEngine
{
	static uint8_t GLFWWindowCount = 0;
	static void GLFWErrorCallback(int error, const char* description)
		{ XCORE_ERROR("GLFW Error ({0}): {1}", error, description); };
	Win10Window::Win10Window(const WindowProps& props)
	{
		XPROFILE_FUNCTION();
		XCORE_INFO("Using Windows 10 Window Class");
		Init(props);
	}
	Win10Window::~Win10Window()
	{
		XPROFILE_FUNCTION();
		Shutdown();
	}
	void Win10Window::Init(const WindowProps& props)
	{
		XPROFILE_FUNCTION();
		SetConsoleTitle(TEXT("X-Engine Console"));
		windowData.Title = props.Title;
		windowData.Width = props.Width;
		windowData.Height = props.Height;
		if (GLFWWindowCount == 0)
		{
			int success = glfwInit();
			XCORE_ASSERT(success, "Could not initialize GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
			XCORE_INFO("GLFW intialized");
		}
		{
			XPROFILE_SCOPE("glfwCreateWindow");
			#if defined(X_DEBUG)
				if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
					glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
			#endif
			window = glfwCreateWindow((int)props.Width, (int)props.Height, windowData.Title.c_str(), nullptr, nullptr);
			++GLFWWindowCount;
		}
		windowContext = GraphicsContext::Create(window);
		windowContext->Init();
		glfwSetWindowUserPointer(window, &windowData);
		SetVSync(false);
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});
		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(static_cast<KeyCode>(key));
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 1);
					data.EventCallback(event);
					break;
				}
			}
		});
		glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(static_cast<KeyCode>(keycode));
			data.EventCallback(event);
		});
		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(static_cast<MouseCode>(button));
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
					data.EventCallback(event);
					break;
				}
			}
		});
		glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}
	void Win10Window::Shutdown()
	{
		XPROFILE_FUNCTION();
		glfwDestroyWindow(window);
		--GLFWWindowCount;
		if (GLFWWindowCount == 0)
		{
			XCORE_INFO("Terminating GLFW");
			glfwTerminate();
		}
	}
	void Win10Window::OnUpdate()
	{
		XPROFILE_FUNCTION();
		glfwPollEvents();
		windowContext->SwapBuffers();
	}
	void Win10Window::SetVSync(bool enabled)
	{
		XPROFILE_FUNCTION();
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		windowData.VSync = enabled;
	}
	bool Win10Window::IsVSync() const
		{ return windowData.VSync; }
}