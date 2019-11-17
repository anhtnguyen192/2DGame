#pragma once
#include <stdio.h>
#include "MainCharacter.h"
#include "BulletType1.h"
#include "EnemyCircle.h"
#include "EnemyRectangle.h"
#include "UpgradeBullet.h"
#include "UpgradeBulletLevel.h"
#include "EnemyBullet.h"
#include "Life.h"
#include "BossCircle.h"
#include "BossRectangle.h"
#include "DoublePoint.h"
#include <vector>

using namespace std;

class Box2DSceneManager
{
public:
	Box2DSceneManager();
	~Box2DSceneManager();
	vector <Object2D*> m_objectList;
	int m_objectNum; // number object type
	int m_maxBullet; // Max bullet of Main
	int m_bulletLevel; // current level of bullet Main
	int m_maxEnemy; // Max boss + Max Enemy circle + Max Enemy Rectangle
	int m_maxEnemyCircle; // Max Enemy circle
	int m_maxEnemyRectangle; // Max Enemy Rectangle
	int m_maxBoss; // Max boss Circle +  Max boss Rectangle
	int m_maxBossCircle; // Max boss Circle
	int m_maxBossRectangle; // Max boss Rectangle
	int m_maxItem; // max item
	int m_maxUpgradeBullet; // max upgrade bullet Main
	int m_maxDoublePoint; // maxDoublePoint
	int m_maxUpgradeBulletLevel; // Max Upgrade Level bullet
	int m_maxLife; // max life
	int m_maxEnemyBullet; // max Enemy bullet


	int scores; // score
	void LoadData();
	void DestroyInstance();
	

	static Box2DSceneManager* GetInstance();
private:
	static Box2DSceneManager* s_Instance;
	void LoadMain(FILE* fp, int id, char type[50], char hitbox[50]);
	void LoadBulletType1(FILE* fp, int id, char type[50], char hitbox[50]);
	void LoadEnemyCircle(FILE* fp, int id, char type[50], char hitbox[50]);
	void LoadEnemyRectangle(FILE* fp, int id, char type[50], char hitbox[50]);
	void LoadBossCircle(FILE* fp, int id, char type[50], char hitbox[50]);
	void LoadBossRectangle(FILE* fp, int id, char type[50], char hitbox[50]);
	void LoadEnemyBullet(FILE* fp, int id, char type[50], char hitbox[50]);
	void LoadItemUpgradeBullet(FILE* fp, int id, char type[50], char hitbox[50]);
	void LoadItemLife(FILE* fp, int id, char type[50], char hitbox[50]);
	void LoadItemDoublePoint(FILE* fp, int id, char type[50], char hitbox[50]);
	void LoadItemUpgradeBulletLevel(FILE* fp, int id, char type[50], char hitbox[50]);
};

