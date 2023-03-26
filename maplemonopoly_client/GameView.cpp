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
#include "AlertText.h"
#include "Sound.h"
#include "Map.h"
#include "Money.h"
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
	InitializeCriticalSection(&m_gameLock);
	m_uiVector.resize(GAMEVIEW_GAME_UI_COUNT, nullptr);
	m_uiVector[GAMEVIEW_GAMEDICEBTN] = new DiceBtn(350, 342, 96, 81, false);
	m_uiVector[GAMEVIEW_GAMEUSER1] = new UserInfo(0, 0, 250, 75, false, m_blackBrush, m_textFormat,0);
	m_uiVector[GAMEVIEW_GAMEUSER2] = new UserInfo2(550, 0, 250, 75, false, m_blackBrush, m_textFormat, 1);
	m_uiVector[GAMEVIEW_GAMEUSER3] = new UserInfo3(0, 525, 250, 75, false, m_blackBrush, m_textFormat, 2);
	m_uiVector[GAMEVIEW_GAMEUSER4] = new UserInfo4(550, 525, 250, 75, false, m_blackBrush, m_textFormat,3);
	m_dice = new Dice();
	m_alertText = new AlertText(332,361,130,70,false);
	m_map = new Map();
	m_money = new Money();
}

void GameView::Update(int _deltaTick)
{
	EnterCriticalSection(&m_gameLock);
	for (auto& player : m_players)
		if (player)
			player->Update(_deltaTick,m_playerIndex);

	m_dice->Update(_deltaTick);
	m_money->Update(_deltaTick, m_alertText);
	LeaveCriticalSection(&m_gameLock);
}

void GameView::Render()
{
    RECT rc;
    GetClientRect(D2D1Core::GetInstance()->GetHWND(), &rc);
    m_crt->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(GAME_BOARD_BITMAP)->GetBitmap(), D2D1::RectF(rc.left, rc.top, rc.right, rc.bottom));

	EnterCriticalSection(&m_gameLock);
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

	m_map->Render();

	for (auto& player : m_players)
		if (player)
			player->Render();

	m_dice->Render();
	m_money->Render();
	m_alertText->Render();
	LeaveCriticalSection(&m_gameLock);

}

void GameView::Clean()
{
	DeleteCriticalSection(&m_gameLock);
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
	for (int i = 0; i < 4; i++)
	{
		if (static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + i]))
			static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + i])->Opacity(true);
	}

	if (static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + _playerIdx]))
		static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + _playerIdx])->Opacity(false);

	if (m_playerIndex == _playerIdx)
	{
		ResourceManager::GetInstance()->GetSound(MYTURN_SOUND)->Playing(false);
		m_myTurn = true;
	}
	else
		m_myTurn = false;
}

void GameView::DiceDropResult(DiceData* _diceData)
{
	bool myTurn = m_playerIndex == _diceData->_playerIndex;
	m_dice->Drop(_diceData, myTurn);
	if (_diceData->_dice1 == _diceData->_dice2)
		m_alertText->SetState(AlertTextState::AlertTextState_DOUBLE);
}

void GameView::PlayerMove(char* _data)
{
	Region dest = *(Region*)_data;
	int playerIndex = *(int*)(_data + sizeof(Region));
	bool salry = *(bool*)(_data + sizeof(Region) + sizeof(int));
	int playerMoney = *(int*)(_data + sizeof(Region) + sizeof(int) + sizeof(bool));

	static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + playerIndex])->SetMoney(playerMoney);
	m_players[playerIndex]->Move(dest);
	m_alertText->SetState(AlertTextState::AlertTextState_NONE);
}

void GameView::GameEnd(int _data)
{
	if (m_playerIndex == _data)
	{
		// 승리 모달창 띄우기
	}
	else
	{
		// 로비로 나가기
	}
}

void GameView::GameBuyRegionModalProcessResponse(char* _dataPtr)
{
	int playerIndex = (*(int*)_dataPtr);
	Region region = (*(Region*)(_dataPtr + 4));
	int money = *(int*)(_dataPtr + 4 + sizeof(Region));


	m_alertText->SetMoney(region._passCost);

	m_money->GameBuyRegionModalProcessResponse(playerIndex);

	m_map->Async(region);
	m_players[playerIndex]->SetMoney(money);

	static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + playerIndex])->SetMoney(money);

	if (m_playerIndex == playerIndex)
		Network::GetInstance()->SendPacket(nullptr, PROCESS_GAME_NEXTTURN_REQUEST, 0, 0);
}

void GameView::MoneyPassCost(char* _dataPtr)
{
	int playerIndex = (*(int*)_dataPtr);
	int money = (*(int*)(_dataPtr + 4));
	int otherPlayerIdx = (*(int*)(_dataPtr + 8));
	int otherMoney = (*(int*)(_dataPtr + 12));

	int o_money = m_players[playerIndex]->GetMoney();
	int dif = o_money - money;

	m_alertText->SetMoney(dif);

	m_money->MoneyPassCost(playerIndex, otherPlayerIdx);

	m_players[playerIndex]->SetMoney(money);
	m_players[otherPlayerIdx]->SetMoney(otherMoney);

	if (static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + playerIndex]))
		static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + playerIndex])->SetMoney(money);

	if (static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + otherPlayerIdx]))
		static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + otherPlayerIdx])->SetMoney(otherMoney);
}

void GameView::GameOtherBuyResponse(char* _dataPtr)
{
	int playerIndex = (*(int*)_dataPtr);
	Region region = (*(Region*)(_dataPtr + 4));
	int money = *(int*)(_dataPtr + 4 + sizeof(Region));
	int otherMoney = *(int*)(_dataPtr + 4 + sizeof(Region) + 4);
	int otherIdx = *(int*)(_dataPtr + 4 + sizeof(Region) + 4 + 4);
	m_alertText->SetMoney(region._passCost);

	m_money->GameOtherBuyResponse(playerIndex, otherIdx);

	m_map->Async(region);
	m_players[playerIndex]->SetMoney(money);
	m_players[otherIdx]->SetMoney(otherMoney);

	if (static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + playerIndex]))
		static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + playerIndex])->SetMoney(money);

	if (static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + otherIdx]))
		static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + otherIdx])->SetMoney(otherMoney);

	if (m_playerIndex == playerIndex)
		Network::GetInstance()->SendPacket(nullptr, PROCESS_GAME_NEXTTURN_REQUEST, 0, 0);
}

void GameView::PlayerDead(char* _data)
{
	EnterCriticalSection(&m_gameLock);
	int playerIndex = (*(int*)_data);
	int otherIndex = (*(int*)(_data + 4));
	int otherMoney = (*(int*)(_data + 8));

	m_map->DestoryUser(playerIndex);
	delete m_players[playerIndex];
	m_players[playerIndex] = nullptr;

	m_alertText->SetMoney(otherMoney);

	m_money->MoneyPassCost(playerIndex, otherIndex);
	
	static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + playerIndex])->Opacity(true);

	if (static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + playerIndex]))
		static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + playerIndex])->SetMoney(0);

	if (static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + otherIndex]))
		static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + otherIndex])->SetMoney(otherMoney);

	if (m_playerIndex == playerIndex)
		Network::GetInstance()->SendPacket((char*)& playerIndex, PROCESS_GAME_USER_DEAD_REQUEST, sizeof(int), 0);


	LeaveCriticalSection(&m_gameLock);
}
