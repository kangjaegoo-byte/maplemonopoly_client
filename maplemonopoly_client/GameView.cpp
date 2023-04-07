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
#include "Marker.h"
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
	m_marker = new Marker();
}

void GameView::Update(int _deltaTick)
{
	EnterCriticalSection(&m_gameLock);
	for (auto& player : m_players)
		if (player)
			player->Update(_deltaTick,m_playerIndex);

	m_dice->Update(_deltaTick);
	m_money->Update(_deltaTick, m_alertText);
	UpdateRank();
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
	m_marker->Render();
	LeaveCriticalSection(&m_gameLock);

}

void GameView::Clean()
{
	for (int i = 0; i < 4; i++)
	{
		if (m_players[i])
		{
			delete m_players[i];
			m_players[i] = nullptr;
		}
	}

	delete m_uiVector[GAMEVIEW_GAMEUSER1];
	delete m_uiVector[GAMEVIEW_GAMEUSER2];
	delete m_uiVector[GAMEVIEW_GAMEUSER3];
	delete m_uiVector[GAMEVIEW_GAMEUSER4];
	delete m_uiVector[GAMEVIEW_GAMEDICEBTN];
	delete m_dice;
	delete m_alertText;
	delete m_map;
	delete m_money;
	delete m_marker;

	m_uiVector[GAMEVIEW_GAMEUSER1] = nullptr;
	m_uiVector[GAMEVIEW_GAMEUSER2] = nullptr;
	m_uiVector[GAMEVIEW_GAMEUSER3] = nullptr;
	m_uiVector[GAMEVIEW_GAMEUSER4] = nullptr;
	m_uiVector[GAMEVIEW_GAMEDICEBTN] = nullptr;
	m_dice	 = nullptr;
	m_alertText = nullptr;
	m_map	 = nullptr;
	m_money	 = nullptr;
	m_marker = nullptr;

	m_uiVector[GAMEVIEW_GAMEUSER1] = new UserInfo(0, 0, 250, 75, false, m_blackBrush, m_textFormat, 0);
	m_uiVector[GAMEVIEW_GAMEUSER2] = new UserInfo2(550, 0, 250, 75, false, m_blackBrush, m_textFormat, 1);
	m_uiVector[GAMEVIEW_GAMEUSER3] = new UserInfo3(0, 525, 250, 75, false, m_blackBrush, m_textFormat, 2);
	m_uiVector[GAMEVIEW_GAMEUSER4] = new UserInfo4(550, 525, 250, 75, false, m_blackBrush, m_textFormat, 3);
	m_dice = new Dice();
	m_alertText = new AlertText(332, 361, 130, 70, false);
	m_map = new Map();
	m_money = new Money();
	m_uiVector[GAMEVIEW_GAMEDICEBTN] = new DiceBtn(350, 342, 96, 81, false);
	m_marker = new Marker();
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
		char buffer[256];
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		header->size = 8;
		header->id = PKT_S_DICEDROP;
		*(int*)(header + 1) = m_playerIndex;
		Network::GetInstance()->Send(buffer, header->size);
		m_myTurn = false;
	}
}

void GameView::CharEvent(WPARAM _key)
{
}
 
ViewType GameView::ChangeView()
{
	if (m_viewChange == false)
	{
		m_viewChange = false;
		return ViewType::VIEW_NONE;
	}
	else
	{
		m_viewChange = false;
		return ViewType::WROOM_VIEW;
	}
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
	m_marker->SetVisiable(false);
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
	m_marker->SetPos(dest._mapIndex);
	m_marker->SetVisiable(true);
	static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + playerIndex])->SetMoney(playerMoney);
	m_players[playerIndex]->Move(dest);
	m_alertText->SetState(AlertTextState::AlertTextState_NONE);

}

void GameView::GameEnd(int _data)
{
	if (m_playerIndex == _data)
	{
		// 승리 모달창 띄우기
		m_viewChange = true;
	}
	else
	{
		// 로비로 나가기
		m_change = true;
	}
}

void GameView::PlayerDisconnect(int _playerIndex)
{
	EnterCriticalSection(&m_gameLock);

	m_map->DestoryUser(_playerIndex);
	delete m_players[_playerIndex];
	m_players[_playerIndex] = nullptr;


	static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + _playerIndex])->Opacity(true);
	static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + _playerIndex])->SetMoney(0);
	LeaveCriticalSection(&m_gameLock);
}

