/* ------------------------------------------------------------------------------------------------
 |						Documentation Conventions
 | ------------------------------------------------------------------------------------------------
 |	This style is intended to be used by Doxygen documentation generator.
 |		// Brief description of method
 |		/**
 |		 * @pre
 |		 *    Any preconditions that this method requires
 |		 * @post
 |		 *    Any post conditions that result because of this method
 |		 * @param [0, n-1] paramName
 |		 *    Brief description of parameter
 |		 * @return
 |		 *    Brief description of return value
 |		 * @throw
 |		 *    An EXPLICIT throw specification - including which guarantee it offers
 |		 *    	(basic, strong, nothrow) and WHY the various exceptions may be thrown.
 |		 *(/)
 | --------------------------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------------------------------
 |						Variable Naming Conventions
 | ------------------------------------------------------------------------------------------------
 |	Type Declarations ([X] represents the rest of the variable name)
 |		g_[X]	-	a global variable. Not a member of a class, or struct,
 |						but global across all files
 |		m_[X]	-	a member variable. used in classes, and structs.
 |						A global variable for each respectively but not the src file
 |		s_[X]	-	a static variable
 |		_p[X]	-	a pointer (*). Underscore only if there is another type declaration
 |		_r[X]	-	a reference (&). Underscore only if there is another type declaration
 |		_s[X]	-	a struct
 |		is[X]	-	Boolean (its like a question, makes reading easier)
 |
 |		C[X]	-	a class. Will be in the class name.
 |		S[X]	-	a struct. Will be in the struct name
 |		I[X]	-	an interface. Contains all pure virtual functions
 |
 |	Methods/Functions will be lower-case starting letter and upper-case for each starting letter
 |		of each different word
 |
 |	Classes/Structs will be upper-cased starting letter
 |
 |	Variables will be lower-case unless constant, or have a non-underscore type declaration
 |		immediately preceding the variable (ie: m_pVar)
 |
 | --------------------------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------------------------
|						Source File Naming Conventions
| ------------------------------------------------------------------------------------------------
| 	1 Main.cpp 	-	Defines the entrance point for the program
|
|	If a source file is only to contain a class or struct, the name of the file is the name of the
|		class or struct. In order to have source files close to their super class, the sub class
|		will be named: [super]_[sub]
|
|	header file header-guards will not be used, instead '#pragma once' will be used for speed
|
| --------------------------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------------------------
 |						Other Conventions
 | ------------------------------------------------------------------------------------------------
 |	No line will be longer than 100 columns
 |
 |	public comes before private, variables before methods
 |
 | --------------------------------------------------------------------------------------------- */

#include "stdafx.h"
#include "IControlledStartStop.h"
#include "CTransformationPipeline.h"
#include "CShader.h"
#include "CCamera.h"

#define WINDOW_WIDTH	1024
#define WINDOW_HEIGHT	768
#define WINDOW_POS_X	100
#define WINDOW_POS_Y	100

class CMain : public IControlledStartStop
{
	/*********************************************************************************************/
	/** public ***********************************************************************************/
	/*********************************************************************************************/
public:
	CMain(int _fps,					// frames per second
		  const char* pTitle,		// title of window, UTF-8 encoding
	      int x, int y,				// position of window
	      int width, int height,	// size of window
	      Uint32 flags				// '0' or >= 1 SDL_Window_* bitOr'ed together ('|')
	     )
	{
		fps = _fps;
		isFrameRateCapped = false;

		initWindow(pTitle, x, y, width, height, flags); // [TEMPORARY LOCATION]
		initOpenGL();

		m_pShaderCode = new CShader();
		m_pGameCamera = new CCamera(WINDOW_WIDTH, WINDOW_HEIGHT);
		m_pTexture = new CTexture(GL_TEXTURE_2D, "test.png");
		m_pTexture->load();
	}


	~CMain()
	{
		std::cout << "~CMain called!" << std::endl;

		// no delete needed because no new as used
		SDL_GL_DeleteContext(m_WindowContext_Opengl);
		SDL_DestroyWindow(m_pGameWindow);

		delete m_pShaderCode;
		delete m_pGameCamera;
		delete m_pTexture;

		// quit subsystems
		//IMG_Quit();
		SDL_Quit();
	}


	// Starts the main game loop
	bool startFunctionality(void)
	{
		gameLoop();
		return true;
	}


