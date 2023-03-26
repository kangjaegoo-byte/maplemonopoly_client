#include "pch.h"
#include "GameScene.h"
#include "UIComponent.h"
#include "GameView.h"
#include "User.h"
#include "GameModalView.h"
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
	m_viewVector.resize(GAME_VIEW_COUNT);
	m_viewVector[GAME_VIEW] = new GameView(m_rt, m_crt, m_textFormat, m_colorBrush2, m_colorBrush1, m_colorBrush2);
	m_viewVector[GAME_MODAL_VIEW] = new GameModalView(m_rt, m_crt, m_textFormat, m_blackBrush, m_colorBrush1, m_colorBrush2);
}

void GameScene::Update(int _deltaTick)
{
	ViewType viewChange = m_viewVector[m_zindex]->ChangeView();

	if (viewChange == ViewType::VIEW_NONE)
	{
		m_viewVector[m_zindex]->Update(_deltaTick);
	}
	else
	{
		m_zindex = viewChange;
	}
}

void GameScene::Render()
{
	for (int i = 0; i <= m_zindex; i++)
	{
		if (m_zindex == GAME_END_VIEW && i == GAME_MODAL_VIEW)
		{
			continue;
		}
		else
		{
			m_viewVector[i]->Render();
		}
	}
}

void GameScene::Clean()
{
	m_blackBrush->Release();
	m_textFormat->Release();
	m_colorBrush1->Release();
	m_colorBrush2->Release();
	ResourceManager::GetInstance()->DeleteSoundEx(MYTURN_SOUND);
	for (auto& item : m_uiVector)
	{
		if (item)
			delete item;
	}
}

void GameScene::MouseMoveEvent(int _x, int _y)
{
	m_viewVector[m_zindex]->MouseMoveEvent(_x, _y);
}

void GameScene::MouseClickUpEnvet(int _x, int _y)
{
	m_viewVector[m_zindex]->MouseClickUpEnvet(_x, _y);
}

void GameScene::MouseClickEvent(int _x, int _y)
{
	m_viewVector[m_zindex]->MouseClickEvent(_x, _y);
}

void GameScene::CharEvent(WPARAM _key)
{
	m_viewVector[m_zindex]->CharEvent(_key);
}

SceneChangeData GameScene::Change()
{
    return SceneChangeData { false, SceneType::NONE };
}

void GameScene::GameUserNumber(int _dataPtr)
{
	m_playerIndex = _dataPtr;
	static_cast<GameView*>(m_viewVector[GAME_VIEW])->GameUserNumber(m_playerIndex);
	static_cast<GameModalView*>(m_viewVector[GAME_MODAL_VIEW])->GameUserNumber(m_playerIndex);
}

void GameScene::GameUserAsync(std::vector<User>& _data)
{
	static_cast<GameView*>(m_viewVector[GAME_VIEW])->GameUserAsync(_data);
}

void GameScene::TurnSend(int _playerIdx)
{
	static_cast<GameView*>(m_viewVector[GAME_VIEW])->TurnSend(_playerIdx);
}

void GameScene::DiceDropResult(DiceData* _diceData)
{
	static_cast<GameView*>(m_viewVector[GAME_VIEW])->DiceDropResult(_diceData);
}

void GameScene::PlayerMove(char* _data)
{
	static_cast<GameView*>(m_viewVector[GAME_VIEW])->PlayerMove(_data);
}

void GameScene::GameBuyRegion(Region* dataPtr)
{
	static_cast<GameModalView*>(m_viewVector[GAME_MODAL_VIEW])->GameBuyRegion(dataPtr);
	m_zindex = GAME_MODAL_VIEW;
}

void GameScene::PlayerDead(char* _data)
{
	static_cast<GameView*>(m_viewVector[GAME_VIEW])->PlayerDead(_data);
}

void GameScene::GameBuyRegionModalProcessResponse(char* _dataPtr)
{
	static_cast<GameView*>(m_viewVector[GAME_VIEW])->GameBuyRegionModalProcessResponse(_dataPtr);
}

void GameScene::MoneyPassCost(char* _dataPtr)
{
	static_cast<GameView*>(m_viewVector[GAME_VIEW])->MoneyPassCost(_dataPtr);
}

void GameScene::GameBuyRegionModalOtherProcessResponseEx(char* _dataPtr)
{
	static_cast<GameModalView*>(m_viewVector[GAME_MODAL_VIEW])->GameBuyRegionModalOtherProcessResponseEx(reinterpret_cast<Region*>(_dataPtr), m_playerIndex);
	m_zindex = GAME_MODAL_VIEW;
}

void GameScene::GameOtherBuyResponse(char* _dataPtr)
{
	static_cast<GameView*>(m_viewVector[GAME_VIEW])->GameOtherBuyResponse(_dataPtr);
}

void GameScene::GameEnd(int _data)
{
	static_cast<GameView*>(m_viewVector[GAME_VIEW])->GameEnd(_data);
}
