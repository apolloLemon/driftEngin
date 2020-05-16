//ENG
#include "ENG/objects/game.h"
#include "ENG/objects/phyx.h"
#include "ENG/shaders/shader.h"
#include "ENG/mesh/mesh.h"
#include "ENG/mesh/sphere.h"
#include "ENG/mesh/cube.h"
#include "ENG/model/model.h"

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alut.h"

//drift
#include "drift/player.h"

//orbitgame
#include "CelestialBody.h"


Game orbitgame(1280, 720);

// GameObjects
// ----------------
Player * player = new Player();
CelestialBody * planet = new CelestialBody();
CelestialBody * planet2 = new CelestialBody();

ALuint audiobuffer, audiosrc;
ALint state;

int main(int argc, char **argv)
{
	if(!alutInit(0,NULL)) std::cout <<"ALerror: "<< alutGetErrorString(alutGetError())<<std::endl;
    // Load pcm data into buffer
    audiobuffer = alutCreateBufferFromFile("/home/melon/driftEngin/orbitgame/sounds/track0.ogg");
    //audiobuffer = alutCreateBufferFromFile("/home/rakl/Repository/spaceProject/driftEngin/orbitgame/sounds/track0.wav");
    // Create sound source (use buffer to fill source)
    if(!audiobuffer) std::cout <<"ALerror: "<< alutGetErrorString(alutGetError()) <<std::endl;
    alGenSources(1, &audiosrc);
    alSourcei(audiosrc, AL_BUFFER, audiobuffer);
    // Play
    // Wait for the song to complete
    //do {
    //    alGetSourcei(audiosrc, AL_SOURCE_STATE, &state);
    //} while (state == AL_PLAYING);
    

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

	std::vector<Texture> moonTextures;
	moonTextures.push_back(tMoon);

	// instantiate meshes
	// ------------------
	Sphere sunMesh(50, 50, sunTextures);
	
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
	player->worldPosition = glm::vec3(30.0f, 0.0f, 0.0f);
	player->Init();
	//player->loadModel(modelsPath + "sputnik/sputnik1.obj");
	player->YV(2); // starting velocity
	player->Mass(1.f);
	player->collider.Dim(1);
	player->orbiting = planet;
	player->name="stan";

	planet->worldPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	planet->Mass(1.f);
	planet->scale = glm::vec3(20);
	planet->collider.Dim(20);

	planet2->worldPosition = glm::vec3(40.0f, 0.0f, 0.0f);
	planet2->Init();
	planet2->YV(2);
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

	bool skip=true;
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		alGetSourcei(audiosrc, AL_SOURCE_STATE, &state);
		if(state != AL_PLAYING) alSourcePlay(audiosrc);
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

		orbitgame.displayImGui();


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	orbitgame.Terminate();
	
	// Clean up sources and buffers
    alDeleteSources(1, &audiosrc);
    alDeleteBuffers(1, &audiobuffer);
    // Exit everything
    alutExit();
	// glfw: terminate, clearing all previously allocated GLFW resources
	// -----------------------------------------------------------------
	glfwTerminate();
	return 0;
}