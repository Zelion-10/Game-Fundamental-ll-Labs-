#include <iostream>
#include "States.h"
#include "StateManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "RenderManager.h"
#include "TextureManager.h"
#include "tinyxml2.h"
using namespace tinyxml2;
#include "GameObject.h"
#include "Turret.h"
using namespace std;

void State::Render()
{
	SDL_RenderPresent(REMA::Instance().GetRenderer());
}

TitleState::TitleState() {}

void TitleState::Enter()
{

}

void TitleState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_N))
	{
		STMA::ChangeState(new GameState());
	}
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(REMA::Instance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(REMA::Instance().GetRenderer());
	State::Render();
}

void TitleState::Exit()
{

}

void GameState::ClearTurrets()
{
	for (unsigned i = 0; i < m_turrets.size(); i++)
	{
		delete m_turrets[i];
		m_turrets[i] = nullptr;
	}
	m_turrets.clear();
	m_turrets.shrink_to_fit();
	// You can assimilate some parts of this code for deleting bullets and enemies.
}

GameState::GameState() :m_spawnCtr(1) {}

void GameState::Enter()
{
	TEMA::Load("../Assets/img/Turret.png", "turret");
	TEMA::Load("../Assets/img/Enemies.png", "enemy");
	s_enemies.push_back(new Enemy({ 80,0,40,57 }, { 512.0f, -57.0f, 40.0f, 57.0f }));
	// Create the DOM and load the XML file.
	XMLDocument xmlDoc;

	float x, y;
	int kills;
	//*
	xmlDoc.LoadFile("../Assets/dat/Turrets.xml");

	XMLNode* pRoot = xmlDoc.FirstChildElement("Root");
	

	if (pRoot != nullptr)
	{
		XMLElement* pElement = pRoot->FirstChildElement("Turret");
		while (pElement != nullptr)
		{

			pElement->QueryFloatAttribute("x", &x); 

			pElement->QueryFloatAttribute("y", &y);

			pElement->QueryIntAttribute("kills", &kills);

			
			

			Turret* temp = new Turret({ 0, 0, 100, 100 },
				{ x, y, 100.0f, 100.0f });
			m_turrets.push_back(temp);
			pElement = pElement->NextSiblingElement("Turret");
			temp->t_destory = kills;
			
		}
	}
	 
}

void GameState::Update()
{
	// Parse T and C events.
	if (EVMA::KeyPressed(SDL_SCANCODE_T))
	{
		m_turrets.push_back(new Turret({ 0,0,100,100 },
			{ 50.0f, 615.0f, 100.0f,100.0f }));
	}
	if (EVMA::KeyPressed(SDL_SCANCODE_C))
	{
		ClearTurrets();
	}
	// Update all GameObjects individually. Spawn enemies. Update turrets. Update enemies. Update bullets.
	if (m_spawnCtr++ % 180 == 0)
	{
		s_enemies.push_back(new Enemy({ 80,0,40,57 },
			{ (float)(rand() % (1024 - 40)), -57.0f, 40.0f, 57.0f }));
	}
	for (auto turret : m_turrets)
		turret->Update();
	for (auto enemy : s_enemies)
		enemy->Update();
	for (auto bullet : s_bullets)
		bullet->Update();
	

		// for all bullets
	for (unsigned i = 0; i < s_bullets.size(); i++)
	{
		// if bullet goes off screen (four bounds checks)
		if (s_bullets[i]->GetDst()->x > 1024.0f || s_bullets[i]->GetDst()->x < 0.0f
			|| s_bullets[i]->GetDst()->y > 768.0f || s_bullets[i]->GetDst()->y < 0.0f)
		{
			// delete s_bullets[i]
			// set s_bullets[i] to nullptr
			delete s_bullets[i];
			s_bullets.erase(s_bullets.begin() + i);
		}
		// or
		// if deleteMe of bullet is true	
	}
	// for all enemies, similar to above
	for (unsigned j = 0; j < s_enemies.size(); j++)
	{
		if (s_enemies[j]->GetDst()->x > 1024.0f || s_enemies[j]->GetDst()->x < 0.0f
			|| s_enemies[j]->GetDst()->y > 768.0f)
		{
			delete s_enemies[j];
			s_enemies.erase(s_enemies.begin() + j);
		}
	}//*/
	// Check for collisions with bullets and enemies.

		// for all bullets
	for (unsigned i = 0; i < s_bullets.size(); i++)
	{
		for (unsigned j = 0; j < s_enemies.size(); j++)
		{
			if (COMA::AABBCheck(*s_bullets[i]->GetDst(), *s_enemies[j]->GetDst()))
			{
				s_bullets[i]->GetTurret->t_destory++;
				delete s_bullets[i];
				s_bullets.erase(s_bullets.begin() + i);

				delete s_enemies[j];
				s_enemies.erase(s_enemies.begin() + j);

				
				return;
			}
		}
	}
		
}

void GameState::Render()
{
	SDL_SetRenderDrawColor(REMA::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(REMA::Instance().GetRenderer());

	for (unsigned i = 0; i < m_turrets.size(); i++)
		m_turrets[i]->Render();
	for (unsigned i = 0; i < s_enemies.size(); i++)
		s_enemies[i]->Render();
	for (unsigned i = 0; i < s_bullets.size(); i++)
		s_bullets[i]->Render();

	SDL_Rect spawnBox = { 50, 618, 100, 100 };
	SDL_SetRenderDrawColor(REMA::Instance().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderDrawRect(REMA::Instance().GetRenderer(), &spawnBox);

	// This code below prevents SDL_RenderPresent from running twice in one frame.
	if (dynamic_cast<GameState*>(STMA::GetStates().back())) // If current state is GameState.
		State::Render();
}

void GameState::Exit()
{
	XMLDocument xmlDoc;
	xmlDoc.LoadFile("../Assets/dat/Turrets.xml");
	// You can clear all children of the root node by calling .DeleteChildren(); and this will essentially clear the DOM.
	xmlDoc.DeleteChildren();

	XMLNode* pRoot = xmlDoc.NewElement("Root");
	xmlDoc.InsertFirstChild(pRoot);
	// Iterate through all the turrets and save their positions as child elements of the root node in the DOM.

	if (pRoot != nullptr)
	{
		for (int i = 0; i < m_turrets.size(); i++)
		{
			
			XMLElement* pElement = xmlDoc.NewElement("Turret");

			// Now let's create objects from the XML file.
			pElement->SetAttribute("x", m_turrets[i]->GetDst()->x);

			pElement->SetAttribute("y", m_turrets[i]->GetDst()->y);

			pElement->SetAttribute("kills", m_turrets[i]->t_destory);

			pRoot->InsertEndChild(pElement);
		}
	}
	// Make sure to save to the XML file.

		// xmlDoc.SaveFile("Turrets.xml");
	xmlDoc.SaveFile("../Assets/dat/Turrets.xml");
	ClearTurrets(); // Deallocate all turrets, then all other objects.
	for (unsigned i = 0; i < s_enemies.size(); i++)
	{
		delete s_enemies[i];
		s_enemies[i] = nullptr;
	}
	s_enemies.clear();
	s_enemies.shrink_to_fit();
	for (unsigned i = 0; i < s_bullets.size(); i++)
	{
		delete s_bullets[i];
		s_bullets[i] = nullptr;
	}
	s_bullets.clear();
	s_bullets.shrink_to_fit();
}

void GameState::Resume()
{

}

// This is how static properties are allocated.
std::vector<Bullet*> GameState::s_bullets;
std::vector<Enemy*> GameState::s_enemies;