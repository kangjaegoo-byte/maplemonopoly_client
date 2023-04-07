#include "pch.h"
#include "GameModalView.h"
#include "ResourceManager.h"
#include "Bitmap.h"
#include "StaticText.h"
#include "UserPickView.h"
#include "Sprite.h"
#include "Button.h"
#include "SceneManager.h"
GameModalView::GameModalView(ID2D1HwndRenderTarget* _rt, ID2D1BitmapRenderTarget* _crt, IDWriteTextFormat* _textFormat, ID2D1SolidColorBrush* _black, ID2D1SolidColorBrush* _color1, ID2D1SolidColorBrush* _color2) : m_rt(_rt), m_crt(_crt), m_textFormat(_textFormat), m_blackBrush(_black), m_colorBrush1(_color1), m_colorBrush2(_color2)
{
	Init();
}

GameModalView::~GameModalView()
{
	Clean();
	DeleteCriticalSection(&m_gameLock);
}

void GameModalView::Init()
{
	InitializeCriticalSection(&m_gameLock);
	m_uiVector.resize(UICOUNT);
	m_text = new StaticText(197 + 30, 381, 197 + 413 - 30, 200, false, m_blackBrush, m_textFormat);
	m_title = new StaticText(204, 97, 137, 15, false, m_blackBrush, m_textFormat);

	m_uiVector[OKBUTTON] = new Button(299.0f, 477.0f, 85.0f, 30.0f, false); // 85 385
	m_uiVector[NOBUTTON] = new Button(413.0f, 477.0f, 85.0f, 30.0f, false);
}

void GameModalView::Update(int _deltaTick)
{
	EnterCriticalSection(&m_gameLock);

	Button* okBtn = static_cast<Button*>(m_uiVector[OKBUTTON]);
	Button* noBtn = static_cast<Button*>(m_uiVector[NOBUTTON]);

	if (okBtn->GetClicked())
	{
		char buffer[256];
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		header->id = m_type;
		header->size = 8;
		*(int*)(header + 1) = m_playerIndex;
		Network::GetInstance()->Send(buffer, header->size);
		Clear();
	}
	else if (noBtn->GetClicked())
	{
		char buffer[256];
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		header->size = 4;
		header->id = PKT_S_PASSTURN;
		Network::GetInstance()->Send(buffer, header->size);
		Clear();
	}

	LeaveCriticalSection(&m_gameLock);
}

void GameModalView::Render()
{
	EnterCriticalSection(&m_gameLock);
	m_crt->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(GAME_MODAL_VIEW_BITMAP)->GetBitmap(), D2D1_RECT_F{ 197,90,197 + 413,90 + 478 });

	m_text->Render();
	m_title->Render();
	m_sprite->Render({ 300,144,300 + 200,144 + 200 }, ResourceManager::GetInstance()->GetBitmap(GAME_MONO_BITMAP));
	LeaveCriticalSection(&m_gameLock);
}

void GameModalView::Clean()
{

}

ViewType GameModalView::ChangeView()
{
	if (m_changed)
	{
		m_changed = false;
		return ViewType::LOBBY_VIEW;
	}
	else
	{
		return ViewType::VIEW_NONE;
	}
}

void GameModalView::MouseMoveEvent(int _x, int _y)
{
}

void GameModalView::MouseClickEvent(int _x, int _y)
{
	for (auto& item : m_uiVector)
	{
		if (item)
			item->ISFocus(_x, _y);
	}
}

void GameModalView::MouseClickUpEnvet(int _x, int _y)
{
}

void GameModalView::CharEvent(WPARAM _key)
{
}


void GameModalView::GameBuyRegionModalOtherProcessResponseEx(Region* dataPtr, int _playerIndex)
{
	EnterCriticalSection(&m_gameLock);
	m_sprite = dataPtr->_level == 0 ? ResourceManager::GetInstance()->GetPlayerHouse(dataPtr->_ownerPlayerIndx) : ResourceManager::GetInstance()->GetPlayerHotel(dataPtr->_ownerPlayerIndx);
	WCHAR house[30] = L"모텔";
	WCHAR hotel[30] = L"호텔";
	dataPtr->_level == 1 ? m_title->SetText(house, 4) : m_title->SetText(hotel, 4);
	WCHAR buf[256] = L"";
	swprintf_s(buf, L"해당지역을 구매 하시겠습니까?\n 구매비용은 %d억 입니다", dataPtr->_passCost);
	m_text->SetText(buf, wcslen(buf) * 2);
	m_type = PKT_S_BUYOTHERREGION;
	LeaveCriticalSection(&m_gameLock);
}

void GameModalView::GameBuyRegion(Region* dataPtr)
{
	EnterCriticalSection(&m_gameLock);
	m_sprite = dataPtr->_level == 0 ? ResourceManager::GetInstance()->GetPlayerHouse(m_playerIndex) : ResourceManager::GetInstance()->GetPlayerHotel(m_playerIndex);
	WCHAR house[30] = L"모텔";
	WCHAR hotel[30] = L"호텔";
	dataPtr->_level == 0 ? m_title->SetText(house, 4) : m_title->SetText(hotel, 4);
	WCHAR buf[256] = L"";
	swprintf_s(buf, L"해당지역을 구매/업그레이드 하시겠습니까?\n 구매비용은 %d억 입니다", dataPtr->_passCost);
	m_text->SetText(buf, wcslen(buf) * 2);
	m_type = PKT_S_BUYREGION;
	LeaveCriticalSection(&m_gameLock);
}

void GameModalView::Clear()
{
	m_text->SetText(nullptr);
	m_sprite = nullptr;
	m_title->SetText(nullptr);
	m_changed = true;
}

void GameModalView::GameUserNumber(int _dataPtr)
{
	m_playerIndex = _dataPtr;
}