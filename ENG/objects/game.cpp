#include "game.h"


Game::Game(unsigned int width, unsigned int height, std::string tPath, std::string mPath)
{
	this->screenWidth = width;
	this->screenHeight = height;

	this->srcPath = PWD;
	this->vShadersPath = srcPath + "ENG/shaders/vertex/";
	this->fShadersPath = srcPath + "ENG/shaders/fragment/";
	this->texturesPath = srcPath + tPath;
	this->modelsPath =	 srcPath + mPath;

	this->lastX = width / 2.0f;
	this->lastY = height / 2.0f;
	this->firstMouse = true;
	SoundENG = irrklang::createIrrKlangDevice();
}

GLFWwindow* Game::Initialize()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "driftENG", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell glfw to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Faild to initialize GLAD." << std::endl;
		glfwTerminate();
	}
	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader programs
	// -------------------------------------
	textureShader = new Shader((vShadersPath + "textureShader.vs").c_str(), (fShadersPath + "textureShader.fs").c_str());
	materialShader = new Shader((vShadersPath + "materialShader.vs").c_str(), (fShadersPath + "materialShader.fs").c_str());
	lightSourceShader = new Shader((vShadersPath + "lightSourceShader.vs").c_str(), (fShadersPath + "lightSourceShader.fs").c_str());
	skyboxShader = new Shader((vShadersPath + "skyboxShader.vs").c_str(), (fShadersPath + "skyboxShader.fs").c_str());

	//* Imgui 2/4
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	//*/

	glfwSetWindowUserPointer(window, this);

	this->inputENG.Init(&gameobjects);
	this->phyxENG.Init(&gameobjects,SoundENG);
	return window;
}

void Game::displayImGui()
{
	//* Imgui 3/4
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("driftEngin", 0, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("player XV:%f", dynamic_cast<PhyxObj2D*>(gameobjects[0])->XV());
	ImGui::Text("player YV:%f", dynamic_cast<PhyxObj2D*>(gameobjects[0])->YV());
	ImGui::Text("player Speed:%f", dynamic_cast<PhyxObj2D*>(gameobjects[0])->Speed());
	ImGui::Text("planet2 Speed:%f", dynamic_cast<PhyxObj2D*>(gameobjects[2])->Speed());
	ImGui::Text("\n");
	ImGui::Text("player GameObj xpos:%f", dynamic_cast<PhyxObj2D*>(gameobjects[0])->worldPosition.x);
	ImGui::Text("player GameObj ypos:%f", dynamic_cast<PhyxObj2D*>(gameobjects[0])->worldPosition.z);

	//ImGui::Text("player  xG:%f", g.x);
	//ImGui::Text("player  yG:%f", g.y);

	ImGui::Text("player in Sun:%d", dynamic_cast<PhyxObj2D*>(gameobjects[1])->collider.isin(dynamic_cast<PhyxObj2D*>(gameobjects[0])->collider));
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//*/
}

void Game::Terminate()
{
	//* Imgui 4/4
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	//*/
	SoundENG->drop();
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
	// make sure the viewport matches the new window dimensions
	glViewport(0, 0, width, height);
	game->screenWidth = width;
	game->screenHeight = height;
}

// processing unique input (simple press)
// --------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
	game->inputENG.Update(window, key, scancode, action, mods);

	if (key == GLFW_KEY_N && action == GLFW_PRESS)
	{
		if (game->cameraMode == FREECAM_MODE)
		{
			for (auto go : game->gameobjects)
			{
				Player* cast = dynamic_cast<Player*>(go);
				if(cast) { game->currentCamera = &cast->camera; break; }
			}
			game->cameraMode = ORTCAM_MODE;
		}
		else if (game->cameraMode == ORTCAM_MODE)
		{
			game->currentCamera = game->freecam;
			game->cameraMode = FREECAM_MODE;
		}
		
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)	{ glfwSetWindowShouldClose(window, true); }
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));

	if (game->firstMouse)
	{
		game->lastX = xpos;
		game->lastY = ypos;
		game->firstMouse = false;
	}

	float xoffset = xpos - game->lastX;
	float yoffset = game->lastY - ypos; // reversed since y-coordinates range from bottom to top
	game->lastX = xpos;
	game->lastY = ypos;

	if (game->cameraMode == FREECAM_MODE)
		game->freecam->ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
	if (game->cameraMode == FREECAM_MODE)
		game->freecam->ProcessMouseScroll(yoffset);
}