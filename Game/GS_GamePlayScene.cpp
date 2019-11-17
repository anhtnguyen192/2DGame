#include "GS_GamePlayScene.h"
#include "Testbed\Tests\AddPair.h"

bool GS_GamePlayScene::m_isNeedLoaded = true;

GS_GamePlayScene::GS_GamePlayScene()
{
	//AddPair::GetInstance();
	//m_type = GS_GAMEPLAY;
	//timecount = 0.0f;
}


GS_GamePlayScene::~GS_GamePlayScene()
{
	Release();
	if (m_buttonPause)
	{
		delete m_buttonPause;
		m_buttonPause = nullptr;
	}
	if (m_endGame)
	{
		delete m_endGame;
		m_endGame = nullptr;
	}
	m_ObjectsRender.clear();
}

GS_GamePlayScene::GS_GamePlayScene(ESContext *esContext)
{
	
	m_endGame = new Event();
	m_isNeedLoaded = true;
	m_isLoaded = false;
	m_type = GS_GAMEPLAY;
	SetIsLoaded(false);
	m_esContext = esContext;
	m_MusicId = 3;
	// Create some button to get Event
	m_buttonPause = new CButtonCircle("PAUSE", 480, 900, 50, 3, BUTTON_TRANS_FORWARD);
	// get the background picture
	m_OBJ_background = dynamic_cast<OBJ_Background*>(SceneManager::GetInstance()->GetBackgroundByID(0));

	// boss1: 0
	m_ObjectsRender.push_back(dynamic_cast <Sprite*>(SceneManager::GetInstance()->GetSpriteByID(0)));

	// boss2: 1
	m_ObjectsRender.push_back(dynamic_cast <Sprite*>(SceneManager::GetInstance()->GetSpriteByID(1)));

	//enemy1: 2
	m_ObjectsRender.push_back(dynamic_cast <Sprite*>(SceneManager::GetInstance()->GetSpriteByID(2)));

	//enemy2: 3
	m_ObjectsRender.push_back(dynamic_cast <Sprite*>(SceneManager::GetInstance()->GetSpriteByID(3)));

	//enemy3: 4
	m_ObjectsRender.push_back(dynamic_cast <Sprite*>(SceneManager::GetInstance()->GetSpriteByID(4)));

	//enemy4: 5
	m_ObjectsRender.push_back(dynamic_cast <Sprite*>(SceneManager::GetInstance()->GetSpriteByID(5)));

	//boss And enemy bullet: 6
	m_ObjectsRender.push_back(dynamic_cast <Sprite*>(SceneManager::GetInstance()->GetSpriteByID(54)));

	//main character: 7
	m_ObjectsRender.push_back(dynamic_cast <Sprite*>(SceneManager::GetInstance()->GetSpriteByID(50)));

	//item up damage bullet: 8
	m_ObjectsRender.push_back(dynamic_cast <Sprite*>(SceneManager::GetInstance()->GetSpriteByID(55)));

	// item up level bullet: 9
	m_ObjectsRender.push_back(dynamic_cast <Sprite*>(SceneManager::GetInstance()->GetSpriteByID(51)));

	// main bullet: 10
	m_ObjectsRender.push_back(dynamic_cast <Sprite*>(SceneManager::GetInstance()->GetSpriteByID(53)));

	// double point: 11
	m_ObjectsRender.push_back(dynamic_cast <Sprite*>(SceneManager::GetInstance()->GetSpriteByID(56)));

	// item life: 12
	m_ObjectsRender.push_back(dynamic_cast <Sprite*>(SceneManager::GetInstance()->GetSpriteByID(57)));

	// null: 13
	m_ObjectsRender.push_back(dynamic_cast <Sprite*>(SceneManager::GetInstance()->GetSpriteByID(100)));

	// engine main
	m_Objengine = dynamic_cast<Sprite*>(SceneManager::GetInstance()->GetSpriteByID(60));
	//Create();
}

bool GS_GamePlayScene::LoadResouces()
{
	m_isLoaded = true;
	
	
	return true;
}

