#include "AddPair.h"

AddPair::~AddPair()
{
	Counter::GetInstance()->DestroyInstance();
	Box2DSceneManager::GetInstance()->DestroyInstance();
	delete settings;
}

void AddPair::DestroyInstance()
{
	if (s_Instance) delete s_Instance;
	s_Instance = nullptr;
}

AddPair::AddPair()
{

	settings = new Settings();
	m_isX2score = false;
}

void AddPair::Init()
{
	printf("init addpair");
	b = Box2DSceneManager::GetInstance();
	Box2DSceneManager::GetInstance()->LoadData();
	t = Counter::GetInstance();
	
	m_world->SetGravity(b2Vec2(0.0f, 0.0f));
	Counter::GetInstance()->Init();
	Box2DSceneManager::GetInstance()->scores = 0;
	srand(time(NULL));
	randomBoss = rand() % 2;
	
	printf("%d\n", randomBoss);
	b2BodyDef bd;
	b2Body* ground;
	//b2BodyDef bd;
	bd.type = b2_staticBody;
	bd.position.Set(0.0f, 0.0f);
	ground = m_world->CreateBody(&bd);


	b2EdgeShape topGround;
	b2EdgeShape botGround;
	b2EdgeShape leftGround;
	b2EdgeShape rightGround;
	topGround.Set(b2Vec2(-SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), b2Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	botGround.Set(b2Vec2(-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2), b2Vec2(SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2));
	leftGround.Set(b2Vec2(-SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), b2Vec2(-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2));
	rightGround.Set(b2Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), b2Vec2(SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2));

	ground->CreateFixture(&topGround, 0.0f);
	ground->CreateFixture(&botGround, 0.0f);
	ground->CreateFixture(&leftGround, 0.0f);
	ground->CreateFixture(&rightGround, 0.0f);

	
	Box2DSceneManager::GetInstance()->m_objectList.at(0)->RenderBox2D(m_world);
	Box2DSceneManager::GetInstance()->m_objectList.at(0)->SetInvincibleState(false);
	printf("make new Addpair \n");
}

