#include "pch.h"
#include "GameScene.h"
#include "D2D1Core.h"
#include "ResourceManager.h"
#include "Bitmap.h"
#include "StaticText.h"
#include "UserPickView.h"
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
	D2D1Core::GetInstance()->SetFontFormat(&m_textFormat, L"³ª´®°íµñ", 13, DWRITE_FONT_WEIGHT_BOLD, DWRITE_TEXT_ALIGNMENT_CENTER);
	D2D1Core::GetInstance()->CreateColorBrush(&m_blackBrush, D2D1::ColorF::Black);

	m_start = false;
	m_end = false;
	m_uiVector.resize(GAME_UI_COUNT);

	m_uiVector[GAMEUSER1_NAME] = new StaticText(703, 119, 72, 17, false, m_blackBrush, m_textFormat);
	m_uiVector[GAMEUSER2_NAME] = new StaticText(703, 162, 72, 17, false, m_blackBrush, m_textFormat);
	m_uiVector[GAMEUSER3_NAME] = new StaticText(703, 206, 72, 17, false, m_blackBrush, m_textFormat);
	m_uiVector[GAMEUSER4_NAME] = new StaticText(703, 249, 72, 17, false, m_blackBrush, m_textFormat);
	
	m_uiVector[GAMEUSER1_USERPICK] = new UserPickView(662, 105, 37, 23, false, CPick::NOUSER);
	m_uiVector[GAMEUSER2_USERPICK] = new UserPickView(662, 146, 37, 23, false, CPick::NOUSER);
	m_uiVector[GAMEUSER3_USERPICK] = new UserPickView(662, 191, 37, 23, false, CPick::NOUSER);
	m_uiVector[GAMEUSER4_USERPICK] = new UserPickView(662, 233, 37, 23, false, CPick::NOUSER);
	m_uiVector[GAME_EXIT_BTN] = new Button(646, 563, 135, 25, false);

	Network::GetInstance()->SendPacket(nullptr, CLIENT_GAME_ENTER_REQUEST, PACKET_HEADER_SIZE, 0);
}

void GameScene::Update()
{
	if (!m_start) return;

	if (static_cast<Button*>(m_uiVector[GAME_EXIT_BTN])->GetClicked())
	{
		// ³ª°¡±â ¿äÃ»
		Network::GetInstance()->SendPacket(nullptr, CLIENT_GAME_EXIT_REQUEST, PACKET_HEADER_SIZE, 0);
	}
}

void GameScene::Render()
{
	m_crt->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(GAME_BACKGROUND_BITMAP)->GetBitmap());

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
}

void GameScene::CharEvent(WPARAM _key)
{
}

void GameScene::GamePlay(std::vector<UserDTO>& dto)
{
	m_start = true;

	for (int user = 0; user < dto.size(); user++) 
	{
		static_cast<StaticText*>(m_uiVector[GAMEUSER1_NAME + user])->SetText(dto[user].GetUsername(), wcslen(dto[user].GetUsername()) * 2);
		static_cast<UserPickView*>(m_uiVector[GAMEUSER1_USERPICK + user])->Refresh(static_cast<CPick>(dto[user].GetPick()));
	}
}

