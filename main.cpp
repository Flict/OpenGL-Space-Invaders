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

	
	const GLint INVADER_AMOUNT = 11;
	Player player;	
	Invader invaders[INVADER_AMOUNT];

	for (int i = 0; i < INVADER_AMOUNT; i++)
	{
		invaders[i] = Invader();

		invaders[i].transform.GetPos().y = 0.6f;
		invaders[i].transform.GetPos().x = -0.9f + (0.14 * i);
		invaders[i].transform.SetScale(glm::vec3(.1f, .05f, .1f));
	}
	
	Transform paddle2Transform; //  Transformations
	
	Camera perspectiveCamera(glm::vec3(0.f, 0.f, 2.f), 70.f, (float)800.f / (float)600.f, 0.1f, 10000.0f);
	Camera orthographicCamera(glm::vec3(0.f, 0.f, 3.f), -1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

	Camera renderCamera = orthographicCamera; // Default camera for rendering scene
	
	player.transform.GetPos().y = -0.7f;
	player.transform.SetScale(glm::vec3(.1f, .05f, .1f));

	

	bool moveRight = true; // Whether the invaders should move right
	bool moveLeft = false; // Whether to move left
	bool moveDown = false;
	while (!display.IsWindowClosed()) /// While the window is open
	{
		display.Clear(0.0f, 0.0f, 0.0f, 0.0f); // Clear the screen to black

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

				if (StickY > 10000)
				{
					if (((player.transform.GetPos().y - 0.1f) - deltaTime * player.speed) >= -1)
						player.transform.GetPos().y -= deltaTime * player.speed;
				}
				else if (StickY < -10000)
				{
					if (((player.transform.GetPos().y + 0.1f) + deltaTime * player.speed) <= 1)
						player.transform.GetPos().y += deltaTime * player.speed;
					
				}
					
			}
			else
			{
				// TODO: This controller is note plugged in.
			}
		}
		
		CalculateDelta(); // Calculate deltaTime from how long it took between frames
		
		player.Update(deltaTime);

		
		
		for (int i = 0; i < INVADER_AMOUNT; i++)
		{
			if (moveRight && !moveLeft)
				invaders[i].transform.GetPos().x += deltaTime * invaders[i].speed;	
			else if (!moveRight && moveLeft)
			{
				invaders[i].transform.GetPos().x -= deltaTime * invaders[i].speed;
			}

			if (moveDown)
			{
				for (int j = 0; j < 50; j++)
				{
					invaders[i].transform.GetPos().y -= deltaTime * 1.f;
				}				
			}
				
			invaders[i].Update(deltaTime);
			invaders[i].Draw(renderCamera);

			if (player.aabb.Intersects(player.aabb, invaders[i].aabb))
				cout << "Intersection with invader: " << i << endl;
		}
		moveDown = false;
		
		
		if (moveRight && ((invaders[10].transform.GetPos().x + 0.1f) + deltaTime * invaders[10].speed) >= 1)
		{
			moveRight = false;
			moveDown = true;
			moveLeft = true;
		}
		
		if (moveLeft && ((invaders[0].transform.GetPos().x - 0.1f) - deltaTime * invaders[0].speed) <= -1)
		{
			moveLeft = false;
			moveDown = true;
			moveRight = true;
		}



		player.Draw(renderCamera);
		

		//cout << player.aabb.Intersects(player.aabb, invaders[0].aabb) << endl;

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

	return 0;
}

