#include "Box2DSceneManager.h"


#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 160

Box2DSceneManager::Box2DSceneManager()
{
	m_bulletLevel = 1;
}


Box2DSceneManager::~Box2DSceneManager()
{
	for (int i = 0; i < m_objectList.size(); i++)
	{
		delete m_objectList.at(i);
	}
	m_objectList.clear();
}

void Box2DSceneManager::LoadMain(FILE* fp, int id, char type[50], char hitbox[50])
{
	Object2D *o = new MainCharacter();
	fscanf(fp, "POS:  %f %f\n", &o->posX, &o->posY);
	fscanf(fp, "SIZE: %f %f\n", &o->width, &o->height);
	fscanf(fp, "LIFE: %d\n\n", &o->m_life);
	o->m_id = id;
	strcpy(o->m_name, type);
	strcpy(o->m_hitbox, hitbox);
	m_objectList.push_back(o);
}

void Box2DSceneManager::LoadBulletType1(FILE* fp, int id, char type[50], char hitbox[50])
{
	float fs, bs;
	float width, height;
	float dame;
	fscanf(fp, "QUANTITY: %d\n", &m_maxBullet);
	fscanf(fp, "FIRING_SPEED: %f\n", &fs);
	fscanf(fp, "BULLET_SPEED: %f\n", &bs);
	fscanf(fp, "SIZE: %f %f\n", &width, &height);
	fscanf(fp, "DAME: %f\n\n", &dame);
	for (int i = 0; i < m_maxBullet; i++)
	{
		Bullet *b = new BulletType1();
		b->m_bulletSpeed = bs;
		b->m_firingSpeed = fs;
		b->height = height;
		b->width = width;
		b->hp = dame;
		b->m_hp = b->hp;
		b->m_id = id;
		strcpy(b->m_name, type);
		strcpy(b->m_hitbox, hitbox);
		m_objectList.push_back(b);
	}
}

void Box2DSceneManager::LoadEnemyCircle(FILE* fp, int id, char type[50], char hitbox[50])
{
	float radius;
	float hp;
	float speed, score;
	fscanf(fp, "QUANTITY: %d\n", &m_maxEnemyCircle);
	fscanf(fp, "RADIUS: %f\n", &radius);
	fscanf(fp, "SPEED: %f\n", &speed);
	fscanf(fp, "HP: %f\n", &hp);
	fscanf(fp, "SCORE: %f\n\n", &score);
	for (int i = 0; i < m_maxEnemyCircle; i++)
	{
		EnemyCircle* enemyCircle = new EnemyCircle(radius);
		enemyCircle->hp = hp;
		enemyCircle->m_enemySpeed = speed;
		enemyCircle->score = score;
		enemyCircle->m_id = id;
		strcpy(enemyCircle->m_name, type);
		strcpy(enemyCircle->m_hitbox, hitbox);
		m_objectList.push_back(enemyCircle);
	}
}

void Box2DSceneManager::LoadEnemyRectangle(FILE* fp, int id, char type[50], char hitbox[50])
{
	float width, height;
	float hp;
	float speed, score;
	fscanf(fp, "QUANTITY: %d\n", &m_maxEnemyRectangle);
	fscanf(fp, "SIZE: %f %f\n", &width, &height);
	fscanf(fp, "SPEED: %f\n", &speed);
	fscanf(fp, "HP: %f\n", &hp);
	fscanf(fp, "SCORE: %f\n\n", &score);
	for (int i = 0; i < m_maxEnemyRectangle; i++)
	{
		EnemyRectangle* enemyRectangle = new EnemyRectangle(width, height);
		enemyRectangle->hp = hp;
		enemyRectangle->m_enemySpeed = speed;
		enemyRectangle->score = score;
		enemyRectangle->m_id = id;
		strcpy(enemyRectangle->m_name, type);
		strcpy(enemyRectangle->m_hitbox, hitbox);
		m_objectList.push_back(enemyRectangle);
	}
}

