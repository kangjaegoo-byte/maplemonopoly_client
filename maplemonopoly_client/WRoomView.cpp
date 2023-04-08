#include "pch.h"
#include "WRoomView.h"
#include "ResourceManager.h"
#include "Bitmap.h"
#include "MaplemonopolyApp.h"
#include "SceneManager.h"
#include "Button.h"
#include "InputEditor.h"
#include "ChattingBox.h"
#include "UserPickView.h"
#include "StaticText.h"
#include "User.h"
#include "Ready.h"
WRoomView::WRoomView(ID2D1HwndRenderTarget* _rt, ID2D1BitmapRenderTarget* _crt, IDWriteTextFormat* _textFormat, IDWriteTextFormat* _staticTextFormat, ID2D1SolidColorBrush* _brush) : m_rt(_rt), m_crt(_crt), m_textFormat(_textFormat), m_staticTextFormat(_staticTextFormat), m_blackBrush(_brush)
{
	Init();
}

WRoomView::~WRoomView()
{
	for (int zindex = 0; zindex < WROOM_UICOUNT; zindex++)
		if (m_uiVector[zindex])
			delete m_uiVector[zindex];
	DeleteCriticalSection(&m_wroomLock);
}

void WRoomView::Init()
{
	InitializeCriticalSection(&m_wroomLock);
	m_uiVector.resize(WROOM_UICOUNT, nullptr);	

	m_uiVector[WROOM_EXIT_BTN] = new Button(749, 572, 26, 19, false, EXIT);
	m_uiVector[WROOM_TITLE_STATICTEXT] = new StaticText(27, 61, 274, 20, false, m_blackBrush, m_staticTextFormat);
	m_uiVector[WROOM_USERNAME1_STATICTEXT] = new StaticText(31, 214, 79, 14, false, m_blackBrush, m_staticTextFormat);
	m_uiVector[WROOM_USERNAME2_STATICTEXT] = new StaticText(134, 214, 79, 14, false, m_blackBrush, m_staticTextFormat);
	m_uiVector[WROOM_USERNAME3_STATICTEXT] = new StaticText(244, 214, 79, 14, false, m_blackBrush, m_staticTextFormat);
	m_uiVector[WROOM_USERNAME4_STATICTEXT] = new StaticText(350, 214, 79, 14, false, m_blackBrush, m_staticTextFormat);
	m_uiVector[WROOM_CHATINPUT] = new InputEditor(184, 523, 300, 20, 10, false, m_blackBrush, m_textFormat);
	m_uiVector[WROOM_CHATTING_LIST] = new ChattingBox(16, 50, 374, 448, false, m_blackBrush, m_textFormat, 15);

	m_uiVector[WROOM_USERPICK1_BTN] = new Button(488, 83, 61, 40, false, HONYPICKCHANGE);
	m_uiVector[WROOM_USERPICK2_BTN] = new Button(560, 83, 61, 40, false, ORANGEPICKCHANGE);
	m_uiVector[WROOM_USERPICK3_BTN] = new Button(633, 83, 61, 40, false, PIGPICKCHANGE);
	m_uiVector[WROOM_GAMESTART_BTN] = new Button(512, 495, 185, 47, false, READY);

	const int padding1 = 10;
	const int padding2 = 20;
	m_uiVector[WROOM_USER1_PICKVIEW] = new UserPickView(29 + padding1, 116 + padding1, 87 - padding2, 87 - padding2, false, Pick::ORANGE_MURSHROOM);
	m_uiVector[WROOM_USER2_PICKVIEW] = new UserPickView(134 + padding1, 116 + padding1, 87 - padding2, 87 - padding2, false, Pick::ORANGE_MURSHROOM);
	m_uiVector[WROOM_USER3_PICKVIEW] = new UserPickView(239 + padding1, 116 + padding1, 87 - padding2, 87 - padding2, false, Pick::ORANGE_MURSHROOM);
	m_uiVector[WROOM_USER4_PICKVIEW] = new UserPickView(344 + padding1, 116 + padding1, 87 - padding2, 87 - padding2, false, Pick::ORANGE_MURSHROOM);

	m_uiVector[WROOM_READY_P2] = new Ready(134,235,95,15,false);
	m_uiVector[WROOM_READY_P3] = new Ready(239,235,95,15,false);
	m_uiVector[WROOM_READY_P4] = new Ready(345,235,95,15,false);

	Button* exitBtn = static_cast<Button*> (m_uiVector[WROOM_EXIT_BTN]);
	Button* honyPick = static_cast<Button*> (m_uiVector[WROOM_USERPICK1_BTN]);
	Button* orangePick = static_cast<Button*> (m_uiVector[WROOM_USERPICK2_BTN]);
	Button* pigPick = static_cast<Button*> (m_uiVector[WROOM_USERPICK3_BTN]);
	Button* gameStart = static_cast<Button*> (m_uiVector[WROOM_GAMESTART_BTN]);

	buttons.push_back(exitBtn);
	buttons.push_back(honyPick);
	buttons.push_back(orangePick);
	buttons.push_back(pigPick);
	buttons.push_back(gameStart);

}

