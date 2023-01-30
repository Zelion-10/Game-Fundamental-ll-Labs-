#include "States.h"
#include <iostream>
#include "Engine.h"
#include "StateManager.h"

using namespace std;

void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

TitleState::TitleState() {}

void TitleState::Enter()
{
	cout << "Entering TitileState! " << endl;
	Mix_PlayMusic(Engine::Music["Seeker Of Rebirth"], -1);
	Mix_VolumeMusic(36);
}

void TitleState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_N))
	{
		cout << " Changing to GameState" << endl;
		STMA::ChangeState(new GameState());
	}
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());


	State::Render();
}

void TitleState::Exit()
{
	cout << " Exiting TitileState " << endl;
}

GameState::GameState() {}


void GameState::Enter()
{
	cout << " Entering GameState " << endl;
	m_Music.emplace("Music", Mix_LoadWAV("../Assets/mus/Seeker Of Rebirth.mp3"));
	m_sfx.emplace("Wizard", Mix_LoadWAV("../Assets/mus/Wizard.mp3"));
	m_sfx.emplace("Blah", Mix_LoadWAV("../Assets/mus/blah blah blah.mp3"));
	// Load sfk tracks and add them to map (x2)
	// Load music track, and add it to map
	//And play it;

}void GameState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
	{
		cout << " Changing to PauseState " << endl;
		STMA::PushState(new PauseState());

	}

}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	if (dynamic_cast<GameState*>(STMA::GetStates().back()))
		State::Render();
}

void GameState::Exit()
{
	cout << " Exiting TitileState " << endl;
}


void GameState::Resume()
{
	cout << " Resume TitileState " << endl;
}




PauseState::PauseState() {}

void PauseState::Enter()
{
	cout << "Entering PauseState! " << endl;
	


	// Making the window
	m_pauseWindow = SDL_CreateWindow("PauseMenu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, PAUSE_WIDTH, PAUSE_HEIGHT, NULL);
	if (m_pauseWindow == nullptr)
	{
		std::cout << "Error during Pause Menu creation" << std::endl;
	}
	m_pauseRenderer = SDL_CreateRenderer(m_pauseWindow, -1, 0);
	if (m_pauseRenderer == nullptr)
	{
		std::cout << "Error during Pause Renderer creation!" << std::endl;
	}
}


void PauseState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_B))
	{
		cout << " Changing to PauseState " << endl;
		STMA::PushState(new GameState());

	}
}

void PauseState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	SDL_SetRenderDrawBlendMode(m_pauseRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(m_pauseRenderer, 255, 0, 0, 0); // Making window transparent
	SDL_RenderClear(m_pauseRenderer);

}

void PauseState::Exit()
{
	cout << " Exiting TitileState " << endl;
	SDL_DestroyRenderer(m_pauseRenderer);
	SDL_DestroyWindow(m_pauseWindow);
}

void PauseState::Resume()
{
	State::Resume();
}

EndState::EndState() {}

void EndState::Enter()
{
}

void EndState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
	{
		STMA::ChangeState(new TitleState);
	}
}

void EndState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
}

void EndState::Exit()
{
	std::cout << "Now exiting ExitState" << std::endl;
}




