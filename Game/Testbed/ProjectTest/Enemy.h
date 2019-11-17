#pragma once
#include "Object2D.h"
#include <vector>

using namespace std;

class Enemy : public Object2D
{
public:
	Enemy();
	~Enemy();
	
	float m_enemySpeed;
	int score;
	int m_score;
	static vector <b2Vec2> trajectory;
	virtual void RenderBox2D(b2World* world) {};
	virtual void Update();
	virtual void UpgradePower();
};
