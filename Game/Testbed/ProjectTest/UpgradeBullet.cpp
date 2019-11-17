#include "UpgradeBullet.h"



UpgradeBullet::UpgradeBullet()
{
	m_body = NULL;
	m_isRender = false;
	
}


UpgradeBullet::~UpgradeBullet()
{
}

void UpgradeBullet::RenderBox2D(b2World *world) {
	if (m_body != NULL)
	{
		world->DestroyBody(m_body);
		m_body = NULL;
	}
	m_isRender = true;
	
	b2CircleShape shape;
	shape.m_radius = radius;

	m_fixtureDef.shape = &shape;
	m_fixtureDef.density = 0.001f;
	m_fixtureDef.filter.categoryBits = k_itemCategory;
	m_fixtureDef.filter.maskBits = k_itemMask;

	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.bullet = true;
	m_bodyDef.position.Set(posX, posY);

	m_body = world->CreateBody(&m_bodyDef);
	m_body->CreateFixture(&m_fixtureDef);
	m_body->SetGravityScale(0);
	m_body->SetLinearVelocity(b2Vec2(0.0f, -1.0f));
}


