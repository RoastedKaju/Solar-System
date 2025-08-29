#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <GLFW/glfw3.h>

#include "PCH.h"

#define BIND_EVENT_FN(fn, obj) std::bind(fn, obj, std::placeholders::_1)

namespace SOLAR
{
	enum class EventType
	{
		WindowResize, WindowClose, WindowMaximize, WindowMinimize,
		MouseButtonPressed, MouseButtonReleased, MouseScrolled, MouseMoved,
		KeyPressed, KeyReleased,
		GuiButtonPressed
	};

	/**
	 * @brief Event interface
	 *
	 */
	class Event
	{
	public:
		virtual ~Event() = default;

		virtual EventType GetType() const = 0;

		bool IsHandled() const { return isHandled; };
		void SetIsHandled(bool value) { isHandled = value; };

		const std::string& GetName() const { return debugName; }

	protected:
		bool isHandled = false;
		std::string debugName = "";
	};

	/**
	 * @brief Keyboard button pressed event
	 *
	 */
	class KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent() { debugName = "KeyPressedEvent"; }
		KeyPressedEvent(int keyCode)
		{
			this->keyCode = keyCode;
			debugName = "KeyPressedEvent";
		}
		virtual ~KeyPressedEvent() {}

		static constexpr EventType descriptor = EventType::KeyPressed;

		virtual EventType GetType() const { return descriptor; }

		int GetKeyCode() const { return keyCode; }

	protected:
		int keyCode = -1;
	};

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent() { debugName = "MouseMovedEvent"; }
		MouseMovedEvent(double x, double y)
		{
			xpos = x;
			ypos = y;
			debugName = "MouseMovedEvent";
		}
		virtual ~MouseMovedEvent() {}

		static constexpr EventType descriptor = EventType::MouseMoved;

		virtual EventType GetType() const { return descriptor; }

		double GetXPos() const { return xpos; }
		double GetYPos() const { return ypos; }

	protected:
		double xpos = -90.0;
		double ypos = 0.0;
	};

	class MousePressedEvent : public Event
	{
	public:
		MousePressedEvent() { debugName = "MousePressedEvent"; }
		MousePressedEvent(int keyCode, GLFWwindow* window)
		{
			this->keyCode = keyCode;
			this->window = window;
			debugName = "MousePressedEvent";
		}
		virtual ~MousePressedEvent() {}

		static constexpr EventType descriptor = EventType::MouseButtonPressed;

		virtual EventType GetType() const { return descriptor; }

		int GetKeyCode() const { return keyCode; }
		GLFWwindow* GetWindowPtr() const { return window; }

	protected:
		int keyCode = -1;
		GLFWwindow* window;
	};

	class MouseReleasedEvent : public Event
	{
	public:
		MouseReleasedEvent() { debugName = "MouseReleasedEvent"; window = nullptr; }
		MouseReleasedEvent(int keyCode, GLFWwindow* window)
		{
			this->keyCode = keyCode;
			this->window = window;
			debugName = "MouseReleasedEvent";
		}
		virtual ~MouseReleasedEvent() {}

		static constexpr EventType descriptor = EventType::MouseButtonReleased;

		virtual EventType GetType() const { return descriptor; }

		int GetKeyCode() const { return keyCode; }
		GLFWwindow* GetWindowPtr() const { return window; }

	protected:
		int keyCode = -1;
		GLFWwindow* window;
	};

	class GuiButtonPressedEvent : public Event
	{
	public:
		GuiButtonPressedEvent() { debugName = "GuiButtonPressedEvent"; buttonId = -1; }
		GuiButtonPressedEvent(int Id) { debugName = "GuiButtonPressedEvent"; buttonId = Id; }
		virtual ~GuiButtonPressedEvent() {}

		static constexpr EventType descriptor = EventType::GuiButtonPressed;

		virtual EventType GetType() const { return descriptor; }

		int GetButtonId() const { return buttonId; }
	protected:
		int buttonId;
	};
}

#endif // !EVENT_H