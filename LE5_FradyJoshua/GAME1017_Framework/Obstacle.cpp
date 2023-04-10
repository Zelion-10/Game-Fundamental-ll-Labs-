#include "Obstacle.h"
#include "RenderManager.h"

Obstacle::Obstacle(const SDL_FRect dst, bool hasImage, const SDL_Rect src, const char* key)
	:m_hasImage(hasImage), m_pImage(nullptr)
{
	m_pos = { dst.x,dst.y };

}

Obstacle::Obstacle(const SDL_FRect dst, bool hasImage, Image* image) : m_hasImage(hasImage), m_pImage(image)
{
	m_pos = { dst.x, dst.y };

}

Obstacle::~Obstacle()
{
	if(m_hasImage) //only needs to deallocate image if it was created.
	{
		delete m_pImage;
		m_pImage = nullptr; //optional wrangle-dangle (what???)
	}
}

void Obstacle::Update()
{
	m_pos.x -= kScrollSpeed;
	if(m_hasImage)
	{
		m_pImage->GetDst()->x = m_pos.x;
		m_pImage->GetDst()->y = m_pos.y;

		m_pImage->Update();
	}
}

void Obstacle::Render()
{
	SDL_FRect m_dst = {m_pos.x,m_pos.y,128.0f,128.0f}; //temporary
	if(m_hasImage)
	{
		
		m_pImage->Render();
	}
	//render outline just for week 9
	SDL_SetRenderDrawColor(REMA::GetRenderer(), 128, 0, 128, 255);
	SDL_RenderDrawRectF(REMA::GetRenderer(), &m_dst);
}
