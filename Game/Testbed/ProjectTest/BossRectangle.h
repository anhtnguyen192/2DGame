#pragma once
#include "Boss.h"

class BossRectangle : public Boss
{
public:
	BossRectangle(float width, float height);
	~BossRectangle();

	b2PolygonShape boss;
	void RenderBox2D(b2World* world);
	bool Intro() ;
	void ShootBullet(b2World* world);
};
