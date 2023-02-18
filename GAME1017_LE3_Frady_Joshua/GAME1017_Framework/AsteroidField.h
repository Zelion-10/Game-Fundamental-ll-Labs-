#ifndef __ASTEROIDFIELD_H__
#define __ASTEROIDFIELD_H__
#include "GameObject.h"
#include <SDL.h>
#include <vector>
#include <string>

class Asteroid : public Sprite
{
public:
	
	Asteroid(SDL_Rect p, SDL_FRect p1, int i);
	void Update();
	void Render();
	const SDL_FPoint& GetCenter() { return m_center; }
	 double& GetRadius() { return m_radius; }
	void SetColMods(const Uint8* colorMods);
	void SetColMods(Uint8 r, Uint8 g, Uint8 b);
	short GetSize();
	void SetSize(short);
	void UpdateDeltas(double);
	Uint8* GetColMods();


private:
	SDL_FPoint m_center;
	double m_angle,
		m_radius,
		m_dx, m_dy,
		m_rotSpeed;
	Uint8 m_rMod, m_gMod, m_bMod;
	short m_size; // New size field. 2 -> 1 -> gone.
};

class AsteroidField : public GameObject
{ // Manager class for the individual asteroids.
public:
	AsteroidField(unsigned int sz = 6);
	~AsteroidField();
	void Update();
	void Render();
	std::vector<Asteroid*>& GetAsteroids() { return m_asteroids; }
	const unsigned int GetSize() { return m_size; }
	void asteroid_split(Asteroid* p_asteroid, double angle);
	

private:
	std::vector<Asteroid*> m_asteroids;
	int m_size;
};

#endif