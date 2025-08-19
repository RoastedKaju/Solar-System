#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "PCH.h"

namespace SOLAR
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		void SetProjection();

		inline const glm::mat4& GetProjectionMatrix() const { return projectionMat; }

	private:
		float fov;
		float aspectRatio;

		float nearPlane;
		float farPlane;

		glm::mat4 projectionMat;
	};
}

#endif // !CAMERA_H
