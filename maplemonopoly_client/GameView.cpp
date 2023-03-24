#include "pch.h"
#include "GameView.h"
#include "UserInfo.h"
#include "UserInfo2.h"
#include "UserInfo3.h"
#include "UserInfo4.h"
#include "User.h"
#include "DiceBtn.h"
#include "Player.h"
#include "Dice.h"
GameView::GameView(ID2D1HwndRenderTarget* _rt, ID2D1BitmapRenderTarget* _crt, IDWriteTextFormat* _textFormat, ID2D1SolidColorBrush* _black, ID2D1SolidColorBrush* _color1, ID2D1SolidColorBrush* _color2) : m_rt(_rt), m_crt(_crt), m_textFormat(_textFormat), m_blackBrush(_black), m_colorBrush1(_color1), m_colorBrush2(_color2)
{
    Init();
}

GameView::~GameView()
{
    Clean();
}

void GameView::Init()
{
	m_uiVector.resize(GAMEVIEW_GAME_UI_COUNT, nullptr);
	m_uiVector[GAMEVIEW_GAMEDICEBTN] = new DiceBtn(350, 342, 96, 81, false);
	m_uiVector[GAMEVIEW_GAMEUSER1] = new UserInfo(0, 0, 250, 75, false, m_blackBrush, m_textFormat,0);
	m_uiVector[GAMEVIEW_GAMEUSER2] = new UserInfo2(550, 0, 250, 75, false, m_blackBrush, m_textFormat, 1);
	m_uiVector[GAMEVIEW_GAMEUSER3] = new UserInfo3(0, 525, 250, 75, false, m_blackBrush, m_textFormat, 2);
	m_uiVector[GAMEVIEW_GAMEUSER4] = new UserInfo4(550, 525, 250, 75, false, m_blackBrush, m_textFormat,3);
	m_dice = new Dice();
}

void GameView::Update(int _deltaTick)
{
	for (auto& player : m_players)
		if (player)
			player->Update(_deltaTick);

	m_dice->Update(_deltaTick);
}

void GameView::Render()
{
    RECT rc;
    GetClientRect(D2D1Core::GetInstance()->GetHWND(), &rc);
    m_crt->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(GAME_BOARD_BITMAP)->GetBitmap(), D2D1::RectF(rc.left, rc.top, rc.right, rc.bottom));

	for (int i = 0; i < GAMEVIEW_GAME_UI_COUNT; i++)
		if (m_uiVector[i])
		{
			if (i == GAMEVIEW_GAMEDICEBTN && m_myTurn)
				m_uiVector[i]->Render();
			else if (i == GAMEVIEW_GAMEDICEBTN && m_myTurn == false)
			{
			}
			else
			{
				m_uiVector[i]->Render();
			}
		}


	for (auto& player : m_players)
		if (player)
			player->Render();

	m_dice->Render();

}

void GameView::Clean()
{
	for (auto& ui : m_uiVector)
	{
		if (ui)
			delete ui;
	}
}

void GameView::MouseMoveEvent(int _x, int _y)
{
}

void GameView::MouseClickEvent(int _x, int _y)
{
	for (int zindex = 0; zindex < GAMEVIEW_GAME_UI_COUNT; zindex++)
	{
		auto uiItem = m_uiVector[zindex];
		if (uiItem)
		{
			bool focused = uiItem->ISFocus(_x, _y);
			
			if (zindex == GAMEVIEW_GAMEDICEBTN && focused && m_myTurn)
			{
				static_cast<DiceBtn*>(m_uiVector[GAMEVIEW_GAMEDICEBTN])->MouseDown();
			}
		}
	}
}

void GameView::MouseClickUpEnvet(int _x, int _y)
{
	if (m_myTurn && m_uiVector[GAMEVIEW_GAMEDICEBTN]->ISFocus(_x, _y))
	{
		static_cast<DiceBtn*>(m_uiVector[GAMEVIEW_GAMEDICEBTN])->MouseUp();
		Network::GetInstance()->SendPacket((char*)&m_playerIndex, PROCESS_GAME_DICE_REQUEST, sizeof(int), 1);
		m_myTurn = false;
	}
}

void GameView::CharEvent(WPARAM _key)
{
}

ViewType GameView::ChangeView()
{
    return ViewType::VIEW_NONE;
}

void GameView::GameUserNumber(int _dataPtr)
{
	m_playerIndex = _dataPtr;
	if (m_players[m_playerIndex])
		m_players[m_playerIndex]->SetMy();
}

void GameView::GameUserAsync(std::vector<User>& _data)
{
	for (int i = 0; i < _data.size(); i++)
	{
		static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + i])->Init(_data[i]);
		m_players[i] = new Player(_data[i].GetPick(), 100, 0, 402, 522);
	}
}

void GameView::TurnSend(int _playerIdx)
{
	m_dice->Hold(_playerIdx);

	if (m_playerIndex == _playerIdx)
		m_myTurn = true;
	else
		m_myTurn = false;
}

void GameView::DiceDropResult(DiceData* _diceData)
{
	bool myTurn = m_playerIndex == _diceData->_playerIndex;
	m_dice->Drop(_diceData, myTurn);
}
