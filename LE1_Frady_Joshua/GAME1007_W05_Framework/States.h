#pragma once
#ifndef __STATES_H__
#define __STATES_H__

#include <map>
#include <string>
#include <iostream>
#include "Engine.h"
#include "StateManager.h"

class State // Abstract base class.
{ // No objects of State can be created.
public:
	virtual void Enter() = 0; // Pure virtual function. No definition.
	virtual void Update() = 0;
	virtual void Render(); // Will be defined in State.
	virtual void Exit() = 0;
	virtual void Resume() {}; // Considered defined for all subclasses.
protected: // Private but inherited.
	State() = default;
};
class TitleState : public State
{
public:
	TitleState();
	virtual void Enter(); // Pure virtual function. No definition
	virtual void Update();
	virtual void Render();
	virtual void Exit();
private:
	// Map for music track goes here
	std::map<std::string, Mix_Chunk*> m_sfx;
	std::map<std::string, Mix_Music*> m_Music;
};

class GameState : public State
{
public:
	GameState();
	virtual void Enter(); // Pure virtual function. No definition
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();

private:
	std::map<std::string, Mix_Chunk*> m_sfx;
	std::map<std::string, Mix_Chunk*> m_Music;
	static map<std::string, Mix_Music*> Music;
};

// Pause State
class PauseState : public State
{
public:
	PauseState();
	virtual void Enter(); // Pure virtual function. No definition
	virtual void Update();
	virtual void Render();
	virtual void Exit();

	void Resume();

private:
	SDL_Window* m_pauseWindow;
	SDL_Renderer* m_pauseRenderer;
};
// Make definition for end state
class EndState : public State
{
public:
	EndState();
	virtual void Enter(); // Pure virtual function. No definition
	virtual void Update();
	virtual void Render();
	virtual void Exit();

private:

};


// This is essential for static properties. Declare them OUTSIDE their class but with class scope.


#endif