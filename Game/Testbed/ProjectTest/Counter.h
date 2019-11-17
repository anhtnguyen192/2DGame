#pragma once
#include <math.h>

// Manager of count in game
class Counter
{
public:
	Counter();
	~Counter();
	int timeCountRenderBullet;
	int timeCountRenderEnemy;
	int timeCountUpdateEnemy;
	int timeCountRespawn;
	int timeCountEnemyShoot;
	int timeCountDoublePoint;
	
	int timeRenderBullet;
	int timeRenderEnemy;
	int timeUpdateEnemy;
	int timeRespawn;
	int timeEnemyShoot;
	int timeBossShoot;
	int enemyRender;
	int timeDoublePoint;

	int enemyRenderCount;
	int killCount;
	int stage;

	float enemyShootPercentage;
	float bossShootPercentage;

	void Init();
	void StageComplete();
	void UpdateCounter();
	void DestroyInstance();

	static Counter* GetInstance();
private:
	static Counter* s_Instance;
};

