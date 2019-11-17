#pragma once
#include "Enemy.h"

class EnemyCircle : public Enemy
{
public:
	EnemyCircle(float radius);
	~EnemyCircle();
	

	b2CircleShape circle;

	void Update();
	void RenderBox2D(b2World *world);
};