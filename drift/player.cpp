#include "player.h"

Player::Player(glm::vec3 position): MovementSpeed(PLAYER_SPEED)
{
	worldPosition = position;
	camera.updateCameraVectors(worldPosition);
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
	float velocity = MovementSpeed * deltaTime;
	if (direction == playerUP)
	{
		AddForce(glm::vec2(0,1));
	}
	if (direction == playerDOWN)
	{
		AddForce(glm::vec2(0,-1));
	}
	if (direction == playerLEFT)
	{
		AddForce(glm::vec2(1,0));
	}
	if (direction == playerRIGHT)
	{
		AddForce(glm::vec2(-1,0));
	}

	//camera.updateCameraVectors(worldPosition);
}