#pragma once
#include<string.h>
#include"Main.h"
#include<math.h>
#include"Event.h"

enum ButtonType {
	BUTTON_TRANS_FORWARD =		1,
	BUTTON_EXIT =				2,
	BUTTON_RESET =				3,
	BUTTON_CONTINUE =			4,
	BUTTON_TRANS_BACKWARD =		5,
	BUTTON_CHOOSE =				6,
	BUTTON_CANCEL =				7,
	BUTTON_SAVE =				8,
	BUTTON_BACK =				9
};


class CButton: public Event
{
public:
	CButton();
	CButton(char* name);
	virtual ~CButton();

	void Render();

	virtual bool CheckClick(int x,int y);

	void SetName(char*name);

	void SetContent(char*name);

	char* GetName();

	char* GetContent();

	Vector2 GetPosition();

	void SetPosition(float x, float y);

	bool GetIsPressed();

	void SetIsPressed(bool i);


	virtual void Init();

	ButtonType m_Type;
	// Spite ID is use
	int m_iOBJ_ButtonID;

	TextRender *m_text;
	bool m_IsTextRender;
	

	// 
	OBJ_Button* m_OBJ_Button;
	OBJ_Button* m_button_origin;

	
private:
	// name of button
	char* m_strName;
	
	// Text will be render
	char* m_strContent;
	
	// flag of isPressed
	bool m_isPressed;

	// Position of Button
	Vector2 m_vPosition;


	
};

