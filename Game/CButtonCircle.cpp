#include "CButtonCircle.h"



CButtonCircle::CButtonCircle()
{
	m_IsTextRender = false;
}


CButtonCircle::~CButtonCircle()
{
	
}

CButtonCircle::CButtonCircle(char * name)
{
	m_IsTextRender = false;
	SetName(name);
	SetContent(name);
}

CButtonCircle::CButtonCircle(char * name, float _x, float _y, float _radius, int _IdButton, ButtonType _type)
{
	m_IsTextRender = false;
	SetName(name);
	SetContent(name);
	SetPosition(_x, _y);
	SetRadius(_radius);
	SetIsPressed(false);
	m_Type = _type; 
	m_OBJ_Button = (dynamic_cast<OBJ_Button*> (SceneManager::GetInstance()->GetButtonByID(_IdButton)));
	
	
	//m_OBJ_Button = dynamic_cast<OBJ_Button*> (SceneManager::GetInstance()->GetButtonByID(_IdButton));
	
	
	//m_OBJ_Button = dynamic_cast<OBJ_Button*> (SceneManager::GetInstance()->GetButtonByID(0));
	//m_OBJ_Button->LinkDaTa();
	//m_OBJ_Button->Init();
}

CButtonCircle::CButtonCircle(char * name, float _x, float _y, float _radius, int _IdButton, ButtonType _type, int _textID)
{
	m_IsTextRender = false;
	SetName(name);
	SetContent(name);
	SetPosition(_x, _y);
	SetRadius(_radius);
	SetIsPressed(false);
	m_Type = _type;
	m_OBJ_Button = (dynamic_cast<OBJ_Button*> (SceneManager::GetInstance()->GetButtonByID(_IdButton)));
	m_text = TextManager::GetInstance()->GetTextByID(_textID);
	if (m_text) m_IsTextRender = true;
}

void CButtonCircle::Init()
{
	//m_button_origin->clone(m_OBJ_Button);
	//m_OBJ_Button->LinkDaTa();
	//m_OBJ_Button->Init();
}

bool CButtonCircle::CheckClick(int x, int y)
{
	if (pow((x - GetPosition().x), 2) + pow(y - GetPosition().y, 2) <= pow(m_fRadius, 2))
	{
		SetIsPressed(!GetIsPressed());
		return true;
	}
		
	return false;
}

void CButtonCircle::SetRadius(float r)
{
	m_fRadius = r;
}
