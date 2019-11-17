#include "MainCharacter.h"



MainCharacter::MainCharacter()
{
	hp = 1000;
	m_type = 1;
	m_hp = hp;
	m_isRender = false;
	m_isInvincible = false;
	m_bulletLevel = 0;
	m_fixtureDef.filter.categoryBits = k_mainCategory;
	m_fixtureDef.filter.maskBits = k_mainMask;
	mainFilter.categoryBits = k_mainCategory;
	mainFilter.maskBits = k_mainMask;
	m_isHit = 0;
	m_timeHit = 0;
}


MainCharacter::~MainCharacter()
{
}



void MainCharacter::RenderBox2D(b2World *world) {
	b2PolygonShape shape;
	shape.SetAsBox(width, height);

	m_fixtureDef.shape = &shape;
	m_fixtureDef.density = 100.0f;

	m_bodyDef.fixedRotation = true;
	m_bodyDef.type = b2_kinematicBody;
	m_bodyDef.position.Set(posX, posY);
	m_hp = hp;
	m_isRender = true;
	m_isInvincible = true;
	
	m_body = world->CreateBody(&m_bodyDef);
	m_body->CreateFixture(&m_fixtureDef);
}

bool MainCharacter::GetInvincibleState() {
	return m_isInvincible;
}

void MainCharacter::SetInvincibleState(bool b) {
	m_isInvincible = b;
}

void MainCharacter::TouchActionMove(b2World *world, int x, int y, int currentX, int currentY) {
	b2Vec2 p = b2Vec2(CoorGLToBox2DForX(x), CoorGLToBox2DForY(y));

	if (m_body->GetPosition().x > 5.0625 / 2 && currentX < x) return;
	else if (m_body->GetPosition().x < -5.0625 / 2 && currentX > x) return;
	else if (m_body->GetPosition().y > 9.0 / 2 && currentY < y) return;
	else if (m_body->GetPosition().y < -9.0 / 2 && currentY > y) return;
	else {
		m_body->SetTransform(b2Vec2(m_body->GetPosition().x + p.x - CoorGLToBox2DForX(currentX), m_body->GetPosition().y + p.y - CoorGLToBox2DForY(currentY)), 0);
	}

	
}


void MainCharacter::IsDestroyed()
{
	m_life--;
	if (m_bulletLevel >= 2) {
		m_bulletLevel -= 2;
	}
	else
	{
		m_bulletLevel = 0;
	}
}

void MainCharacter::Move(b2Vec2 p)

{
	if (abs(m_body->GetPosition().x) < 5.625 / 2 && abs(m_body->GetPosition().y) < 10 / 2)
	{
		m_body->SetTransform(b2Vec2(m_body->GetPosition().x + p.x - prevPos.x, m_body->GetPosition().y + p.y - prevPos.y), 0);
	}
	
}

float MainCharacter::CoorGLToBox2DForX(int x)
{
	float tmp = (float) x;
	return tmp / 106.66 - 5.0625 /2;
	
}

float MainCharacter::CoorGLToBox2DForY(int y)
{
	float tmp = (float)y;
	return tmp / 106.66 - 9.0 / 2;

}

void MainCharacter::Respawn(b2World *world)
{
	if (m_isRender == false)
	{
		if (m_life > 0)
		{
			if (Counter::GetInstance()->timeCountRespawn == Counter::GetInstance()->timeRespawn)
			{
				m_fixtureDef.filter.categoryBits = 0;
				RenderBox2D(world);
				m_isHit = 1;
			}
		}
		else
		{
			printf("End Game :))\n");
		}
	}

	//invincible state after respawn
	if (Counter::GetInstance()->timeCountRespawn == Counter::GetInstance()->timeRespawn * 2 && m_life > 0)
	{
		m_body->GetFixtureList()->SetFilterData(mainFilter);
		SetInvincibleState(false);
		m_isHit = 0;
	}
}