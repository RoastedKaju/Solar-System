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
		OribitPlanet(mercury, (float)deltaTime);
	}

	// Venus transform
	{
		auto& venus = nameToPlanetMap["venus"];
		const glm::vec3 oldRotation = venus->GetRotation();
		venus->SetRotation(oldRotation + glm::vec3(0.0f, -0.062f * rotationScale * (float)deltaTime, 0.0f));
		OribitPlanet(venus, (float)deltaTime);
	}

	// Earth transform
	{
		auto& earth = nameToPlanetMap["earth"];
		const glm::vec3 oldRotation = earth->GetRotation();
		earth->SetRotation(oldRotation + glm::vec3(0.0f, 15.6f * rotationScale * (float)deltaTime, 0.0f));
		OribitPlanet(earth, (float)deltaTime);
	}

	// Mars transform
	{
		auto& mars = nameToPlanetMap["mars"];
		const glm::vec3 oldRotation = mars->GetRotation();
		mars->SetRotation(oldRotation + glm::vec3(0.0f, 14.0f * rotationScale * (float)deltaTime, 0.0f));
		OribitPlanet(mars, (float)deltaTime);
	}

	// Jupiter transform
	{
		auto& jupiter = nameToPlanetMap["jupiter"];
		const glm::vec3 oldRotation = jupiter->GetRotation();
		jupiter->SetRotation(oldRotation + glm::vec3(0.0f, 36.0f * rotationScale * (float)deltaTime, 0.0f));
		OribitPlanet(jupiter, (float)deltaTime);
	}

	// Saturn transform
	{
		auto& saturn = nameToPlanetMap["saturn"];
		const glm::vec3 oldRotation = saturn->GetRotation();
		saturn->SetRotation(oldRotation + glm::vec3(0.0f, 33.3f * rotationScale * (float)deltaTime, 0.0f));
		OribitPlanet(saturn, (float)deltaTime);
	}

	// Uranus transform
	{
		auto& uranus = nameToPlanetMap["uranus"];
		const glm::vec3 oldRotation = uranus->GetRotation();
		uranus->SetRotation(oldRotation + glm::vec3(0.0f, -20.0f * rotationScale * (float)deltaTime, 0.0f));
		OribitPlanet(uranus, (float)deltaTime);
	}

	// Neptune transform
	{
		auto& neptune = nameToPlanetMap["neptune"];
		const glm::vec3 oldRotation = neptune->GetRotation();
		neptune->SetRotation(oldRotation + glm::vec3(0.0f, 22.0f * rotationScale * (float)deltaTime, 0.0f));
		OribitPlanet(neptune, (float)deltaTime);
	}

	// Pluto transform
	{
		auto& pluto = nameToPlanetMap["pluto"];
		const glm::vec3 oldRotation = pluto->GetRotation();
		pluto->SetRotation(oldRotation + glm::vec3(0.0f, -2.3f * rotationScale * (float)deltaTime, 0.0f));
		OribitPlanet(pluto, (float)deltaTime);
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
	mercury->SetScale(glm::vec3(0.38f));
	mercury->orbitRadius = 35.0f;
	mercury->orbitSpeed = 75.0f;
	mercury->theta = 0.0f;
	AddModel(mercury);
	nameToPlanetMap["mercury"] = mercury;

	// Add Venus
	std::shared_ptr<Model> venus = std::make_shared<Model>("resources/models/moon/Moon.gltf");
	venus->ReplaceTexture("texture_diffuse", "textures/2k_venus_surface.jpg");
	venus->SetParent(sun);
	venus->SetScale(glm::vec3(0.95f));
	venus->orbitRadius = 40.0f;
	venus->orbitSpeed = 29.3f;
	venus->theta = 45.0f;
	AddModel(venus);
	nameToPlanetMap["venus"] = venus;

	// Add Earth
	std::shared_ptr<Model> earth = std::make_shared<Model>("resources/models/moon/Moon.gltf");
	earth->ReplaceTexture("texture_diffuse", "textures/2k_earth_daymap.jpg");
	earth->SetParent(sun);
	earth->SetScale(glm::vec3(1.0f));
	earth->orbitRadius = 45.0f;
	earth->orbitSpeed = 18.0f;
	earth->theta = 90.0f;
	AddModel(earth);
	nameToPlanetMap["earth"] = earth;

	// Add Mars
	std::shared_ptr<Model> mars = std::make_shared<Model>("resources/models/moon/Moon.gltf");
	mars->ReplaceTexture("texture_diffuse", "textures/2k_mars.jpg");
	mars->SetParent(sun);
	mars->SetScale(glm::vec3(0.53f));
	mars->orbitRadius = 55.0f;
	mars->orbitSpeed = 9.5f;
	mars->theta = 135.0f;
	AddModel(mars);
	nameToPlanetMap["mars"] = mars;

	// Add Jupiter
	std::shared_ptr<Model> jupiter = std::make_shared<Model>("resources/models/moon/Moon.gltf");
	jupiter->ReplaceTexture("texture_diffuse", "textures/2k_jupiter.jpg");
	jupiter->SetParent(sun);
	jupiter->SetScale(glm::vec3(10.5f));
	jupiter->orbitRadius = 95.0f;
	jupiter->orbitSpeed = 1.15f;
	jupiter->theta = 210.0f;
	AddModel(jupiter);
	nameToPlanetMap["jupiter"] = jupiter;

	// Add Saturn
	std::shared_ptr<Model> saturn = std::make_shared<Model>("resources/models/moon/Moon.gltf");
	saturn->ReplaceTexture("texture_diffuse", "textures/2k_saturn.jpg");
	saturn->SetParent(sun);
	saturn->SetScale(glm::vec3(9.0f));
	saturn->orbitRadius = 125.0f;
	saturn->orbitSpeed = 0.61f;
	saturn->theta = 270.0f;
	AddModel(saturn);
	nameToPlanetMap["saturn"] = saturn;

	// Add Uranus
	std::shared_ptr<Model> uranus = std::make_shared<Model>("resources/models/moon/Moon.gltf");
	uranus->ReplaceTexture("texture_diffuse", "textures/2k_uranus.jpg");
	uranus->SetParent(sun);
	uranus->SetScale(glm::vec3(4.0f));
	uranus->orbitRadius = 165.0f;
	uranus->orbitSpeed = 0.21f;
	uranus->theta = 330.0f;
	AddModel(uranus);
	nameToPlanetMap["uranus"] = uranus;

	// Add Neptune
	std::shared_ptr<Model> neptune = std::make_shared<Model>("resources/models/moon/Moon.gltf");
	neptune->ReplaceTexture("texture_diffuse", "textures/2k_neptune.jpg");
	neptune->SetParent(sun);
	neptune->SetScale(glm::vec3(3.9f));
	neptune->orbitRadius = 205.0f;
	neptune->orbitSpeed = 0.11f;
	neptune->theta = 60.0f;
	AddModel(neptune);
	nameToPlanetMap["neptune"] = neptune;

	// Add Pluto
	std::shared_ptr<Model> pluto = std::make_shared<Model>("resources/models/moon/Moon.gltf");
	pluto->ReplaceTexture("texture_diffuse", "textures/2k_neptune.jpg");
	pluto->SetParent(sun);
	pluto->SetScale(glm::vec3(0.19f));
	pluto->orbitRadius = 225.0f;
	pluto->orbitSpeed = 0.072f;
	pluto->theta = 120.0f;
	AddModel(pluto);
	nameToPlanetMap["pluto"] = pluto;
}

void SOLAR::Scene::OribitPlanet(std::shared_ptr<Model> planet, float deltaTime)
{
	planet->theta += planet->orbitSpeed * deltaTime;
	const float x = planet->orbitRadius * cos(glm::radians(planet->theta));
	const float y = planet->orbitRadius * sin(glm::radians(planet->theta));
	planet->SetPosition(glm::vec3(x, 0.0f, y));
}
