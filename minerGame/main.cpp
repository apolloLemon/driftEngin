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

Game miningGame(1280, 720, "minerGame/textures/", "minerGame/models/", "minerGame/sounds/");
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

	miningGame.phyxENG.gravitymode = None;

	miningGame.soundENG.soundFiles.push_back(miningGame.soundsPath + "track0.ogg");
	miningGame.soundENG.soundFiles.push_back(miningGame.soundsPath + "bleep.ogg");
	miningGame.soundENG.soundFiles.push_back(miningGame.soundsPath + "solid.ogg");
	miningGame.soundENG.soundFiles.push_back(miningGame.soundsPath + "electricshock.ogg");
	miningGame.soundENG.soundFiles.push_back(miningGame.soundsPath + "asteroidBreak.ogg");
	miningGame.soundENG.soundFiles.push_back(miningGame.soundsPath + "thruster.ogg");
	miningGame.soundENG.Play(0,1);

	// initialize glfw and game
	// ------------------------
	miningGame.freecam = new Freecam(glm::vec3(0.0f, 7.0f, 10.0f));
	miningGame.currentCamera = miningGame.freecam;
	miningGame.cameraMode = FREECAM_MODE;

	asteroidsPositions = generateAsteroidsPos(nbAsteroids, 10.F, -60.F, 60.F);

	miningGame.gameobjects.push_back(miningGame.freecam);
	miningGame.gameobjects.push_back(player);
	miningGame.gameobjects.push_back(shield);
	for (unsigned int i = 0; i < nbAsteroids; i++)
	{
		asteroids.push_back(new Asteroid());
		miningGame.gameobjects.push_back(asteroids[i]);
	}


	GLFWwindow* window = miningGame.Initialize();

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
	tSkybox.id = loadCubemap(faces, miningGame.texturesPath);
	tSkybox.type = "texture_skybox";
	tSkybox.path = "skybox";

	Texture tSquare;
	tSquare.id = TextureFromFile("square/square.png", miningGame.texturesPath);
	tSquare.type = "texture_diffuse";
	tSquare.path = "square/square.png";

	Texture tMoon;
	tMoon.id = TextureFromFile("moon/moon.jpg", miningGame.texturesPath);
	tMoon.type = "texture_diffuse";
	tMoon.path = "moon/moon.jpg";

	Texture tShield;
	tShield.id = TextureFromFile("shield.jpg", miningGame.texturesPath);
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

	player->loadModel(miningGame.modelsPath + "ship/V1.obj");
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
		miningGame.collENG.Update();
		miningGame.inputENG.Update(window);
		miningGame.phyxENG.Update();

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(miningGame.currentCamera->Zoom), (float)miningGame.screenWidth / (float)miningGame.screenHeight, 0.1f, 100.0f);
		glm::mat4 view = miningGame.currentCamera->GetViewMatrix();


		// configuring the light source shader and meshes
		// ----------------------------------------------
		miningGame.lightSourceShader->use();
		miningGame.lightSourceShader->setMat4("projection", projection);
		miningGame.lightSourceShader->setMat4("view", view);

		// configuring the texture shader and meshes
		// -----------------------------------------
		miningGame.textureShader->use();
		miningGame.textureShader->setMat4("projection", projection);
		miningGame.textureShader->setMat4("view", view);
		miningGame.textureShader->setVec3("light.position", lightPos);
		miningGame.textureShader->setVec3("light.ambient", lAmbient);
		miningGame.textureShader->setVec3("light.diffuse", lDiffuse);
		miningGame.textureShader->setVec3("light.specular", lSpecular);
		miningGame.textureShader->setVec3("viewPos", miningGame.currentCamera->worldPosition());

		for (unsigned int i = 0; i < nbAsteroids; i++)
		{
			asteroids[i]->Draw(miningGame.textureShader);
			asteroids[i]->UpdateCollider(glm::vec3(0), 0, asteroids[i]->size * 0.9f, 0);
		}

		std::vector<CollisionMsg*> playerCollisions = miningGame.collENG.CollisionsWith(shield, 0);
		for (unsigned int i = 0; i < playerCollisions.size(); i++)
		{
			shield->startAnimation(window);
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
						player->score++;
						j++;
					}
				}
			}
			if(qAst)
			{
				player->target = qAst;
				if(player->target->lifePoints <= 0)	{ player->target=nullptr; }
			}
		}
		shield->Update(window);

		// configuring the material shader and meshes
		// ------------------------------------------
		miningGame.materialShader->use();
		miningGame.materialShader->setMat4("projection", projection);
		miningGame.materialShader->setMat4("view", view);
		miningGame.materialShader->setVec3("light.position", lightPos);
		miningGame.materialShader->setVec3("light.ambient", lAmbient);
		miningGame.materialShader->setVec3("light.diffuse", lDiffuse);
		miningGame.materialShader->setVec3("light.specular", lSpecular);
		miningGame.materialShader->setVec3("viewPos", miningGame.currentCamera->worldPosition());

		player->Draw(miningGame.materialShader);
		player->camera.updateCameraVectors(player->worldPosition());

		// draw skybox at last
		// -------------------
		glDepthFunc(GL_LEQUAL);
		miningGame.skyboxShader->use();
		view = glm::mat4(glm::mat3(miningGame.currentCamera->GetViewMatrix()));
		miningGame.skyboxShader->setMat4("view", view);
		miningGame.skyboxShader->setMat4("projection", projection);
		skyboxMesh.Draw(miningGame.skyboxShader);
		glDepthFunc(GL_LESS);

		// ImGui displaying
		// ----------------
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (miningGame.cameraMode == ORTCAM_MODE)
		{
			player->gui(window);
			if(player->target)
				player->target->gui(window);
			if(shield->animation.isAnimating)
				shield->gui(window);
		}
		else
		{
			Freecam* gamecam = static_cast<Freecam*>(miningGame.currentCamera);
			gamecam->gui(window);
		}
		

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());	


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	miningGame.Terminate();

	// glfw: terminate, clearing all previously allocated GLFW resources
	// -----------------------------------------------------------------
	glfwTerminate();
	return 0;
}