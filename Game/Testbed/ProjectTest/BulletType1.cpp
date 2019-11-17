#include "BulletType1.h"



BulletType1::BulletType1()
{
	m_body = NULL;
	m_type = 3;
	m_isRender = false;
	
	
}


BulletType1::~BulletType1()
{
}

void BulletType1::RenderBox2D(b2World *world) {
	if (m_body != NULL)
	{
		world->DestroyBody(m_body);
		m_body = NULL;
	}
	b2PolygonShape rectangle;
	rectangle.SetAsBox(this->width / 2, this->height / 2);

	m_fixtureDef.shape = &rectangle;
	m_fixtureDef.density = 0.001f;
	m_fixtureDef.filter.categoryBits = k_bulletCategory;
	m_fixtureDef.filter.maskBits = k_bulletMask;

	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.fixedRotation = true;
	m_bodyDef.bullet = true;

	//m_bodyDef.position.Set(Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_body->GetPosition().x, Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_body->GetPosition().y + 0.5);
	m_isRender = true;

	m_body = world->CreateBody(&m_bodyDef);
	m_body->CreateFixture(&m_fixtureDef);
	m_body->SetGravityScale(0);
	m_body->SetLinearVelocity(b2Vec2(0.0f, m_bulletSpeed));
}
