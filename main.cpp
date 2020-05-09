//* Imgui 1/4
#include "includes/imgui/imgui.h"
#include "includes/imgui/imgui_impl_glfw.h"
#include "includes/imgui/imgui_impl_opengl3.h"
//*/

#include "init.h"

#include "actors/camera/freecam.h"
#include "actors/player.h"

#include "shaders/shader.h"

#include "mesh/mesh.h"
#include "mesh/sphere.h"
#include "mesh/cube.h"

#include "model/model.h"

// Simple process to switch between Matthew's and Nathan's directories
// -------------------------------------------------------------------
#define N
//#define M
#if defined(N)
	#define PWD "/home/rakl/Repository/spaceProject/dirftEngin/driftEngin/"
#elif defined(M)
	#define PWD "/home/melon/driftEngin"
#endif


// path variables
// --------------
std::string srcPath = PWD;
std::string vShadersPath = srcPath + "shaders/vertex/";
std::string fShadersPath = srcPath + "shaders/fragment/";
std::string texturesPath = srcPath + "mesh/textures/";
std::string modelsPath = srcPath + "model/models/"

// camera variables
// ----------------
Freecam freecam(glm::vec3(0.0f, 7.0f, 10.0f));
Camera *currentCamera = &freecam; // starting the game with freecam
bool freecamMode = true;
// variables to manipulate camera with mouse
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// player variables
// ----------------
Player player;

// timing variables
// ----------------
float deltaTime = 0.0f;
float lastFrame = 0.0f;


int main(int argc, char **argv)
{
	// initialize glfw
	// ---------------
	GLFWwindow* window = init();

	//* Imgui 2/4
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	//*/

	stbi_set_flip_vertically_on_load(true); // make textures to be flipped (we have to do this, otherwise textures will be messed up)

	// build and compile our shader programs
	// -------------------------------------
	Shader textureShader((vShadersPath + "textureShader.vs").c_str(), (fShadersPath + "textureShader.fs").c_str());
	Shader materialShader((vShadersPath + "materialShader.vs").c_str(), (fShadersPath + "materialShader.fs").c_str());
	Shader lightSourceShader((vShadersPath + "lightSourceShader.vs").c_str(), (fShadersPath + "lightSourceShader.fs").c_str());

	// adding our textures
	// -------------------
	Texture tSquare;
	tSquare.path = "square/square.png";
	tSquare.id = TextureFromFile(texturesPath + tSquare.path, srcPath);
	tSquare.type = "texture_diffuse";

	Texture tSquare2;
	tSquare2.path = "square2/square2.png";
	tSquare2.id = TextureFromFile(texturesPath + tSquare2.path, srcPath);
	tSquare2.type = "texture_diffuse";

	Texture tSquare2_specular;
	tSquare2_specular.path = "square2/square2_specular.png";
	tSquare2_specular.id = TextureFromFile(texturesPath + tSquare2_specular.path, srcPath);
	tSquare2_specular.type = "texture_diffuse";

	Texture tSun;
	tSun.path = "sun/sun.jpg";
	tSun.id = TextureFromFile(texturesPath + tSun.path, srcPath);
	tSun.type = "texture_diffuse";

	// adding our materals
	// -------------------
	Material emerald;
	emerald.ambient = glm::vec3(0.0215f, 0.1745f, 0.0215f);
	emerald.diffuse = glm::vec3(0.07568f, 0.61424f, 0.07568f);
	emerald.specular = glm::vec3(0.633f, 0.727811f, 0.633f);
	// TODO: Import new materials from www.devernay.free.fr/cours/opengl/materials.html

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

	// initializing the player
	// -----------------------
	player.loadModel(modelsPath + "sputnik/sputnik1.obj");
	player.YV(-5); // starting velocity

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

		// configuring the light source shader and meshes
		// ----------------------------------------------
		lightSourceShader.use();
		lightSourceShader.setMat4("projection", projection);
		lightSourceShader.setMat4("view", view);

		sunMesh.Draw(&lightSourceShader, glm::vec3(0.0f), glm::vec3(8.0f));

		// configuring the texture shader and meshes
		// -----------------------------------------
		textureShader.use();
		textureShader.setMat4("projection", projection);
		textureShader.setMat4("view", view);
		textureShader.setVec3("light.position", glm::vec3(0.0f));
		textureShader.setVec3("light.ambient", lAmbient);
		textureShader.setVec3("light.diffuse", lDiffuse);
		textureShader.setVec3("light.specular", lSpecular);
		textureShader.setVec3("viewPos", currentCamera->worldPosition);

		texturedCube.Draw(&textureShader);

		player.AddForce(-player.X()/2, -player.Y()/2);
		player.Update();
		player.ResetA();
		player.worldPosition.x = player.X();
		player.worldPosition.y = player.Y();
		player.Draw(&textureShader);

		// configuring the material shader and meshes
		// ------------------------------------------
		materialShader.use();
		materialShader.setMat4("projection", projection);
		materialShader.setMat4("view", view);
		materialShader.setVec3("light.position", glm::vec3(0.0f));
		materialShader.setVec3("light.ambient", lAmbient);
		materialShader.setVec3("light.diffuse", lDiffuse);
		materialShader.setVec3("light.specular", lSpecular);
		materialShader.setVec3("viewPos", currentCamera->worldPosition);


		//* Imgui 3/4
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("driftEngin", 0, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Hello World!");
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		//*/

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//* Imgui 4/4
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
// -----------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (freecamMode)	{ freecam.ProcessKeyboard(FORWARD, deltaTime); }
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (freecamMode)	{ freecam.ProcessKeyboard(BACKWARD, deltaTime); }
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if (freecamMode)	{ freecam.ProcessKeyboard(LEFT, deltaTime); }
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if (freecamMode)	{ freecam.ProcessKeyboard(RIGHT, deltaTime); }
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
		freecamMode = !freecamMode;
		if (freeMode)	{ currentCamera = &freecam; }
		else			{ currentCamera = &player.camera; }
	}
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
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