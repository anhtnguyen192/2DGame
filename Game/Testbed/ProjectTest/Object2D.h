#pragma once
#include "..\Test.h"
#include "Counter.h"

#define SCREEN_WIDTH 5.625
#define SCREEN_HEIGHT 10

const uint16 k_mainCategory = 0x0002;
const uint16 k_enemyCategory = 0x0004;
const uint16 k_bulletCategory = 0x0008;
const uint16 k_itemCategory = 0x0010;

const uint16 k_itemMask = 0xFFFF ^ k_enemyCategory ^ k_bulletCategory ^ k_itemCategory;
const uint16 k_mainMask = 0xFFFF ^ k_bulletCategory;
const uint16 k_enemyMask = 0xFFFF ^ k_enemyCategory;
const uint16 k_bulletMask = 0xFFFF ^ k_bulletCategory ^ k_mainCategory;

class Object2D
{
public:
	Object2D();
	~Object2D();
	b2Body *m_body;
	int m_id;
	int m_type;
	char m_hitbox[50];
	char m_name[50];
	int m_life;
	float m_hp;
	float hp;
	b2BodyDef m_bodyDef;
	b2FixtureDef m_fixtureDef;
	bool m_isRender;
	bool m_isHit;
	int m_timeHit;
	float radius, width, height, posX, posY, initialLife;
	virtual int GetBulletRest() { return 0; };
	virtual float GetItemDropPercentage() { return 0; }
	virtual bool GetInvincibleState() { return false; }
	virtual void SetInvincibleState(bool b) {};
	virtual void RenderBox2D(b2World *world) {};
	virtual void IsDestroyed() {};
	virtual void Update() {};
	virtual void TouchActionMove(b2World *world, int x, int y, int currentX, int currentY) {};

};

