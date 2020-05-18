//ENG
#include "ENG/objects/game.h"
#include "ENG/objects/phyx.h"
#include "ENG/shaders/shader.h"
#include "ENG/mesh/mesh.h"
#include "ENG/mesh/sphere.h"
#include "ENG/mesh/cube.h"
#include "ENG/model/model.h"
//drift
#include "drift/simplebody.h"
Game SolarSystem(1280, 720, "SolarSystem/textures/", "SolarSystem/models/");


// GameObjects
// ----------------
CelestialBody * sun = new CelestialBody();
CelestialBody * earth = new CelestialBody();
CelestialBody * mercury = new CelestialBody();
CelestialBody * venus = new CelestialBody();
CelestialBody * mars = new CelestialBody();


int main(int argc, char **argv)
{
	// initialize glfw and game
	// ------------------------
	SolarSystem.freecam = new Freecam(glm::vec3(0.0f, 7.0f, 10.0f));
	SolarSystem.currentCamera = SolarSystem.freecam;
	SolarSystem.cameraMode = FREECAM_MODE;

	SolarSystem.gameobjects.push_back(sun);
	SolarSystem.gameobjects.push_back(earth);
	SolarSystem.gameobjects.push_back(venus);
	SolarSystem.gameobjects.push_back(mercury);
	SolarSystem.gameobjects.push_back(mars);

	SolarSystem.gameobjects.push_back(SolarSystem.freecam);

	GLFWwindow* window = SolarSystem.Initialize();

	// creating our skybox
	// -------------------
	std::vector<std::string> faces
	{
		"skybox/right.png",
		"skybox/left.png",
		"skybox/top.png",
		"skybox/bottom.png",
		"skybox/front.png",
		"skybox/back.png"
	};
/*	Texture tSkybox;
	tSkybox.id = loadCubemap(faces, SolarSystem.texturesPath);
	tSkybox.type = "texture_skybox";
	tSkybox.path = "skybox";


	Texture tMoon;
	tMoon.id = TextureFromFile("moon/moon.jpg", SolarSystem.texturesPath);
	tMoon.type = "texture_diffuse";
	tMoon.path = "moon/moon.jpg";
*/
	Texture tSun;
	tSun.id = TextureFromFile("sun.jpg", SolarSystem.texturesPath);
	tSun.type = "texture_diffuse";
	tSun.path = "sun.jpg";

	Texture tvenus;
	tvenus.id = TextureFromFile("venus.jpg", SolarSystem.texturesPath);
	tvenus.type = "texture_diffuse";
	tvenus.path = "venus.jpg";
	
	Texture tmercury;
	tmercury.id = TextureFromFile("mercury.jpg", SolarSystem.texturesPath);
	tmercury.type = "texture_diffuse";
	tmercury.path = "mercury.jpg";
	
	Texture tmars;
	tmars.id = TextureFromFile("mars.jpg", SolarSystem.texturesPath);
	tmars.type = "texture_diffuse";
	tmars.path = "mars.jpg";

	Texture tEarth;
	tEarth.id = TextureFromFile("earthsquare.jpg", SolarSystem.texturesPath);
	tEarth.type = "texture_diffuse";
	tEarth.path = "earthsquare.jpg";	
	// creating texture vectors
	// ------------------------
/*	std::vector<Texture> sunTextures;
	sunTextures.push_back(tSun);

	std::vector<Texture> skyboxTextures;
	skyboxTextures.push_back(tSkybox);

	std::vector<Texture> moonTextures;
	moonTextures.push_back(tMoon);
*/
	std::vector<Texture> earthTextures;
	earthTextures.push_back(tEarth);

	std::vector<Texture> sunTextures;
	sunTextures.push_back(tSun);

	std::vector<Texture> venusTextures;
	venusTextures.push_back(tvenus);
	std::vector<Texture> mercuryTextures;
	mercuryTextures.push_back(tmercury);
	std::vector<Texture> marsTextures;
	marsTextures.push_back(tmars);

	// instantiate meshes
	// ------------------
//	Sphere sunMesh(50, 50, sunTextures);
//	Cube skyboxMesh(skyboxTextures);
	

	sun->meshes.push_back(new Sphere(50,50,sunTextures));
	venus->meshes.push_back(new Sphere(50,50,venusTextures));
	mercury->meshes.push_back(new Sphere(50,50,mercuryTextures));
	mars->meshes.push_back(new Sphere(50,50,marsTextures));
	earth->meshes.push_back(new Sphere(50,50,earthTextures));

	// initializing the system
	// -----------------------
	sun->worldPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	sun->Mass(1.f);
	sun->scale = glm::vec3(8);
	sun->collider.Dim(8);

	earth->worldPosition = glm::vec3(22.0f, 0.0f, 0.0f);
	earth->Init();
	earth->YV(2);
	earth->Mass(1.f);
	earth->scale = glm::vec3(1);
	earth->collider.Dim(1);
	earth->orbiting = sun;
	earth->name="earth";

	venus->worldPosition = glm::vec3(15.0f, 0.0f, 0.0f);
	venus->Init();
	venus->YV(2);
	venus->Mass(1.f);
	venus->scale = glm::vec3(0.9);
	venus->collider.Dim(0.9);
	venus->orbiting = sun;
	venus->name="venus";

	mercury->worldPosition = glm::vec3(10.0f, 0.0f, 0.0f);
	mercury->Init();
	mercury->YV(2);
	mercury->Mass(1.f);
	mercury->scale = glm::vec3(0.3);
	mercury->collider.Dim(0.3);
	mercury->orbiting = sun;
	mercury->name="mercury";

	mars->worldPosition = glm::vec3(30.0f, 0.0f, 0.0f);
	mars->Init();
	mars->YV(2);
	mars->Mass(1.f);
	mars->scale = glm::vec3(0.6);
	mars->collider.Dim(0.6);
	mars->orbiting = sun;
	mars->name="mars";

	// lighting options
	// ----------------
	glm::vec3 lightColor(1.0f);
	glm::vec3 lDiffuse = lightColor * glm::vec3(0.8f);
	glm::vec3 lAmbient = lDiffuse * glm::vec3(0.2f);
	glm::vec3 lSpecular(1.0f, 1.0f, 1.0f);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(SolarSystem.currentCamera->Zoom), (float)SolarSystem.screenWidth / (float)SolarSystem.screenHeight, 0.1f, 100.0f);
		glm::mat4 view = SolarSystem.currentCamera->GetViewMatrix();


		// configuring the light source shader and meshes
		// ----------------------------------------------
		SolarSystem.lightSourceShader->use();
		SolarSystem.lightSourceShader->setMat4("projection", projection);
		SolarSystem.lightSourceShader->setMat4("view", view);
		sun->Draw(SolarSystem.lightSourceShader);