void WRoomView::Update(int _deltaTick)
{
	m_sumTick += _deltaTick;
	m_animationUpdateTick += _deltaTick;

	if (m_animationUpdateTick >= animationPassTick)
	{
		for (int i = 0; i < 4; i++)
		{
			UserPickView* pickView = static_cast<UserPickView*>(m_uiVector[WROOM_USER1_PICKVIEW + i]);
			pickView->Update(NULL);
			m_animationUpdateTick = 0;
		}
	}

	{
		for (int i = 0; i < 4; i++) 
		{
			EnterCriticalSection(&m_wroomLock);
			if (m_users[i])
			{
				if (i != 0)
					static_cast<Ready*>(m_uiVector[i + 15])->SetReady(m_users[i]->GetReady());
				static_cast<StaticText*>(m_uiVector[WROOM_USERNAME1_STATICTEXT + i])->SetText(m_users[i]->GetUsername(), wcslen(m_users[i]->GetUsername()) * 2);
				static_cast<UserPickView*>(m_uiVector[WROOM_USER1_PICKVIEW + i])->Refresh(m_users[i]->GetPick());
			}
			LeaveCriticalSection(&m_wroomLock);
		}
	}

	for (auto& button : buttons)
	{
		ButtonEventHandelr(button->GetClickedCommand());
	}

}

void WRoomView::Render()
{
	m_crt->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(WATING_ROOM_BACKGROUND_BITMAP)->GetBitmap());

	for (int zindex = 0; zindex < WROOM_UICOUNT; zindex++)
		if (m_uiVector[zindex])
		{
			if (zindex != WROOM_USERNAME1_STATICTEXT 
				&& zindex != WROOM_USERNAME2_STATICTEXT 
				&& zindex != WROOM_USERNAME3_STATICTEXT 
				&& zindex != WROOM_USERNAME4_STATICTEXT 
				&& zindex != WROOM_USER1_PICKVIEW 
				&& zindex != WROOM_USER2_PICKVIEW
				&& zindex != WROOM_USER3_PICKVIEW
				&& zindex != WROOM_USER4_PICKVIEW
				&& zindex != WROOM_READY_P2
				&& zindex != WROOM_READY_P3
				&& zindex != WROOM_READY_P4
				)
			m_uiVector[zindex]->Render();
		}

	{
		for (int i = 0; i < 4; i++)
		{
			EnterCriticalSection(&m_wroomLock);
			if (m_users[i])
			{
				if (i != 0)
					static_cast<Ready*>(m_uiVector[i + 15])->Render();
				static_cast<StaticText*>(m_uiVector[WROOM_USERNAME1_STATICTEXT + i])->Render();
				static_cast<UserPickView*>(m_uiVector[i + 12])->Render();
			}
			LeaveCriticalSection(&m_wroomLock);
		}
	}


}

void WRoomView::Clean()
{
	static_cast<ChattingBox*>(m_uiVector[WROOM_CHATTING_LIST])->ClearChat();
	EnterCriticalSection(&m_wroomLock);
	for (int i = 0; i < 4; i++) 
	{
		if (m_users[i])
			m_users[i]->SetReady(false);
	}
	LeaveCriticalSection(&m_wroomLock);
}

void WRoomView::MouseMoveEvent(int _x, int _y)
{

}

void WRoomView::MouseClickEvent(int _x, int _y)
{
	for (int zindex = 0; zindex < WROOM_UICOUNT; zindex++)
	{
		auto uiItem = m_uiVector[zindex];
		if (uiItem)
			uiItem->ISFocus(_x, _y);
	}
}

