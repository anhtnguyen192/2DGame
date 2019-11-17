#pragma once
#include "Boss.h"

class BossCircle : public Boss
{
public:
	BossCircle(float radius);
	~BossCircle();
	
	b2CircleShape boss;
	void RenderBox2D(b2World* world);
	bool Intro();
};