void AddPair::Step(Settings* settings) {
	//randomBoss = rand() % 2;
	//printf("Boss: %d\n", randomBoss);
	// move main character via touch action
	/*if (Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_isRender == true)
	{
	Box2DSceneManager::GetInstance()->m_objectList.at(0)->TouchActionMove(m_world, b2Vec2(0, -4.5));
	}*/

	// render enemy after certain time
	//printf("%f, %f\n ", Box2DSceneManager::GetInstance()->m_objectList.at(1 + Box2DSceneManager::GetInstance()->m_maxBullet)->hp, Box2DSceneManager::GetInstance()->m_objectList.at(1)->m_hp);
	//b = Box2DSceneManager::GetInstance();
	//t = Counter::GetInstance();
	if (Counter::GetInstance()->enemyRenderCount == Counter::GetInstance()->enemyRender)
	{
		if (Counter::GetInstance()->killCount == Counter::GetInstance()->enemyRenderCount)
		{
			dynamic_cast <Boss*> (Box2DSceneManager::GetInstance()->m_objectList.at(1 + Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemyCircle + Box2DSceneManager::GetInstance()->m_maxEnemyRectangle + randomBoss))->BossEntering(m_world);
		}
		if (Counter::GetInstance()->killCount == (Counter::GetInstance()->enemyRenderCount + 1))
		{
			Box2DSceneManager::GetInstance()->m_objectList.at(1 + Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemyCircle + Box2DSceneManager::GetInstance()->m_maxEnemyRectangle + randomBoss)->IsDestroyed();
			
			srand(time(NULL)); 
			randomBoss = rand() % 2;
			//printf("Boss: %d\n", randomBoss);
			Counter::GetInstance()->StageComplete();
			for (int i1 = 0; i1 < Box2DSceneManager::GetInstance()->m_maxEnemy; i1++)
			{
				dynamic_cast <Enemy*> (Box2DSceneManager::GetInstance()->m_objectList.at(1 + Box2DSceneManager::GetInstance()->m_maxBullet + i1))->UpgradePower();
			}
		}
	}
	else
	{
		//render normal enemy
		if (Counter::GetInstance()->timeCountRenderEnemy >= Counter::GetInstance()->timeRenderEnemy)
		{
			int j, count = 0;
			do {
				srand(time(NULL));
				j = rand() % (Box2DSceneManager::GetInstance()->m_maxEnemy - Box2DSceneManager::GetInstance()->m_maxBoss);
				count++;
			} while (Box2DSceneManager::GetInstance()->m_objectList.at(j + Box2DSceneManager::GetInstance()->m_maxBullet + 1)->m_isRender == true
				&& count != Box2DSceneManager::GetInstance()->m_maxEnemy - Box2DSceneManager::GetInstance()->m_maxBoss);
			if (Box2DSceneManager::GetInstance()->m_objectList.at(j + Box2DSceneManager::GetInstance()->m_maxBullet + 1)->m_isRender == false) {
				Box2DSceneManager::GetInstance()->m_objectList.at(j + Box2DSceneManager::GetInstance()->m_maxBullet + 1)->RenderBox2D(m_world);
				Counter::GetInstance()->enemyRenderCount++;
			}
			Counter::GetInstance()->timeCountRenderEnemy = 0;
		}
		Counter::GetInstance()->timeCountRenderEnemy++;
	}

	// enemy is Hit ?

	for (int i2 = 0; i2 < Box2DSceneManager::GetInstance()->m_maxEnemy; i2++)
	{
		if (Box2DSceneManager::GetInstance()->m_objectList.at(i2 + Box2DSceneManager::GetInstance()->m_maxBullet + 1)->m_isRender == 1)
		{
			if (Box2DSceneManager::GetInstance()->m_objectList.at(i2 + Box2DSceneManager::GetInstance()->m_maxBullet + 1)->m_isHit == 1)
			{
				if (Box2DSceneManager::GetInstance()->m_objectList.at(i2 + Box2DSceneManager::GetInstance()->m_maxBullet + 1)->m_timeHit < 20)
				{
					Box2DSceneManager::GetInstance()->m_objectList.at(i2 + Box2DSceneManager::GetInstance()->m_maxBullet + 1)->m_timeHit++;
				}
				else
				{
					Box2DSceneManager::GetInstance()->m_objectList.at(i2 + Box2DSceneManager::GetInstance()->m_maxBullet + 1)->m_timeHit = 0;
					Box2DSceneManager::GetInstance()->m_objectList.at(i2 + Box2DSceneManager::GetInstance()->m_maxBullet + 1)->m_isHit = 0;
				}
			}
		}
	}

	//update enemy movement
	if (Counter::GetInstance()->timeCountUpdateEnemy == Counter::GetInstance()->timeUpdateEnemy)
	{
		for (int i3 = 0; i3 < Box2DSceneManager::GetInstance()->m_maxEnemy; i3++)
		{
			if (Box2DSceneManager::GetInstance()->m_objectList.at(i3 + Box2DSceneManager::GetInstance()->m_maxBullet + 1)->m_isRender == true)
			{
				if (i3 >= Box2DSceneManager::GetInstance()->m_maxEnemy - Box2DSceneManager::GetInstance()->m_maxBoss)
				{
					if (dynamic_cast <Boss*> (Box2DSceneManager::GetInstance()->m_objectList.at(i3 + Box2DSceneManager::GetInstance()->m_maxBullet + 1))->Intro() == false)
					{
						Box2DSceneManager::GetInstance()->m_objectList.at(i3 + Box2DSceneManager::GetInstance()->m_maxBullet + 1)->Update();
					}
				}
				else
				{
					Box2DSceneManager::GetInstance()->m_objectList.at(i3 + Box2DSceneManager::GetInstance()->m_maxBullet + 1)->Update();
				}
			}
		}
		Counter::GetInstance()->timeCountUpdateEnemy = 0;
	}

	//Boss shoot bullet
	if (Box2DSceneManager::GetInstance()->m_objectList.at(1 + Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemyCircle + Box2DSceneManager::GetInstance()->m_maxEnemyRectangle + randomBoss)->m_isRender)
	{
		if (dynamic_cast <Boss*> (Box2DSceneManager::GetInstance()->m_objectList.at(1 + Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemyCircle + Box2DSceneManager::GetInstance()->m_maxEnemyRectangle + randomBoss))->Intro() == false)
		{
			if (Counter::GetInstance()->timeCountEnemyShoot == Counter::GetInstance()->timeBossShoot)
			{
				float isShoot = RandomFloat(0.0f, 100.0f);
				if (isShoot < Counter::GetInstance()->bossShootPercentage)
				{
					b2Vec2 enemyBulletPos = Box2DSceneManager::GetInstance()->m_objectList.at(1 + Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemyCircle + Box2DSceneManager::GetInstance()->m_maxEnemyRectangle + randomBoss)->m_body->GetPosition();
					for (int j1 = 0; j1 < Box2DSceneManager::GetInstance()->m_maxEnemyBullet; j1++)
					{
						if (Box2DSceneManager::GetInstance()->m_objectList.at(j1 + Box2DSceneManager::GetInstance()->m_maxBullet + 1 + Box2DSceneManager::GetInstance()->m_maxEnemy)->m_isRender == false)
						{
							if (randomBoss == 1)
							{
								Box2DSceneManager::GetInstance()->m_objectList.at(j1 + Box2DSceneManager::GetInstance()->m_maxBullet + 1 + Box2DSceneManager::GetInstance()->m_maxEnemy)->posX = enemyBulletPos.x + RandomFloat(-Box2DSceneManager::GetInstance()->m_objectList.at(1 + Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemyCircle + Box2DSceneManager::GetInstance()->m_maxEnemyRectangle + randomBoss)->width / 2, Box2DSceneManager::GetInstance()->m_objectList.at(1 + Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemyCircle + Box2DSceneManager::GetInstance()->m_maxEnemyRectangle + randomBoss)->width / 2);
								Box2DSceneManager::GetInstance()->m_objectList.at(j1 + Box2DSceneManager::GetInstance()->m_maxBullet + 1 + Box2DSceneManager::GetInstance()->m_maxEnemy)->posY = enemyBulletPos.y - Box2DSceneManager::GetInstance()->m_objectList.at(1 + Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemyCircle + Box2DSceneManager::GetInstance()->m_maxEnemyRectangle + randomBoss)->height / 2;
								Box2DSceneManager::GetInstance()->m_objectList.at(j1 + Box2DSceneManager::GetInstance()->m_maxBullet + 1 + Box2DSceneManager::GetInstance()->m_maxEnemy)->RenderBox2D(m_world);
								break;
							}
							else if (randomBoss == 0)
							{
								Box2DSceneManager::GetInstance()->m_objectList.at(j1 + Box2DSceneManager::GetInstance()->m_maxBullet + 1 + Box2DSceneManager::GetInstance()->m_maxEnemy)->posX = enemyBulletPos.x + RandomFloat(-Box2DSceneManager::GetInstance()->m_objectList.at(1 + Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemyCircle + Box2DSceneManager::GetInstance()->m_maxEnemyRectangle + randomBoss)->radius, Box2DSceneManager::GetInstance()->m_objectList.at(1 + Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemyCircle + Box2DSceneManager::GetInstance()->m_maxEnemyRectangle + randomBoss)->radius);
								Box2DSceneManager::GetInstance()->m_objectList.at(j1 + Box2DSceneManager::GetInstance()->m_maxBullet + 1 + Box2DSceneManager::GetInstance()->m_maxEnemy)->posY = enemyBulletPos.y - Box2DSceneManager::GetInstance()->m_objectList.at(1 + Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemyCircle + Box2DSceneManager::GetInstance()->m_maxEnemyRectangle + randomBoss)->radius;
								Box2DSceneManager::GetInstance()->m_objectList.at(j1 + Box2DSceneManager::GetInstance()->m_maxBullet + 1 + Box2DSceneManager::GetInstance()->m_maxEnemy)->RenderBox2D(m_world);
								break;
							}
						}
					}
				}

				Counter::GetInstance()->timeCountEnemyShoot = 0;
			}
		}
	}

	// enemy shoot bullet
	if (Counter::GetInstance()->timeCountEnemyShoot >= Counter::GetInstance()->timeEnemyShoot)
	{
		for (int i4 = 0; i4 < Box2DSceneManager::GetInstance()->m_maxEnemy - Box2DSceneManager::GetInstance()->m_maxBoss; i4++)
		{
			if (Box2DSceneManager::GetInstance()->m_objectList.at(i4 + Box2DSceneManager::GetInstance()->m_maxBullet + 1)->m_isRender == true)
			{
				float isShoot = RandomFloat(0.0f, 100.0f);
				if (isShoot < Counter::GetInstance()->enemyShootPercentage)
				{
					b2Vec2 enemyBulletPos = Box2DSceneManager::GetInstance()->m_objectList.at(i4 + Box2DSceneManager::GetInstance()->m_maxBullet + 1)->m_body->GetPosition();
					for (int j4 = 0; j4 < Box2DSceneManager::GetInstance()->m_maxEnemyBullet; j4++)
					{
						if (Box2DSceneManager::GetInstance()->m_objectList.at(j4 + Box2DSceneManager::GetInstance()->m_maxBullet + 1 + Box2DSceneManager::GetInstance()->m_maxEnemy)->m_isRender == false)
						{
							if (i4 < Box2DSceneManager::GetInstance()->m_maxEnemyCircle)
							{
								Box2DSceneManager::GetInstance()->m_objectList.at(j4 + Box2DSceneManager::GetInstance()->m_maxBullet + 1 + Box2DSceneManager::GetInstance()->m_maxEnemy)->posX = enemyBulletPos.x;
								Box2DSceneManager::GetInstance()->m_objectList.at(j4 + Box2DSceneManager::GetInstance()->m_maxBullet + 1 + Box2DSceneManager::GetInstance()->m_maxEnemy)->posY = enemyBulletPos.y - Box2DSceneManager::GetInstance()->m_objectList.at(i4 + Box2DSceneManager::GetInstance()->m_maxBullet + 1)->radius - Box2DSceneManager::GetInstance()->m_objectList.at(j4 + Box2DSceneManager::GetInstance()->m_maxBullet + 1 + Box2DSceneManager::GetInstance()->m_maxEnemy)->radius;
								Box2DSceneManager::GetInstance()->m_objectList.at(j4 + Box2DSceneManager::GetInstance()->m_maxBullet + 1 + Box2DSceneManager::GetInstance()->m_maxEnemy)->RenderBox2D(m_world);
								break;
							}
							/*	if (i4 >= Box2DSceneManager::GetInstance()->m_maxEnemyCircle)
							{
							Box2DSceneManager::GetInstance()->m_objectList.at(j4 + Box2DSceneManager::GetInstance()->m_maxBullet + 1 + Box2DSceneManager::GetInstance()->m_maxEnemy)->posX = enemyBulletPos.x;
							Box2DSceneManager::GetInstance()->m_objectList.at(j4 + Box2DSceneManager::GetInstance()->m_maxBullet + 1 + Box2DSceneManager::GetInstance()->m_maxEnemy)->posY = enemyBulletPos.y - Box2DSceneManager::GetInstance()->m_objectList.at(i4 + Box2DSceneManager::GetInstance()->m_maxBullet + 1)->height/2 - Box2DSceneManager::GetInstance()->m_objectList.at(j4 + Box2DSceneManager::GetInstance()->m_maxBullet + 1 + Box2DSceneManager::GetInstance()->m_maxEnemy)->height/2;
							Box2DSceneManager::GetInstance()->m_objectList.at(j4 + Box2DSceneManager::GetInstance()->m_maxBullet + 1 + Box2DSceneManager::GetInstance()->m_maxEnemy)->RenderBox2D(m_world);
							break;
							}*/
						}
					}
				}
			}
		}
		Counter::GetInstance()->timeCountEnemyShoot = 0;
	}

	//respawn main character 
	dynamic_cast <MainCharacter*> (Box2DSceneManager::GetInstance()->m_objectList.at(0))->Respawn(m_world);

	// main character shoot bullet
	if (Counter::GetInstance()->timeCountRenderBullet >= Box2DSceneManager::GetInstance()->m_objectList.at(1)->GetBulletRest() && Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_isRender == true)
	{
		int count = 0;
		for (int i5 = 0; i5 < Box2DSceneManager::GetInstance()->m_maxBullet; i5++)
		{
			if (Box2DSceneManager::GetInstance()->m_objectList.at(i5 + 1)->m_isRender == false)
			{
				if (Box2DSceneManager::GetInstance()->m_bulletLevel == 1)
				{
					Box2DSceneManager::GetInstance()->m_objectList.at(i5 + 1)->m_bodyDef.position.Set(Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_body->GetPosition().x, Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_body->GetPosition().y + 0.5);
					Box2DSceneManager::GetInstance()->m_objectList.at(i5 + 1)->RenderBox2D(m_world);
					break;
				}
				if (Box2DSceneManager::GetInstance()->m_bulletLevel == 2)
				{
					count++;
					switch (count)
					{
					case 1:
						Box2DSceneManager::GetInstance()->m_objectList.at(i5 + 1)->m_bodyDef.position.Set(Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_body->GetPosition().x - 0.25, Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_body->GetPosition().y + 0.5);
						Box2DSceneManager::GetInstance()->m_objectList.at(i5 + 1)->RenderBox2D(m_world);
						break;
					case 2:
						Box2DSceneManager::GetInstance()->m_objectList.at(i5 + 1)->m_bodyDef.position.Set(Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_body->GetPosition().x + 0.25, Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_body->GetPosition().y + 0.5);
						Box2DSceneManager::GetInstance()->m_objectList.at(i5 + 1)->RenderBox2D(m_world);
						break;
					}
					if (count == 3)
					{
						break;
					}
				}
				if (Box2DSceneManager::GetInstance()->m_bulletLevel == 3)
				{
					count++;
					switch (count)
					{
					case 1:
						Box2DSceneManager::GetInstance()->m_objectList.at(i5 + 1)->m_bodyDef.position.Set(Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_body->GetPosition().x - 0.25, Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_body->GetPosition().y + 0.5);
						Box2DSceneManager::GetInstance()->m_objectList.at(i5 + 1)->RenderBox2D(m_world);
						break;
					case 2:
						Box2DSceneManager::GetInstance()->m_objectList.at(i5 + 1)->m_bodyDef.position.Set(Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_body->GetPosition().x, Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_body->GetPosition().y + 0.6);
						Box2DSceneManager::GetInstance()->m_objectList.at(i5 + 1)->RenderBox2D(m_world);
						break;
					case 3:
						Box2DSceneManager::GetInstance()->m_objectList.at(i5 + 1)->m_bodyDef.position.Set(Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_body->GetPosition().x + 0.25, Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_body->GetPosition().y + 0.5);
						Box2DSceneManager::GetInstance()->m_objectList.at(i5 + 1)->RenderBox2D(m_world);
						break;
					}
					if (count == 4)
					{
						break;
					}
				}
			}
		}
		Counter::GetInstance()->timeCountRenderBullet = 0;
	}
	//stop double point state
	if (Counter::GetInstance()->timeCountDoublePoint == Counter::GetInstance()->timeDoublePoint)
	{
		Counter::GetInstance()->timeCountDoublePoint = Counter::GetInstance()->timeDoublePoint +100;
		// Fix bug x2 score doesn't active  correcly
		/*for (int i6 = 0; i6 < Box2DSceneManager::GetInstance()->m_maxEnemy; i6++)
		{
			dynamic_cast <Enemy*> (Box2DSceneManager::GetInstance()->m_objectList.at(i6 + 1 + Box2DSceneManager::GetInstance()->m_maxBullet))->score /= 2;
			dynamic_cast <Enemy*> (Box2DSceneManager::GetInstance()->m_objectList.at(i6 + 1 + Box2DSceneManager::GetInstance()->m_maxBullet))->m_score = dynamic_cast <Enemy*> (Box2DSceneManager::GetInstance()->m_objectList.at(i6 + 1 + Box2DSceneManager::GetInstance()->m_maxBullet))->score;
		}*/
		m_isX2score = false;
	}

	Test::Step(settings);

	// check collision between objects 
	const int32 k_maxNuke = 10;
	b2Body* nuke[k_maxNuke];
	int32 nukeCount = 0;
	for (int32 i = 0; i < m_pointCount; ++i)
	{
		ContactPoint* point = m_points + i;

		b2Body* body1 = point->fixtureA->GetBody();
		b2Body* body2 = point->fixtureB->GetBody();

		bool isEdge = true;
		for (int i7 = 0; i7 < Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemy + Box2DSceneManager::GetInstance()->m_maxEnemyBullet + 1; i7++)
		{
			if (Box2DSceneManager::GetInstance()->m_objectList.at(i7)->m_body == body1)
			{
				for (int j7 = 0; j7 < Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemy + Box2DSceneManager::GetInstance()->m_maxEnemyBullet + 1; j7++) {
					if (Box2DSceneManager::GetInstance()->m_objectList.at(j7)->m_body == body2)
					{
						isEdge = false;
						if ((i7 >= 0 && i7 < Box2DSceneManager::GetInstance()->m_maxBullet + 1)
							&& Box2DSceneManager::GetInstance()->m_objectList.at(i7)->GetInvincibleState() == false
							&& (j7 > Box2DSceneManager::GetInstance()->m_maxBullet && j7 < Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemy + Box2DSceneManager::GetInstance()->m_maxEnemyBullet + 1))
						{
							nuke[nukeCount++] = body1;
							if (CollisionForBullet(i7, j7) == true)
							{
								nuke[nukeCount++] = body2;
							}

						}
						else if ((j7 >= 0 && j7 < Box2DSceneManager::GetInstance()->m_maxBullet + 1)
							&& Box2DSceneManager::GetInstance()->m_objectList.at(i7)->GetInvincibleState() == false
							&& (i7 > Box2DSceneManager::GetInstance()->m_maxBullet && i7 < Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemy + Box2DSceneManager::GetInstance()->m_maxEnemyBullet + 1))
						{
							nuke[nukeCount++] = body2;
							if (CollisionForBullet(j7, i7) == true)
							{
								nuke[nukeCount++] = body1;
							}
						}
						break;
					}
				}
				break;
			}

		}

		if (isEdge == true)
		{
			for (int i10 = 0; i10 < Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemy + Box2DSceneManager::GetInstance()->m_maxItem + Box2DSceneManager::GetInstance()->m_maxEnemyBullet + 1; i10++)
			{
				if ((i10 > Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemyCircle && i10 < 1 + Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemyCircle + Box2DSceneManager::GetInstance()->m_maxEnemyRectangle)
					&& Box2DSceneManager::GetInstance()->m_objectList.at(i10)->m_body == body2 && Box2DSceneManager::GetInstance()->m_objectList.at(i10)->m_body->GetPosition().y < -SCREEN_HEIGHT / 2 + Box2DSceneManager::GetInstance()->m_objectList.at(i10)->height)
				{
					//Box2DSceneManager::GetInstance()->killCount++;
					Counter::GetInstance()->enemyRenderCount--;
					nuke[nukeCount++] = body2;
					Box2DSceneManager::GetInstance()->m_objectList.at(i10)->m_body = NULL;
					Box2DSceneManager::GetInstance()->m_objectList.at(i10)->m_isRender = false;
					break;
				}

				if (((i10 > 0 && i10 < Box2DSceneManager::GetInstance()->m_maxBullet + 1) || i10 > Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemy) &&
					(Box2DSceneManager::GetInstance()->m_objectList.at(i10)->m_body == body2 || Box2DSceneManager::GetInstance()->m_objectList.at(i10)->m_body == body1))
				{
					if (Box2DSceneManager::GetInstance()->m_objectList.at(i10)->m_body == body2)
					{
						nuke[nukeCount++] = body2;
					}
					else if (Box2DSceneManager::GetInstance()->m_objectList.at(i10)->m_body == body1)
					{
						nuke[nukeCount++] = body1;
					}
					Box2DSceneManager::GetInstance()->m_objectList.at(i10)->m_body = NULL;
					Box2DSceneManager::GetInstance()->m_objectList.at(i10)->m_isRender = false;
					if (Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_body == body1)
					{
						if (i10 == Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemy + Box2DSceneManager::GetInstance()->m_maxEnemyBullet + 1)
						{
							dynamic_cast <MainCharacter*> (Box2DSceneManager::GetInstance()->m_objectList.at(0))->m_bulletLevel++;
							for (int k = 1; k < Box2DSceneManager::GetInstance()->m_maxBullet + 1; k++)
							{
								//Box2DSceneManager::GetInstance()->m_objectList.at(k)->m_hp = Box2DSceneManager::GetInstance()->m_objectList.at(k)->hp * pow(1.3, dynamic_cast <MainCharacter*> (Box2DSceneManager::GetInstance()->m_objectList.at(0))->m_bulletLevel);
								Box2DSceneManager::GetInstance()->m_objectList.at(k)->m_hp = Box2DSceneManager::GetInstance()->m_objectList.at(k)->hp + 5*dynamic_cast <MainCharacter*> (Box2DSceneManager::GetInstance()->m_objectList.at(0))->m_bulletLevel;
							}
						}
						else if (i10 == Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemy + Box2DSceneManager::GetInstance()->m_maxEnemyBullet + 1 + 1)
						{
							if (Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_life < 3) {
								Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_life++;
							}

						}
						else if (i10 == Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemy + Box2DSceneManager::GetInstance()->m_maxEnemyBullet + 1 + 2)
						{
							Counter::GetInstance()->timeCountDoublePoint = 0;
							if (!m_isX2score)
							{
								// Fix bug x2 score doesn't active  correcly
								/*for (int i9 = 0; i9 < Box2DSceneManager::GetInstance()->m_maxEnemy; i9++)
								{
									dynamic_cast <Enemy*> (Box2DSceneManager::GetInstance()->m_objectList.at(i9 + 1 + Box2DSceneManager::GetInstance()->m_maxBullet))->score *= 2;
								}*/
								m_isX2score = true;
							}
						}
						else if (i10 == Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemy + Box2DSceneManager::GetInstance()->m_maxEnemyBullet + 1 + 3)
						{
							if (Box2DSceneManager::GetInstance()->m_bulletLevel < 3)
							{
								Box2DSceneManager::GetInstance()->m_bulletLevel++;
							}
						}
					}
					break;
				}
			}
		}

		if (nukeCount == k_maxNuke)
		{
			break;
		}
	}
	std::sort(nuke, nuke + nukeCount);

	// Destroy the bodies, skipping duplicates.
	int32 i11 = 0;
	while (i11 < nukeCount)
	{
		b2Body* b = nuke[i11++];
		while (i11 < nukeCount && nuke[i11] == b)
		{
			++i11;
		}

		if (b != m_bomb)
		{
			m_world->DestroyBody(b);
			b = NULL;
		}
	}
	Counter::GetInstance()->UpdateCounter();


	
}

