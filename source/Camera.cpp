#include "Camera.h"

SOLAR::Camera::Camera()
{
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

	deltaTime = 0.0;
	cameraMoveSpeed = 20.0f;
	mouseSensitivity = 0.3f;
}

SOLAR::Camera::~Camera()
{
	EventDispatcher::Get().Unsubscribe(KeyPressedEvent::descriptor, KeyPressedHandle);
	EventDispatcher::Get().Unsubscribe(MouseMovedEvent::descriptor, MouseMovedHandle);
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
	//fmt::print(fmt::fg(fmt::color::antique_white), "Camera Position : {} | {} | {}    Camera Rotation : {} | {}\n", position.x, position.y, position.z, pitch, yaw);

	this->deltaTime = deltaTime;

	// Calculate the new Front vector from Yaw and Pitch
	glm::vec3 new_forward;
	new_forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	new_forward.y = sin(glm::radians(pitch));
	new_forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(new_forward);

	// Re-calculate the Right and Up vectors
	right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, forward));
}

void SOLAR::Camera::OnKeyPressed(Event& event)
{
	if (event.GetType() == EventType::KeyPressed)
	{
		KeyPressedEvent& keyEvent = static_cast<KeyPressedEvent&>(event);
		
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
	if (event.GetType() == EventType::MouseMoved)
	{
		MouseMovedEvent& mouseEvent = static_cast<MouseMovedEvent&>(event);

		float xoffset = (float)mouseEvent.GetXPos() * mouseSensitivity;
		float yoffset = (float)mouseEvent.GetYPos() * mouseSensitivity;

		yaw += xoffset;
		pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		pitch = glm::clamp(pitch, -89.0f, 89.0f);

		event.SetIsHandled(false);
	}
}
