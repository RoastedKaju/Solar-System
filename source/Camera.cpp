#include "Camera.h"

SOLAR::Camera::Camera()
{
	fov = 45.0f;
	aspectRatio = 1280.0f / 720.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	SetProjection(); // Initialize on creation
}

SOLAR::Camera::~Camera()
{

}

void SOLAR::Camera::SetProjection()
{
	projectionMat = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
}