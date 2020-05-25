#ifndef PLAYER_H
#define PLAYER_H

// including what we need from our engine
#include "ENG/includes/glm/glm.hpp"
#include "ENG/includes/glm/gtc/matrix_transform.hpp"
#include "ENG/camera/camOrt.h"
#include "ENG/shaders/shader.h"
#include "ENG/model/model.h"
#include "ENG/objects/phyx.h"
#include "ENG/objects/kldr.h"
#include "ENG/objects/ctrl.h"
#include "ENG/objects/rndr.h"

#include <locale> // used to format the score with imbue (10000 -> 10,000)

// forward declarations
// --------------------
class Asteroid;

// player class
// ------------
class Player : public PhyxObj2D, public InputObj, public RenderObj
{
public:
	CamOrt camera; // orthogonal camera
	glm::vec3 Direction; // directionnal vector
	Asteroid* target; // the targeted asteroid
	bool thrusting; // if the player's thrusters are active or not
	int score; // player's score

	// constructor
	Player();
	// input functions
	void inputCallback(GLFWwindow* window) override; // used for long keyboard press
	void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override; // used for simple keyboard press
	// gui function
	void gui(GLFWwindow* window);
};

// shield class
// ------------
struct Animation
{
	bool isAnimating;
	float start; // store the starting time of the animation
};

class Shield : public PhyxObj2D, public RenderObj
{
public:
	float size;
	int lifePoints;
	Animation animation;

	// constructor
	Shield(float);
	// shield functions
	void startAnimation(GLFWwindow* window); // begin an animation
	void Update(GLFWwindow* window); // update shield's animation
	// gui function
	void gui(GLFWwindow* window);
};

#endif