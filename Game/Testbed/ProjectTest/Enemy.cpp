#include "Enemy.h"

Enemy::Enemy()
{
	
}

Enemy::~Enemy()
{

}

vector<b2Vec2> Enemy::trajectory =
{
	b2Vec2(-1.0f,1.0f), // 0
	b2Vec2(1.0f,1.0f),	// 1
	b2Vec2(0.0f,1.0f),	//	2
	b2Vec2(1.0f,0.0f),	// 3
	b2Vec2(-1.0f,0.0f), // 4
	b2Vec2(0.0f,-1.0f), // 5
	b2Vec2(-1.0f,-1.0f), // 6
	b2Vec2(1.0f,-1.0f) // 7 
	
};

void Enemy::Update()
{
	b2Vec2 velocity = Enemy::trajectory.at(rand() % Enemy::trajectory.size());
	velocity.x = velocity.x * m_enemySpeed;
	velocity.y = velocity.y * m_enemySpeed;
	m_body->SetLinearVelocity(velocity);
}

void Enemy::UpgradePower()
{
	hp *= 1.25;
	m_enemySpeed *= 1.1;
}