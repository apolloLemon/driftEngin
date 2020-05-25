// engine classes
// --------------
#include "ENG/objects/game.h"
#include "ENG/objects/phyx.h"
#include "ENG/shaders/shader.h"
#include "ENG/mesh/mesh.h"
#include "ENG/mesh/sphere.h"
#include "ENG/mesh/cube.h"
#include "ENG/model/model.h"

// minergame gameobjects
// --------------------
#include "player.h"
#include "asteroid.h"

// instanciating our game with a resolution and path variables
Game miningGame(1280, 720, "minerGame/textures/", "minerGame/models/", "minerGame/sounds/");

// instanciating gameobjects
// -------------------------
Player * player = new Player();
Shield * shield = new Shield(2.0f); // creating a shield with a radius of 2.0f
std::vector<Asteroid*> asteroids; // pointers to our asteroids
std::vector<glm::vec3> asteroidsPositions; // used to store our generated asteroid positions
unsigned int nbAsteroids;

int main(int argc, char **argv)
{
	srand(time(NULL)); // initializing rand() seed with time

	miningGame.phyxENG.gravitymode = None; // used to avoid objects being attracted with each other as it's not working yet

	// importing our sound effects into the sound engine
	// -------------------------------------------------
	miningGame.soundENG.soundFiles.push_back(miningGame.soundsPath + "track0.ogg");
	miningGame.soundENG.soundFiles.push_back(miningGame.soundsPath + "bleep.ogg");
	miningGame.soundENG.soundFiles.push_back(miningGame.soundsPath + "solid.ogg");
	miningGame.soundENG.soundFiles.push_back(miningGame.soundsPath + "electricshock.ogg");
	miningGame.soundENG.soundFiles.push_back(miningGame.soundsPath + "asteroidBreak.ogg");
	miningGame.soundENG.soundFiles.push_back(miningGame.soundsPath + "thruster.ogg");
	miningGame.soundENG.Play(0, true); // play the background music

	// initialize glfw and game
	// ------------------------
	miningGame.freecam = new Freecam(glm::vec3(0.0f, 7.0f, 10.0f)); // we instantiate the freecam with a position
	miningGame.currentCamera = miningGame.freecam; // the pointer to the used camera is now pointing to freecam
	miningGame.cameraMode = FREECAM_MODE; // change mode, used to know in which camera mode we are

	// generate asteroids positions thanks to poisson disk sampling
	// we generate positions in a 120*120 square (-60 -> 60) with a minimum distance of 10 between positions
	// nbAsteroids become the positions number
	asteroidsPositions = generateAsteroidsPos(nbAsteroids, 10.F, -60.F, 60.F);

	// adding the gameobjects to the game engine gameobjects list, so it can manage them
	miningGame.gameobjects.push_back(miningGame.freecam);
	miningGame.gameobjects.push_back(player);
	miningGame.gameobjects.push_back(shield);
	for (unsigned int i = 0; i < nbAsteroids; i++)
	{
		asteroids.push_back(new Asteroid());
		miningGame.gameobjects.push_back(asteroids[i]);
	}

	// initialize the openGL context and the game engine
	GLFWwindow* window = miningGame.Initialize();

	// creating our used textures
	// --------------------------
	// skybox cubemap textures
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
	// moon textures, used for asteroids
	Texture tMoon;
	tMoon.id = TextureFromFile("moon/moon.jpg", miningGame.texturesPath);
	tMoon.type = "texture_diffuse";
	tMoon.path = "moon/moon.jpg";
	// shield textures
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

	// initializing our gameobjects attributes and phyx settings
	// ---------------------------------------------------------
	// player
	player->name="player"; // giving our object a name, used in debug
	player->scale = glm::vec3(0.001f); // scaling the player model, as the ship model is way too big
	player->MoveTo(glm::vec2(-5.0f, -5.0f)); // moving our player to a location
	player->Mass(1.0f); // setting our player mass, it changes its reaction to collisions
	// shield
	shield->name="shield";
	shield->attach(player); // linking the shield to player, making it his parent
	shield->scale = glm::vec3(shield->size);
	shield->CreateCollider(glm::dvec3(0.0f), 0, shield->size); // create a circle collider, with no offset, at layer 0 and sized like the shield
	// asteroids
	for (unsigned int i = 0; i < nbAsteroids; i++)
	{
		asteroids[i]->Generate(&moonTextures); // generate an asteroid with a random shape thanks to perlin noise
		glm::vec3 pos(asteroidsPositions[i]);

		asteroids[i]->name="asteroid"+std::to_string(i);
		asteroids[i]->MoveTo(pos);
		asteroids[i]->CreateCollider(glm::dvec3(0), 0, asteroids[i]->size * 0.9f);
		asteroids[i]->Mass(100.0f * asteroids[i]->size);
		asteroids[i]->YV(0.5f); // giving our asteroids a starting Y speed, making them move slowly together
	}

	// lighting options
	// ----------------
	glm::vec3 lightColor(1.0f); // rgb value, here it's white
	glm::vec3 lDiffuse = lightColor * glm::vec3(0.8f); // adjusting the light diffuse value
	glm::vec3 lAmbient = lDiffuse * glm::vec3(0.2f); // adjusting the light ambient value
	glm::vec3 lSpecular(1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos(100.0f, 10.0f, 100.0f); // create a distant light position
	lightPos.x *= -0.64f; // scaling light position to match our skybox's sun
	lightPos.z *= -0.77f;

	// render loop, called every frame
	// -------------------------------
	while (!glfwWindowShouldClose(window))
	{
		// call the engines update()
		// -------------------------
		miningGame.collENG.Update();
		miningGame.inputENG.Update(window);
		miningGame.phyxENG.Update();

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// our projection matrix is made using perspective, with the current camera and our screen dimensions
		// the last two values are respectively the minimum distance view and the maximum
		glm::mat4 projection = glm::perspective(glm::radians(miningGame.currentCamera->Zoom), (float)miningGame.screenWidth / (float)miningGame.screenHeight, 0.1f, 100.0f);
		// ask our camera to return the view matrix and store it
		glm::mat4 view = miningGame.currentCamera->GetViewMatrix();


		// configuring the light source shader
		// -----------------------------------
		miningGame.lightSourceShader->use();
		miningGame.lightSourceShader->setMat4("projection", projection);
		miningGame.lightSourceShader->setMat4("view", view);

		// draw light sources here
		// -----------------------

		// configuring the texture shader
		// ------------------------------
		miningGame.textureShader->use();
		miningGame.textureShader->setMat4("projection", projection);
		miningGame.textureShader->setMat4("view", view);
		miningGame.textureShader->setVec3("light.position", lightPos);
		miningGame.textureShader->setVec3("light.ambient", lAmbient);
		miningGame.textureShader->setVec3("light.diffuse", lDiffuse);
		miningGame.textureShader->setVec3("light.specular", lSpecular);
		miningGame.textureShader->setVec3("viewPos", miningGame.currentCamera->worldPosition());

		// draw textured objects here
		// --------------------------
		for (unsigned int i = 0; i < nbAsteroids; i++)
		{
			asteroids[i]->Draw(miningGame.textureShader); // draw our asteroid using the textureShader
			asteroids[i]->UpdateCollider(glm::vec3(0), 0, asteroids[i]->size * 0.9f, 0); // we update the asteroid collider to its actual size
		}

		// we get the collisions informations that concerns the player from the collision engine
		std::vector<CollisionMsg*> playerCollisions = miningGame.collENG.CollisionsWith(shield, 0);
		// for each of this collision
		for (unsigned int i = 0; i < playerCollisions.size(); i++)
		{
			shield->startAnimation(window); // ask the shield to start animating
			Asteroid* qAst = dynamic_cast<Asteroid*>(playerCollisions[i]->Q.first); // we cast the second actor to see if it's an asteroid
			if(qAst) // if it's an asteroid
			{
				unsigned j = 0;
				while (j<10) // find 10 points to break from it
				{
					int point = rand() % 121; // since our asteroids are drawn with 121 vertices, we generate a number between 0 and 120
					if(qAst->maxLayer == qAst->activeLayer[point].layer)
					{
						qAst->Break(point, window); // break the point, passing the window to play a sound effect
						player->score++;
						j++;
					}
				}
				player->target = qAst; // changing the player target to be the asteroid collisioned with
				if (player->target->lifePoints <= 0)	{ player->target = nullptr; } // if the asteroid is destroyed, the player has no target anymore
			}
		}
		shield->Update(window); // updating the shield to draw if it's animated and check if the animation sould end or not (based on time)

		// configuring the material shader
		// -------------------------------
		miningGame.materialShader->use();
		miningGame.materialShader->setMat4("projection", projection);
		miningGame.materialShader->setMat4("view", view);
		miningGame.materialShader->setVec3("light.position", lightPos);
		miningGame.materialShader->setVec3("light.ambient", lAmbient);
		miningGame.materialShader->setVec3("light.diffuse", lDiffuse);
		miningGame.materialShader->setVec3("light.specular", lSpecular);
		miningGame.materialShader->setVec3("viewPos", miningGame.currentCamera->worldPosition());

		// draw untextured objects here
		// ----------------------------
		player->Draw(miningGame.materialShader);
		player->camera.updateCameraVectors(player->worldPosition()); // updating our player orthogonal camera position every frame

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
		// display our game informations, each of our object has its own gui() function
		// see ImGui documentation to understand how to make your windows
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