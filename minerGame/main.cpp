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
//Shield * shield = new Shield();
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
	driftgame.soundENG.Play(0,1);

	// initialize glfw and game
	// ------------------------
	driftgame.freecam = new Freecam(glm::vec3(0.0f, 7.0f, 10.0f));
	driftgame.currentCamera = driftgame.freecam;
	driftgame.cameraMode = FREECAM_MODE;

	asteroidsPositions = generateAsteroidsPos(nbAsteroids, 10.F, -50.F, 50.F);

	driftgame.gameobjects.push_back(driftgame.freecam);
	driftgame.gameobjects.push_back(player);
//	driftgame.gameobjects.push_back(shield);
	for (unsigned int i = 0; i < nbAsteroids; i++)
	{
		asteroids.push_back(new Asteroid());
		driftgame.gameobjects.push_back(asteroids[i]);
	}


	GLFWwindow* window = driftgame.Initialize();

	// creating our skybox
	// -------------------
//*
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
//*/
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
/*	std::vector<Texture> sunTextures;
	sunTextures.push_back(tSun);
*/
	std::vector<Texture> skyboxTextures;
	skyboxTextures.push_back(tSkybox);

	std::vector<Texture> moonTextures;
	moonTextures.push_back(tMoon);

	std::vector<Texture> shieldTextures;
	shieldTextures.push_back(tShield);
/*
	std::vector<Texture> squareTextures;
	squareTextures.push_back(tSquare);
*/
	// instantiate meshes
	// ------------------
//	Sphere sunMesh(50, 50, sunTextures);
	Cube skyboxMesh(skyboxTextures);
	
	player->meshes.push_back(new Sphere(50,50,shieldTextures));
//	player->loadModel(driftgame.modelsPath + "ship/V1.obj");

//	shield->meshes.push_back(new Sphere(50, 50, shieldTextures));

//	A->meshes.push_back(new Sphere(50,50,squareTextures));
//	B->meshes.push_back(new Sphere(50,50,squareTextures));
//	C->meshes.push_back(new Sphere(50,50,squareTextures));

	// initializing the player
	// -----------------------
	//*	
	player->name="player";
	player->scale = glm::vec3(1.f);
	player->MoveTo(glm::vec2(-5.0f, -5.0f));
//	player->CreateCollider(glm::dvec3(0), 0);
	player->XV(0);
	player->YV(0);
	player->Mass(1.0f);
	//*/
/*	shield->name="shield";
	shield->position=glm::dvec3(0.1,0,0.1);
	shield->attach(player);
	shield->scale = glm::vec3(2.0f);
	shield->CreateCollider(glm::dvec3(0), 0, 1.5f);
	shield->Mass(2.0f);
*/
	//*
	for (unsigned int i = 0; i < nbAsteroids; i++)
	{
		asteroids[i]->Generate(&moonTextures);
		glm::vec3 pos(asteroidsPositions[i]);

		//std::cout << "pos: [x:" << pos.x << ", y:" << pos.y << ", z:" << pos.z << "]" << std::endl;
		float size = asteroids[i]->preciseSize();
		asteroids[i]->name="asteroid"+std::to_string(i);
		asteroids[i]->MoveTo(pos);
		asteroids[i]->CreateCollider(glm::dvec3(0), 0, size);
		asteroids[i]->Mass(10.0f * size);
		asteroids[i]->YV(0.5f);
	}
	//*/
//	A->name="A";
//	A->MoveTo(glm::vec3(0.0f, 0.0f, 0.0f));
//	A->CreateCollider(glm::dvec3(0),0);
//	A->YV(0);
//	A->XV(0);
//	A->Mass(10000.f);
//	A->isKinematic(true);

//	TESTLOG(dynamic_cast<CircleCollider *>(A->collidersLayer(0)[0])->Dim());

//	B->name="B";
//	B->MoveTo(glm::vec3(-5.0f, 0.0f, 1.0f));
//	B->CreateCollider(glm::dvec3(0),0);
//	B->YV(.5);
//	B->Mass(.1f);
//	B->orbiting=A;

