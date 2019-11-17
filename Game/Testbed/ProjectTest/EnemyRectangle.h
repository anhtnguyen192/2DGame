#pragma once
#include "Enemy.h"

class EnemyRectangle : public Enemy
{
public:
	EnemyRectangle(float width, float height);
	~EnemyRectangle();


	b2PolygonShape rectangle;

	void Update();
	void RenderBox2D(b2World* world);
};