void GameView::UpdateRank()
{
	struct tempData 
	{
		int _playerIndex;
		int _money;
	};

	std::vector<tempData> v;

	for (int i = 0; i < 4; i++)
	{
		if (m_players[i])
		{
			tempData t ={ i,m_players[i]->GetMoney() };
			v.push_back(t);
		}
	}
	
	std::sort(v.begin(), v.end(), [](tempData left, tempData right) -> bool { return left._money > right._money; });

	for (int i = 0; i < v.size(); i++) 
	{
		static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + v[i]._playerIndex])->SetRank(i+1);
	}
}

void GameView::GameBuyRegionModalProcessResponse(char* _dataPtr)
{
	int playerIndex = (*(int*)_dataPtr);
	Region region = (*(Region*)(_dataPtr + 4));
	int money = *(int*)(_dataPtr + 4 + sizeof(Region));

	int o_money = m_players[playerIndex]->GetMoney();
	const int dif = abs(o_money - money);

	m_money->GameBuyRegionModalProcessResponse(playerIndex);
	m_map->Async(region);
	m_players[playerIndex]->SetMoney(money);
	m_alertText->SetMoney(region._passCost);

	static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + playerIndex])->SetMoney(money);

	if (m_playerIndex == playerIndex)
	{
		char buffer[256];
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		header->size = 4;
		header->id = PKT_S_PASSTURN;
		Network::GetInstance()->Send(buffer, header->size);
	}
}

void GameView::MoneyPassCost(char* _dataPtr)
{
	int playerIndex = (*(int*)_dataPtr);
	int money = (*(int*)(_dataPtr + 4));
	int otherPlayerIdx = (*(int*)(_dataPtr + 8));
	int otherMoney = (*(int*)(_dataPtr + 12));
	int o_money = m_players[playerIndex]->GetMoney();
	int dif = abs(o_money - money);
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
	int o_money = m_players[playerIndex]->GetMoney();
	m_money->GameOtherBuyResponse(playerIndex, otherIdx);
	m_map->Async(region);
	m_players[playerIndex]->SetMoney(money);
	m_players[otherIdx]->SetMoney(otherMoney);

	const int dif = abs(o_money - money);
	m_alertText->SetMoney(dif);

	if (static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + playerIndex]))
		static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + playerIndex])->SetMoney(money);

	if (static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + otherIdx]))
		static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + otherIdx])->SetMoney(otherMoney);

	if (m_playerIndex == playerIndex)
	{
		char buffer[256];
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		header->size = 4;
		header->id = PKT_S_PASSTURN;
		Network::GetInstance()->Send(buffer, header->size);
	}
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

	int money = ::abs(otherMoney - m_players[otherIndex]->GetMoney());

	m_alertText->SetMoney(money);

	m_money->MoneyPassCost(playerIndex, otherIndex);
	
	static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + playerIndex])->Opacity(true);

	if (static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + playerIndex]))
		static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + playerIndex])->SetMoney(0);

	if (static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + otherIndex]))
		static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + otherIndex])->SetMoney(otherMoney);

	if (m_playerIndex == playerIndex)
	{
		char buffer[256];
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		header->size = 4;
		header->id = PKT_S_PLAYERDEAD;
		*(int*)(header + 1) = m_playerIndex;
		Network::GetInstance()->Send(buffer, header->size);
	}


	LeaveCriticalSection(&m_gameLock);
}

bool GameView::GameEnd()
{
	bool ret = m_change;

	m_change = false;

	return ret;
}

void GameView::GameUserAsync(char* _buffer)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(_buffer);

	char* readPos = (char*)(header + 1);

	int playerCount = *(int*)(readPos);			readPos += 4;

	for (int i = 0; i < playerCount; i++) 
	{
		int pick = *(int*)(readPos);			readPos += 4;
		int order = *(int*)(readPos);			readPos += 4;
		int usernameSize = *(int*)(readPos);	readPos += 4;
		WCHAR* username = (WCHAR*)(readPos);	readPos += usernameSize;


		User user;
		user.SetPick((Pick)pick);
		user.SetOrder(order);
		user.SetUsername(username, usernameSize);

		static_cast<UserInfo*>(m_uiVector[GAMEVIEW_GAMEUSER1 + order])->Init(user);
		m_players[order] = new Player(user.GetPick(), 100, 0, 402, 522);
	}
}
