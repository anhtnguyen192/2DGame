#include "EnemyCircle.h"

EnemyCircle::EnemyCircle(float radius)
{
	this->radius = radius;
	m_type = 2;
	m_isRender = false;
	circle.m_radius = this->radius;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.fixedRotation = true;
	
	m_fixtureDef.shape = &circle;
	m_fixtureDef.density = 100.0f;
	m_fixtureDef.filter.categoryBits = k_enemyCategory;
	m_fixtureDef.filter.maskBits = k_enemyMask;
	m_isHit = 0;
	m_timeHit = 0;
}

EnemyCircle::~EnemyCircle()
{

}


void EnemyCircle::RenderBox2D(b2World *world)
{
	m_score = score;
	int i = rand() % 2;
	if (i == 0)
	{
		posX = RandomFloat(-SCREEN_WIDTH / 2 + radius, SCREEN_WIDTH / 2 - radius);
		posY = (SCREEN_HEIGHT / 2) - radius;
	}
	else if (i == 1)
	{
		int j = rand() % 2;
		posY = RandomFloat((SCREEN_HEIGHT / 2) - 3.0f, (SCREEN_HEIGHT / 2) - radius);
		if (j == 0)
		{
			posX = -SCREEN_WIDTH / 2 + radius;
		}
		else if (j == 1)
		{
			posX = SCREEN_WIDTH / 2 - radius;
		}
	}
	m_bodyDef.position.Set(posX, posY);
	b2Vec2 velocity = Enemy::trajectory.at(rand() % Enemy::trajectory.size());
	velocity.x = velocity.x * m_enemySpeed;
	velocity.y = velocity.y * m_enemySpeed;
	m_bodyDef.linearVelocity = velocity;
	m_hp = hp;
	m_isRender = true;
	m_body = world->CreateBody(&m_bodyDef);
	m_body->CreateFixture(&m_fixtureDef);
}

void EnemyCircle::Update()
{
	Enemy::Update();
	/*b2Vec2 velocity = b2Vec2(RandomFloat(-1, 1), RandomFloat(-1, 1));
	velocity.x = velocity.x * m_enemySpeed;
	velocity.y = velocity.y * m_enemySpeed;
	m_body->SetLinearVelocity(velocity);*/
}