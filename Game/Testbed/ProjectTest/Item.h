#pragma once
#include "Object2D.h"
class Item :
	public Object2D
{
public:
	Item();
	~Item();

	float m_dropPercentage;
	float GetItemDropPercentage();
	
	virtual void RenderBox2D(b2World *world) {};
	
};