void GS_GamePlayScene::Render(ESContext *esContext)
{
	/*int iii = dynamic_cast<BulletType1*>(Box2DSceneManager::GetInstance()->m_objectList.at(1))->m_hp;
	printf("bullet dame: %d", iii);*/
	//Render Something during loading file

	// set environment for render
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// render something 

	//m_OBJ_background->UpdatePosition(Vector3(200, 300, 0));
	m_OBJ_background->Render();
	Box2DSceneManager *b = Box2DSceneManager::GetInstance();
	//if(timecount > timeBase + 1.0 / 60)
	//if (m_isRender)
	{	
		if (b->m_objectList.at(0)->m_life > 0)
		
		{
			if (b->m_objectList.at(0)->m_isRender == true)
			{
				int x = ChangeXfromBox2DtoGraphic(b->m_objectList.at(0)->m_body->GetPosition().x);
				int y = ChangeYfromBox2DtoGraphic(b->m_objectList.at(0)->m_body->GetPosition().y);
				
				m_Objengine->RenderByParameter(Vector3(x, y - 80, 0), Vector3(0, 0, 0), 0.0f);
				//Sprite *s = dynamic_cast<Sprite*> (SceneManager::GetInstance()->GetSpriteByID(51));
				//s->RenderByParameter(Vector3(x, y, 0), Vector3(0, 0, 0), Vector3(0.13, 0.13, 0.2), 0.0f);

			}
			
			for (int i = 0; i < b->m_objectList.size(); i++)
			{
				// draw engine
				
					
				if (b->m_objectList.at(i)->m_isRender == true)
				{
					int id = Match2DObjectListToObjectRender(b->m_objectList.at(i)->m_id);
					int x = ChangeXfromBox2DtoGraphic(b->m_objectList.at(i)->m_body->GetPosition().x);
					int y = ChangeYfromBox2DtoGraphic(b->m_objectList.at(i)->m_body->GetPosition().y);
					//fix Position because texture error
					if (id == 7) { x += 1; y += 4; }
					if (id == 0) { x += 62; y += 107; }
					if (id == 2) { x += 5; y += 4; }
					if (id == 5) { x += 7; }

					Vector3 Position = Vector3(x, y, 0);
					Vector3 Rotation = Vector3(0, 0, 0);

					// pass isHit to ObjectRender
					float hit = 0.0f;
					if (b->m_objectList.at(i)->m_isHit)
					{
						if (id == 7)
						{
							if (timecount - floor(timecount) > 0.5) hit = 1.0;
							else hit = 0.0;
						}
						else
						{
							hit = 1.0f;
						}
					}

					m_ObjectsRender[id]->RenderByParameter(Position, Rotation, hit);
				}
			}
		}
	}
	m_isRender = false;
	//render Score
	int score = Box2DSceneManager::GetInstance()->scores;
	if (score >= 0)
	{
		Vector2 text2Position = Vector2(10, 930);
		char text[30] = "SCORE:";
		char str[20];
		memset(str, 0, 20);
		_itoa(score, str, 10);
		TextRender *t = TextManager::GetInstance()->GetTextByID(12);
		t->Render(strcat(text, str), text2Position, Vector4(1, 1, 1, 1), 1, 1);
	}

	//render number if life
	for (int i = 0; i < Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_life; i++)
	{
		Sprite* s = dynamic_cast<Sprite*> (SceneManager::GetInstance()->GetSpriteByID(58));
		s->RenderByParameter(s->m_Position + Vector3(30*i, 0, 0), Vector3(0, 0, 0), 0.0f);
	}

	//reder count bullet level
	dynamic_cast<Sprite*> (SceneManager::GetInstance()->GetSpriteByID(59))->Render();
	int levelBuller = dynamic_cast<MainCharacter*>(Box2DSceneManager::GetInstance()->m_objectList.at(0))->m_bulletLevel;
	if (levelBuller >= 0)
	{
		Vector3 text1Position = (SceneManager::GetInstance()->GetSpriteByID(59))->m_Position;
		char text[10] = "x";
		char str[4];
		memset(str, 0, 4);
		_itoa(levelBuller, str, 10);
		TextRender *t = TextManager::GetInstance()->GetTextByID(12);
		t->Render(strcat(text, str), Vector2(text1Position.x + 10, text1Position.y -22), Vector4(1,1,1,1), 1,1);
	}
	// render is X2 score 
	//if (Counter::GetInstance()->timeCountDoublePoint >= 0 && Counter::GetInstance()->timeCountDoublePoint <= Counter::GetInstance()->timeDoublePoint)
	if (AddPair::GetInstance()->m_isX2score)
	{
		dynamic_cast <Sprite*>(SceneManager::GetInstance()->GetSpriteByID(56))->RenderByParameter(Vector3(20, 780, 0), Vector3(0, 0, 0), Vector3(0.05, 0.05, 0.05), 0.0f);
	}


	m_buttonPause->Render();
	// swap buffer 
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);


}

