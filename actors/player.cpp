#include "player.h"

Player::Player(glm::vec3 position)
{
	worldPosition = position;
	camera.updateCameraVectors(this->worldPosition);
	InitTime();
}

/*/
void Player::draw(Shader* shader)
{
	worldPosition.x = X();
	worldPosition.z = Y();

	//Cube cube;
	//cube.draw(worldPosition, glm::vec4(1.0f), MODE_TEX1, shader, texture, 1);
	//glDeleteVertexArrays(1, &cube.m_VAO);
	//glDeleteBuffers(1, &cube.m_VBO);
	camera.updateCameraVectors(worldPosition);
}
//*/

void Player::ProcessKeyboard(Player_Movement direction, float deltaTime)
{
	if (direction == playerUP)
	{
		AddForce(0,1);
	}
	if (direction == playerDOWN)
	{
		AddForce(0,-1);
	}
	if (direction == playerLEFT)
	{
		AddForce(1,0);
	}
	if (direction == playerRIGHT)
	{
		AddForce(-1,0);
	}

	//camera.updateCameraVectors(Position);
}