//		sunMesh.Draw(SolarSystem.lightSourceShader, glm::vec3(0.0f,0.f,0.f), glm::vec3(10.0f));

		// configuring the texture shader and meshes
		// -----------------------------------------
		SolarSystem.textureShader->use();
		SolarSystem.textureShader->setMat4("projection", projection);
		SolarSystem.textureShader->setMat4("view", view);
		SolarSystem.textureShader->setVec3("light.position", glm::vec3(0.0f,0.f,0.f));
		SolarSystem.textureShader->setVec3("light.ambient", lAmbient);
		SolarSystem.textureShader->setVec3("light.diffuse", lDiffuse);
		SolarSystem.textureShader->setVec3("light.specular", lSpecular);
		SolarSystem.textureShader->setVec3("viewPos", SolarSystem.currentCamera->worldPosition);

		SolarSystem.phyxENG.Update();
		SolarSystem.inputENG.Update(window);

//		player->Draw(SolarSystem.textureShader);
//		player->camera.updateCameraVectors(player->worldPosition);

		earth->Draw(SolarSystem.textureShader);
		venus->Draw(SolarSystem.textureShader);
		mercury->Draw(SolarSystem.textureShader);
		mars->Draw(SolarSystem.textureShader);

		// configuring the material shader and meshes
		// ------------------------------------------
		SolarSystem.materialShader->use();
		SolarSystem.materialShader->setMat4("projection", projection);
		SolarSystem.materialShader->setMat4("view", view);
		SolarSystem.materialShader->setVec3("light.position", glm::vec3(0.0f));
		SolarSystem.materialShader->setVec3("light.ambient", lAmbient);
		SolarSystem.materialShader->setVec3("light.diffuse", lDiffuse);
		SolarSystem.materialShader->setVec3("light.specular", lSpecular);
		SolarSystem.materialShader->setVec3("viewPos", SolarSystem.currentCamera->worldPosition);

		// draw skybox at last
/*		// -------------------
		glDepthFunc(GL_LEQUAL);
		SolarSystem.skyboxShader->use();
		view = glm::mat4(glm::mat3(SolarSystem.currentCamera->GetViewMatrix()));
		SolarSystem.skyboxShader->setMat4("view", view);
		SolarSystem.skyboxShader->setMat4("projection", projection);
		skyboxMesh.Draw(SolarSystem.skyboxShader);
		glDepthFunc(GL_LESS);
*/
//		SolarSystem.displayImGui();


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	SolarSystem.Terminate();
	// glfw: terminate, clearing all previously allocated GLFW resources
	// -----------------------------------------------------------------
	glfwTerminate();
	return 0;
}