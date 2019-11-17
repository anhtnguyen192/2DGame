/*
* Copyright (c) 2006-2012 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef AddPair_H
#define AddPair_H


#include "..\ProjectTest\Box2DSceneManager.h"
#include "..\ProjectTest\BulletType1.h"
#include "..\ProjectTest\EnemyCircle.h"
#include "..\ProjectTest\EnemyRectangle.h"
#include "..\ProjectTest\UpgradeBullet.h"
#include "..\ProjectTest\EnemyBullet.h"
#include "..\ProjectTest\Boss.h"
#include "..\ProjectTest\Counter.h"
#include "..\Test.h"
#include<time.h>

#define SCREEN_WIDTH 5.625
#define SCREEN_HEIGHT 10

class AddPair : public Test
{
public:
	Box2DSceneManager *b;
	Counter *t;
	Settings *settings;
	int randomBoss ;
	bool m_isX2score;
	~AddPair();
	void DestroyInstance();
	AddPair();
	void Init();


	void Step(Settings* settings);
	
	void Print();
		

	bool CollisionForBullet(int i, int j);

	/*static Test* Create()
	{
		return new AddPair;
	}*/
	
	static AddPair* GetInstance();
private:
	static AddPair* s_Instance;
	

	
	
	
};

#endif
