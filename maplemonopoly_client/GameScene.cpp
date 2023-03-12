#include "pch.h"
#include "GameScene.h"
#include "D2D1Core.h"
#include "ResourceManager.h"
#include "Bitmap.h"
#include "StaticText.h"
#include "GameUserInfoUI.h"
#include "UserDTO.h"
#include "Button.h"
GameScene::GameScene() : Scene(GAME_SCENE)
{
	Init();
}

GameScene::~GameScene()
{
	Clean();
}

void GameScene::Init()
{
	m_crt = D2D1Core::GetInstance()->GetCRT();
	m_rt = D2D1Core::GetInstance()->GetRT();
	D2D1Core::GetInstance()->SetFontFormat(&m_textFormat, L"³ª´®°íµñ", 15, DWRITE_FONT_WEIGHT_BOLD, DWRITE_TEXT_ALIGNMENT_LEADING);
	D2D1Core::GetInstance()->CreateColorBrush(&m_blackBrush, D2D1::ColorF::Black);
	D2D1Core::GetInstance()->CreateColorBrush(&m_colorBrush1, D2D1::ColorF::CornflowerBlue);
	D2D1Core::GetInstance()->CreateColorBrush(&m_colorBrush2, D2D1::ColorF::Snow);

	m_start = false;
	m_end = false;
	m_uiVector.resize(GAME_UI_COUNT);

	m_uiVector[GAMEUSER1_NAME] = new StaticText(703, 119, 72, 17, false, m_blackBrush, m_textFormat);
	m_uiVector[GAMEUSER2_NAME] = new StaticText(703, 162, 72, 17, false, m_blackBrush, m_textFormat);
	m_uiVector[GAMEUSER3_NAME] = new StaticText(703, 206, 72, 17, false, m_blackBrush, m_textFormat);
	m_uiVector[GAMEUSER4_NAME] = new StaticText(703, 249, 72, 17, false, m_blackBrush, m_textFormat);
	
	m_uiVector[GAMEUSER1] = new GameUserInfoUI(0, 0, 250, 75, false, m_colorBrush1, m_colorBrush2, m_blackBrush, m_textFormat);
	m_uiVector[GAMEUSER2] = new GameUserInfoUI(550, 0, 250, 75, false, m_colorBrush1, m_colorBrush2, m_blackBrush, m_textFormat);
	m_uiVector[GAMEUSER3] = new GameUserInfoUI(0, 525, 250, 75, false, m_colorBrush1, m_colorBrush2, m_blackBrush, m_textFormat);
	m_uiVector[GAMEUSER4] = new GameUserInfoUI(550, 525, 250, 75, false, m_colorBrush1, m_colorBrush2, m_blackBrush, m_textFormat);
	// m_uiVector[GAME_EXIT_BTN] = new Button(646, 563, 135, 25, false);

	Network::GetInstance()->SendPacket(nullptr, CLIENT_GAME_ENTER_REQUEST, PACKET_HEADER_SIZE, 0);
}

void GameScene::Update()
{
	if (!m_start) return;

	//if (static_cast<Button*>(m_uiVector[GAME_EXIT_BTN])->GetClicked())
	//{
	//	// ³ª°¡±â ¿äÃ»
	//	Network::GetInstance()->SendPacket(nullptr, CLIENT_GAME_EXIT_REQUEST, PACKET_HEADER_SIZE, 0);
	//}
}

void GameScene::Render()
{
	RECT rc;
	GetClientRect(D2D1Core::GetInstance()->GetHWND(), &rc);

	m_crt->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(GAME_BOARD_BITMAP)->GetBitmap(), D2D1::RectF(rc.left, rc.top, rc.right, rc.bottom));

	if (!m_start) return;


	for (auto& item : m_uiVector) 
	{
		if (item)
			item->Render();
	}

}

void GameScene::Clean()
{
	ResourceManager::GetInstance()->Delete(GAME_BACKGROUND_BITMAP);
	m_blackBrush->Release();
	m_textFormat->Release();
	m_colorBrush1->Release();
	m_colorBrush2->Release();
	for (auto& item : m_uiVector) 
	{
		if (item)
			delete item;
	}

}
 
void GameScene::MouseMoveEvent(int _x, int _y)
{
}

void GameScene::MouseClickEnvet(int _x, int _y)
{
	for (int zindex = 0; zindex < GAME_UI_COUNT; zindex++)
	{
		auto uiItem = m_uiVector[zindex];
		if (uiItem)
			uiItem->ISFocus(_x, _y);
	}
}

void GameScene::CharEvent(WPARAM _key)
{
}

void GameScene::GamePlay(std::vector<UserDTO>& dto)
{
	m_start = true;

	for (int user = 0; user < dto.size(); user++) 
	{
		static_cast<GameUserInfoUI*>(m_uiVector[GAMEUSER1 + user])->Init(dto[user]);
	}
}

void GameScene::GameExit(int _exitGameUserIndex)
{

	for (int i = 0; i < 4; i++) 
	{
		static_cast<GameUserInfoUI*>(m_uiVector[GAMEUSER1 + i])->Hide(_exitGameUserIndex);
	}
}

