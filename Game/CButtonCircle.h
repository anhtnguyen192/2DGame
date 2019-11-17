#pragma once
#include "CButton.h"
class CButtonCircle :
	public CButton
{
public:
	CButtonCircle();
	~CButtonCircle();
	CButtonCircle(char *name); 
	CButtonCircle(char *name, float _x, float _y, float _radius, int _IdButton,ButtonType _type);
	CButtonCircle(char *name, float _x, float _y, float _radius, int _IdButton, ButtonType _type, int _textID);
	void Init();
	virtual bool CheckClick(int x, int y);
	
	void SetRadius(float r);

private:
	float m_fRadius;
	
};

