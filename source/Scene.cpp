#include "Scene.h"

SOLAR::Scene::Scene(std::string sceneName)
{
	this->sceneName = sceneName;
	this->rotationScale = 0.15f;

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
		sun->SetRotation(oldRotation + glm::vec3(0.0f, 0.59f * rotationScale * (float)deltaTime, 0.0f));
	}

	// Mercury transform
	{
		auto& mercury = nameToPlanetMap["mercury"];
		const glm::vec3 oldRotation = mercury->GetRotation();
		mercury->SetRotation(oldRotation + glm::vec3(0.0f, 0.25f * rotationScale * (float)deltaTime, 0.0f));
	}

	// Venus transform
	{
		auto& venus = nameToPlanetMap["venus"];
		const glm::vec3 oldRotation = venus->GetRotation();
		venus->SetRotation(oldRotation + glm::vec3(0.0f, -0.062f * rotationScale * (float)deltaTime, 0.0f));
	}

	// Earth transform
	{
		auto& earth = nameToPlanetMap["earth"];
		const glm::vec3 oldRotation = earth->GetRotation();
		earth->SetRotation(oldRotation + glm::vec3(0.0f, 15.6f * rotationScale * (float)deltaTime, 0.0f));
	}

	// Mars transform
	{
		auto& mars = nameToPlanetMap["mars"];
		const glm::vec3 oldRotation = mars->GetRotation();
		mars->SetRotation(oldRotation + glm::vec3(0.0f, 14.0f * rotationScale * (float)deltaTime, 0.0f));
	}

	// Jupiter transform
	{
		auto& jupiter = nameToPlanetMap["jupiter"];
		const glm::vec3 oldRotation = jupiter->GetRotation();
		jupiter->SetRotation(oldRotation + glm::vec3(0.0f, 36.0f * rotationScale * (float)deltaTime, 0.0f));
	}

	// Saturn transform
	{
		auto& saturn = nameToPlanetMap["saturn"];
		const glm::vec3 oldRotation = saturn->GetRotation();
		saturn->SetRotation(oldRotation + glm::vec3(0.0f, 33.3f * rotationScale * (float)deltaTime, 0.0f));
	}

	// Uranus transform
	{
		auto& uranus = nameToPlanetMap["uranus"];
		const glm::vec3 oldRotation = uranus->GetRotation();
		uranus->SetRotation(oldRotation + glm::vec3(0.0f, -20.0f * rotationScale * (float)deltaTime, 0.0f));
	}

	// Neptune transform
	{
		auto& neptune = nameToPlanetMap["neptune"];
		const glm::vec3 oldRotation = neptune->GetRotation();
		neptune->SetRotation(oldRotation + glm::vec3(0.0f, 22.0f * rotationScale * (float)deltaTime, 0.0f));
	}

	// Pluto transform
	{
		auto& pluto = nameToPlanetMap["pluto"];
		const glm::vec3 oldRotation = pluto->GetRotation();
		pluto->SetRotation(oldRotation + glm::vec3(0.0f, -2.3f * rotationScale * (float)deltaTime, 0.0f));
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

	// Add Earth
	std::shared_ptr<Model> earth = std::make_shared<Model>("resources/models/moon/Moon.gltf");
	earth->ReplaceTexture("texture_diffuse", "textures/2k_earth_daymap.jpg");
	earth->SetParent(sun);
	earth->SetRelativePosition(glm::vec3(-45.0f, 0.0f, 0.0));
	earth->SetScale(glm::vec3(1.0f));
	AddModel(earth);
	nameToPlanetMap["earth"] = earth;

	// Add Mars
	std::shared_ptr<Model> mars = std::make_shared<Model>("resources/models/moon/Moon.gltf");
	mars->ReplaceTexture("texture_diffuse", "textures/2k_mars.jpg");
	mars->SetParent(sun);
	mars->SetRelativePosition(glm::vec3(-55.0f, 0.0f, 0.0));
	mars->SetScale(glm::vec3(0.53f));
	AddModel(mars);
	nameToPlanetMap["mars"] = mars;

	// Add Jupiter
	std::shared_ptr<Model> jupiter = std::make_shared<Model>("resources/models/moon/Moon.gltf");
	jupiter->ReplaceTexture("texture_diffuse", "textures/2k_jupiter.jpg");
	jupiter->SetParent(sun);
	jupiter->SetRelativePosition(glm::vec3(-95.0f, 0.0f, 0.0));
	jupiter->SetScale(glm::vec3(10.5f));
	AddModel(jupiter);
	nameToPlanetMap["jupiter"] = jupiter;

	// Add Saturn
	std::shared_ptr<Model> saturn = std::make_shared<Model>("resources/models/moon/Moon.gltf");
	saturn->ReplaceTexture("texture_diffuse", "textures/2k_saturn.jpg");
	saturn->SetParent(sun);
	saturn->SetRelativePosition(glm::vec3(-125.0f, 0.0f, 0.0));
	saturn->SetScale(glm::vec3(9.0f));
	AddModel(saturn);
	nameToPlanetMap["saturn"] = saturn;

	// Add Uranus
	std::shared_ptr<Model> uranus = std::make_shared<Model>("resources/models/moon/Moon.gltf");
	uranus->ReplaceTexture("texture_diffuse", "textures/2k_uranus.jpg");
	uranus->SetParent(sun);
	uranus->SetRelativePosition(glm::vec3(-165.0f, 0.0f, 0.0));
	uranus->SetScale(glm::vec3(4.0f));
	AddModel(uranus);
	nameToPlanetMap["uranus"] = uranus;

	// Add Neptune
	std::shared_ptr<Model> neptune = std::make_shared<Model>("resources/models/moon/Moon.gltf");
	neptune->ReplaceTexture("texture_diffuse", "textures/2k_neptune.jpg");
	neptune->SetParent(sun);
	neptune->SetRelativePosition(glm::vec3(-205.0f, 0.0f, 0.0));
	neptune->SetScale(glm::vec3(3.9f));
	AddModel(neptune);
	nameToPlanetMap["neptune"] = neptune;

	// Add Pluto
	std::shared_ptr<Model> pluto = std::make_shared<Model>("resources/models/moon/Moon.gltf");
	pluto->ReplaceTexture("texture_diffuse", "textures/2k_neptune.jpg");
	pluto->SetParent(sun);
	pluto->SetRelativePosition(glm::vec3(-225.0f, 0.0f, 0.0));
	pluto->SetScale(glm::vec3(0.19f));
	AddModel(pluto);
	nameToPlanetMap["pluto"] = pluto;
}
