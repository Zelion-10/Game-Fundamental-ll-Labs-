#include "ScrollingBackground.h"

ScrollingBackground::ScrollingBackground()
{
	m_backgrounds.reserve(10);
	m_backgrounds.push_back(new Background({ 0,0,1024,768 }, { 0.0f,0.0f,1024.0f,768.0f }, 1.0f));
	m_backgrounds.push_back(new Background({ 0,0,1024,768 }, { 1024.0f,0.0f,1024.0f,768.0f }, 1.0f));

	

	//This was nice, but u know what would be better, A nice nap

}

ScrollingBackground::~ScrollingBackground()
{
	for (auto background : m_backgrounds)
	{
		delete background;
		background = nullptr;
	}
	m_backgrounds.clear();
}

void ScrollingBackground::Update()
{
	for (const auto background : m_backgrounds)background->Update();

}

void ScrollingBackground::Render()
{
	for (const auto background : m_backgrounds)background->Render();
}

void ScrollingBackground::Setspeeds(const float back, float mid, float fore)
{
	m_backgrounds[0]->SetSpeed(back);
	m_backgrounds[1]->SetSpeed(back);

	m_backgrounds[2]->SetSpeed(back);
	m_backgrounds[3]->SetSpeed(back);
	m_backgrounds[4]->SetSpeed(back);
	m_backgrounds[5]->SetSpeed(back);
	m_backgrounds[6]->SetSpeed(back);

	m_backgrounds[7]->SetSpeed(back);
	m_backgrounds[8]->SetSpeed(back);
	m_backgrounds[9]->SetSpeed(back);



}


//This is getting way too tedious its not even hard just tired from.... idk what i did.
