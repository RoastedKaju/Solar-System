#include "Scene.h"

SOLAR::Scene::Scene(std::string sceneName)
{
	this->sceneName = sceneName;

	// Create camera
	mainCamera = std::make_shared<Camera>();
}