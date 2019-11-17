#pragma once
#include "Item.h"
class Life :
	public Item
{
public:
	Life();
	~Life();
	void RenderBox2D(b2World *world);
};

