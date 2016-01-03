#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <SDL.h>
#include <glm\glm.hpp>
#include "Shader.h"
#include "Display.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include <time.h>
#include "Player.h"
#include "Invader.h"
#include "GameObject.h"
#include "Square.h"

#define MAX_CONTROLLERS 4
SDL_GameController *ControllerHandles[MAX_CONTROLLERS]; 

using namespace std;

void HandleInput(float deltaTime, Camera camera)
{
	SDL_Event event; // Used for storing the SDL event

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		
		{
			printf("entered switch detected\n");
		case SDL_KEYUP:
			//camera.MoveForward(deltaTime);
			printf("Key press detected\n");
			break;
		}
	}
}

double lastElapsedTime = SDL_GetTicks() - 1, deltaTime = 0.0f;
// Calculate Deltatime
void CalculateDelta()
{
	double elapsedTime = SDL_GetTicks();
	deltaTime = (elapsedTime / lastElapsedTime) / 1000.0f;
	lastElapsedTime = elapsedTime;
}


int main( int argc, char* args[] )
{	
	srand(time(NULL));

	Display display(800, 600, "Space Invaders");

	int maxJoysticks = SDL_NumJoysticks();
	int controllerIndex = 0;
	for (int joystickIndex = 0; joystickIndex < maxJoysticks; ++joystickIndex)
	{
		if (!SDL_IsGameController(joystickIndex))
		{
			continue;
		}
		if (controllerIndex >= MAX_CONTROLLERS)
		{
			break;
		}
		ControllerHandles[controllerIndex] = SDL_GameControllerOpen(joystickIndex);
		controllerIndex++;
	}

	const GLint INVADER_ROWS = 5; // Amount of rows of invaders 
	const GLint INVADERS_PER_ROW = 11; // Amount of Invaders per row

	GLuint invaderGrid[INVADER_ROWS][INVADERS_PER_ROW]
	{
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0}
	};
	
	
	Player player;
	Square score;
	score.texture = new Texture("./assets/OpenSans-Regular.ttf", TextureType::Font, "Bob came to town");
	score.transform.SetScale(glm::vec3( 0.3f,0.3f,0.3f ));

	for (GLint r = 0; r < INVADER_ROWS; r++)
	{
		for (GLint c = 0; c < INVADERS_PER_ROW; c++)
		{
			Invader* temp = new Invader();
			temp->transform.GetPos().y = 0.9f - (0.14 * r);
			temp->transform.GetPos().x = -0.7f + (0.14 * c);
			temp->transform.SetScale(glm::vec3(.1f, .05f, .1f));
		}
	}

	player.transform.GetPos().y = -0.7f;
	player.transform.SetScale(glm::vec3(.1f, .05f, .1f));
	
	Transform paddle2Transform; //  Transformations
	
	//Camera perspectiveCamera(glm::vec3(0.f, 0.f, 2.f), 70.f, (float)800.f / (float)600.f, 0.1f, 10000.0f);
	Camera orthographicCamera(glm::vec3(0.f, 0.f, 3.f), -1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

	Camera renderCamera = orthographicCamera; // Default camera for rendering scene

	const GLfloat COOLDOWN_INTERVAL = 30.0f; // How long to wait
	GLfloat cooldownTimer = 0.0f; // Current timer
	GLfloat coolDownActive = false; // Whether or not the cool down is active
	GLfloat gameSpeed = 1.0f; // Speed of the game

	GLint scoreCounter = 0;

	bool moveRight = true; // Whether the invaders should move right
	bool moveLeft = false; // Whether to move left
	bool moveDown = false;
	while (!display.IsWindowClosed()) /// While the window is open
	{
		display.Clear(0.0f, 0.0f, 0.0f, 0.0f); // Clear the screen to black

		CalculateDelta(); // Calculate deltaTime from how long it took between frames
		deltaTime *= gameSpeed;
		scoreCounter++;
		delete score.texture;
		score.texture = new Texture("./assets/OpenSans-Regular.ttf", TextureType::Font, "Score: " + std::to_string(scoreCounter));

		for (int ControllerIndex = 0;
		ControllerIndex < MAX_CONTROLLERS;
			++ControllerIndex)
		{
			if (ControllerHandles[ControllerIndex] != 0 && SDL_GameControllerGetAttached(ControllerHandles[ControllerIndex]))
			{
				// NOTE: We have a controller with index ControllerIndex.
				bool Up = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_UP);
				bool Down = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_DOWN);
				bool Left = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_LEFT);
				bool Right = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
				bool Start = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_START);
				bool Back = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_BACK);
				bool LeftShoulder = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
				bool RightShoulder = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
				bool AButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_A);
				bool BButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_B);
				bool XButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_X);
				bool YButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_Y);

				int StickX = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex], SDL_CONTROLLER_AXIS_LEFTX);
				int StickY = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex], SDL_CONTROLLER_AXIS_LEFTY);

				if (StickX > 10000)
				{
					if (((player.transform.GetPos().x + 0.1f) + deltaTime * player.speed) <= 1)
						player.transform.GetPos().x += deltaTime * player.speed;
				}
				else if (StickX < -10000)
				{
					if (((player.transform.GetPos().x - 0.1f) - deltaTime * player.speed) >= -1)
						player.transform.GetPos().x -= deltaTime * player.speed;
				}

				if (Down)
				{
					//if (((player.transform.GetPos().y - 0.1f) - deltaTime * player.speed) >= -1)
						//player.transform.GetPos().y -= deltaTime * player.speed;
					gameSpeed-= 0.1f;
					if (gameSpeed < 0)
						gameSpeed = 0;
					cout << gameSpeed << endl;
				}
				else if (Up)
				{
					//if (((player.transform.GetPos().y + 0.1f) + deltaTime * player.speed) <= 1)
						//player.transform.GetPos().y += deltaTime * player.speed;
					gameSpeed += 0.1f;
					if (gameSpeed > 5)
						gameSpeed = 5;

					cout << gameSpeed << endl;
					
				}

				if (Start)
				{
					if (gameSpeed == 0) // Already paused
						gameSpeed = 1;
					else
						gameSpeed = 0;
				}

				
				if (AButton)
				{
					if (!coolDownActive)
					{
						player.Fire(BulletDirection::UP);
						coolDownActive = true; // Make the cool down active
					}
				}

				if (coolDownActive)
				{
					cooldownTimer++; // Increase the cooldown timer

					if (cooldownTimer >= COOLDOWN_INTERVAL) // Whether cooldown has elapsed
					{
						cooldownTimer = 0.0f; // Reset timer
						coolDownActive = false; // Turn cooldown off
					}
				}
			}
			else
			{
				// TODO: This controller is note plugged in.
			}
		}

		// Draw and Update all objects
		for (std::vector<int>::size_type i = 0; i != GameObject::gameObjects.size(); i++)
		{
			if (GameObject::gameObjects[i]->m_type == GameObjectType::invader)
			{
				Invader* invader = (Invader*)GameObject::gameObjects[i];
				
				if (moveRight)
				{
					if (invader->transform.GetPos().x + (invader->speed * deltaTime) >= 1.0f)
					{
						invader->transform.GetPos().x += (invader->speed * deltaTime);
						moveRight = false;
						moveDown = true;
					}
						
					else
						invader->transform.GetPos().x += (invader->speed * deltaTime);
				}
				else
				{
					if (invader->transform.GetPos().x - (invader->speed * deltaTime) <= -1.0f)
					{
						invader->transform.GetPos().x += (invader->speed * deltaTime);
						moveRight = true;
						moveDown = true;
					}
						
					else
						invader->transform.GetPos().x -= (invader->speed * deltaTime);
				}
					
			}
			

			// Draw and update all game models 
			GameObject::gameObjects[i]->Draw(renderCamera); // BUG: Must draw before updating otherwise a crash will occur
			GameObject::gameObjects[i]->Update(deltaTime);

			if (i >= GameObject::gameObjects.size()) // Break the loop if an object is destroyed and the index is now invalid
				break;
		}		

		// Move invaders down
		for (std::vector<int>::size_type i = 0; i != GameObject::gameObjects.size(); i++)
		{
			if (GameObject::gameObjects[i]->m_type == GameObjectType::invader)
			{
				Invader* invader = (Invader*)GameObject::gameObjects[i];
				if (moveDown)
				{
					for (int y = 0; y < 2; y++)
					{
						invader->transform.GetPos().y -= y * 0.1f;
					}
				}
			}
		}


		moveDown = false;
		renderCamera.Update();
		display.Update(deltaTime, renderCamera); // Update the display
	}

	for (int ControllerIndex = 0; ControllerIndex < MAX_CONTROLLERS; ++ControllerIndex)
	{
		if (ControllerHandles[ControllerIndex])
		{
			SDL_GameControllerClose(ControllerHandles[ControllerIndex]);
		}
	}

	SDL_Quit();

	// Free memory
//	invaders.empty();

	return 0;
}

