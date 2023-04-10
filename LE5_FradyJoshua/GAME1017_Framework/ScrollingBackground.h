
#ifndef SCROLLINGBACKGROUND_H__
#define SCROLLINGBACKGROUND_H__
#include "GameObject.h"
#include "Background.h"
#include <vector>
class ScrollingBackground :public GameObject
{
public:
	ScrollingBackground();
	~ScrollingBackground();
	void Update();
	void Render();
	void Setspeeds(const float back = 0.5f, float mid = 2.0f, float fore = 3.0f);
private:
	std::vector < Background*> m_backgrounds;
};
#endif

