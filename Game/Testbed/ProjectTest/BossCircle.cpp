#include "BossCircle.h"

BossCircle::BossCircle(float radius)
{
	this->radius = radius;
	m_type = 2;
	m_isRender = false;

	boss.m_radius = this->radius;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.fixedRotation = true;
	m_bodyDef.position.Set(0.0f, SCREEN_HEIGHT / 2 + this->radius);

	m_fixtureDef.shape = &boss;
	m_fixtureDef.density = 100.0f;
	m_fixtureDef.filter.categoryBits = 0;
	//bossFD.filter.maskBits = k_enemyMask;
	timeIntro = 0;
	m_isHit = 0;
	m_timeHit = 0;
}

BossCircle::~BossCircle()
{

}


bool BossCircle::Intro()
{
	if (timeIntro <= (radius*2/m_enemySpeed)*60 + 200)
	{
		return true;
	}
	return false;
}

void BossCircle::RenderBox2D(b2World *world)
{
	m_score = score;
	m_hp = hp;
	m_isRender = true;
	m_body = world->CreateBody(&m_bodyDef);
	m_body->CreateFixture(&m_fixtureDef);
	m_body->SetLinearVelocity(b2Vec2(0.0f, -m_enemySpeed));
}