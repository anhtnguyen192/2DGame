#include "BossRectangle.h"

BossRectangle::BossRectangle(float width, float height)
{
	m_type = 2;
	m_isRender = false;
	this->width = width;
	this->height = height;

	boss.SetAsBox(this->width / 2, this->height / 2);

	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.fixedRotation = true;
	m_bodyDef.position.Set(0, (SCREEN_HEIGHT + this->height)/2);

	m_fixtureDef.shape = &boss;
	m_fixtureDef.density = 100.0f;
	m_fixtureDef.filter.categoryBits = 0;
	timeIntro = 0;
	m_isHit = 0;
	m_timeHit = 0;
}

BossRectangle::~BossRectangle()
{

}

bool BossRectangle::Intro()
{
	if (timeIntro <= (height / m_enemySpeed) * 60 + 500)
	{
		return true;
	}
	return false;
}

void BossRectangle::RenderBox2D(b2World* world)
{
	m_score = score;
	/*b2Vec2 velocity = Enemy::trajectory.at(rand() % Enemy::trajectory.size());
	velocity.x = velocity.x * m_enemySpeed;
	velocity.y = velocity.y * m_enemySpeed;
	m_bodyDef.linearVelocity = velocity;*/
	m_hp = hp;
	m_isRender = true;
	m_body = world->CreateBody(&m_bodyDef);
	m_body->CreateFixture(&m_fixtureDef);
	m_body->SetLinearVelocity(b2Vec2(0.0f, -m_enemySpeed));
}

void BossRectangle::ShootBullet(b2World* world)
{

	
}