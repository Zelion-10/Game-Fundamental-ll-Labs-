#ifndef __ENEMY_H__
#define __ENEMY_H__
#include <SDL.h>
#include "GameObject.h"
#include <vector>
#include "Bullet.h"

class Enemy : public Sprite
{
public:
	Enemy(const SDL_Rect src, const SDL_FRect dst,float speed);
	Enemy(SDL_Rect src, SDL_FRect dst);
	void Update();
	void Render();

private:
	
	static const float s_speed; // Common to all enemies. Also just showing a static property again.
};

#endif