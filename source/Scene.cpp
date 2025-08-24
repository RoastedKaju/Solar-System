#include "Scene.h"

SOLAR::Scene::Scene(std::string sceneName)
{
	this->sceneName = sceneName;

	// Create camera
	mainCamera = std::make_shared<Camera>();

	InitSolarScene();
}

void SOLAR::Scene::Update(double deltaTime)
{
	// Sun transform
	{
		auto& sun = nameToPlanetMap["sun"];
		const glm::vec3 oldRotation = sun->GetRotation();
		sun->SetRotation(oldRotation + glm::vec3(0.0f, 0.59f * (float)deltaTime, 0.0f));
	}

	// Mercury transform
	{
		auto& mercury = nameToPlanetMap["mercury"];
		const glm::vec3 oldRotation = mercury->GetRotation();
		mercury->SetRotation(oldRotation + glm::vec3(0.0f, 0.25f * (float)deltaTime, 0.0f));
	}

	// Venus transform
	{
		auto& venus = nameToPlanetMap["venus"];
		const glm::vec3 oldRotation = venus->GetRotation();
		venus->SetRotation(oldRotation + glm::vec3(0.0f, -0.062f * (float)deltaTime, 0.0f));
	}

}

void SOLAR::Scene::InitSolarScene()
{
	std::vector<std::string> spaceSkyboxSrc = {
	"resources/space/right.png",
	"resources/space/left.png",
	"resources/space/top.png",
	"resources/space/bottom.png",
	"resources/space/front.png",
	"resources/space/back.png"
	};

	std::shared_ptr<Skybox> solarSkybox = std::make_shared<Skybox>(spaceSkyboxSrc);
	SetSkybox(solarSkybox);

	// Add Sun
	std::shared_ptr<Model> sun = std::make_shared<Model>("resources/models/moon/Moon.gltf");
	sun->ReplaceTexture("texture_diffuse", "textures/2k_sun.jpg");
	sun->SetPosition(glm::vec3(0.0f, 0.0f, 0.0));
	sun->SetScale(glm::vec3(25.0f));
	AddModel(sun);
	nameToPlanetMap["sun"] = sun;

	// Add Mercury
	std::shared_ptr<Model> mercury = std::make_shared<Model>("resources/models/moon/Moon.gltf");
	mercury->ReplaceTexture("texture_diffuse", "textures/2k_mercury.jpg");
	mercury->SetParent(sun);
	mercury->SetRelativePosition(glm::vec3(-35.0f, 0.0f, 0.0));
	mercury->SetScale(glm::vec3(0.38f));
	AddModel(mercury);
	nameToPlanetMap["mercury"] = mercury;

	// Add Venus
	std::shared_ptr<Model> venus = std::make_shared<Model>("resources/models/moon/Moon.gltf");
	venus->ReplaceTexture("texture_diffuse", "textures/2k_venus_surface.jpg");
	venus->SetParent(sun);
	venus->SetRelativePosition(glm::vec3(-40.0f, 0.0f, 0.0));
	venus->SetScale(glm::vec3(0.95f));
	AddModel(venus);
	nameToPlanetMap["venus"] = venus;
}
