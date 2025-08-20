#include "Window.h"

SOLAR::Window::Window(const char* title, unsigned int width, unsigned int height) :
	title{ title },
	width{ width },
	height{ height },
	vsync{ true }
{
	Init();

	// Vsync
	SetVsync(vsync);

	KeyPressedHandle = EventDispatcher::Get().Subscribe(KeyPressedEvent::descriptor, BIND_EVENT_FN(&SOLAR::Window::OnKeyPressed, this));
}

SOLAR::Window::~Window()
{
	EventDispatcher::Get().Unsubscribe(KeyPressedEvent::descriptor, KeyPressedHandle);

	if (window)
	{
		fmt::print(fmt::fg(fmt::color::orange), "Window Object Destoryed\n");
		glfwDestroyWindow(window);
	}
}

void SOLAR::Window::Update(double deltaTime)
{
	glfwPollEvents();
	glfwSwapBuffers(window);
}

void SOLAR::Window::SetVsync(bool enabled)
{
	vsync = enabled;
	glfwSwapInterval(enabled ? 1 : 0);
}

bool SOLAR::Window::IsVsync() const
{
	return vsync;
}

void SOLAR::Window::OnKeyPressed(Event& event)
{
	if (event.GetType() == KeyPressedEvent::descriptor)
	{
		KeyPressedEvent& KeyEvent = static_cast<KeyPressedEvent&>(event);

		if (KeyEvent.GetKeyCode() == GLFW_KEY_ESCAPE)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		event.SetIsHandled(false);
	}
}

void SOLAR::Window::Init()
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GL_TRUE);

	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!window)
	{
		fmt::print(fmt::fg(fmt::color::crimson), "Failed to create GLFW window\n");
		return;
	}

	// Make context current
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		fmt::print(fmt::fg(fmt::color::crimson), "Failed to initialize GLEW\n");
		glfwDestroyWindow(window);
		return;
	}

	glewExperimental = GL_TRUE;

	// Set initial viewport
	glViewport(0, 0, width, height);
	// Resize callback
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* _window, int _width, int _height)
		{
			glViewport(0, 0, _width, _height);
		});
}