bool AddPair::CollisionForBullet(int i, int j)
{
	Box2DSceneManager::GetInstance()->m_objectList.at(i)->m_body = NULL;
	Box2DSceneManager::GetInstance()->m_objectList.at(i)->m_isRender = false;

	//if main character is destroyed
	if (i == 0)
	{
		Counter::GetInstance()->timeCountRespawn = 0;
		Box2DSceneManager::GetInstance()->m_bulletLevel = 1;
		Box2DSceneManager::GetInstance()->m_objectList.at(0)->IsDestroyed();
		for (int k = 1; k < Box2DSceneManager::GetInstance()->m_maxBullet + 1; k++)
		{
			Box2DSceneManager::GetInstance()->m_objectList.at(k)->m_hp = Box2DSceneManager::GetInstance()->m_objectList.at(k)->hp + 5 * dynamic_cast <MainCharacter*> (Box2DSceneManager::GetInstance()->m_objectList.at(0))->m_bulletLevel;
		}
	}

	Box2DSceneManager::GetInstance()->m_objectList.at(j)->m_hp -= Box2DSceneManager::GetInstance()->m_objectList.at(i)->m_hp;
	Box2DSceneManager::GetInstance()->m_objectList.at(j)->m_isHit = 1;
	Box2DSceneManager::GetInstance()->m_objectList.at(j)->m_timeHit = 0;
	if (Box2DSceneManager::GetInstance()->m_objectList.at(j)->m_hp <= 0) {
		if (j > Box2DSceneManager::GetInstance()->m_maxBullet && j < Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemy + 1)
		{
			Counter::GetInstance()->killCount++;

			//// Fix bug x2 score doesn't active  correcly
			if (m_isX2score)
				Box2DSceneManager::GetInstance()->scores += dynamic_cast <Enemy*> (Box2DSceneManager::GetInstance()->m_objectList.at(j))->m_score*2;
			else 
				Box2DSceneManager::GetInstance()->scores += dynamic_cast <Enemy*> (Box2DSceneManager::GetInstance()->m_objectList.at(j))->m_score;
			//printf("%d\n", Box2DSceneManager::GetInstance()->scores);
			float isDrop = RandomFloat(0.0f, 100.0f);
			int l = rand() % Box2DSceneManager::GetInstance()->m_maxItem;
			if (Box2DSceneManager::GetInstance()->m_objectList.at(Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemy + Box2DSceneManager::GetInstance()->m_maxEnemyBullet + 1 + l)->m_isRender == false
				&& isDrop < Box2DSceneManager::GetInstance()->m_objectList.at(Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemy + Box2DSceneManager::GetInstance()->m_maxEnemyBullet + 1 + l)->GetItemDropPercentage())
			{
				Box2DSceneManager::GetInstance()->m_objectList.at(Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemy + Box2DSceneManager::GetInstance()->m_maxEnemyBullet + 1 + l)->posX = Box2DSceneManager::GetInstance()->m_objectList.at(j)->m_body->GetPosition().x;
				Box2DSceneManager::GetInstance()->m_objectList.at(Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemy + Box2DSceneManager::GetInstance()->m_maxEnemyBullet + 1 + l)->posY = Box2DSceneManager::GetInstance()->m_objectList.at(j)->m_body->GetPosition().y;
				Box2DSceneManager::GetInstance()->m_objectList.at(Box2DSceneManager::GetInstance()->m_maxBullet + Box2DSceneManager::GetInstance()->m_maxEnemy + Box2DSceneManager::GetInstance()->m_maxEnemyBullet + 1 + l)->RenderBox2D(m_world);
			}
		}

		Box2DSceneManager::GetInstance()->m_objectList.at(j)->m_body = NULL;
		Box2DSceneManager::GetInstance()->m_objectList.at(j)->m_isRender = false;
		return true;
	}
	return false;
}

