#pragma once

#include <string>
#include <SDL.h>
#include <GL/glew.h>
#include <iostream>

#include "Camera.h"
#include "Transform.h"
#include "Player.h" // Temporary for speed of handling input

using namespace std;
enum CameraViewPorts // Current viewport for camera
{
	STANDARD,
	FOLLOWBALL,
	PADDLE1,
	PADDLE2
};
class Display
{
public:
	Display(GLint width, GLint height, const std::string& title);

	GLvoid Clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	GLvoid Update(float deltaTime, Camera& camera, Player& player); // Swaps between the window buffers to update the display
	GLboolean IsWindowClosed(); // Returns whether or not the window is closed
	static GLfloat gameSpeed; // Speed of the game
	static GLfloat cooldownTimer[2]; // Current timers
	static GLfloat cooldownActive[2]; // Whether or not the cool down is active
	GLboolean m_perspective; // Whether the camera is perspective
	GLboolean m_cameraMode; // Whether the camera should be controlled or static. False is paddle control and true is Camera control
	virtual ~Display();

	CameraViewPorts m_viewPort;

	SDL_Window* m_window;
	SDL_GLContext m_glContext; // OpenGL Context for use with drawing in the Window
	GLboolean m_isWindowClosed;

	GLboolean KEYS[322]; // Keyboard handling

	
};

//#include <SDL.h>
//#include <iostream>
//#include <string>
//#include <algorithm>
//#include <GL/glew.h>
//using namespace std;
//class Display
//{
//public:
//	Display(GLint width, GLint height, const std::string& title);
//	virtual ~Display();
//	void CreateWindow(GLint width, GLint height, const std::string& title); // Creates an SDL Window
//	void CreateContext(); // Creates an OpenGL Context
//	void CleanUp(); // Clean up context
//	void SetGLAttributes();
//	void InitGlew();
//	void Clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
//
//
//	std::string m_exeName;
//	SDL_Window *m_pWin; // Pointer to the SDL_Window
//	SDL_GLContext m_context; //the SDL_GLContext
//	
//};