	// Stops the main game loop
	bool stopFunctionality(void)
	{
		isGameRunning = false;
		return true;
	}


	/*********************************************************************************************/
	/** private **********************************************************************************/
	/*********************************************************************************************/
private:
	SDL_Window* m_pGameWindow; // window rendered to
	SDL_GLContext m_WindowContext_Opengl; // OpenGL context (connects OpenGL to SDL)

	bool isGameRunning; // controls the main game loop continuation

	CShader* m_pShaderCode;
	CCamera* m_pGameCamera;
	CTexture* m_pTexture;

	int fps; // requested frames-per-second
	bool isFrameRateCapped; // wither or not to stop frames at requested fps


	// main game loop
	void gameLoop(void)
	{
		SDL_Event gameEvents;	// event handler

		CTimer gameTimer;		// game loop timer
#ifdef DEBUG
		CTimer fpsTracker;		// keep track of what the game is actually running at
		fpsTracker.start();
		int frames = 0; // frames that happened within one second
#endif

		isGameRunning = true;
		while (isGameRunning)
		{
			gameTimer.start();

			userInput(gameEvents);
			//gameUpdate();
			gameRender();

			// limit top of frame-rate
			if ( (isFrameRateCapped == true) && gameTimer.getTime() < (Uint32)(1000/fps) )
			{
				SDL_Delay( (1000/fps) - gameTimer.getTime() );
			}

#ifdef DEBUG
			++frames;
			if (fpsTracker.getTime() >= 1000)
			{
				std::cout << frames << std::endl;
				frames = 0;
				fpsTracker.start();
			}
#endif // DEBUG
		}
	}


	// Updates the states of every object rendered with OpenGL - updating defined by each object
	void gameUpdate(void) {}


	// Renders each object in OpenGL programmable pipeline code - represents 1 frame
	void gameRender(void)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		static float scale = 0.0f;

		scale += 0.5f;

		CTransformationPipeline transPipe;
		transPipe.setRotateInfo(0.0f, scale, 0.0f);
		transPipe.setWorldPos(0.0f, 0.0f, 3.0f);

		transPipe.setCamera(m_pGameCamera->getPosition(), m_pGameCamera->getTarget(), m_pGameCamera->getUp());

		transPipe.setPerspectiveProjection(60.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 100.0f);

		glUniformMatrix4fv(m_pShaderCode->getShaderVar("gWVP"), 1, GL_TRUE, (const GLfloat*)transPipe.getTransformations());

		glEnableVertexAttribArray(0); // Position
		glEnableVertexAttribArray(1); // TexCoord

		glBindBuffer(GL_ARRAY_BUFFER, m_pShaderCode->getVBO());

		// Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), 0);
		// TexCoord
		glVertexAttribPointer(1, 2, 
			GL_FLOAT, GL_FALSE, 
			sizeof(SVertex), (const GLvoid*)12); // last param: offset in bytes from SVertex to texture attributes


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pShaderCode->getIBO());

		m_pTexture->bind(GL_TEXTURE0);

		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		SDL_GL_SwapWindow(m_pGameWindow);	// Swap the window/buffer to display the result.
	}


	// * Handle the events the user has caused
	// * Switchboard method (only points to other methods, no processing)
	// * SDL creates a queue of events for multiple the user causes
	void userInput(SDL_Event& userEvent)
	{
		// handle events on queue
		while (SDL_PollEvent(&userEvent) != 0)
		{
			// user requests quit
			if (userEvent.type == SDL_QUIT)
			{
				isGameRunning = false;
			}
			// user did something with mouse
			else if (userEvent.type == SDL_MOUSEBUTTONDOWN ||
			         userEvent.type == SDL_MOUSEBUTTONUP ||
			         userEvent.type == SDL_MOUSEWHEEL ||
			         userEvent.type == SDL_MOUSEMOTION)
			{
				userInput_mouse(userEvent);
			}
			// user pressed a key
			else if (userEvent.type == SDL_KEYDOWN ||
			         userEvent.type == SDL_KEYUP)
			{
				userInput_keyboard(userEvent);
			}
		}
	}


	void userInput_keyboard(SDL_Event& keyboardEvent)
	{
		if (keyboardEvent.type == SDL_KEYDOWN)
		{
			// camera processing
			if (m_pGameCamera->isCamera_key(keyboardEvent))
			{
				m_pGameCamera->proccess_key(keyboardEvent);
			}

			switch (keyboardEvent.key.keysym.sym) // switch on key code
			{
			case SDLK_ESCAPE:
				isGameRunning = false;
				break;
			case SDLK_F1:
				isFrameRateCapped = !isFrameRateCapped;
				break;
			}
		}
		else if (keyboardEvent.type == SDL_KEYUP)
		{

		}
	}


	void userInput_mouse(SDL_Event& mouseEvent)
	{
		// camera processing
		if (m_pGameCamera->isCamera_mouse(mouseEvent))
		{
			m_pGameCamera->proccess_mouse(mouseEvent);
		}
	}


	void userInput_window(SDL_Event& windowEvent) {}


	// * All windows use SDL
	// * This window configuration specifically is from ogldev (OpenGL)
	void initWindow(const char* pTitle,		// title of window, UTF-8 encoding
	                int x, int y,			// position of window
	                int width, int height,	// size of window
	                Uint32 flags			// '0' or >= 1 SDL_Window_* bitOr'ed together ('|')
	               )
	{
		// ** initialize video **
		int initCode = 1;
		initCode = SDL_Init(SDL_INIT_VIDEO); // = 0 is failure
#ifdef DEBUG
		assert(initCode == 0);
#endif // DEBUG

		// ** SET window context **
		// NOTE!!! THIS CONTEXT ONLY SUPPORTS OPENGL 3.X! (no fixed pipeline eg: glBegin!)
		//		comment this section to return to OpenGL < 3.X
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		// note: SDL_GL_MULTISAMPLESAMPLES && SDL_GL_MULTISAMPLEBUFFERS atributes can be used for
		//		multi-sample anti-aliasing doc: http://wiki.libsdl.org/moin.fcg/SDL_GLattr#OpenGL
		// note: double buffering is enabled by default doc^

		// ** create window **
		m_pGameWindow = NULL;
		m_pGameWindow = SDL_CreateWindow(pTitle, x, y, width, height, flags);
#ifdef DEBUG
		assert(m_pGameWindow);
#endif // DEBUG

		// ** CREATE window context **
		m_WindowContext_Opengl = SDL_GL_CreateContext(m_pGameWindow);

		SDL_GL_MakeCurrent(m_pGameWindow, m_WindowContext_Opengl);
	}


	void initOpenGL(void)
	{
		glewExperimental = GL_TRUE;

		// init GLEW
		// Must be done after window is initialized!
		GLenum glewInitCode = glewInit();
#ifdef DEBUG
		assert(glewInitCode == GLEW_OK);
#endif // DEBUG

		printf("GL version: %s\n", glGetString(GL_VERSION));

		// background color for OpenGL (r,g,b,a)
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		// enable culling
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
	}


}; // CMain end

int threadFunction(void* ptr)
{
	for (int i = 0; i < 100; ++i)
	{
		std::cout << i << std::endl;
	}
	return 1;
}

void threadTesting(void)
{
	// Thread Testing
	SDL_Thread* threadTest;
	threadTest = SDL_CreateThread(threadFunction, "TestThread", NULL);
	assert(threadTest != NULL);
	std::cout << "normal thread" << std::endl;
	SDL_WaitThread(threadTest, NULL);
}

void hashMapTesting(void)
{
	// Hash Map testing (unordered_map in c++11)
	typedef std::unordered_map<std::string, GLuint> shaderMap;
	shaderMap map;

	map.insert(shaderMap::value_type("gShader", (GLuint)10));
	map.insert(shaderMap::value_type("gWVP", (GLuint)5));

	shaderMap::const_iterator itr = map.find("gShader");
	if (itr == map.end())
	{
		assert(false);
	}
	else
	{
		std::cout << itr->first << ": " << itr->second << std::endl;
	}
}

int main(int argc, char* args[])
{
	CMain* pApp = new CMain(5,
							"SDL tutorial",
	                        WINDOW_POS_X, WINDOW_POS_Y,
	                        WINDOW_WIDTH, WINDOW_HEIGHT,
	                        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
	                       );
	pApp->startFunctionality();
	delete pApp;

	//threadTesting();
	//hashMapTesting();

	//std::cout<< "End of application. [ENTER] to end" << std::endl;
	//std::cin.get();

	return EXIT_SUCCESS;
}