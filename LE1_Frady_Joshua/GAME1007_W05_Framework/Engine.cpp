#include "Engine.h"
#include <iostream>
#include <string>
#include "StateManager.h"
using namespace std;



Engine::Engine():m_pWindow(nullptr), m_pRenderer(nullptr), m_isRunning(false)
{
	cout << "Constructing Engine object!" << endl;
	; 
}

int Engine::Run()
{
	if (m_isRunning)
	{
		return 1; // 1 arbitrarily means that engine is already running.
	}
	if (Init("GAME1017 Framework", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, NULL))
	{
		return 2; // 2 arbitrarily means that something went wrong in init.
	}
	while (m_isRunning) // Main game loop. Run while isRunning = true.
	{
		Wake();
		HandleEvents(); // Input
		Update();       // Processing
		Render();       // Output
		if (m_isRunning == true)
			Sleep();
	}
	Clean(); // Deinitialize SDL and free up memory.
	return 0;
}

int Engine::Init(const char* title, const int xPos, const int yPos, 
	const int width, const int height, const int flags)
{
	cout << "Initializing framework..." << endl;
	SDL_Init(SDL_INIT_EVERYTHING);
	m_pWindow = SDL_CreateWindow(title,	xPos, yPos, width, height, flags);
	if (m_pWindow == nullptr)
	{
		cout << "Error during window creation!" << endl;
		return 1;
	}
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
	if (m_pRenderer == nullptr)
	{
		cout << "Error during renderer creation!" << endl;
		return 1;
	}

	if (Mix_Init(MIX_INIT_MP3)) {

		Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
		Mix_AllocateChannels(16);
		Music.emplace("Music", Mix_LoadMUS("../Assets/mus/Seeker Of Rebirth.mp3"));
		m_sfx.emplace("Wizard",Mix_LoadWAV("../Assets/mus/Wizard.mp3")); 
		m_sfx.emplace("Blah",Mix_LoadWAV("../Assets/mus/blah blah blah.mp3")); 

	}
	else return false;
	// Initialize SDL sublibraries.
	
	// Example-specific initialization.
	 STMA::ChangeState(new TitleState());
	// Initialize rest of framework.
	m_fps = 1.0 / (double)FPS; // Converts FPS into a fraction of seconds.
	m_pKeystates = SDL_GetKeyboardState(nullptr);
	lastFrameTime = chrono::high_resolution_clock::now();
	m_isRunning = true; // Start your engine.
	return 0;
}

void Engine::HandleEvents()
{
	cout << "Handling events..." << endl;
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // Pressing 'X' icon in SDL window.
			m_isRunning = false; // Tell Run() we're done.
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			{

				Mix_PlayChannel(-1, m_sfx["Wizard"], 0);
			}
		}
	}
}

void Engine::Wake()
{
	thisFrameTime = chrono::high_resolution_clock::now(); // New snapshot of number of seconds.
	lastFrameDuration = thisFrameTime - lastFrameTime;
	deltaTime = lastFrameDuration.count(); // Now we have our deltaTime multiplier.
	lastFrameTime = thisFrameTime;

	m_start = thisFrameTime; // Comment this out to just use deltaTime.
}

bool Engine::KeyDown(SDL_Scancode c)
{
	if (m_pKeystates != nullptr)
	{
		if (m_pKeystates[c] == 1)
			return true;
	}
	return false;
}

SDL_Renderer* Engine::GetRenderer()
{
	return m_pRenderer;
}

Engine& Engine::Instance()
{
	static Engine instance; // Creating Engine object.
	return instance;
}

void Engine::Update()
{
	cout << "Updating frame..." << endl;
	STMA::Update();

	
}

void Engine::Sleep() 
{
	// Note: Not really better, but you can decide to not limit frameRate and just use deltaTime.
	// Comment all this out to just use deltaTime.
	m_end = chrono::high_resolution_clock::now();
	m_diff = m_end - m_start; // Similar to before, but now chrono and double.
	if (m_diff.count() < m_fps)
		SDL_Delay((Uint32)((m_fps - m_diff.count()) * 1000.0)); // Sleep for number of ms.
}

void Engine::Render()
{
	cout << "Rendering changes..." << endl;
	STMA::Render();
}

void Engine::Clean()
{
	cout << "Cleaning up..." << endl;
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	for (auto const& i : m_Music)
	{
		Mix_FreeChunk(i.second);
	}
	STMA::Quit();
	SDL_Quit();

}map<std::string, Mix_Music*> Engine::Music; 
