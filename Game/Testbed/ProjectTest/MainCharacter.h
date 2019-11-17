#pragma once
#include "Object2D.h"
#include "Counter.h"
class MainCharacter : public Object2D
{
public:
	MainCharacter();
	~MainCharacter();
	bool m_isInvincible;
	int m_bulletLevel;
	b2Filter mainFilter;
	bool isInside;
	b2Vec2 prevPos;
	bool GetInvincibleState();
	void SetInvincibleState(bool b);
	void RenderBox2D(b2World *world);
	void TouchActionMove(b2World *world, int x, int y, int currentX, int currentY);

	void Respawn(b2World *world);
	void IsDestroyed();
	void Move(b2Vec2 p);
	float CoorGLToBox2DForX(int x);
	float CoorGLToBox2DForY(int y);
};

