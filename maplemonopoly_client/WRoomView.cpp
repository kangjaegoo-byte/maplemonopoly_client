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
		//WROOM_GAMESTART_BTN = 1,
		//WROOM_USERPICK1_BTN = 2,
		//WROOM_USERPICK2_BTN = 3,
		//WROOM_USERPICK3_BTN = 4,
		//WROOM_UICOUNT = 11
	m_uiVector.resize(WROOM_UICOUNT, nullptr);
	m_uiVector[WROOM_EXIT_BTN] = new Button(749,572,26,19,false);
	m_uiVector[WROOM_TITLE_STATICTEXT] = new StaticText(27,61,274,20,false,m_blackBrush,m_staticTextFormat);
	m_uiVector[WROOM_USERNAME1_STATICTEXT] = new StaticText(31,214,79,14,false,m_blackBrush, m_staticTextFormat);
	m_uiVector[WROOM_USERNAME2_STATICTEXT] = new StaticText(134,214,79,14,false,m_blackBrush, m_staticTextFormat);
	m_uiVector[WROOM_USERNAME3_STATICTEXT] = new StaticText(244,214,79,14,false,m_blackBrush, m_staticTextFormat);
	m_uiVector[WROOM_USERNAME4_STATICTEXT] = new StaticText(350,214,79,14,false,m_blackBrush, m_staticTextFormat);
	m_uiVector[WROOM_CHATINPUT] = new InputEditor(184,523,300,20,10,false,m_blackBrush,m_textFormat);
	m_uiVector[WROOM_CHATTING_LIST] = new ChattingBox(16, 50, 374, 448, false, m_blackBrush, m_textFormat,15);
}

void WRoomView::Update()
{
	const int passTick = 1000;

	int currentTick = ::GetTickCount64();
	int deltaTick = currentTick - m_lastTick;

	m_sumTick += deltaTick;
	m_lastTick = currentTick;

	if (m_sumTick >= passTick)
	{
		int nowRoomSq = MaplemonopolyApp::GetInstance()->GetUserInfo()->GetRoomSq();
		Network::GetInstance()->SendPacket((char*) & nowRoomSq, CLIENT_WATING_ROOM_ASYNCDATA, PACKET_HEADER_SIZE + sizeof(int), 1);
		m_sumTick = 0;
	}

	Button* exitBtn = reinterpret_cast<Button*> (m_uiVector[WROOM_EXIT_BTN]);

	if (exitBtn->GetClicked())
	{
		int roomSq = MaplemonopolyApp::GetInstance()->GetUserInfo()->GetRoomSq();
		// 방 나가기
		Network::GetInstance()->SendPacket((char*)& roomSq, CLIENT_WROOM_EXIT_REQUEST, PACKET_HEADER_SIZE + sizeof(int), 0);
		SceneManager::GetInstance()->MoveViewIndex(0); // Lobby 이동
		reinterpret_cast<ChattingBox*>(m_uiVector[WROOM_CHATTING_LIST])->ClearChat();
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
				WCHAR* text = reinterpret_cast<InputEditor*>(m_uiVector[zindex])->GetText();
				Network::GetInstance()->SendPacket((char*)text, CLIENT_WROOM_CHAT_MSG_SEND_REQUEST, wcslen(text) * sizeof(WCHAR) + PACKET_HEADER_SIZE, 1);
				reinterpret_cast<InputEditor*>(m_uiVector[zindex])->TextInit();
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

	reinterpret_cast<StaticText*>(m_uiVector[WROOM_USERNAME1_STATICTEXT])->SetText(nullptr);
	reinterpret_cast<StaticText*>(m_uiVector[WROOM_USERNAME2_STATICTEXT])->SetText(nullptr);
	reinterpret_cast<StaticText*>(m_uiVector[WROOM_USERNAME3_STATICTEXT])->SetText(nullptr);
	reinterpret_cast<StaticText*>(m_uiVector[WROOM_USERNAME4_STATICTEXT])->SetText(nullptr);

	for (int i = 0; i < _data.size(); i++)
	{
		reinterpret_cast<StaticText*>(m_uiVector[i + 6])->SetText(_data[i].GetUsername(), wcslen(_data[i].GetUsername())*2);
	}
	LeaveCriticalSection(&m_wroomLock);
}

void WRoomView::WatingRoomTitle(WCHAR* _buffer, int _dataCnt)
{
	EnterCriticalSection(&m_wroomLock);
	reinterpret_cast<StaticText*>(m_uiVector[WROOM_TITLE_STATICTEXT])->SetText(_buffer, _dataCnt);
	LeaveCriticalSection(&m_wroomLock);
}

void WRoomView::WatingRoomBoom()
{
	MaplemonopolyApp::GetInstance()->GetUserInfo()->SetRoomSq(0);
	SceneManager::GetInstance()->MoveViewIndex(0); // Lobby 이동
	reinterpret_cast<ChattingBox*>(m_uiVector[WROOM_CHATTING_LIST])->ClearChat();
}

void WRoomView::WRoomChatMsgRecv(WCHAR* _buffer, int _dataSize)
{
	reinterpret_cast<ChattingBox*>(m_uiVector[WROOM_CHATTING_LIST])->Add((char*)_buffer, _dataSize);
}
