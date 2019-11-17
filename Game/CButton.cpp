#include "stdafx.h"
#include "CButton.h"



CButton::CButton()
{
	m_IsTextRender = false;
}

CButton::CButton(char * name)
{
	//m_strName = NULL;
	//m_strContent = NULL;
	SetName(name);
	SetContent(name);
	m_IsTextRender = false;
	
}


CButton::~CButton()
{
	delete[] m_strName;
	m_strName = nullptr;
	delete[] m_strContent;
	m_strContent = nullptr;
}

void CButton::Render()
{
	//m_OBJ_Button->UpdatePosition(Vector3(GetPosition().x, GetPosition().y, 0));
	/*if (GetIsPressed())
	{
		m_OBJ_Button->Render4CButton(1);
		SetIsPressed(false);
	}
	else
	{
		m_OBJ_Button->Render4CButton(0);
		
	}*/
	//m_OBJ_Button->Render4CButton(0);
	m_OBJ_Button->RenderByParameter(Vector3(GetPosition().x, GetPosition().y, 0), Vector3(0, 0, 0), 0.0f);
	if (m_IsTextRender) m_text->RenderString();
	//if (m_IsTextRender) m_text->Render(GetContent(), m_textData.position, m_textData.color, m_textData.scaleX, m_textData.scaleY);
	//m_OBJ_Button->Render4CButton();
	/*if (GetIsPressed())
	{
		Sleep(200);
		SetIsPressed(false);
	}*/
}

bool CButton::CheckClick(int x, int y)
{
	return false;
}

void CButton::SetName(char* name)
{
	char*str = new char[strlen(name)+1];
	strcpy(str, name);
	m_strName = str;

}

void CButton::SetContent(char *name)
{
	char*str1 = new char[strlen(name)+1];
	strcpy(str1, name);
	m_strContent = str1;
}

char * CButton::GetName()
{
	return m_strName;
}

char * CButton::GetContent()
{
	return m_strContent;
}

Vector2 CButton::GetPosition()
{
	return m_vPosition;
}

void CButton::SetPosition(float x, float y)
{
	m_vPosition = Vector2(x, y);
}

bool CButton::GetIsPressed()
{
	return m_isPressed;
}

void CButton::SetIsPressed(bool i)
{
	m_isPressed = i;
}

void CButton::Init()
{
}


