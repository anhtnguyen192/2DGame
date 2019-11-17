#include "Boss.h"

Boss::Boss()
{
	enemyFilter.categoryBits = k_enemyCategory;
	enemyFilter.maskBits = k_enemyMask;
	setFilter = 0;
}

Boss::~Boss()
{

}

void Boss::Update()
{
	b2Vec2 velocity;
	if (m_body->GetPosition().y < 2)
	{
		velocity = Enemy::trajectory.at(rand() % 3);
	}
		
	else 
	{
		velocity = Enemy::trajectory.at(rand() % Enemy::trajectory.size());
	}
	velocity.x = velocity.x * m_enemySpeed;
	velocity.y = velocity.y * m_enemySpeed;
	m_body->SetLinearVelocity(velocity);
}

void Boss::RenderBox2D(b2World* world)
{

}

void Boss::BossEntering(b2World* world)
{
	if (m_isRender == false)
	{
		RenderBox2D(world);
	}

	if (Intro() == false)
	{
		if (setFilter == 0)
		{
			m_body->GetFixtureList()->SetFilterData(enemyFilter);
			m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			setFilter = 1;
		}
	}
	else
	{
		timeIntro++;
		Counter::GetInstance()->timeCountRenderBullet = 0;
	}
}

void Boss::IsDestroyed()
{
	Counter::GetInstance()->enemyRenderCount = 0;
	Counter::GetInstance()->killCount = 0;
	timeIntro = 0;
	setFilter = 0;
}