void Box2DSceneManager::LoadBossCircle(FILE* fp, int id, char type[50], char hitbox[50])
{
	float radius;
	float hp;
	float speed, score;
	fscanf(fp, "QUANTITY: %d\n", &m_maxBossCircle);
	fscanf(fp, "RADIUS: %f\n", &radius);
	fscanf(fp, "SPEED: %f\n", &speed);
	fscanf(fp, "HP: %f\n", &hp);
	fscanf(fp, "SCORE: %f\n\n", &score);
	for (int i = 0; i < m_maxBossCircle; i++)
	{
		BossCircle* bossCircle = new BossCircle(radius);
		bossCircle->hp = hp;
		bossCircle->m_enemySpeed = speed;
		bossCircle->score = score;
		bossCircle->m_id = id;
		strcpy(bossCircle->m_name, type);
		strcpy(bossCircle->m_hitbox, hitbox);
		m_objectList.push_back(bossCircle);
	}
}

void Box2DSceneManager::LoadBossRectangle(FILE* fp, int id, char type[50], char hitbox[50])
{
	float width, height;
	float hp;
	float speed, score;
	fscanf(fp, "QUANTITY: %d\n", &m_maxBossRectangle);
	fscanf(fp, "SIZE: %f %f\n", &width, &height);
	fscanf(fp, "SPEED: %f\n", &speed);
	fscanf(fp, "HP: %f\n", &hp);
	fscanf(fp, "SCORE: %f\n\n", &score);
	for (int i = 0; i < m_maxBossRectangle; i++)
	{
		BossRectangle* bossRectangle = new BossRectangle(width, height);
		bossRectangle->hp = hp;
		bossRectangle->m_enemySpeed = speed;
		bossRectangle->score = score;
		bossRectangle->m_id = id;
		strcpy(bossRectangle->m_name, type);
		strcpy(bossRectangle->m_hitbox, hitbox);
		m_objectList.push_back(bossRectangle);
	}
}

void Box2DSceneManager::LoadEnemyBullet(FILE* fp, int id, char type[50], char hitbox[50])
{
	float radius;
	fscanf(fp, "QUANTITY: %d\n", &m_maxEnemyBullet);
	fscanf(fp, "RADIUS: %f\n", &radius);
	for (int i = 0; i < m_maxEnemyBullet; i++)
	{
		EnemyBullet* enemyBullet = new EnemyBullet();
		enemyBullet->radius = radius;
		enemyBullet->m_id = id;
		strcpy(enemyBullet->m_name, type);
		strcpy(enemyBullet->m_hitbox, hitbox);
		Box2DSceneManager::GetInstance()->m_objectList.push_back(enemyBullet);
	}
}

void Box2DSceneManager::LoadItemUpgradeBullet(FILE* fp, int id, char type[50], char hitbox[50])
{
	float dp;
	float radius;
	fscanf(fp, "DROP_PERCENTAGE: %f\n", &dp);
	fscanf(fp, "QUANTITY: %d\n", &m_maxUpgradeBullet);
	fscanf(fp, "RADIUS: %f\n\n", &radius);
	for (int i = 0; i < m_maxUpgradeBullet; i++)
	{
		UpgradeBullet* upgradeBullet = new UpgradeBullet();
		upgradeBullet->radius = radius;
		upgradeBullet->m_dropPercentage = dp;
		upgradeBullet->m_id = id;
		strcpy(upgradeBullet->m_name, type);
		strcpy(upgradeBullet->m_hitbox, hitbox);
		Box2DSceneManager::GetInstance()->m_objectList.push_back(upgradeBullet);
	}
}

void Box2DSceneManager::LoadItemLife(FILE* fp, int id, char type[50], char hitbox[50])
{
	float dp;
	float width, height;
	fscanf(fp, "DROP_PERCENTAGE: %f\n", &dp);
	fscanf(fp, "QUANTITY: %d\n", &m_maxLife);
	fscanf(fp, "SIZE: %f %f\n\n", &width, &height);
	for (int i = 0; i < m_maxLife; i++)
	{
		Life *s = new Life();
		s->width = width;
		s->height = height;
		s->m_dropPercentage = dp;
		s->m_id = id;
		strcpy(s->m_name, type);
		strcpy(s->m_hitbox, hitbox);
		Box2DSceneManager::GetInstance()->m_objectList.push_back(s);
	}
}

