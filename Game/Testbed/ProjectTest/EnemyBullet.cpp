#include "EnemyBullet.h"

EnemyBullet::EnemyBullet()
{
	m_hp = 1;
	m_isRender = false;

	m_bodyDef.linearVelocity = b2Vec2(RandomFloat(-0.5, 0.5), -1.5f);
	m_bodyDef.fixedRotation = true;
	m_bodyDef.type = b2_dynamicBody;	
}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::RenderBox2D(b2World* world)
{
	
	b2CircleShape shape;
	shape.m_radius = radius;

	m_fixtureDef.shape = &shape;

	m_fixtureDef.density = 0.001f;

	m_fixtureDef.filter.categoryBits = k_itemCategory;
	m_fixtureDef.filter.maskBits = k_itemMask;

	m_isRender = true;
	m_bodyDef.position.Set(posX, posY);
	m_body = world->CreateBody(&m_bodyDef);
	m_body->CreateFixture(&m_fixtureDef);
}