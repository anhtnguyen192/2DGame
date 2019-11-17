#include "GS_OptionMenuScene.h"

bool GS_OptionMenuScene::m_isNeedLoaded = true;

GS_OptionMenuScene::GS_OptionMenuScene()
{
	m_type = GS_OPTIONMENU;
}


GS_OptionMenuScene::~GS_OptionMenuScene()
{
	Release();
	// delete buttons
	delete m_buttonBack;
	m_buttonBack = nullptr;
	delete m_buttonMusicDown;
	m_buttonMusicDown = nullptr;
	delete m_buttonMusicUp;
	m_buttonMusicUp = nullptr;
	delete m_buttonSoundDown;
	m_buttonSoundDown = nullptr;
	delete m_buttonSoundUp;
	m_buttonSoundUp = nullptr;
}

GS_OptionMenuScene::GS_OptionMenuScene(ESContext *esContext)
{
	//m_isLoaded = false;       
	SetIsLoaded(false);
	m_esContext = esContext;
	m_MusicId = 6;
	Create();

	// Create some button to get Event
	m_buttonBack = new CButtonCircle("BACK", 270, 300, 50, 2, BUTTON_BACK);
	m_buttonMusicUp = new CButtonCircle("MusicUp", 420, 700, 50, 5, BUTTON_CHOOSE);
	m_buttonMusicDown = new CButtonCircle("MusicDown", 120, 700, 50, 6, BUTTON_CHOOSE);
	m_buttonSoundUp = new CButtonCircle("SoundUp", 420, 500, 50, 7, BUTTON_CHOOSE);
	m_buttonSoundDown = new CButtonCircle("SoundDown", 120, 500, 50, 8, BUTTON_CHOOSE);
	// get the background picture
	m_OBJ_background = dynamic_cast<OBJ_Background*>(SceneManager::GetInstance()->GetBackgroundByID(0));

	
}

bool GS_OptionMenuScene::LoadResouces()
{
	m_isLoaded = true;
	return true;
}

void GS_OptionMenuScene::Render(ESContext *esContext)
{
	//Render Something during loading file

	// set environment for render
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// render something 

	//m_OBJ_background->UpdatePosition(Vector3(200, 300, 0));
	m_OBJ_background->Render();

	SceneManager::GetInstance()->GetButtonByID(20)->RenderByParameter(Vector3(270, 700, 0), Vector3(0, 0, 0), 0.0);
	SceneManager::GetInstance()->GetButtonByID(20)->RenderByParameter(Vector3(270, 500, 0), Vector3(0, 0, 0), 0.0);

	m_buttonBack->Render();
	m_buttonBack->Render();
	m_buttonMusicDown->Render();
	m_buttonMusicUp->Render();
	m_buttonSoundDown->Render();
	m_buttonSoundUp->Render();

	/*
	Text render
	*/
	int volume = SoundManager::GetInstance()->GetVolumeMusic();
	char str[4];
	memset(str, 0, 4);
	_itoa(volume, str, 10);
	char text[20] = "MUSIC: ";
	TextRender *t = TextManager::GetInstance()->GetTextByID(10);
	//TextManager::GetInstance()->GetTextByID(10)->BackWardTextData();
	//TextManager::GetInstance()->GetTextByID(10)->PushBackTextData(str);
	//TextManager::GetInstance()->GetTextByID(10)->RenderString();
	t->Render(strcat(text, str), t->position, t->color, t->scaleX, t->scaleY);

	volume = SoundManager::GetInstance()->GetVolumeSound();
	memset(str, 0, 4);
	_itoa(volume, str, 10);
	TextRender *tt = TextManager::GetInstance()->GetTextByID(11);
	//TextManager::GetInstance()->GetTextByID(11)->BackWardTextData();
	//TextManager::GetInstance()->GetTextByID(11)->PushBackTextData(str);
	//TextManager::GetInstance()->GetTextByID(11)->RenderString();
	char text1[20] = "SOUND: ";
	tt->Render(strcat(text1, str), tt->position, tt->color, tt->scaleX, tt->scaleY);

	// swap buffer 
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);


}

