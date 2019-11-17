#pragma once
#include "Enemy.h"

class EnemyBullet : public Enemy
{
public:
	EnemyBullet();
	~EnemyBullet();



	b2PolygonShape box;

	void RenderBox2D(b2World* world);
};