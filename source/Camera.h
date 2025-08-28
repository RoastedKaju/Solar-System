#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "PCH.h"
#include "Event.h"
#include "EventDispatcher.h"

namespace SOLAR
{
	enum class CameraMode
	{
		FREE,
		PLANET
	};

	class Camera
	{
	public:
		Camera();
		~Camera();

		void SetProjection();

		const glm::mat4 GetViewMatrix() const;

		void Update(double deltaTime);

		inline const glm::mat4& GetProjectionMatrix() const { return projectionMat; }

		inline const glm::vec3& GetPosition() const { return position; }
		inline const glm::vec3& GetForward() const { return forward; }
		inline const glm::vec3& GetRight() const { return right; }
		inline const glm::vec3& GetUp() const { return up; }

		inline float GetPitch() const { return pitch; }
		inline float GetYaw() const { return yaw; }

		inline void SetPosition(const glm::vec3& value) { position = value; }
		inline void SetPitch(float value) { pitch = value; }
		inline void SetYaw(float value) { yaw = value; }

		void OnKeyPressed(Event& event);
		void OnMouseMoved(Event& event);
		void OnMousePressed(Event& event);
		void OnMouseReleased(Event& event);

		inline bool IsMouseHeldDown() const { return isMousePressed; }

	private:
		float fov;
		float aspectRatio;

		float nearPlane;
		float farPlane;

		glm::mat4 projectionMat;

		glm::vec3 position;
		float pitch;
		float yaw;
		glm::vec3 forward;
		glm::vec3 up;
		glm::vec3 right;

		size_t KeyPressedHandle;
		size_t MouseMovedHandle;
		size_t MousePressedHandle;
		size_t MouseReleasedHandle;

		double deltaTime;

		float cameraMoveSpeed;
		float mouseSensitivity;

		bool isMousePressed;
		CameraMode currentCameraMode;
	};
}

#endif // !CAMERA_H
