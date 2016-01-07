#include "Display.h"
#include "SDL_ttf.h"

GLfloat Display::gameSpeed; // Speed of the game
GLfloat Display::cooldownTimer[2] = { 0.f, 0.f }; // Current timers
GLfloat Display::cooldownActive[2] = { false, false }; // Whether or not the cool down is active

Display::Display(GLint width, GLint height, const std::string& title)
{
	/*if (!TTF_WasInit() && TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(1);
	}*/
	TTF_Init();
	SDL_Init(SDL_INIT_EVERYTHING); // Initialise SDL

								   // Set RGB colour data to 32 bit
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // Number of bits for displaying the colour red
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // Number of bits for displaying the colour green
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); // Number of bits for displaying the colour blue
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // Number of bits for displaying the colour alpha

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); // How many bits to allocate for a single pixel 32 / 4(each colour)
												 //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Allocate space for two windows, which can be used for layering objects and for drawing to one buffer window while another displays.

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL); // Creates an SDL Window and stores the pointer
	m_glContext = SDL_GL_CreateContext(m_window); // Create the OpenGL context

	GLenum status = glewInit(); // Initialise GLEW
	if (status != GLEW_OK) // Error
	{
		std::cerr << "Glew failed to initialize!" << std::endl; // Output a console error
	}

	m_isWindowClosed = false;

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (GLint i = 0; i < 322; i++)
	{
		KEYS[i] = false; // Initialise all keys to false
	}

	m_perspective = false;
	m_cameraMode = false;
	m_viewPort = STANDARD;
	//SDL_EnableKeyRepeat()
	//SDL_SetRelativeMouseMode(SDL_TRUE);
}

Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext); // Deletes the OpenGL context
	SDL_DestroyWindow(m_window); // Destroy the Window
	SDL_Quit(); // De-initialise Window
	TTF_Quit(); // De-initialise TrueType fonts
}

GLvoid Display::Clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	glClearColor(r, g, b, a); // Fill the display with colour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the colour buffer so we can fill it with the display colour
}
float rot = 0.1f, pitch = 0.1f;
GLvoid Display::Update(GLfloat deltaTime, Camera& camera, Player& player)
{
	SDL_GL_SwapWindow(m_window); // Swap the window buffers

	SDL_Event e; // Create an SDL event structure for handling OS events

	while (SDL_PollEvent(&e)) // 
	{
		switch (e.type)
		{
		case SDL_QUIT:
			m_isWindowClosed = true; // Set that the window is closed
			break;
		case SDL_KEYDOWN:
			//KEYS[e.key.keysym.sym] = true; // Set key is down
			switch (e.key.keysym.sym)
			{
			case SDLK_a:
				if (((player.transform.GetPos().x - 0.1f) - deltaTime * player.speed) >= -1)
					player.transform.GetPos().x -= deltaTime * player.speed;
				break;
			case SDLK_d:
				if (((player.transform.GetPos().x + 0.1f) + deltaTime * player.speed) <= 1)
					player.transform.GetPos().x += deltaTime * player.speed;
				break;
			case SDLK_UP:
				Display::gameSpeed += 0.1f;
				if (Display::gameSpeed > 5)
					Display::gameSpeed = 5;

				cout << "Game Speed: " << Display::gameSpeed << endl;
				break;
			case SDLK_DOWN:
				Display::gameSpeed -= 0.1f;
				if (Display::gameSpeed < 0)
					Display::gameSpeed = 0;
				cout << "Game Speed: " << Display::gameSpeed << endl;
				break;
			case SDLK_SPACE:
				if (!cooldownActive[0])
				{
					player.Fire(BulletDirection::UP);
					Display::cooldownActive[0] = true; // Make the cool down active
				}
				break;
			case SDLK_RETURN:
				if (!Display::cooldownActive[1])
				{
					if (Display::gameSpeed == 0) // Already paused
						Display::gameSpeed = 1;
					else
						Display::gameSpeed = 0;
					Display::cooldownActive[1] = true; // Make the cool down active
				}
				
				break;
			}
			break;
			
		case SDL_KEYUP:
			//KEYS[e.key.keysym.sym] = false; // Set key is up
			break;
		}


	}
}

GLboolean Display::IsWindowClosed()
{
	return m_isWindowClosed;
}
