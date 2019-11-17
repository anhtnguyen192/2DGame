#include "EnemyRectangle.h"

EnemyRectangle::EnemyRectangle(float width, float height)
{
	m_type = 2;
	m_isRender = false;
	this->width = width;
	this->height = height;

	rectangle.SetAsBox(this->width / 2, this->height / 2);

	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.fixedRotation = true;

	m_fixtureDef.shape = &rectangle;
	m_fixtureDef.density = 100.0f;
	m_fixtureDef.filter.categoryBits = k_enemyCategory;
	m_fixtureDef.filter.maskBits = k_enemyMask;
	m_isHit = 0;
	m_timeHit = 0;
}

EnemyRectangle::~EnemyRectangle()
{

}

void EnemyRectangle::RenderBox2D(b2World* world)
{
	m_score = score;
	posX = RandomFloat((-SCREEN_WIDTH + width) / 2, (SCREEN_WIDTH - width) / 2);
	posY = (SCREEN_HEIGHT - height) / 2;
	m_bodyDef.position.Set(posX, posY);
	b2Vec2 velocity = b2Vec2(0,-1);
	velocity.x = velocity.x * m_enemySpeed;
	velocity.y = velocity.y * m_enemySpeed;
	m_bodyDef.linearVelocity = velocity;
	m_hp = hp;
	m_isRender = true;
	m_body = world->CreateBody(&m_bodyDef);
	m_body->CreateFixture(&m_fixtureDef);
}

void EnemyRectangle::Update()
{
	b2Vec2 velocity = b2Vec2(RandomFloat(-0.5, 0.5), -1);
	velocity.x = velocity.x * m_enemySpeed;
	velocity.y = velocity.y * m_enemySpeed;
	m_body->SetLinearVelocity(velocity);
}