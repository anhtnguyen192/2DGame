#pragma once
#include "Item.h"
class UpgradeBullet :
	public Item
{
public:
	UpgradeBullet();
	~UpgradeBullet();

	void RenderBox2D(b2World *world) ;
};