void GS_GamePlayScene::Update(ESContext * esContext, float deltaTime)
{
	// check file all loading done or not
	// if done, change to MainMenu Scene
	
	
	// check loading file is done yet
	if (m_isLoaded && m_isNeedLoaded)
	{
		m_isNeedLoaded = false;
		printf("\nLOADING DONE!!\n");
	}
	if (Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_life <= 0) m_event = m_endGame ;
	//Update the Sprite Animation for Render Background
	m_OBJ_background->Update(deltaTime);
	m_buttonPause->m_OBJ_Button->Update(deltaTime);
	m_Objengine->Update(deltaTime);
	
	
	//Update the Sprite Animation for Render button
	timecount += deltaTime;
	if (timecount > timeChangeMusic + 60)
	{
		SoundManager::GetInstance()->m_aMusic[ChangeInMusicID(m_MusicId)]->Stop();
		m_MusicId += 1 + rand() % 7;
		m_MusicId = m_MusicId % 8;
		SoundManager::GetInstance()->m_aMusic[ChangeInMusicID(m_MusicId)]->Play();
		timeChangeMusic = timecount;
	}

	if (timecount > timeBase + 1.0 / 120)
	{
		AddPair::GetInstance()->Step(AddPair::GetInstance()->settings);
		m_isRender = true;
		//printf("%f\n", timecount);
		timeBase = timecount;
		//AddPair::GetInstance()->Print();
		
	}
	
	for (int i = 0; i < m_ObjectsRender.size(); i++)
	{
		m_ObjectsRender[i]->Update(deltaTime);
	}
}

// GS process when an Event is Catch, call in Game's Update, after GS is updated
GS_TYPE GS_GamePlayScene::OnEvent(Event *_event)
{
	if (_event == m_buttonPause)
	{
		//printf("Event Handle\n");
		m_event = nullptr;
		return GS_GAMEPAUSE;
	}
	if (_event == m_endGame)
	{
		//printf("Event Handle\n");
		m_event = nullptr;
		return GS_GAMEEND;
	}
}

void GS_GamePlayScene::Create()
{
	AddPair::GetInstance();
	AddPair::GetInstance()->Init();
	timecount = 0.0f;
	timeBase = 0.0f;
	timeChangeMusic = 0.0f;
	// test Resources file are loaded yet and load file if they aren't loaded
	if (m_isNeedLoaded)
	{
		LoadResouces();
		m_isNeedLoaded = false;
	}

	// Play Music
	//SoundManager::GetInstance()->m_aMusic[0]->Play();

	

}

// clean up when the GS is released
void GS_GamePlayScene::Release()
{
	AddPair::GetInstance()->DestroyInstance();
	/*for (int i = 0; i < m_ObjectsRender.size(); i++)
	{
		delete m_ObjectsRender[i];
	}*/
	// delete buttons
	
}

float GS_GamePlayScene::ChangeSizefromBox2DtoGraphic(float x)
{
	return x / 9.0;
}

int GS_GamePlayScene::ChangeXfromBox2DtoGraphic(float x)
{
	return floor((x + 5.0625 / 2)*106.66);
}

int GS_GamePlayScene::ChangeYfromBox2DtoGraphic(float y)
{
	return floor((y + 9.0 / 2)*106.66);
}

// CALLBACK when Touch Down Event is call
void GS_GamePlayScene::TouchActionDown(int x, int y)
{
	//printf("down\n");
	
}

// CALLBACK when Touch Up Event is call
void GS_GamePlayScene::TouchActionUp(int x, int y)
{
	//printf("up\n");
	if (m_buttonPause->CheckClick(x, y)) m_event = m_buttonPause;
}

// CALLBACK when Touch Move Event is call
void GS_GamePlayScene::TouchActionMove(int x, int y, int currentX, int currentY)
{
	//printf("Move\n");
	if (Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_isRender)
	{
		Box2DSceneManager::GetInstance()->m_objectList.at(0)->TouchActionMove(AddPair::GetInstance()->m_world, x, y, currentX, currentY);
	}
}



int GS_GamePlayScene::Match2DObjectListToObjectRender(int id)
{
	if (id == 0) return 7;
	if (id == 1) return 10;
	if (id == 2) return 2;
	if (id == 3) return 4;
	if (id == 4) return 0;
	if (id == 5) return 1;
	if (id == 6) return 6;
	if (id == 7) return 8;
	if (id == 8) return 12;
	if (id == 9) return 11;
	if (id == 10) return 9;
	return 13;
}

void GS_GamePlayScene::SetIsLoaded(bool i)
{
	m_isLoaded = i;
}

bool GS_GamePlayScene::GetIsLoaded()
{
	return m_isLoaded;
}
