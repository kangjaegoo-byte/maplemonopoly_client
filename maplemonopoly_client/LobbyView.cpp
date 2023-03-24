#include "pch.h"
#include "LobbyView.h"
#include "UIComponent.h"
#include "ResourceManager.h"
#include "Bitmap.h"
#include "MaplemonopolyApp.h"
#include "SceneManager.h"
#include "InputEditor.h"
#include "User.h"
#include "Button.h"
#include "ChattingBox.h"
#include "UserPageList.h"
#include "RoomPageList.h"
D2D1_RECT_F roomListRect[10] = { D2D1::RectF(15, 125, 502, 25), D2D1::RectF(15, 151,502, 25), D2D1::RectF(15, 177, 502, 25), D2D1::RectF(15, 206, 502, 25), D2D1::RectF(15, 232, 502, 25), D2D1::RectF(15, 259, 502, 25), D2D1::RectF(15, 286, 502, 25), D2D1::RectF(15, 313, 502, 25), D2D1::RectF(15, 341, 502, 25), D2D1::RectF(15, 367, 502, 25) };

LobbyView::LobbyView(ID2D1HwndRenderTarget* _rt, ID2D1BitmapRenderTarget* _crt, IDWriteTextFormat* _textFormat, IDWriteTextFormat* _boldTextFormat, ID2D1SolidColorBrush* _black, ID2D1SolidColorBrush* _blue, ID2D1SolidColorBrush* _red) : m_rt(_rt), m_crt(_crt), m_textFormat(_textFormat), m_blackBrush(_black), m_blueBrush(_blue), m_redBrush(_red), m_boldTextAliginNormalForamt(_boldTextFormat)
{
	Init();
}

LobbyView::~LobbyView()
{
	Clean();
}

void LobbyView::Init()
{
	m_uiVector.resize(LobbyView_UICOUNT);
	m_uiVector[LobbyView_CHATINPUT] = new InputEditor(38, 566, 300, 18, 10, false, m_blackBrush, m_textFormat);
	m_uiVector[LobbyView_CHATLIST] = new ChattingBox(16, 100, 350, 448, false, m_blackBrush, m_textFormat, 7);
	m_uiVector[LobbyView_USERLIST] = new UserPageList(9, m_blackBrush, m_blueBrush, m_redBrush, m_boldTextAliginNormalForamt);
	m_uiVector[LobbyView_ROOMLIST] = new RoomPageList(10, m_blackBrush, m_blueBrush, m_redBrush, m_boldTextAliginNormalForamt);
	m_uiVector[LobbyView_CROOMBTN] = new Button(408, 464, 123, 34, false);
}

void LobbyView::Update(int _deltaTick)
{
	m_sumTick += _deltaTick;

	Button* croomBtn = static_cast<Button*> (m_uiVector[LobbyView_CROOMBTN]);
	if (croomBtn->GetClicked())
	{
		m_croomChange = true;
	}

	if (m_sumTick < passTick)
		return;

	Network::GetInstance()->SendPacket(nullptr, PROCESS_ASYNC_LOBBY_REQUEST, 0, 0);

	m_sumTick = 0;
}

void LobbyView::Render()
{
	m_crt->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(LOBBY_BACKGROUND_BITMAP)->GetBitmap());
	m_crt->DrawTextW(m_username, wcslen(m_username), m_textFormat, D2D1::RectF(645.0f, 501.0f, 745.0f, 529.0f), m_blackBrush);

	for (int zindex = 0; zindex < LobbyView_UICOUNT; zindex++)
		if (m_uiVector[zindex])
			m_uiVector[zindex]->Render();
}

void LobbyView::Clean()
{
	ResourceManager::GetInstance()->DeleteBitmap(LOBBY_BACKGROUND_BITMAP);

	for (int zindex = 0; zindex < LobbyView_UICOUNT; zindex++)
		if (m_uiVector[zindex])
			delete m_uiVector[zindex];
}

void LobbyView::MouseMoveEvent(int _x, int _y)
{

}

void LobbyView::MouseClickEvent(int _x, int _y)
{
	for (int zindex = 0; zindex < LobbyView_UICOUNT; zindex++)
	{
		auto uiItem = m_uiVector[zindex];
		if (uiItem)
			uiItem->ISFocus(_x, _y);
	}

	WRoomEnter(_x, _y);
}

void LobbyView::MouseClickUpEnvet(int _x, int _y)
{
}

void LobbyView::CharEvent(WPARAM _key)
{
	for (int zindex = 0; zindex < LobbyView_UICOUNT; zindex++)
	{
		auto uiItem = m_uiVector[zindex];
		if (uiItem && uiItem->FocuseCheck())
		{
			if (zindex == LobbyView_CHATINPUT && _key == 13 /* ENTER */)
			{
				WCHAR* text = static_cast<InputEditor*>(m_uiVector[zindex])->GetText();
				Network::GetInstance()->SendPacket((char*)text, PROCESS_LOBBY_CHAT_REQUEST, wcslen(text) * sizeof(WCHAR), 1);
				static_cast<InputEditor*>(m_uiVector[zindex])->TextInit();
			}
			else
			{
				uiItem->Update(_key);
			}
		}
	}
}

ViewType LobbyView::ChangeView()
{
	if (m_croomChange)
	{
		m_croomChange = false;
		m_wroomChange = false;
		m_sumTick = passTick;
		return CROOM_VIEW;
	}
	else if (m_wroomChange)
	{
		m_croomChange = false;
		m_wroomChange = false;
		m_sumTick = passTick;
		return WROOM_VIEW;
	}
	else
	{
		m_croomChange = false;
		m_wroomChange = false;
		return VIEW_NONE;
	}

}

void LobbyView::WRoomEnter(int _x, int _y)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		D2D1_RECT_F rect = roomListRect[i];
		if (_x >= rect.left && _x <= rect.left + rect.right && _y >= rect.top && _y <= rect.top + rect.bottom)
		{
			if (reinterpret_cast<RoomPageList*>(m_uiVector[LobbyView_ROOMLIST])->EnterRoomEvent(i)) 
			{
				m_wroomChange = true;
			}
			break;
		}
	}
}

void LobbyView::LobbyUserListDataAsync(const std::vector<class User>& _data)
{
	static_cast<UserPageList*>(m_uiVector[LobbyView_USERLIST])->AsyncData(_data);
}

void LobbyView::LobbyRoomListDataAsync(const std::vector<class Room>& _data)
{
	static_cast<RoomPageList*>(m_uiVector[LobbyView_ROOMLIST])->AsyncData(_data);
}

void LobbyView::LobbyChatMsgRecv(WCHAR* _text, int _size)
{
	static_cast<ChattingBox*>(m_uiVector[LobbyView_CHATLIST])->Add((char*)_text, _size);
}

void LobbyView::LobbyUsernameAsync(WCHAR* _text, int _size)
{
	memcpy(m_username, _text, _size);
}