void WRoomView::MouseClickUpEnvet(int _x, int _y)
{
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
				char buffer[256];
				
				WCHAR* text = static_cast<InputEditor*>(m_uiVector[zindex])->GetText();
				int textSize = wcslen(text) * sizeof(WCHAR);
			
				PacketHeader* head = reinterpret_cast<PacketHeader*>(buffer);
				*(int*)(head + 1) = textSize;
				::memcpy(((int*)(head + 1) + 1), text, textSize);

				head->size = 4 + 4 + textSize;
				head->id = PKT_S_WROOMCHAT;

				Network::GetInstance()->Send(buffer,head->size);
				static_cast<InputEditor*>(m_uiVector[zindex])->TextInit();
			}
			else
			{
				uiItem->Update(_key);
			}
		}
	}
}

ViewType WRoomView::ChangeView()
{
	if (m_lobbyRoomChange)
	{
		m_lobbyRoomChange = false;
		return ViewType::LOBBY_VIEW;
	}
	else
	{
		return ViewType::VIEW_NONE;
	}
}


void WRoomView::WRoomChatMsgRecv(WCHAR* _dataPtr, int _dataSize)
{
	static_cast<ChattingBox*>(m_uiVector[WROOM_CHATTING_LIST])->Add((char*)_dataPtr, _dataSize);
}

void WRoomView::PlayerWRoomExit(User* _user)
{
	
	for (int i = 0; i < 4; i++)
	{
		if (m_users[i] != nullptr && m_users[i]->GetUserId() == _user->GetUserId())
		{
			delete m_users[i];
			m_users[i] = nullptr;

			for (int j = i; j < 3; j++)
			{
				::std::swap(m_users[j], m_users[j + 1]);
			}
			break;
		}
	}
}

void WRoomView::PlayerWRoomEnter(User* _user)
{
	for (int i = 0; i < 4; i++)
	{
		if (m_users[i] == nullptr)
		{
			m_users[i] = new User(*_user);
			break;
		}
	}
}

void WRoomView::PlayerWRoomEnter(char* buffer)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

	char* readBuffer = (char*)(header + 1);

	int playerCount = *(int*)(readBuffer);			readBuffer += 4;
	
	for (int i = 0; i < playerCount; i++) 
	{
		int pick = *(int*)(readBuffer);			readBuffer += 4;
		int order = *(int*)(readBuffer);			readBuffer += 4;
		bool ready = *(bool*)(readBuffer);		readBuffer += sizeof(bool);
		int usernameSize = *(int*)(readBuffer);		readBuffer += 4;
		WCHAR* username = (WCHAR*)(readBuffer);		readBuffer += usernameSize;
	
		m_users[order] = new User();
		m_users[order]->SetPick(static_cast<Pick>(pick));
		m_users[order]->SetOrder(order);
		m_users[order]->SetReady(ready);
		m_users[order]->SetUsername(username, usernameSize);
	}

	int titleSize = *(int*)readBuffer; readBuffer += 4;
	WCHAR* title = (WCHAR*)readBuffer; readBuffer += titleSize;
	WRoomTitleAsync(title, titleSize);
}

void WRoomView::PlayerWRoomOtherEnter(char* buffer)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	char* readBuffer = (char*)(header + 1);
	int pick = *(int*)(readBuffer);			readBuffer += 4;
	int order = *(int*)(readBuffer);			readBuffer += 4;
	bool ready = *(bool*)(readBuffer);		readBuffer += sizeof(bool);
	int usernameSize = *(int*)(readBuffer);		readBuffer += 4;
	WCHAR* username = (WCHAR*)(readBuffer);		readBuffer += usernameSize;

	m_users[order] = new User();
	m_users[order]->SetPick(static_cast<Pick>(pick));
	m_users[order]->SetOrder(order);
	m_users[order]->SetReady(ready);
	m_users[order]->SetUsername(username, usernameSize);
}

void WRoomView::PlayerReady(char* _buffer)
{
	int userId = *(int*)_buffer;
	bool ready = *(bool*)(_buffer + 4);

	for (int i = 0; i < 4; i++) 
	{
		if (m_users[i] != nullptr && m_users[i]->GetUserId() == userId)
		{
			m_users[i]->SetReady(ready);
		}
	}
}

