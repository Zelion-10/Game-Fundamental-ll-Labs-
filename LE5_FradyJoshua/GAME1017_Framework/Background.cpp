#include "Background.h"

Background::Background(const SDL_Rect src, const SDL_FRect dst, float speed) :Image(src, dst, "city"), m_scrollSpeed(speed)
{
	m_startX = m_dst.x;// or dst.x or GetDst->x I am way too tired for this so.....
	m_endX = m_startX - m_dst.w;

}

void Background::Update()
{
	//check if journey is over, My life is about to be over after this
	if (m_dst.x <= m_endX)
		m_dst.x = m_startX; //Im starting to write random things in these its kinda funny to think about, cuz most people wont see it 

	//scroll the background... they are running in a endless loop and is waiting someone to stop them running
	m_dst.x -= m_scrollSpeed;

}

void Background::Render()
{
	Image::Render();
}

void Background::SetSpeed(float speed)
{
	m_scrollSpeed = speed;
}

//dont worry im fine
//My name is Walter Hartwell White. I live at 308 Negra Arroyo Lane, Albuquerque, New Mexico, 87104. To all law enforcement entities, this is not an admission of guilt. I am speaking to my family now. Skyler, you are the love of my life. I hope you know that. Walter Jr., you're my big man. There are going to be some things that you'll come to learn about me in the next few days. But just know that no matter how it may look, I only had you in my heart. Goodbye.