void Box2DSceneManager::LoadItemDoublePoint(FILE* fp, int id, char type[50], char hitbox[50])
{
	float dp;
	float radius;
	fscanf(fp, "DROP_PERCENTAGE: %f\n", &dp);
	fscanf(fp, "QUANTITY: %d\n", &m_maxDoublePoint);
	fscanf(fp, "RADIUS: %f\n\n", &radius);
	for (int i = 0; i < m_maxDoublePoint; i++)
	{
		DoublePoint* doublePoint = new DoublePoint();
		doublePoint->radius = radius;
		doublePoint->m_dropPercentage = dp;
		doublePoint->m_id = id;
		strcpy(doublePoint->m_name, type);
		strcpy(doublePoint->m_hitbox, hitbox);
		Box2DSceneManager::GetInstance()->m_objectList.push_back(doublePoint);
	}
}

void Box2DSceneManager::LoadItemUpgradeBulletLevel(FILE* fp, int id, char type[50], char hitbox[50])
{
	float dp;
	float radius;
	fscanf(fp, "DROP_PERCENTAGE: %f\n", &dp);
	fscanf(fp, "QUANTITY: %d\n", &m_maxUpgradeBulletLevel);
	fscanf(fp, "RADIUS: %f\n\n", &radius);
	for (int i = 0; i < m_maxUpgradeBulletLevel; i++)
	{
		UpgradeBulletLevel* upgradeBulletLevel = new UpgradeBulletLevel();
		upgradeBulletLevel->radius = radius;
		upgradeBulletLevel->m_dropPercentage = dp;
		upgradeBulletLevel->m_id = id;
		strcpy(upgradeBulletLevel->m_name, type);
		strcpy(upgradeBulletLevel->m_hitbox, hitbox);
		Box2DSceneManager::GetInstance()->m_objectList.push_back(upgradeBulletLevel);
	}
}
void Box2DSceneManager::LoadData() {
	FILE *fp = fopen("../Resources/Box2D_SM.txt", "r");
	if (fp == NULL) {
		printf("the fuck");
		return;
	}
	fscanf(fp, "#Objects: %d\n\n", &m_objectNum);
	for (int i = 0; i < m_objectNum; i++)
	{
		int id;
		char type[50];
		char hitbox[50];
		fscanf(fp, "ID %d %s\n", &id, type);
		fscanf(fp, "HITBOX: %s\n", hitbox);
		
		if (strcmp(type, "MainCharacter") == 0)
		{
			LoadMain(fp, id, type, hitbox);
		}
		if (strcmp(type, "BulletType1") == 0)
		{
			LoadBulletType1(fp, id, type, hitbox);
		}
		if (strcmp(type, "EnemyCircle") == 0)
		{
			LoadEnemyCircle(fp, id, type, hitbox);
		}
		if (strcmp(type, "EnemyRectangle") == 0)
		{
			LoadEnemyRectangle(fp, id, type, hitbox);
		}
		if (strcmp(type, "BossCircle") == 0)
		{
			LoadBossCircle(fp, id, type, hitbox);
		}
		if (strcmp(type, "BossRectangle") == 0)
		{
			LoadBossRectangle(fp, id, type, hitbox);
		}
		if (strcmp(type, "EnemyBullet") == 0)
		{
			LoadEnemyBullet(fp, id, type, hitbox);
		}
		if (strcmp(type, "ItemUpgradeBullet") == 0)
		{
			LoadItemUpgradeBullet(fp, id, type, hitbox);
		}
		if (strcmp(type, "ItemLife") == 0)
		{
			LoadItemLife(fp, id, type, hitbox);
		}
		if (strcmp(type, "ItemDoublePoint") == 0)
		{
			LoadItemDoublePoint(fp, id, type, hitbox);
		}
		if (strcmp(type, "ItemUpgradeBulletLevel") == 0)
		{
			LoadItemUpgradeBulletLevel(fp, id, type, hitbox);
		}
	}
	fclose(fp);
	m_maxBoss = m_maxBossCircle + m_maxBossRectangle;
	m_maxEnemy = m_maxEnemyCircle + m_maxEnemyRectangle + m_maxBoss;
	m_maxItem = m_maxUpgradeBullet + m_maxLife + m_maxDoublePoint + m_maxUpgradeBulletLevel;
}

void Box2DSceneManager::DestroyInstance()
{
	if (s_Instance) delete s_Instance;
	s_Instance = nullptr;
}



Box2DSceneManager* Box2DSceneManager::s_Instance = 0;
Box2DSceneManager* Box2DSceneManager::GetInstance()
{
	if (!s_Instance) {
		s_Instance = new Box2DSceneManager();
	}
	return s_Instance;
}