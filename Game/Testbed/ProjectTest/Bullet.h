#pragma once
#include "Object2D.h"

class Bullet : public Object2D
{
public:
	Bullet();
	~Bullet();
	float m_firingSpeed;
	float m_bulletSpeed;
	virtual void RenderBox2D(b2World *world) {};
	int GetBulletRest();
};

