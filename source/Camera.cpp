#include "Camera.h"

SOLAR::Camera::Camera()
{
	fov = 45.0f;
	aspectRatio = 1280.0f / 720.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	position = glm::vec3(0.0f, 0.0f, 0.0f);
	pitch = 0.0f;
	yaw = -90.0f;
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);

	SetProjection(); // Initialize on creation

	// Bind the key pressed event
	KeyPressedHandle = EventDispatcher::Get().Subscribe(KeyPressedEvent::descriptor, BIND_EVENT_FN(&SOLAR::Camera::OnKeyPressed, this));

	deltaTime = 0.0;
	cameraMoveSpeed = 5.0f;
}

SOLAR::Camera::~Camera()
{
	EventDispatcher::Get().Unsubscribe(KeyPressedEvent::descriptor, KeyPressedHandle);
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
	if (event.GetType() == KeyPressedEvent::descriptor)
	{
		KeyPressedEvent& KeyEvent = static_cast<KeyPressedEvent&>(event);
		
		switch (KeyEvent.GetKeyCode())
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
