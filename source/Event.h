#ifndef EVENT_H
#define EVENT_H

#include <iostream>

#include "PCH.h"

#define BIND_EVENT_FN(fn, obj) std::bind(fn, obj, std::placeholders::_1)

namespace SOLAR
{
	enum class EventType
	{
		WindowResize, WindowClose, WindowMaximize, WindowMinimize,
		MouseButtonPressed, MouseButtonReleased, MouseScrolled, MouseMoved,
		KeyPressed, KeyReleased
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
		MouseMovedEvent() { debugName = "MouseMovedEvent";}
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
}

#endif // !EVENT_H