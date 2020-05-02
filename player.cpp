#include "player.h"

Player::Player(glm::vec3 position): MovementSpeed(PLAYER_SPEED)
{
	this->Position = position;
	camera.updateCameraVectors(this->Position);
}

void Player::draw(Shader* shader, Texture* texture)
{
	Cube cube;
	cube.draw(Position, glm::vec4(1.0f), MODE_TEX1, shader, texture, 1);
	glDeleteVertexArrays(1, &cube.m_VAO);
	glDeleteBuffers(1, &cube.m_VBO);
	camera.updateCameraVectors(Position);
}

void Player::ProcessKeyboard(Player_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == playerUP)
	{
		Position.z += velocity;
		camera.updateCameraVectors(Position);
	}
	if (direction == playerDOWN)
	{
		Position.z -= velocity;
		camera.updateCameraVectors(Position);
	}
	if (direction == playerLEFT)
	{
		Position.x += velocity;
		camera.updateCameraVectors(Position);
	}
	if (direction == playerRIGHT)
	{
		Position.x -= velocity;
		camera.updateCameraVectors(Position);
	}
}