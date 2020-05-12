#include "player.h"

Player::Player(glm::vec3 position): MovementSpeed(PLAYER_SPEED)
{
	worldPosition = position;
	Direction.x = sin(glm::radians(rotation.y));
	Direction.y = 0.0f;
	Direction.z = cos(glm::radians(rotation.y));
	Direction = glm::normalize(Direction);
	camera.updateCameraVectors(worldPosition, Direction);
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
	float velocity = MovementSpeed * deltaTime;
	if (direction == playerUP)
	{
		worldPosition += (Direction * velocity);
	}
	if (direction == playerDOWN)
	{
		worldPosition -= (Direction * velocity);
	}
	if (direction == playerLEFT)
	{
		rotation.y += 1.0f;
	}
	if (direction == playerRIGHT)
	{
		rotation.y -= 1.0f;
	}

	Direction.x = sin(glm::radians(rotation.y));
	Direction.y = 0.0f;
	Direction.z = cos(glm::radians(rotation.y));
	Direction = glm::normalize(Direction);

	camera.updateCameraVectors(worldPosition, Direction);
}