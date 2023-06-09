#include "pch.h"
#include "WRoomView.h"
#include "ResourceManager.h"
#include "Bitmap.h"
#include "StaticText.h"
#include "MaplemonopolyApp.h"
#include "Button.h"
#include "SceneManager.h"
#include "InputEditor.h"
#include "ChattingBox.h"
#include "UserPickView.h"
WRoomView::WRoomView(ID2D1HwndRenderTarget* _rt, ID2D1BitmapRenderTarget* _crt, IDWriteTextFormat* _textFormat, IDWriteTextFormat* _staticTextFormat, ID2D1SolidColorBrush* _brush) : m_rt(_rt), m_crt(_crt), m_textFormat(_textFormat), m_staticTextFormat(_staticTextFormat), m_blackBrush(_brush)
{
	Init();
}

WRoomView::~WRoomView()
{
	Clean();
}

void WRoomView::Init()
{
	InitializeCriticalSection(&m_wroomLock);
	m_uiVector.resize(WROOM_UICOUNT, nullptr);
	m_uiVector[WROOM_EXIT_BTN] = new Button(749,572,26,19,false);
	m_uiVector[WROOM_TITLE_STATICTEXT] = new StaticText(27,61,274,20,false,m_blackBrush,m_staticTextFormat);
	m_uiVector[WROOM_USERNAME1_STATICTEXT] = new StaticText(31,214,79,14,false,m_blackBrush, m_staticTextFormat);
	m_uiVector[WROOM_USERNAME2_STATICTEXT] = new StaticText(134,214,79,14,false,m_blackBrush, m_staticTextFormat);
	m_uiVector[WROOM_USERNAME3_STATICTEXT] = new StaticText(244,214,79,14,false,m_blackBrush, m_staticTextFormat);
	m_uiVector[WROOM_USERNAME4_STATICTEXT] = new StaticText(350,214,79,14,false,m_blackBrush, m_staticTextFormat);
	m_uiVector[WROOM_CHATINPUT] = new InputEditor(184,523,300,20,10,false,m_blackBrush,m_textFormat);
	m_uiVector[WROOM_CHATTING_LIST] = new ChattingBox(16, 50, 374, 448, false, m_blackBrush, m_textFormat,15);
	m_uiVector[WROOM_USERPICK1_BTN] = new Button(488, 83, 61, 40, false); 
	m_uiVector[WROOM_USERPICK2_BTN] = new Button(560, 83, 61, 40, false); 
	m_uiVector[WROOM_USERPICK3_BTN] = new Button(633, 83, 61, 40, false); 	
	m_uiVector[WROOM_GAMESTART_BTN] = new Button(512, 495, 185, 47, false); 	

	const int padding1 = 10;
	const int padding2 = 20;
	m_uiVector[WROOM_USER1_PICKVIEW] = new UserPickView(29  + padding1, 116 + padding1, 87 - padding2, 87 - padding2, false, CPick::ORANGE_MURSHROOM); 
	m_uiVector[WROOM_USER2_PICKVIEW] = new UserPickView(134 + padding1, 116 + padding1, 87 - padding2, 87 - padding2, false, CPick::ORANGE_MURSHROOM);
	m_uiVector[WROOM_USER3_PICKVIEW] = new UserPickView(239 + padding1, 116 + padding1, 87 - padding2, 87 - padding2, false, CPick::ORANGE_MURSHROOM);
	m_uiVector[WROOM_USER4_PICKVIEW] = new UserPickView(344 + padding1, 116 + padding1, 87 - padding2, 87 - padding2, false, CPick::ORANGE_MURSHROOM);

}

void WRoomView::Update()
{
	const int passTick = 1000;
	const int animationPassTick = 100;

	int currentTick = ::GetTickCount64();
	int deltaTick = currentTick - m_lastTick;

	m_sumTick += deltaTick;
	m_lastTick = currentTick;
	m_animationUpdateTick += deltaTick;

	if (m_sumTick >= passTick)
	{
		int nowRoomSq = MaplemonopolyApp::GetInstance()->GetUserInfo()->GetRoomSq();
		Network::GetInstance()->SendPacket((char*) & nowRoomSq, CLIENT_WATING_ROOM_ASYNCDATA, PACKET_HEADER_SIZE + sizeof(int), 1);
		m_sumTick = 0;
	}

	if (m_animationUpdateTick >= animationPassTick)
	{
		for (int i = 0; i < 4; i++)
		{
			UserPickView* pickView = static_cast<UserPickView*>(m_uiVector[WROOM_USER1_PICKVIEW + i]);
			pickView->Update(NULL);
			m_animationUpdateTick = 0;
		}
	}

	Button* exitBtn = static_cast<Button*> (m_uiVector[WROOM_EXIT_BTN]);
	Button* honyPick = static_cast<Button*> (m_uiVector[WROOM_USERPICK1_BTN]);
	Button* orangePick = static_cast<Button*> (m_uiVector[WROOM_USERPICK2_BTN]);
	Button* pigPick = static_cast<Button*> (m_uiVector[WROOM_USERPICK3_BTN]);
	Button* gameStart = static_cast<Button*> (m_uiVector[WROOM_GAMESTART_BTN]);

	if (exitBtn->GetClicked())
	{
		int roomSq = MaplemonopolyApp::GetInstance()->GetUserInfo()->GetRoomSq();
		// 방 나가기
		Network::GetInstance()->SendPacket((char*)& roomSq, CLIENT_WROOM_EXIT_REQUEST, PACKET_HEADER_SIZE + sizeof(int), 0);
		SceneManager::GetInstance()->MoveViewIndex(0); // Lobby 이동
		static_cast<ChattingBox*>(m_uiVector[WROOM_CHATTING_LIST])->ClearChat();
	}
	else if (honyPick->GetClicked())
	{
		CPick myPick = CPick::HONY_MURSHROOM;
		Network::GetInstance()->SendPacket((char*)&myPick, CLIENT_CPICK_REQUEST, PACKET_HEADER_SIZE+sizeof(int), 0);
	}
	else if (orangePick->GetClicked())
	{
		CPick myPick = CPick::ORANGE_MURSHROOM;
		Network::GetInstance()->SendPacket((char*)&myPick, CLIENT_CPICK_REQUEST, PACKET_HEADER_SIZE + sizeof(int), 0);
	}
	else if (pigPick->GetClicked())
	{
		CPick myPick = CPick::PIG;
		Network::GetInstance()->SendPacket((char*)&myPick, CLIENT_CPICK_REQUEST, PACKET_HEADER_SIZE + sizeof(int), 0);
	}
	else if (gameStart->GetClicked())
	{
		Network::GetInstance()->SendPacket(nullptr,CLIENT_GAME_START_REQUEST, PACKET_HEADER_SIZE, 0);
	}
}