void AddPair::Print()
{
	/*for (int i = 0; i < Box2DSceneManager::GetInstance()->m_objectList.size(); i++)
	{
		if (Box2DSceneManager::GetInstance()->m_objectList.at(i)->m_isRender == true)
		{
			
			printf("ID: %d %d\n", Box2DSceneManager::GetInstance()->m_objectList.at(i)->m_id, i);
			printf("NAME: %s\n", Box2DSceneManager::GetInstance()->m_objectList.at(i)->m_name);
			printf("HITBOX: %s\n", Box2DSceneManager::GetInstance()->m_objectList.at(i)->m_hitbox);
			if (strcmp(Box2DSceneManager::GetInstance()->m_objectList.at(i)->m_hitbox, "RECTANGLE") == 0)
			{
				printf("SIZE: %f %f\n", Box2DSceneManager::GetInstance()->m_objectList.at(i)->width, Box2DSceneManager::GetInstance()->m_objectList.at(i)->height);
			}
			if (strcmp(Box2DSceneManager::GetInstance()->m_objectList.at(i)->m_hitbox, "CIRCLE") == 0)
			{
				printf("RADIUS: %f\n", Box2DSceneManager::GetInstance()->m_objectList.at(i)->radius);
			}
			printf("POSITION: %f %f\n", Box2DSceneManager::GetInstance()->m_objectList.at(i)->m_body->GetPosition().x, Box2DSceneManager::GetInstance()->m_objectList.at(i)->m_body->GetPosition().y);
			printf("HP: %f\n\n", Box2DSceneManager::GetInstance()->m_objectList.at(i)->m_hp);
		}
	}
	printf("\n-------------------\n");*/
}



AddPair* AddPair::s_Instance = 0;
AddPair* AddPair::GetInstance()
{
	if (!s_Instance) {
		s_Instance = new AddPair();
	}
	return s_Instance;
}