void GS_OptionMenuScene::Update(ESContext * esContext, float deltaTime)
{
	// check file all loading done or not
	// if done, change to MainMenu Scene

	// check loading file is done yet
	if (m_isLoaded && m_isNeedLoaded)
	{
		m_isNeedLoaded = false;
		printf("\nLOADING DONE!!\n");
	}

	//Update the Sprite Animation for Render Background
	m_OBJ_background->Update(deltaTime);
	m_buttonBack->m_OBJ_Button->Update(deltaTime);
	m_buttonMusicDown->m_OBJ_Button->Update(deltaTime);
	m_buttonMusicUp->m_OBJ_Button->Update(deltaTime);
	m_buttonSoundDown->m_OBJ_Button->Update(deltaTime);
	m_buttonSoundUp->m_OBJ_Button->Update(deltaTime);
	//Update the Sprite Animation for Render button


}

// GS process when an Event is Catch, call in Game's Update, after GS is updated
GS_TYPE GS_OptionMenuScene::OnEvent(Event *_event)
{
	if (_event == m_buttonBack)
	{
		//printf("Event Handle\n");
		m_event = nullptr;
		return GS_BACK;
	}
	
	//// event when button is call
	//if (_event == m_buttonMusicUp)
	//{
	//	//printf("Event Handle Music Up\n");
	//	SoundManager::GetInstance()->VolumeMusicUp();
	//	SoundManager::GetInstance()->Update();
	//	m_event = nullptr;
	//}
	//if (_event == m_buttonMusicDown)
	//{
	//	//printf("Event Handle Music Down\n");
	//	SoundManager::GetInstance()->VolumeMusicDow();
	//	SoundManager::GetInstance()->Update();
	//	m_event = nullptr;
	//}
	//if (_event == m_buttonSoundUp)
	//{
	//	//printf("Event Handle Sound Up\n");
	//	SoundManager::GetInstance()->VolumeSoundUp();
	//	SoundManager::GetInstance()->Update();
	//	m_event = nullptr;
	//}
	//if (_event == m_buttonSoundDown)
	//{
	//	//printf("Event Handle Sound Down\n");
	//	SoundManager::GetInstance()->VolumeSoundDow();
	//	SoundManager::GetInstance()->Update();
	//	m_event = nullptr;
	//}
}

void GS_OptionMenuScene::Create()
{

	// test Resources file are loaded yet and load file if they aren't loaded
	if (m_isNeedLoaded)
	{
		LoadResouces();
	}

	// Play Music
	//SoundManager::GetInstance()->m_aMusic[0]->Play();

	

}

// clean up when the GS is released
void GS_OptionMenuScene::Release()
{
	
}

// CALLBACK when Touch Down Event is call
void GS_OptionMenuScene::TouchActionDown(int x, int y)
{
	//printf("down\n");
	
	
	if (m_buttonMusicUp->CheckClick(x, y)) 
		//m_event = m_buttonMusicUp;
	{
		//printf("Event Handle Music Up\n");
		SoundManager::GetInstance()->VolumeMusicUp();
		SoundManager::GetInstance()->Update();
	}
	if (m_buttonMusicDown->CheckClick(x, y)) 
		//m_event = m_buttonMusicDown;
	{
		//printf("Event Handle Music Down\n");
		SoundManager::GetInstance()->VolumeMusicDow();
		SoundManager::GetInstance()->Update();
		//m_event = nullptr;
	}
	if (m_buttonSoundUp->CheckClick(x, y))
		//m_event = m_buttonSoundUp;
	{
		SoundManager::GetInstance()->VolumeSoundUp();
		SoundManager::GetInstance()->Update();
	}
	if (m_buttonSoundDown->CheckClick(x, y))
		//m_event = m_buttonSoundDown;
	{
		SoundManager::GetInstance()->VolumeSoundDow();
		SoundManager::GetInstance()->Update();
	}
}

// CALLBACK when Touch Up Event is call
void GS_OptionMenuScene::TouchActionUp(int x, int y)
{
	//printf("up\n");
	if (m_buttonBack->CheckClick(x, y))
		m_event = m_buttonBack;
}

// CALLBACK when Touch Move Event is call
void GS_OptionMenuScene::TouchActionMove(int x, int y, int currentX, int currentY)
{
	//printf("Move\n");
}

//void GS_OptionMenuScene::Key(unsigned char key, bool bIsPressed)
//{
//	if (bIsPressed && key == 0x20 && m_event == nullptr) m_event = m_buttonBack;
//}

void GS_OptionMenuScene::SetIsLoaded(bool i)
{
	m_isLoaded = i;
}

bool GS_OptionMenuScene::GetIsLoaded()
{
	return m_isLoaded;
}
