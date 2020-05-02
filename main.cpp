#include "init.h" // initialize function prototypes

#include "camera/freecam.h"
#include "meshes/cube.h"
#include "meshes/sphere.h"
#include "player.h"

#include "utilities/perlin.h"
#include <vector>

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

Player player(glm::vec3(0.0f, 0.0f, 0.0f));

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

	// build and compile our shader program
	// ------------------------------------
	Shader ourShader((shadersPath+"shader.vs").c_str(), (shadersPath+"shader.fs").c_str());

    // adding our textures
    // -------------------------
    Texture texture(texturesPath);
    
	texture.add("square.png");
	texture.add("square2.png");
	// tell OpenGL for each sampler to which texture unit it belongs to
	// -------------------------------------------------------------------------------------------
	ourShader.use();
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	ourShader.setVec4("lightColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	Cube matthew;
	Cube nathan;

	std::vector<Cube> cubes;
	for(int i=0;i<10;i++)
		cubes.push_back(Cube());

	std::vector<std::vector<Cube>> cubeplain;
	for(int j=0;j<10;j++)
		cubeplain.push_back(cubes);

	Perlin2D a;

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
		
		for(int i=0;i<10;i++)
			for(int j=0;j<10;j++)
			cubes[i].draw(glm::vec3(i, a.Noise(i,j), j), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),  MODE_TEX1, &ourShader, &texture, ((a.Noise(i,j)>0.5)?0:1));

		player.draw(&ourShader, &texture);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

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
		else			{ player.ProcessKeyboard(playerUP, deltaTime); }
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (freeMode)	{ freecam.ProcessKeyboard(BACKWARD, deltaTime); }
		else			{ player.ProcessKeyboard(playerDOWN, deltaTime); }
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if (freeMode)	{ freecam.ProcessKeyboard(LEFT, deltaTime); }
		else			{ player.ProcessKeyboard(playerLEFT, deltaTime); }
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if (freeMode)	{ freecam.ProcessKeyboard(RIGHT, deltaTime); }
		else			{ player.ProcessKeyboard(playerRIGHT, deltaTime); }
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
		else			{ currentCamera = &player.camera; }
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