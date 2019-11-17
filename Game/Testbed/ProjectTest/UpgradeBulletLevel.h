#pragma once
#include "Item.h"
class UpgradeBulletLevel :
	public Item
{
public:
	UpgradeBulletLevel();
	~UpgradeBulletLevel();

	void RenderBox2D(b2World *world);
};

