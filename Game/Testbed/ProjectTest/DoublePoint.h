#pragma once
#include "Item.h"
class DoublePoint :
	public Item
{
public:
	DoublePoint();
	~DoublePoint();
	void RenderBox2D(b2World *world);
};