void WRoomView::Render()
{
	m_crt->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(WATING_ROOM_BACKGROUND_BITMAP)->GetBitmap());

	for (int zindex = 0; zindex < WROOM_UICOUNT; zindex++)
		if (m_uiVector[zindex])
			m_uiVector[zindex]->Render();
}

void WRoomView::Clean()
{
	for (int zindex = 0; zindex < WROOM_UICOUNT; zindex++)
		if (m_uiVector[zindex])
			delete m_uiVector[zindex];
	DeleteCriticalSection(&m_wroomLock);
}

void WRoomView::MouseMoveEvent(int _x, int _y)
{

}

void WRoomView::MouseClickEnvet(int _x, int _y)
{
	for (int zindex = 0; zindex < WROOM_UICOUNT; zindex++)
	{
		auto uiItem = m_uiVector[zindex];
		if (uiItem)
			uiItem->ISFocus(_x, _y);
	}
}

void WRoomView::CharEvent(WPARAM _key)
{
	for (int zindex = 0; zindex < WROOM_UICOUNT; zindex++)
	{
		auto uiItem = m_uiVector[zindex];
		if (uiItem && uiItem->FocuseCheck())
		{
			if (zindex == WROOM_CHATINPUT && _key == 13 /* ENTER */)
			{
				WCHAR* text = static_cast<InputEditor*>(m_uiVector[zindex])->GetText();
				Network::GetInstance()->SendPacket((char*)text, CLIENT_WROOM_CHAT_MSG_SEND_REQUEST, wcslen(text) * sizeof(WCHAR) + PACKET_HEADER_SIZE, 1);
				static_cast<InputEditor*>(m_uiVector[zindex])->TextInit();
			}
			else
			{
				uiItem->Update(_key);
			}
		}
	}
}

void WRoomView::WatingRoomUserList(std::vector<UserDTO>& _data)
{
	EnterCriticalSection(&m_wroomLock);
	static_cast<StaticText*>(m_uiVector[WROOM_USERNAME2_STATICTEXT])->SetText(nullptr);
	static_cast<StaticText*>(m_uiVector[WROOM_USERNAME3_STATICTEXT])->SetText(nullptr);
	static_cast<StaticText*>(m_uiVector[WROOM_USERNAME4_STATICTEXT])->SetText(nullptr);

	for (int i = 0; i < 4; i++) 
	{
		static_cast<StaticText*>(m_uiVector[WROOM_USERNAME1_STATICTEXT + i])->SetText(nullptr);
	}

	int user;
	for (user = 0; user < _data.size(); user++)
	{
		static_cast<UserPickView*>(m_uiVector[user + 12])->Refresh(static_cast<CPick>(_data[user].GetPick()));
		static_cast<StaticText*>(m_uiVector[user + 6])->SetText(_data[user].GetUsername(), wcslen(_data[user].GetUsername())*2);
	}

	for (; user < 4; user++)
		static_cast<UserPickView*>(m_uiVector[user + 12])->Refresh(static_cast<CPick>(NOUSER));


	LeaveCriticalSection(&m_wroomLock);
}

void WRoomView::WatingRoomTitle(WCHAR* _buffer, int _dataCnt)
{
	EnterCriticalSection(&m_wroomLock);
	static_cast<StaticText*>(m_uiVector[WROOM_TITLE_STATICTEXT])->SetText(_buffer, _dataCnt);
	LeaveCriticalSection(&m_wroomLock);
}

void WRoomView::WatingRoomBoom()
{
	MaplemonopolyApp::GetInstance()->GetUserInfo()->SetRoomSq(0);
	SceneManager::GetInstance()->MoveViewIndex(0); // Lobby 이동
	static_cast<ChattingBox*>(m_uiVector[WROOM_CHATTING_LIST])->ClearChat();
}

void WRoomView::WRoomChatMsgRecv(WCHAR* _buffer, int _dataSize)
{
	static_cast<ChattingBox*>(m_uiVector[WROOM_CHATTING_LIST])->Add((char*)_buffer, _dataSize);
}
