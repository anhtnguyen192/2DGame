#include "CButtonRectangle.h"



CButtonRectangle::CButtonRectangle()
{
	m_IsTextRender = false;
}


CButtonRectangle::~CButtonRectangle()
{

}

CButtonRectangle::CButtonRectangle(char * name, float _x, float _y, float _witdh, float _height, int _IdButton, ButtonType _type, int _textID)
{
	SetName(name);
	SetContent(name);
	SetPosition(_x, _y);
	SetSizeWH(_witdh, _height);
	SetIsPressed(false);
	m_Type = _type;
	m_OBJ_Button = (dynamic_cast<OBJ_Button*> (SceneManager::GetInstance()->GetButtonByID(_IdButton)));
	m_text = TextManager::GetInstance()->GetTextByID(_textID);
	if (m_text) m_IsTextRender = true;
}

CButtonRectangle::CButtonRectangle(char * name, float _x, float _y, float _witdh, float _height, int _IdButton, ButtonType _type)
{
	SetName(name);
	SetContent(name);
	SetPosition(_x, _y);
	SetSizeWH(_witdh, _height);
	SetIsPressed(false);
	m_Type = _type;
	m_IsTextRender = false;
	m_OBJ_Button = (dynamic_cast<OBJ_Button*> (SceneManager::GetInstance()->GetButtonByID(_IdButton)));
}

bool CButtonRectangle::CheckClick(int x, int y)
{ 
	if ((x <= GetPosition().x + m_fWidth / 2.0) && (x >= GetPosition().x - m_fWidth / 2.0))
	{
		if ((y <= GetPosition().y + m_fHeight / 2.0) && (y >= GetPosition().y - m_fHeight / 2.0))
		{
			SetIsPressed(true);
			return true;
		}
	}
	return false;
}

void CButtonRectangle::Init()
{
}

void CButtonRectangle::SetSizeWH(float _width, float _height)
{
	m_fWidth = _width;
	m_fHeight = _height;
}
