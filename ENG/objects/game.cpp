#include "game.h"


Game::Game(unsigned int width, unsigned int height, std::string tPath, std::string mPath, std::string sPath)
{
	this->screenWidth = width;
	this->screenHeight = height;

	this->srcPath = PWD;
	this->vShadersPath = srcPath + "ENG/shaders/vertex/";
	this->fShadersPath = srcPath + "ENG/shaders/fragment/";
	this->texturesPath = srcPath + tPath;
	this->modelsPath = srcPath + mPath;
	this->soundsPath = srcPath + sPath;

	this->lastX = width / 2.0f;
	this->lastY = height / 2.0f;
	this->firstMouse = true;
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

	this->collENG.Init(&gameobjects);
	this->inputENG.Init(&gameobjects);
	this->phyxENG.Init(&gameobjects,&collENG, &soundENG);
	return window;
}



void Game::phyxGui()
{

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("driftEngine", 0, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Phyx/s: %f",phyxENG.fps);
	static bool showPhyxSettings = false;
	if (ImGui::Button("Show Phyx Settings")) showPhyxSettings = !showPhyxSettings;

	static bool showPhyxObj = false;
	if (ImGui::Button("Show PhyxObj2D Data")) showPhyxObj = !showPhyxObj;

	static bool setPhyxObj = false;
	if (ImGui::Button("Set PhyxObj2D Data")) setPhyxObj = !setPhyxObj;

	if(showPhyxSettings){
		ImGui::Begin("Phyx Settings", 0, ImGuiWindowFlags_AlwaysAutoResize);
		static double ts = phyxENG.timescale;
		ImGui::InputDouble("##ts", &ts, 0.01f, 1.0f, "%.8f");
		if (ImGui::Button("Time Scale Set / Play")) phyxENG.timescale = ts;
		ImGui::SameLine();
		if (ImGui::Button("pause")) phyxENG.timescale = 0;

		static float ggravity = phyxENG.G;
		ImGui::InputFloat("G", &ggravity, 0.01f, 1.0f, "%.8f");
		if (ImGui::Button("Set G constant")) phyxENG.G = ggravity;

		static double colEl = phyxENG.colEl;
		ImGui::InputDouble("##colEl", &colEl, 0.01f, 1.0f, "%.8f");
		if (ImGui::Button("Set collision elasticity")) phyxENG.colEl = colEl;

//		static bool clipping = ;
		ImGui::Text("%s",((phyxENG.clipping)? "clip":"noclip"));
		if (ImGui::Button("toggle collisions")) phyxENG.clipping = !phyxENG.clipping;

		ImGui::End();
	}

	if(setPhyxObj){
		ImGui::Begin("set obj", 0, ImGuiWindowFlags_AlwaysAutoResize);
		static double m=1;
		static double s=1;
		static double x=0;
		static double y=0;
		static double xv=0;
		static double yv=0;
		ImGui::InputDouble("mass", &m, 0.01f, 1.0f, "%.4f");
		ImGui::InputDouble("scale", &s, 0.01f, 1.0f, "%.4f");
		ImGui::InputDouble("x pos", &x, 0.01f, 1.0f, "%.4f");
		ImGui::InputDouble("y pos", &y, 0.01f, 1.0f, "%.4f");
		ImGui::InputDouble("x speed", &xv, 0.01f, 1.0f, "%.4f");
		ImGui::InputDouble("y speed", &yv, 0.01f, 1.0f, "%.4f");
		if(ImGui::Button("*-1.")){
			x*=-1.; y*=-1.; xv*=-1.; yv*=-1.;
		}
		for(auto go : gameobjects){
			auto po = dynamic_cast<PhyxObj2D*>(go);
			if(po) {
				ImGui::PushID(po);
				ImGui::Text(po->name.c_str());
				ImGui::SameLine();
	/*			if (ImGui::Button("Load###po->name.c_str()[0]")){
					x = po->X();
					y = po->Y();
					xv = po->XV();
					yv = po->YV();
				}*/
				ImGui::SameLine();
				if (ImGui::Button("Set###po->name.c_str()[0]")){
					po->MoveTo(glm::dvec2(x,y));
					po->XV(xv);
					po->YV(yv);
					po->Mass(m);
					po->scale=glm::dvec3(s);
					po->colliders[0]->scale=glm::dvec3(s);
				}
				ImGui::PopID();
			}
		}
		ImGui::End();
	}

	if(showPhyxObj) for(auto go : gameobjects) {
		auto po = dynamic_cast<PhyxObj2D*>(go);
		if(po){
			ImGui::Begin(po->name.c_str(), 0, ImGuiWindowFlags_AlwaysAutoResize);
		//	static char str1[128] = "";
		//	ImGui::InputTextWithHint("input text (w/ hint)", "enter text here", str1, IM_ARRAYSIZE(str1));
			ImGui::Text("Mass:%f", po->Mass());
			ImGui::Text("Position X:%.2f\tY:%.2f", po->X(),po->Y());
			ImGui::Text("Vitesse X:%.2f\tY:%.2f", po->XV(),po->YV());
//			ImGui::InputDouble("input double", &d0, 0.01f, 1.0f, "%.8f");
//			if (ImGui::Button("Set A")) po->Mass(d0);

			ImGui::End();
		}
	}


	ImGui::End();
	
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());	
}

void Game::Terminate()
{
	//* Imgui 4/4
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	//*/
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
//		game->soundENG.Play(1,0);
		if (game->cameraMode == FREECAM_MODE)
		{
			for (auto go : game->gameobjects)
			{
				Player* cast = dynamic_cast<Player*>(go);
				if(cast) { game->currentCamera = &cast->camera; break; }
			}
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			game->cameraMode = ORTCAM_MODE;
		}
		else if (game->cameraMode == ORTCAM_MODE)
		{

			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
	else if (game->cameraMode == ORTCAM_MODE)
	{
		CamOrt* camort = dynamic_cast<CamOrt*>(game->currentCamera);
		camort->ProcessMouseScroll(yoffset);
	}
}