#include "player.h"

Player::Player(glm::vec3 position): MovementSpeed(PLAYER_SPEED)
{
	this->Position = position;
	camera.updateCameraVectors(this->Position);
	point.InitTime();
	point.X(this->Position.x);
	point.Y(this->Position.z);
}

void Player::draw(Shader* shader, Texture* texture)
{
	point.Update();
	Position.x = point.X();
	Position.z = point.Y();


	Cube cube;
	cube.draw(Position, glm::vec4(1.0f), MODE_TEX1, shader, texture, 1);
	glDeleteVertexArrays(1, &cube.m_VAO);
	glDeleteBuffers(1, &cube.m_VBO);
	camera.updateCameraVectors(Position);
}

void Player::ProcessKeyboard(Player_Movement direction, float deltaTime)
{
	if (direction == playerUP)
	{
		point.YA(10);
	}
	if (direction == playerDOWN)
	{
		point.YA(-10);
	}
	if (direction == playerLEFT)
	{
		point.XA(10);
	}
	if (direction == playerRIGHT)
	{
		point.XA(-10);
	}

	point.Update();
	Position.x = point.X();
	Position.z = point.Y();
	point.ResetA();
	camera.updateCameraVectors(Position);
}