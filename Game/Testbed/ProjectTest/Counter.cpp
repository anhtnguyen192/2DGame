#include "Counter.h"



Counter::Counter()
{
}


Counter::~Counter()
{
}

void Counter::Init()
{
	timeCountRenderBullet = 0;
	timeCountRenderEnemy = 0;
	timeCountUpdateEnemy = 0;
	timeCountRespawn = 0;
	timeCountDoublePoint = 300;
	enemyRenderCount = 0;
	killCount = 0;
	timeCountEnemyShoot = 0;
	stage = 0; 

	timeRenderEnemy = 120;
	timeUpdateEnemy = 60;
	timeRespawn = 240;
	timeDoublePoint = 240;
	timeEnemyShoot = 240;
	timeBossShoot = 60;
	enemyRender = 10;

	enemyShootPercentage = 80;
	bossShootPercentage = 80;
}

void Counter::StageComplete()
{
	stage++;
	enemyRender += 5; 
	timeRenderEnemy *= 0.8;
	timeBossShoot *= 0.8;
	timeEnemyShoot *= 0.8;
	enemyShootPercentage += 1;
	bossShootPercentage += 2;
}

void Counter::UpdateCounter()
{
	timeCountEnemyShoot++;
	timeCountRenderBullet++;
	timeCountUpdateEnemy++;
	timeCountRespawn++;
	timeCountDoublePoint++;
}

void Counter::DestroyInstance()
{
	if (s_Instance) delete s_Instance;
	s_Instance = nullptr;
}

Counter* Counter::s_Instance = 0;
Counter* Counter::GetInstance()
{
	if (!s_Instance) {
		s_Instance = new Counter();
	}
	return s_Instance;
}
