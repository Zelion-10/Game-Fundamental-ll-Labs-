#include "ObstacleRow.h"
#include "RenderManager.h"
#include "TextureManager.h"



ObstacleRow::ObstacleRow() :m_gapCtr(0), m_gapMax(3)
{
	
	for (int i = 0; i < 9; i++)
	{
		m_obstacles.push_back(new Obstacle({ 128.0f * i, 384.0f, 128.0f, 128.0f }));
	}
	m_obstacles.shrink_to_fit();
	TEMA::Load("../Assets/img/tempObstacles.png", "obstacleSheet");
	TEMA::Load("../Assets/img/Obstacles.png", "obstacle");

	
}

void ObstacleRow::RandomObstacle()
{
	CurrentObstacle = static_cast<ObstacleTexture>(rand() % static_cast<int>(ObstacleTexture::NUM_OBSTACLES));
}

void ObstacleRow::Update()
{



	for (const auto obstacle : m_obstacles)
	{
		// When the first obstacle goes completely offscreen
		if (obstacle != nullptr) // Error checker!
		{
			if (obstacle->GetPos().x <= 0 - 128.0f)
			{
				delete m_obstacles[0];
				m_obstacles[0] = nullptr;
				m_obstacles.erase(m_obstacles.begin());

				if (m_gapCtr++ % m_gapMax == 0)
				{
					RandomObstacle();
					switch (CurrentObstacle) {
					case TRASHCAN:
						m_obstacles.push_back(new Obstacle({ m_obstacles.back()->GetPos().x + 128.0f, 384.0f, 128.0f, 128.0f }, true, new Image({ { 20, 0, 20, 20 }, { 20 , (-80/2 ), 20, 20 }, "obstacleSheet" })));
						break;

					case CONE:
						m_obstacles.push_back(new Obstacle({ m_obstacles.back()->GetPos().x + 128.0f, 384.0f, 128.0f, 128.0f }, true, new Image({ { 40, 0, 20, 20 }, { 20, (-80/2 ), 20, 20 }, "obstacleSheet" })));
						break;

					case HYDRANT:
						m_obstacles.push_back(new Obstacle({ m_obstacles.back()->GetPos().x + 128.0f, 384.0f, 128.0f, 128.0f }, true, new Image({ { 60, 0, 20, 20 }, { 20, (-80/2), 20, 20 }, "obstacleSheet" })));
						break;

					}

				}
				else {
					m_obstacles.push_back(new Obstacle({ m_obstacles.back()->GetPos().x + 128.0f, 384.0f, 128.0f, 128.0f }, false,nullptr));

				}


				m_obstacles.shrink_to_fit();
			}
			else { // Scroll the obstacles.
				obstacle->Update();
			}
		}
	}
}

void ObstacleRow::Render()
{
	// Blue line under obstacles.
	SDL_SetRenderDrawColor(REMA::GetRenderer(), 0, 0, 255, 255);
	SDL_RenderDrawLine(REMA::GetRenderer(), 0, 512, 1024, 512);
	// Render the obstacles.
	for (const auto obstacle : m_obstacles)
	{
		if (obstacle != nullptr) // Error checker!
		{
			obstacle->Render();
		}
	}
}