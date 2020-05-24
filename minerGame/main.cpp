//ENG
#include "ENG/objects/game.h"
#include "ENG/objects/phyx.h"
#include "ENG/shaders/shader.h"
#include "ENG/mesh/mesh.h"
#include "ENG/mesh/sphere.h"
#include "ENG/mesh/cube.h"
#include "ENG/model/model.h"

//drift
#include "player.h"
#include "simplebody.h"
#include "minerGame/asteroid.h"

#include <iostream>

Game driftgame(1280, 720, "minerGame/textures/", "minerGame/models/", "minerGame/sounds/");
// GameObjects
// ----------------
Player * player = new Player();
Shield * shield = new Shield(2.0f);
std::vector<Asteroid*> asteroids;
std::vector<glm::vec3> asteroidsPositions;
unsigned int nbAsteroids = 0;

int main(int argc, char **argv)
{
	srand(time(NULL));

	driftgame.phyxENG.gravitymode = None;

	driftgame.soundENG.soundFiles.push_back(driftgame.soundsPath + "track0.ogg");
	driftgame.soundENG.soundFiles.push_back(driftgame.soundsPath + "bleep.ogg");
	driftgame.soundENG.soundFiles.push_back(driftgame.soundsPath + "solid.ogg");
	driftgame.soundENG.soundFiles.push_back(driftgame.soundsPath + "electricshock.ogg");
	driftgame.soundENG.soundFiles.push_back(driftgame.soundsPath + "asteroidBreak.ogg");
	driftgame.soundENG.soundFiles.push_back(driftgame.soundsPath + "thruster.ogg");
	driftgame.soundENG.Play(0,1);

	// initialize glfw and game
	// ------------------------
	driftgame.freecam = new Freecam(glm::vec3(0.0f, 7.0f, 10.0f));
	driftgame.currentCamera = driftgame.freecam;
	driftgame.cameraMode = FREECAM_MODE;

	asteroidsPositions = generateAsteroidsPos(nbAsteroids, 10.F, -50.F, 50.F);

	driftgame.gameobjects.push_back(driftgame.freecam);
	driftgame.gameobjects.push_back(player);
	driftgame.gameobjects.push_back(shield);
	for (unsigned int i = 0; i < nbAsteroids; i++)
	{
		asteroids.push_back(new Asteroid());
		driftgame.gameobjects.push_back(asteroids[i]);
	}


	GLFWwindow* window = driftgame.Initialize();

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
	tSkybox.id = loadCubemap(faces, driftgame.texturesPath);
	tSkybox.type = "texture_skybox";
	tSkybox.path = "skybox";

	Texture tSquare;
	tSquare.id = TextureFromFile("square/square.png", driftgame.texturesPath);
	tSquare.type = "texture_diffuse";
	tSquare.path = "square/square.png";

	Texture tMoon;
	tMoon.id = TextureFromFile("moon/moon.jpg", driftgame.texturesPath);
	tMoon.type = "texture_diffuse";
	tMoon.path = "moon/moon.jpg";

	Texture tShield;
	tShield.id = TextureFromFile("shield.jpg", driftgame.texturesPath);
	tShield.type = "texture_diffuse";
	tShield.path = "shield.jpg";

	// creating texture vectors
	// ------------------------
	std::vector<Texture> skyboxTextures;
	skyboxTextures.push_back(tSkybox);

	std::vector<Texture> moonTextures;
	moonTextures.push_back(tMoon);

	std::vector<Texture> shieldTextures;
	shieldTextures.push_back(tShield);

	// instantiate meshes
	// ------------------
	Cube skyboxMesh(skyboxTextures);

	player->loadModel(driftgame.modelsPath + "ship/V1.obj");
	shield->meshes.push_back(new Sphere(50, 50, shieldTextures));

	// initializing the player
	// -----------------------
	player->name="player";
	player->scale = glm::vec3(0.001f);
	player->MoveTo(glm::vec2(-5.0f, -5.0f));
	player->XV(0);
	player->YV(0);
	player->Mass(1.0f);

	shield->name="shield";
	shield->position=glm::dvec3(0.1,0,0.1);
	shield->attach(player);
	shield->scale = glm::vec3(2.0f);
	shield->CreateCollider(glm::dvec3(0), 0, shield->size);
	shield->Mass(2.0f);

	for (unsigned int i = 0; i < nbAsteroids; i++)
	{
		asteroids[i]->Generate(&moonTextures);
		glm::vec3 pos(asteroidsPositions[i]);

		//std::cout << "pos: [x:" << pos.x << ", y:" << pos.y << ", z:" << pos.z << "]" << std::endl;
		asteroids[i]->name="asteroid"+std::to_string(i);
		asteroids[i]->MoveTo(pos);
		asteroids[i]->CreateCollider(glm::dvec3(0), 0, asteroids[i]->size * 0.9f);
		asteroids[i]->Mass(100.0f * asteroids[i]->size);
		asteroids[i]->YV(0.5f);
	}

	// lighting options
	// ----------------
	glm::vec3 lightColor(1.0f);
	glm::vec3 lDiffuse = lightColor * glm::vec3(0.8f);
	glm::vec3 lAmbient = lDiffuse * glm::vec3(0.2f);
	glm::vec3 lSpecular(1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos(-100.0f, 10.0f, 50.0f);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		driftgame.collENG.Update();
		driftgame.inputENG.Update(window);
		driftgame.phyxENG.Update();

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(driftgame.currentCamera->Zoom), (float)driftgame.screenWidth / (float)driftgame.screenHeight, 0.1f, 100.0f);
		glm::mat4 view = driftgame.currentCamera->GetViewMatrix();


		// configuring the light source shader and meshes
		// ----------------------------------------------
		driftgame.lightSourceShader->use();
		driftgame.lightSourceShader->setMat4("projection", projection);
		driftgame.lightSourceShader->setMat4("view", view);

		// configuring the texture shader and meshes
		// -----------------------------------------
		driftgame.textureShader->use();
		driftgame.textureShader->setMat4("projection", projection);
		driftgame.textureShader->setMat4("view", view);
		driftgame.textureShader->setVec3("light.position", lightPos);
		driftgame.textureShader->setVec3("light.ambient", lAmbient);
		driftgame.textureShader->setVec3("light.diffuse", lDiffuse);
		driftgame.textureShader->setVec3("light.specular", lSpecular);
		driftgame.textureShader->setVec3("viewPos", driftgame.currentCamera->worldPosition());

		for (unsigned int i = 0; i < nbAsteroids; i++)
		{
			asteroids[i]->Draw(driftgame.textureShader);
			asteroids[i]->UpdateCollider(glm::vec3(0), 0, asteroids[i]->size * 0.9f, 0);
		}

		std::vector<CollisionMsg*> playerCollisions = driftgame.collENG.CollisionsWith(shield, 0);
		for (unsigned int i = 0; i < playerCollisions.size(); i++)
		{
			shield->startAnimation(window);
			Asteroid* pAst = dynamic_cast<Asteroid*>(playerCollisions[i]->P.first);
			Asteroid* qAst = dynamic_cast<Asteroid*>(playerCollisions[i]->Q.first);
			unsigned int j = 0;
			while (j<10)
			{
				int point = rand() % 122;
				if(qAst)
				{
					if(qAst->maxLayer == qAst->activeLayer[point].layer)
					{
						qAst->Break(point, window);
						j++;
					}
				}
			}
		}
		shield->Update(window);

		// configuring the material shader and meshes
		// ------------------------------------------
		driftgame.materialShader->use();
		driftgame.materialShader->setMat4("projection", projection);
		driftgame.materialShader->setMat4("view", view);
		driftgame.materialShader->setVec3("light.position", lightPos);
		driftgame.materialShader->setVec3("light.ambient", lAmbient);
		driftgame.materialShader->setVec3("light.diffuse", lDiffuse);
		driftgame.materialShader->setVec3("light.specular", lSpecular);
		driftgame.materialShader->setVec3("viewPos", driftgame.currentCamera->worldPosition());

		player->Draw(driftgame.materialShader);
		player->camera.updateCameraVectors(player->worldPosition());

		// draw skybox at last
		// -------------------
		glDepthFunc(GL_LEQUAL);
		driftgame.skyboxShader->use();
		view = glm::mat4(glm::mat3(driftgame.currentCamera->GetViewMatrix()));
		driftgame.skyboxShader->setMat4("view", view);
		driftgame.skyboxShader->setMat4("projection", projection);
		skyboxMesh.Draw(driftgame.skyboxShader);
		glDepthFunc(GL_LESS);

		driftgame.phyxGui();


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	driftgame.Terminate();

	// glfw: terminate, clearing all previously allocated GLFW resources
	// -----------------------------------------------------------------
	glfwTerminate();
	return 0;
}