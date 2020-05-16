//ENG
#include "ENG/objects/game.h"
#include "ENG/objects/phyx.h"
#include "ENG/shaders/shader.h"
#include "ENG/mesh/mesh.h"
#include "ENG/mesh/sphere.h"
#include "ENG/mesh/cube.h"
#include "ENG/model/model.h"

//drift
#include "drift/player.h"

//orbitgame
#include "CelestialBody.h"


Game orbitgame(1280, 720, "orbitgame/textures/", "orbitgame/models/");

// GameObjects
// ----------------
Player * player = new Player();
CelestialBody * planet = new CelestialBody();
CelestialBody * planet2 = new CelestialBody();


int main(int argc, char **argv)
{
	// initialize glfw and game
	// ------------------------
	orbitgame.freecam = new Freecam(glm::vec3(0.0f, 7.0f, 10.0f));
	orbitgame.currentCamera = orbitgame.freecam;
	orbitgame.cameraMode = FREECAM_MODE;

	orbitgame.gameobjects.push_back(player);
	orbitgame.gameobjects.push_back(planet);
	orbitgame.gameobjects.push_back(planet2);
	orbitgame.gameobjects.push_back(orbitgame.freecam);

	GLFWwindow* window = orbitgame.Initialize();

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
	Texture tSkybox;
	tSkybox.id = loadCubemap(faces, orbitgame.texturesPath);
	tSkybox.type = "texture_skybox";
	tSkybox.path = "skybox";

	Texture tSun;
	tSun.id = TextureFromFile("sun/sun.jpg", orbitgame.texturesPath);
	tSun.type = "texture_diffuse";
	tSun.path = "sun/sun.jpg";

	Texture tMoon;
	tMoon.id = TextureFromFile("moon/moon.jpg", orbitgame.texturesPath);
	tMoon.type = "texture_diffuse";
	tMoon.path = "moon/moon.jpg";

	// creating texture vectors
	// ------------------------
	std::vector<Texture> sunTextures;
	sunTextures.push_back(tSun);

	std::vector<Texture> skyboxTextures;
	skyboxTextures.push_back(tSkybox);

	std::vector<Texture> moonTextures;
	moonTextures.push_back(tMoon);

	// instantiate meshes
	// ------------------
	Sphere sunMesh(50, 50, sunTextures);
	Cube skyboxMesh(skyboxTextures);
	
	player->meshes.push_back(new Sphere(50,50,moonTextures));
	planet->meshes.push_back(new Sphere(50,50,moonTextures));
	planet2->meshes.push_back(new Sphere(50,50,moonTextures));
/*
	for (unsigned int i = 0; i < sunMesh.vertices.size(); i++)
	{
		sunMesh.vertices[i].Position += glm::vec3(20.0f);
	}
	for (unsigned int i = 0; i < sunMesh.vertices.size(); i++)
	{
		planet->meshes[0]->vertices[i].Position += glm::vec3(2.0f);
	}*/
	// initializing the player
	// -----------------------
	player->worldPosition = glm::vec3(15.0f, 0.0f, 0.0f);
	player->Init();
	//player->loadModel(modelsPath + "sputnik/sputnik1.obj");
	player->YV(0); // starting velocity
	player->Mass(1.f);
	player->collider.Dim(1);
	player->orbiting = planet;
	player->name="stan";

	planet->worldPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	planet->Mass(1.f);
	planet->scale = glm::vec3(8);
	planet->collider.Dim(8);

	planet2->worldPosition = glm::vec3(20.0f, 0.0f, 0.0f);
	planet2->Init();
	planet2->YV(0);
	planet2->Mass(1.f);
	planet2->scale = glm::vec3(2);
	planet2->collider.Dim(2);
	planet2->orbiting = planet;
	planet2->name="nats";

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

		glm::mat4 projection = glm::perspective(glm::radians(orbitgame.currentCamera->Zoom), (float)orbitgame.screenWidth / (float)orbitgame.screenHeight, 0.1f, 100.0f);
		glm::mat4 view = orbitgame.currentCamera->GetViewMatrix();


		// configuring the light source shader and meshes
		// ----------------------------------------------
		orbitgame.lightSourceShader->use();
		orbitgame.lightSourceShader->setMat4("projection", projection);
		orbitgame.lightSourceShader->setMat4("view", view);

		sunMesh.Draw(orbitgame.lightSourceShader, glm::vec3(50.0f,0.f,0.f), glm::vec3(10.0f));

		// configuring the texture shader and meshes
		// -----------------------------------------
		orbitgame.textureShader->use();
		orbitgame.textureShader->setMat4("projection", projection);
		orbitgame.textureShader->setMat4("view", view);
		orbitgame.textureShader->setVec3("light.position", glm::vec3(50.0f,0.f,0.f));
		orbitgame.textureShader->setVec3("light.ambient", lAmbient);
		orbitgame.textureShader->setVec3("light.diffuse", lDiffuse);
		orbitgame.textureShader->setVec3("light.specular", lSpecular);
		orbitgame.textureShader->setVec3("viewPos", orbitgame.currentCamera->worldPosition);

		orbitgame.phyxENG.Update();
		orbitgame.inputENG.Update(window);

		player->Draw(orbitgame.textureShader);
		player->camera.updateCameraVectors(player->worldPosition);

		planet->Draw(orbitgame.textureShader);
		planet2->Draw(orbitgame.textureShader);

		// configuring the material shader and meshes
		// ------------------------------------------
		orbitgame.materialShader->use();
		orbitgame.materialShader->setMat4("projection", projection);
		orbitgame.materialShader->setMat4("view", view);
		orbitgame.materialShader->setVec3("light.position", glm::vec3(0.0f));
		orbitgame.materialShader->setVec3("light.ambient", lAmbient);
		orbitgame.materialShader->setVec3("light.diffuse", lDiffuse);
		orbitgame.materialShader->setVec3("light.specular", lSpecular);
		orbitgame.materialShader->setVec3("viewPos", orbitgame.currentCamera->worldPosition);

		// draw skybox at last
		// -------------------
		glDepthFunc(GL_LEQUAL);
		orbitgame.skyboxShader->use();
		view = glm::mat4(glm::mat3(orbitgame.currentCamera->GetViewMatrix()));
		orbitgame.skyboxShader->setMat4("view", view);
		orbitgame.skyboxShader->setMat4("projection", projection);
		skyboxMesh.Draw(orbitgame.skyboxShader);
		glDepthFunc(GL_LESS);

		orbitgame.displayImGui();


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	orbitgame.Terminate();
	// glfw: terminate, clearing all previously allocated GLFW resources
	// -----------------------------------------------------------------
	glfwTerminate();
	return 0;
}