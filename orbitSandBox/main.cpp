//ENG
#include "ENG/objects/game.h"
#include "ENG/objects/phyx.h"
#include "ENG/shaders/shader.h"
#include "ENG/mesh/mesh.h"
#include "ENG/mesh/sphere.h"
#include "ENG/mesh/cube.h"
#include "ENG/model/model.h"
//#include <ENG/eng.h>


//drift
//#include "drift/player.h"
//#include "drift/simplebody.h"
#include <drift/drift.h>

#include <iostream>

Game sandBox(1280, 720, "drift/textures/", "drift/models/", "drift/sounds/");
// GameObjects
// ----------------
//Player * player = new Player();
SimpleBody * A = new SimpleBody();
SimpleBody * B = new SimpleBody();
SimpleBody * C = new SimpleBody(); 

int main(int argc, char **argv)
{
	sandBox.phyxENG.gravitymode = Everything;
	sandBox.soundENG.soundFiles.push_back(sandBox.soundsPath + "track0.ogg");
	sandBox.soundENG.soundFiles.push_back(sandBox.soundsPath + "bleep.ogg");
	sandBox.soundENG.soundFiles.push_back(sandBox.soundsPath + "solid.ogg");
	sandBox.soundENG.Play(0,1);

	// initialize glfw and game
	// ------------------------
	sandBox.freecam = new Freecam(glm::vec3(0.0f, 7.0f, 10.0f));
	sandBox.currentCamera = sandBox.freecam;
	sandBox.cameraMode = FREECAM_MODE;

	sandBox.gameobjects.push_back(sandBox.freecam);
//	sandBox.gameobjects.push_back(player);
	sandBox.gameobjects.push_back(A);
	sandBox.gameobjects.push_back(B);
	sandBox.gameobjects.push_back(C);

	GLFWwindow* window = sandBox.Initialize();

	// creating our skybox
	// -------------------
/*
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
	tSkybox.id = loadCubemap(faces, sandBox.texturesPath);
	tSkybox.type = "texture_skybox";
	tSkybox.path = "skybox";
//*/
	Texture tSquare;
	tSquare.id = TextureFromFile("square/square.png", sandBox.texturesPath);
	tSquare.type = "texture_diffuse";
	tSquare.path = "square/square.png";

	// creating texture vectors
	// ------------------------
/*	std::vector<Texture> sunTextures;
	sunTextures.push_back(tSun);

	std::vector<Texture> skyboxTextures;
	skyboxTextures.push_back(tSkybox);
*/
	std::vector<Texture> squareTextures;
	squareTextures.push_back(tSquare);

	// instantiate meshes
	// ------------------
//	Sphere sunMesh(50, 50, sunTextures);
//	Cube skyboxMesh(skyboxTextures);
	
//	planet->meshes.push_back(new Sphere(50,50,moonTextures));
//	player->loadModel(sandBox.modelsPath + "ship/V1.obj");

	A->meshes.push_back(new Sphere(50,50,squareTextures));
	B->meshes.push_back(new Sphere(50,50,squareTextures));
	C->meshes.push_back(new Sphere(50,50,squareTextures));

	// initializing the player
	// -----------------------
/*	player->worldPosition = glm::vec3(15.0f, 0.0f, 0.0f);
	player->scale = glm::vec3(0.001f);
	player->Init();
	//player->loadModel(modelsPath + "sputnik/sputnik1.obj");
	player->YV(2); // starting velocity
	player->Mass(1.f);
	player->collider.Dim(1);
	player->orbiting = planet;
	player->name="stan";
*/
	A->name="A";
	A->MoveTo(glm::vec3(0.0f, 0.0f, 0.0f));
	A->CreateCollider(glm::dvec3(0),0);
	A->YV(0);
	A->XV(0);
	A->Mass(10000.f);
//	A->isKinematic(true);

//	TESTLOG(dynamic_cast<CircleCollider *>(A->collidersLayer(0)[0])->Dim());

	B->name="B";
	B->MoveTo(glm::vec3(-5.0f, 0.0f, 1.0f));
	B->CreateCollider(glm::dvec3(0),0);
	B->YV(.5);
	B->Mass(.1f);
//	B->orbiting=A;

	C->name="C";
	C->MoveTo(glm::vec3(4.0f, 0.0f, 1.0f));
	C->CreateCollider(glm::dvec3(0),0);
//	C->XV(-1);
	C->YV(-.5);
	C->Mass(.1f);
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
		sandBox.collENG.Update();
		sandBox.inputENG.Update(window);
		sandBox.phyxENG.Update();

/*		for(auto e : sandBox.collENG.events)		
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

		glm::mat4 projection = glm::perspective(glm::radians(sandBox.currentCamera->Zoom), (float)sandBox.screenWidth / (float)sandBox.screenHeight, 0.1f, 100.0f);
		glm::mat4 view = sandBox.currentCamera->GetViewMatrix();


		// configuring the light source shader and meshes
		// ----------------------------------------------
		sandBox.lightSourceShader->use();
		sandBox.lightSourceShader->setMat4("projection", projection);
		sandBox.lightSourceShader->setMat4("view", view);

//		sunMesh.Draw(sandBox.lightSourceShader, glm::vec3(50.0f,0.f,0.f), glm::vec3(10.0f));

		// configuring the texture shader and meshes
		// -----------------------------------------
		sandBox.textureShader->use();
		sandBox.textureShader->setMat4("projection", projection);
		sandBox.textureShader->setMat4("view", view);
		sandBox.textureShader->setVec3("light.position", glm::vec3(50.0f,0.f,0.f));
		sandBox.textureShader->setVec3("light.ambient", lAmbient);
		sandBox.textureShader->setVec3("light.diffuse", lDiffuse);
		sandBox.textureShader->setVec3("light.specular", lSpecular);
		sandBox.textureShader->setVec3("viewPos", sandBox.currentCamera->worldPosition());


//		planet->Draw(sandBox.textureShader);
//		planet2->Draw(sandBox.textureShader);


		A->Draw(sandBox.textureShader);
		B->Draw(sandBox.textureShader);
		C->Draw(sandBox.textureShader);

		// configuring the material shader and meshes
		// ------------------------------------------
		sandBox.materialShader->use();
		sandBox.materialShader->setMat4("projection", projection);
		sandBox.materialShader->setMat4("view", view);
		sandBox.materialShader->setVec3("light.position", glm::vec3(0.0f));
		sandBox.materialShader->setVec3("light.ambient", lAmbient);
		sandBox.materialShader->setVec3("light.diffuse", lDiffuse);
		sandBox.materialShader->setVec3("light.specular", lSpecular);
		sandBox.materialShader->setVec3("viewPos", sandBox.currentCamera->worldPosition());

//		player->Draw(sandBox.materialShader);
//		player->camera.updateCameraVectors(player->worldPosition);

		// draw skybox at last
		// -------------------
/*		glDepthFunc(GL_LEQUAL);
		sandBox.skyboxShader->use();
		view = glm::mat4(glm::mat3(sandBox.currentCamera->GetViewMatrix()));
		sandBox.skyboxShader->setMat4("view", view);
		sandBox.skyboxShader->setMat4("projection", projection);
		skyboxMesh.Draw(sandBox.skyboxShader);
		glDepthFunc(GL_LESS);
*/
		sandBox.phyxGui();


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	sandBox.Terminate();
	
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