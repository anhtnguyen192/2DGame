#pragma once
#include "Enemy.h"



class Boss : public Enemy
{
public:
	Boss();
	~Boss();
	virtual void Update();
	float timeIntro;
	int setFilter;
	b2Filter enemyFilter;

	virtual void RenderBox2D(b2World* world);
	virtual bool Intro() { return true; };
	virtual void ShootBullet(b2World* world) {};
	void IsDestroyed();
	void BossEntering(b2World* world);
	
};