void WRoomView::PlayerPickChange(char* _buffer)
{
	int userId = *(int*)_buffer;
	Pick pick = *((Pick*)(_buffer + 4));

	for (int i = 0; i < 4; i++)
	{
		if (m_users[i] != nullptr && m_users[i]->GetUserId() == userId)
		{
			m_users[i]->SetPick(pick);
		}
	}
}

void WRoomView::WRoomTitleAsync(WCHAR* _dataPtr, int _dataSize)
{
	static_cast<StaticText*>(m_uiVector[WROOM_TITLE_STATICTEXT])->SetText(_dataPtr, _dataSize);
}

void WRoomView::WRoomChat(char* buffer)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	int* strSize = (int*)(header + 1);
	char* dataPtr = reinterpret_cast<char*>(strSize + 1);
	static_cast<ChattingBox*>(m_uiVector[WROOM_CHATTING_LIST])->Add(dataPtr, *strSize);
}

void WRoomView::WRoomAsync(char* buffer)
{
	for (int i = 0; i < 4; i++) 
	{
		if (m_users[i] != nullptr) 
		{
			delete m_users[i];
			m_users[i] = nullptr;
		}
	}

	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	char* readBuffer = (char*)(header + 1);
	int playerCount = *(int*)(readBuffer);			readBuffer += 4;

	for (int i = 0; i < playerCount; i++)
	{
		int pick = *(int*)(readBuffer);			readBuffer += 4;
		int order = *(int*)(readBuffer);			readBuffer += 4;
		bool ready = *(bool*)(readBuffer);		readBuffer += sizeof(bool);
		int usernameSize = *(int*)(readBuffer);		readBuffer += 4;
		WCHAR* username = (WCHAR*)(readBuffer);		readBuffer += usernameSize;
		m_users[order] = new User();
		m_users[order]->SetPick(static_cast<Pick>(pick));
		m_users[order]->SetOrder(order);
		m_users[order]->SetReady(ready);
		m_users[order]->SetUsername(username, usernameSize);
	}
}

void WRoomView::WRoomPickChange(char* buffer)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	int userIndex = *(int*)(header + 1);
	Pick pick = static_cast<Pick>(*((int*)(header + 1) + 1));
	m_users[userIndex]->SetPick(pick);
}

void WRoomView::WRoomReady(char* buffer)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	int userIndex = *(int*)(header + 1);
	bool ready = *(bool*)((int*)(header + 1) + 1);
	m_users[userIndex]->SetReady(ready);
}

void WRoomView::ButtonEventHandelr(ButtonCommand command)
{
	switch (command)
	{
	case EXIT:
	{
		char buffer[256];

		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		header->id = PKT_S_EXITWROOM;
		header->size = 4;
		Network::GetInstance()->Send(buffer, header->size);

		m_lobbyRoomChange = true;
		static_cast<ChattingBox*>(m_uiVector[WROOM_CHATTING_LIST])->ClearChat();

		for (int i = 0; i < 4; i++)
		{
			EnterCriticalSection(&m_wroomLock);
			delete m_users[i];
			m_users[i] = nullptr;
			LeaveCriticalSection(&m_wroomLock);
		}
	
	}
		break;

	case HONYPICKCHANGE:
	{
		Pick myPick = Pick::HORN_MURSHROOM;
		char buffer[256];
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		header->id = PKT_S_PICKCHANGE;
		header->size = 8;
		*(int*)(header + 1) = static_cast<int>(myPick);
		Network::GetInstance()->Send(buffer, header->size);
	}
		break;

	case ORANGEPICKCHANGE:
	{
		Pick myPick = Pick::ORANGE_MURSHROOM;
		char buffer[256];
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		header->id = PKT_S_PICKCHANGE;
		header->size = 8;
		*(int*)(header + 1) = static_cast<int>(myPick);
		Network::GetInstance()->Send(buffer, header->size);
	}
		break;

	case PIGPICKCHANGE:
	{
		Pick myPick = Pick::PIG;
		char buffer[256];
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		header->id = PKT_S_PICKCHANGE;
		header->size = 8;
		*(int*)(header + 1) = static_cast<int>(myPick);
		Network::GetInstance()->Send(buffer, header->size);
	}
		break;

	case READY:
	{
		char buffer[256];
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		header->id = PKT_S_READY;
		header->size = 4;
		Network::GetInstance()->Send(buffer, header->size);
	}
		break;
	}
}