//	C->name="C";
//	C->MoveTo(glm::vec3(4.0f, 0.0f, 1.0f));
//	C->CreateCollider(glm::dvec3(0),0);
//	C->XV(-1);
//	C->YV(-.5);
//	C->Mass(.1f);
//	C->orbiting=A;
//	C->isKinematic(true);	

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
		driftgame.collENG.Update();
		driftgame.inputENG.Update(window);
		driftgame.phyxENG.Update();

/*		for(auto e : driftgame.collENG.events)		
			std::cout
				<< "collision event \t" << e << std::endl  
				<< "life \t" << e->life << "layer \t" << e->layer << std::endl
				<< "Pname \t" << e->P.first->name << std::endl
				<< "Qname \t" << e->Q.first->name << std::endl;
//*/

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

//		sunMesh.Draw(driftgame.lightSourceShader, glm::vec3(50.0f,0.f,0.f), glm::vec3(10.0f));

		// configuring the texture shader and meshes
		// -----------------------------------------
		driftgame.textureShader->use();
		driftgame.textureShader->setMat4("projection", projection);
		driftgame.textureShader->setMat4("view", view);
		driftgame.textureShader->setVec3("light.position", glm::vec3(50.0f,0.f,0.f));
		driftgame.textureShader->setVec3("light.ambient", lAmbient);
		driftgame.textureShader->setVec3("light.diffuse", lDiffuse);
		driftgame.textureShader->setVec3("light.specular", lSpecular);
		driftgame.textureShader->setVec3("viewPos", driftgame.currentCamera->worldPosition());


//		planet->Draw(driftgame.textureShader);
//		planet2->Draw(driftgame.textureShader);

		for (unsigned int i = 0; i < nbAsteroids; i++)
		{
			asteroids[i]->Draw(driftgame.textureShader);
			asteroids[i]->UpdateCollider(glm::vec3(0), 0, asteroids[i]->preciseSize(), 0);
		}
/*
		std::vector<CollisionMsg*> playerCollisions = driftgame.collENG.CollisionsWith(shield, 0);
		for (unsigned int i = 0; i < playerCollisions.size(); i++)
		{
			shield->Draw(driftgame.textureShader);
			PhyxObj2D* p = dynamic_cast<PhyxObj2D *>(playerCollisions[i]->P.first);
			PhyxObj2D* q = dynamic_cast<PhyxObj2D *>(playerCollisions[i]->Q.first);
			if(glm::length(glm::dot(p->v, q->v) * 10000.0f)>0.3)
			{
				driftgame.soundENG.Play(3, false);
			}
			Asteroid* pAst = dynamic_cast<Asteroid*>(p);
			Asteroid* qAst = dynamic_cast<Asteroid*>(q);
			int point = rand() % 100;
			if(pAst) 	{ pAst->Break(point); }
			if(qAst)	{ qAst->Break(point); }

			
		}
*/

		// configuring the material shader and meshes
		// ------------------------------------------
		driftgame.materialShader->use();
		driftgame.materialShader->setMat4("projection", projection);
		driftgame.materialShader->setMat4("view", view);
		driftgame.materialShader->setVec3("light.position", glm::vec3(0.0f));
		driftgame.materialShader->setVec3("light.ambient", lAmbient);
		driftgame.materialShader->setVec3("light.diffuse", lDiffuse);
		driftgame.materialShader->setVec3("light.specular", lSpecular);
		driftgame.materialShader->setVec3("viewPos", driftgame.currentCamera->worldPosition());

		player->Draw(driftgame.textureShader);
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
	
	// Clean up sources and buffers
   // alDeleteSources(1, &audiosrc);
   // alDeleteBuffers(1, &audiobuffer);
    // Exit everything
  //  alutExit();
	// glfw: terminate, clearing all previously allocated GLFW resources
	// -----------------------------------------------------------------
	glfwTerminate();
	return 0;
}