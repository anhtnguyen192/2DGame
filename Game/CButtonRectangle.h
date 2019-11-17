#pragma once
#include "CButton.h"
class CButtonRectangle :
	public CButton
{
public:
	CButtonRectangle();
	~CButtonRectangle();

	CButtonRectangle(char *name, float _x, float _y, float _witdh, float _height, int _IdButton, ButtonType _type, int _textID);
	CButtonRectangle(char *name, float _x, float _y, float _witdh, float _height, int _IdButton, ButtonType _type);
	virtual bool CheckClick(int x, int y);
	void Init();
	void SetSizeWH(float _width, float _height);
private:
	float m_fWidth;
	float m_fHeight;
};

