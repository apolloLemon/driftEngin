//#include "imgui/imgui.h"
//#include "imgui/imgui_impl_glfw.h"
//#include "imgui/imgui_impl_opengl3.h"

#include "init.h" // initialize function prototypes

#include "camera/freecam.h"
#include "shaders/shader.h"
#include "meshtest/mesh.h"
#include "meshtest/model.h"
#include "meshtest/cube.h"
#include "meshtest/sphere.h"
//#include "meshes/cube.h"
//#include "meshes/sphere.h"
//#include "player.h"

//#include "utilities/perlin.h"
//#include <vector>

#include <iostream>

#define N
//#define M
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

//Player player(glm::vec3(6.0f, 0.0f, 0.0f));

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

	/*
	//GUI
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    //*/

    stbi_set_flip_vertically_on_load(true);

	// build and compile our shader program
	// ------------------------------------
	Shader ourShader((shadersPath+"shader.vs").c_str(), (shadersPath+"shader.fs").c_str());

    // adding our textures
    // -------------------------
    std::vector<Texture> cubeTextures;
    Texture cubeTexture;
    cubeTexture.id = TextureFromFile("textures/square2.png", srcPath);
    cubeTexture.type = "texture_diffuse";
    cubeTexture.path = "textures/square.png";
    cubeTextures.push_back(cubeTexture);

    std::vector<Texture> sphereTextures;
    Texture sphereTexture;
    sphereTexture.id = TextureFromFile("textures/square.png", srcPath);
    sphereTexture.type = "texture_diffuse";
    sphereTexture.path = "textures/square.png";
    sphereTextures.push_back(sphereTexture);

    // instantiate meshes
	// ------------------
	Cube cube(sphereTextures);
	Sphere sphere(10, 10, cubeTextures);
	Cube cube2(cubeTextures);

	// load models
	// -----------
	Model ship(srcPath + "meshtest/backpack/backpack.obj");

	//start velocity
	player.point.YV(-5);

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

		// activate shader
		ourShader.use();

		// pass projection matrix to shader
		glm::mat4 projection = glm::perspective(glm::radians(currentCamera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);

		// camera/view transformation
		glm::mat4 view = currentCamera->GetViewMatrix();
		ourShader.setMat4("view", view);

		//int matx = -3.0f, natx = 0.0f, shipx = 3.0f;
		//matthew.draw(glm::vec3(matx, 0.0f, a.Get(matx)*3), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), MODE_COLOR, &ourShader, &texture, 0.0f, 0.0f, 1.0f, glm::vec4(0.3f, 1.0f, 1.0f, 1.0f));
		//nathan.draw(glm::vec3(natx, 0.0f, a.Get(natx)*3), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), MODE_COLOR, &ourShader, &texture, 0.0f, 0.0f, 1.0f, glm::vec4(0.3f, 1.0f, 1.0f, 1.0f));
		/*		
		for(int i=-3;i<=3;i++)
			for(int j=-3;j<=3;j++)
				if ((i*i + j*j) <= 9)
					cube.draw(glm::vec3(i, a.Noise(i,j), j), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),  MODE_TEX1, &ourShader, &texture, ((a.Noise(i,j)>0.5)?0:1));

		player.point.AddForce(-player.point.X()/2,-player.point.Y()/2);
		player.point.Update();
		player.point.ResetA();
		player.draw(&ourShader, &texture);
		//*/
		cube.Draw(&ourShader);
		sphere.worldPosition = glm::vec3(2.0f, 0.0f, 0.0f); 
		sphere.Draw(&ourShader);
		cube2.worldPosition = glm::vec3(-2.0f, 0.0f, 0.0f);
		cube2.Draw(&ourShader); 

		ship.worldPosition = glm::vec3(0.0f, 4.0f, 0.0f);
		ship.Draw(&ourShader);

		///*
		ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
		
		ImGui::Begin("driftEngin",0,ImGuiWindowFlags_AlwaysAutoResize);
//		ImGui::Text("player X:%f",player.point.X());
//		ImGui::Text("player Y:%f",player.point.Y());
//		ImGui::Text("player XV:%f",player.point.XV());
//		ImGui::Text("player YV:%f",player.point.YV());
//		ImGui::Text("player Speed:%f",player.point.V());
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		//*/

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	///*
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