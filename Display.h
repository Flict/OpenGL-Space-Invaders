#pragma once

#include <string>
#include <SDL.h>
#include <GL/glew.h>
#include <iostream>

#include "Camera.h"
#include "Transform.h"

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

	void Clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void Update(float deltaTime, Camera& camera); // Swaps between the window buffers to update the display
	bool IsWindowClosed(); // Returns whether or not the window is closed
	
	bool m_perspective = false; // Whether the camera is perspective
	bool m_cameraMode = false; // Whether the camera should be controlled or static. False is paddle control and true is Camera control
	virtual ~Display();

	CameraViewPorts m_viewPort = STANDARD;
	void operator=(const Display& display) {}
	Display(const Display& display) {}

	SDL_Window* m_window;
	SDL_GLContext m_glContext; // OpenGL Context for use with drawing in the Window
	bool m_isWindowClosed;

	bool KEYS[322]; // Keyboard handling

	
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

