#include "pch.h"
#include "Application.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace Jolt
{
	Window* Window::Create(const char* name)
	{
		return new Window(name);
	}

	bool Window::WindowShouldClose()
	{
		return glfwWindowShouldClose(m_window);
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void Window::SetEventCallback(const EventCallbackFn& fn)
	{
		static EventCallbackFn local = fn;
		glfwSetWindowUserPointer(m_window, (void*)&local);
	}

	Window::Window(const char* name)
	{
		m_window = glfwCreateWindow(1280, 720, name, NULL, NULL);

		/* Event Callback */
		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			EventCallbackFn& callback = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent* event = new KeyPressedEvent(key, 0);
					callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent* event = new KeyReleasedEvent(key);
					callback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent* event = new KeyPressedEvent(key, 1);
					callback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_window, [](GLFWwindow * window, unsigned int key)
		{
			EventCallbackFn& callback = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
			KeyTypedEvent* event = new KeyTypedEvent(key);
			callback(event);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow * window, double xPos, double yPos)
		{
			EventCallbackFn& callback = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
			MouseMovedEvent* event = new MouseMovedEvent((float)xPos, (float)yPos);
			callback(event);
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow * window, double xoffset, double yoffset)
		{
			EventCallbackFn& callback = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent* event = new MouseScrolledEvent((float)xoffset, (float)yoffset);
			callback(event);
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow * window, int button, int action, int mods)
		{
			EventCallbackFn& callback = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent* event = new MouseButtonPressedEvent(button);
					callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent* event = new MouseButtonReleasedEvent(button);
					callback(event);
					break;
				}
			}
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow * window)
		{
			EventCallbackFn& callback = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
			WindowCloseEvent* event = new WindowCloseEvent();
			callback(event);
		});

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow * window, int width, int height)
		{
			EventCallbackFn& callback = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
			WindowResizeEvent* event = new WindowResizeEvent(width, height);
			callback(event);
		});

		glfwSetWindowFocusCallback(m_window, [](GLFWwindow * window, int focused)
		{
			EventCallbackFn& callback = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
			if (focused)
			{
				WindowFocusEvent* event = new WindowFocusEvent();
				callback(event);
			}
			else
			{
				WindowLostFocusEvent* event = new WindowLostFocusEvent();
				callback(event);
			}
		});

		glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int xpos, int ypos)
		{
			EventCallbackFn& callback = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
			WindowMovedEvent* event = new WindowMovedEvent(xpos, ypos);
			callback(event);
		});

		glfwSetDropCallback(m_window, [](GLFWwindow* window, int count, const char** paths)
		{
			EventCallbackFn& callback = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
			FileDropEvent* event = new FileDropEvent(count, paths);
			callback(event);
		});
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}
}