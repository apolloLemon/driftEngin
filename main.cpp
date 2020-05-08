
//*Imgui 1/4
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
//*/
#include "init.h" // initialize function prototypes

#include "camera/freecam.h"
#include "shaders/shader.h"
#include "mesh/mesh.h"
#include "mesh/model.h"
#include "mesh/cube.h"
#include "mesh/sphere.h"

#include "gameobjects/player.h"
//#include "utilities/perlin.h"
//#include <vector>

#include <iostream>

//#define N
#define M
#if defined(N)
	#define PWD "/home/rakl/Repository/spaceProject/driftEngin/"
#elif defined(M)
	#define PWD "/home/melon/driftEngin/"
#endif	

// path variables
// --------------
std::string srcPath = PWD;
std::string shadersPath = srcPath + "shaders/";
std::string texturesPath = srcPath + "textures/";

Player player(glm::vec3(6.0f, 0.0f, 0.0f),"Games/OrbitGame/Assets/sputnik1.obj");

// camera variables
// ----------------
Freecam freecam(glm::vec3(0.0f, 7.0f, 10.0f));
// starting in freecam
Camera* currentCamera = &freecam;
bool freeMode = true;
// variables to manipulate camera with mouse
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing variables
// ----------------
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main(int argc, char **argv)
{
	// initialize glfw
	// ---------------
	GLFWwindow* window = init();

	//*Imgui 2/4
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    //*/

    stbi_set_flip_vertically_on_load(true);

	// build and compile our shader program
	// ------------------------------------

	Shader textureShader((shadersPath+"textureShader.vs").c_str(), (shadersPath+"textureShader.fs").c_str());
	Shader materialShader((shadersPath+"materialShader.vs").c_str(), (shadersPath+"materialShader.fs").c_str());
	Shader lightSourceShader((shadersPath+"lightSourceShader.vs").c_str(), (shadersPath+"lightSourceShader.fs").c_str());

    // adding our textures
    // -------------------------
    Texture tSquare;
    tSquare.id = TextureFromFile("textures/square/square.png", srcPath);
    tSquare.type = "texture_diffuse";
    tSquare.path = "textures/square/square.png";

    Texture tSquare2;
    tSquare2.id = TextureFromFile("textures/square2/square2.png", srcPath);
    tSquare2.type = "texture_diffuse";
    tSquare2.path = "textures/square2/square2.png";

    Texture tSquare2_specular;
    tSquare2_specular.id = TextureFromFile("textures/square2/square2_specular.png", srcPath);
    tSquare2_specular.type = "texture_specular";
    tSquare2_specular.path = "textures/square2/square2_specular.png";

    Texture tSun;
    tSun.id = TextureFromFile("textures/sun/sun.jpg", srcPath);
    tSun.type = "texture_light";
    tSun.path = "textures/sun/sun.jpg";

    // adding our materials
    // --------------------
    Material emerald;
    emerald.ambient = glm::vec3(0.0215f, 0.1745f, 0.0215f);
    emerald.diffuse = glm::vec3(0.07568f, 0.61424f, 0.07568f);
    emerald.specular = glm::vec3(0.633f, 0.727811f, 0.633f);
    //TODO: Import new materials from www.devernay.free.fr/cours/opengl/materials.html

    // creating texture vectors
    // ------------------------
    std::vector<Texture> cubeTextures;
    cubeTextures.push_back(tSquare2);
    cubeTextures.push_back(tSquare2_specular);
    std::vector<Texture> sunTextures;
    sunTextures.push_back(tSun);

    // instantiate meshes
	// ------------------
	Cube texturedCube(cubeTextures);
	Cube materialCube(std::vector<Texture>(), &emerald);
	Sphere materialSphere(50, 50, std::vector<Texture>(), &emerald);
	Sphere sunMesh(50, 50, sunTextures);

	// load models
	// -----------
	Model ship(srcPath + "mesh/models/backpack/backpack.obj");

	// lighting options
	// ----------------
	glm::vec3 lightColor(1.0f);
	glm::vec3 lDiffuse = lightColor * glm::vec3(0.8f);
	glm::vec3 lAmbient = lDiffuse * glm::vec3(0.2f);
	glm::vec3 lSpecular(1.0f, 1.0f, 1.0f);

	//start velocity
	player.YV(-5);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(currentCamera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = currentCamera->GetViewMatrix();
		
		player.AddForce(-player.X()/2,-player.Y()/2);
		player.Update();
		player.ResetA();
		// configuring the light source shader and meshes
		// ----------------------------------------------
		lightSourceShader.use();
		lightSourceShader.setMat4("projection", projection);
		lightSourceShader.setMat4("view", view);
		// the sun is the source light here
		sunMesh.worldPosition = glm::vec3(cos(glfwGetTime()) * 20.0f, sin(glfwGetTime()) * 20.0f, 4.0f);
		sunMesh.scale = glm::vec3(10.0f);
		sunMesh.Draw(&lightSourceShader);

		// configuring textureShader to draw textured meshes
		// -------------------------------------------------
		textureShader.use();
		textureShader.setVec3("light.position", sunMesh.worldPosition);
		textureShader.setVec3("light.ambient", lAmbient);
		textureShader.setVec3("light.diffuse", lDiffuse);
		textureShader.setVec3("light.specular", lSpecular);
		textureShader.setVec3("viewPos", currentCamera->Position);
		textureShader.setMat4("projection", projection);
		textureShader.setMat4("view", view);

		texturedCube.Draw(&textureShader);
		ship.worldPosition = glm::vec3(0.0f, 2.0f, 0.0f);
		ship.Draw(&textureShader);

		// configuring materialShader to draw untextured meshes
		// ----------------------------------------------------
		materialShader.use();
		materialShader.setVec3("light.position", sunMesh.worldPosition);
		materialShader.setVec3("light.ambient", lAmbient);
		materialShader.setVec3("light.diffuse", lDiffuse);
		materialShader.setVec3("light.specular", lSpecular);
		materialShader.setVec3("viewPos", currentCamera->Position);
		materialShader.setMat4("projection", projection);
		materialShader.setMat4("view", view);

		materialCube.worldPosition = glm::vec3(2.0f, 0.0f, 0.0f);
		materialCube.Draw(&materialShader);
		materialSphere.worldPosition = glm::vec3(-2.0f, 0.0f, 0.0f);
		materialSphere.Draw(&materialShader);
		

		//*Imgui 3/4
		ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
		
		ImGui::Begin("driftEngin",0,ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::Text("player X:%f",player.X());
		ImGui::Text("player Y:%f",player.Y());
		ImGui::Text("player XV:%f",player.XV());
		ImGui::Text("player YV:%f",player.YV());
		ImGui::Text("player Speed:%f",player.V());

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		//*/

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//*Imgui 4/4
	ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
	//*/

	// glfw: terminate, clearing all previously allocated GLFW resources
	// -----------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// processing input every frame (long press)
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (freeMode)	{ freecam.ProcessKeyboard(FORWARD, deltaTime); }
		//else			{ player.ProcessKeyboard(playerUP, deltaTime); }
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (freeMode)	{ freecam.ProcessKeyboard(BACKWARD, deltaTime); }
		//else			{ player.ProcessKeyboard(playerDOWN, deltaTime); }
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if (freeMode)	{ freecam.ProcessKeyboard(LEFT, deltaTime); }
		//else			{ player.ProcessKeyboard(playerLEFT, deltaTime); }
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if (freeMode)	{ freecam.ProcessKeyboard(RIGHT, deltaTime); }
		//else			{ player.ProcessKeyboard(playerRIGHT, deltaTime); }
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions
	glViewport(0, 0, width, height);
}

// processing unique input (simple press)
// --------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_N && action == GLFW_PRESS)
	{
		freeMode = !freeMode;
		if (freeMode) 	{ currentCamera = &freecam; }
		//else			{ currentCamera = &player.camera; }
	}
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if(firstMouse) // initially set to true
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	freecam.ProcessMouseMovement(xoffset, yoffset);
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	freecam.ProcessMouseScroll(yoffset);
}