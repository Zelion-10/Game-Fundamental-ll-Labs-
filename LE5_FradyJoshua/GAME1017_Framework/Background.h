#pragma once
#ifndef __BACKGROUND__
#define __BACKGROUND__
#include "Primitives.h"

class Background : public Image
{
public:
	Background(const SDL_Rect src, const SDL_FRect dst, float speed);
	void Update();
	void Render();
	void SetSpeed(float speed);
private:
	float m_scrollSpeed; //for more pixels and stuff
	float m_startX, m_endX;
};
#endif
