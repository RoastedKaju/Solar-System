#include "Camera.h"

SOLAR::Camera::Camera()
{
	isFreeCam = true;
	isMousePressed = false;
	cameraTheta = 0.0f;
	cameraZoom = 10.0f;

	fov = 45.0f;
	aspectRatio = 1280.0f / 720.0f;
	nearPlane = 0.1f;
	farPlane = 1000.0f;

	position = glm::vec3(0.0f, 0.0f, 50.0f);
	pitch = 0.0f;
	yaw = -90.0f;
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);

	SetProjection(); // Initialize on creation

	// Bindings
	KeyPressedHandle = EventDispatcher::Get().Subscribe(KeyPressedEvent::descriptor, BIND_EVENT_FN(&SOLAR::Camera::OnKeyPressed, this));
	MouseMovedHandle = EventDispatcher::Get().Subscribe(MouseMovedEvent::descriptor, BIND_EVENT_FN(&SOLAR::Camera::OnMouseMoved, this));
	MousePressedHandle = EventDispatcher::Get().Subscribe(MousePressedEvent::descriptor, BIND_EVENT_FN(&SOLAR::Camera::OnMousePressed, this));
	MouseReleasedHandle = EventDispatcher::Get().Subscribe(MouseReleasedEvent::descriptor, BIND_EVENT_FN(&SOLAR::Camera::OnMouseReleased, this));
	GuiButtonPressedHandle = EventDispatcher::Get().Subscribe(GuiButtonPressedEvent::descriptor, BIND_EVENT_FN(&SOLAR::Camera::OnGuiButtonPressed, this));

	deltaTime = 0.0;
	cameraMoveSpeed = 20.0f;
	mouseSensitivity = 0.3f;
}

SOLAR::Camera::~Camera()
{
	EventDispatcher::Get().Unsubscribe(KeyPressedEvent::descriptor, KeyPressedHandle);
	EventDispatcher::Get().Unsubscribe(MouseMovedEvent::descriptor, MouseMovedHandle);
	EventDispatcher::Get().Unsubscribe(MousePressedEvent::descriptor, MousePressedHandle);
	EventDispatcher::Get().Unsubscribe(MouseReleasedEvent::descriptor, MouseReleasedHandle);
	EventDispatcher::Get().Unsubscribe(GuiButtonPressedEvent::descriptor, GuiButtonPressedHandle);
}

void SOLAR::Camera::SetProjection()
{
	projectionMat = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
}

const glm::mat4 SOLAR::Camera::GetViewMatrix() const
{
	return glm::lookAt(position, position + forward, up);
}

void SOLAR::Camera::Update(double deltaTime)
{
	this->deltaTime = deltaTime;

	if (isFreeCam)
	{
		// Calculate the new Front vector from Yaw and Pitch
		glm::vec3 new_forward;
		new_forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		new_forward.y = sin(glm::radians(pitch));
		new_forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		forward = glm::normalize(new_forward);
	}
	else
	{
		forward = glm::normalize(targetPosition - position);
	}

	// Re-calculate the Right and Up vectors
	right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, forward));
}

void SOLAR::Camera::OnKeyPressed(Event& event)
{
	if (event.GetType() == EventType::KeyPressed)
	{
		KeyPressedEvent& keyEvent = static_cast<KeyPressedEvent&>(event);

		if (!isFreeCam)
		{
			return;
		}
		
		switch (keyEvent.GetKeyCode())
		{
		case GLFW_KEY_W:
			position += forward * cameraMoveSpeed * (float)deltaTime;
			break;
		case GLFW_KEY_A:
			position -= right * cameraMoveSpeed * (float)deltaTime;
			break;
		case GLFW_KEY_S:
			position -= forward * cameraMoveSpeed * (float)deltaTime;
			break;
		case GLFW_KEY_D:
			position += right * cameraMoveSpeed * (float)deltaTime;
			break;
		default:
			break;
		}

		event.SetIsHandled(false);
	}
}

void SOLAR::Camera::OnMouseMoved(Event& event)
{
	// Ignore look input if left mouse button is not pressed
	if (!isMousePressed)
	{
		return;
	}

	if (event.GetType() == EventType::MouseMoved)
	{
		MouseMovedEvent& mouseEvent = static_cast<MouseMovedEvent&>(event);

		float xoffset = (float)mouseEvent.GetXPos() * mouseSensitivity;
		float yoffset = (float)mouseEvent.GetYPos() * mouseSensitivity;

		yaw += xoffset;
		pitch += yoffset;

		cameraTheta += xoffset; // For lock target camera

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		pitch = glm::clamp(pitch, -89.0f, 89.0f);

		event.SetIsHandled(false);
	}
}

void SOLAR::Camera::OnMousePressed(Event& event)
{
	if (event.GetType() == EventType::MouseButtonPressed)
	{
		MousePressedEvent& mouseEvent = static_cast<MousePressedEvent&>(event);

		if (mouseEvent.GetKeyCode() == GLFW_MOUSE_BUTTON_1 && mouseEvent.GetWindowPtr())
		{
			isMousePressed = true;
			glfwSetInputMode(mouseEvent.GetWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		event.SetIsHandled(false);
	}
}

void SOLAR::Camera::OnMouseReleased(Event& event)
{
	if (event.GetType() == EventType::MouseButtonReleased)
	{
		MouseReleasedEvent& mouseEvent = static_cast<MouseReleasedEvent&>(event);

		if (mouseEvent.GetKeyCode() == GLFW_MOUSE_BUTTON_1 && mouseEvent.GetWindowPtr())
		{
			isMousePressed = false;
			glfwSetInputMode(mouseEvent.GetWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		event.SetIsHandled(false);
	}
}

void SOLAR::Camera::OnGuiButtonPressed(Event& event)
{
	if (event.GetType() == EventType::GuiButtonPressed)
	{
		GuiButtonPressedEvent& buttonEvent = static_cast<GuiButtonPressedEvent&>(event);

		switch (buttonEvent.GetButtonId())
		{
		case 1:
			if (isFreeCam) { std::cout << "Already In Free Cam Mode." << std::endl; break; }
			// Calculate the pitch and yaw from forward to ensure smooth transition back to free cam
			pitch = glm::degrees(asin(forward.y));
			yaw = glm::degrees(atan2(forward.z, forward.x));
			isFreeCam = true;
			break;
		case 2:
			isFreeCam = false;
			targetPlanet = "sun";
			break;
		case 3:
			isFreeCam = false;
			targetPlanet = "mercury";
			break;
		case 4:
			targetPlanet = "venus";
			isFreeCam = false;
			break;
		case 5:
			targetPlanet = "earth";
			isFreeCam = false;
			break;
		case 6:
			targetPlanet = "mars";
			isFreeCam = false;
			break;
		case 7:
			targetPlanet = "jupiter";
			isFreeCam = false;
			break;
		case 8:
			targetPlanet = "saturn";
			isFreeCam = false;
			break;
		case 9:
			targetPlanet = "uranus";
			isFreeCam = false;
			break;
		case 10:
			targetPlanet = "neptune";
			isFreeCam = false;
			break;
		case 11:
			targetPlanet = "pluto";
			isFreeCam = false;
			break;

		default:
			break;
		}

		event.SetIsHandled(false);
	}
}
