#include "pch.h"
#include "CRoomView.h"
#include "Bitmap.h"
#include "ResourceManager.h"
#include "Button.h"
#include "InputEditor.h"
#include "SceneManager.h"
CRoomView::CRoomView(ID2D1HwndRenderTarget* _rt, ID2D1BitmapRenderTarget* _crt, IDWriteTextFormat* _textFormat, ID2D1SolidColorBrush* _brush) : m_rt(_rt), m_crt(_crt), m_textFormat(_textFormat), m_blackBrush(_brush)
{
	Init();
}

CRoomView::~CRoomView()
{
	Clean();
	for (int zindex = 0; zindex < CROOM_UICOUNT; zindex++)
		if (m_uiVector[zindex])
			delete m_uiVector[zindex];
}

void CRoomView::Init()
{
	m_uiVector.resize(CROOM_UICOUNT, nullptr);
	m_uiVector[CROOM_NOBTN] = new Button(467.0f, 355.0f, 85.0f, 30.0f, false); // 85 385
	m_uiVector[CROOM_OKBTN] = new Button(270 + 71.0f, 178 + 175.0f, 85.0f, 30.0f, false);
	m_uiVector[CROOM_TITLEINPUT] = new InputEditor(270 + 80.0f, 178 + 48.0f, 237.0f, 20.0f, 10, true, m_blackBrush, m_textFormat); // 592 ,246
}

void CRoomView::Update(int _deltaTick)
{

}

void CRoomView::Render()
{
	m_crt->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(LOBBY_CREATEROOMMODAL_BITMAP)->GetBitmap(), D2D1_RECT_F{ 270,178,352 + 270,232 + 178 });

	for (int zindex = 0; zindex < CROOM_UICOUNT; zindex++)
		if (m_uiVector[zindex])
			m_uiVector[zindex]->Render();
}

void CRoomView::Clean()
{

}

void CRoomView::MouseMoveEvent(int _x, int _y)
{

}

void CRoomView::MouseClickUpEnvet(int _x, int _y)
{
}

void CRoomView::MouseClickEvent(int _x, int _y)
{
	for (int zindex = 0; zindex < CROOM_UICOUNT; zindex++)
	{
		auto uiItem = m_uiVector[zindex];
		if (uiItem)
			uiItem->ISFocus(_x, _y);
	}
}

void CRoomView::CharEvent(WPARAM _key)
{
	for (int zindex = 0; zindex < CROOM_UICOUNT; zindex++)
	{
		auto uiItem = m_uiVector[zindex];
		if (uiItem && uiItem->FocuseCheck())
		{
			uiItem->Update(_key);
		}
	}
}

ViewType CRoomView::ChangeView()
{
	Button* noBtn = static_cast<Button*> (m_uiVector[CROOM_NOBTN]);
	Button* okBtn = static_cast<Button*> (m_uiVector[CROOM_OKBTN]);
	InputEditor* title = static_cast<InputEditor*> (m_uiVector[CROOM_TITLEINPUT]);

	if (noBtn->GetClicked())
	{
		title->TextInit();

		return ViewType::LOBBY_VIEW;
	}
	else if (okBtn->GetClicked())
	{
		char buffer[256] = {};
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		*(int*)(header + 1) = wcslen(title->GetText()) * sizeof(WCHAR);
		WCHAR* textPtr = (WCHAR*)((int*)(header + 1) + 1);
		memcpy(textPtr, title->GetText(), wcslen(title->GetText()) * sizeof(WCHAR));

		header->id = PKT_S_CREATEROOM;
		header->size = 4 + 4 + wcslen(title->GetText()) * sizeof(WCHAR);

		Network::GetInstance()->Send(buffer, header->size);
		title->TextInit();
		return ViewType::WROOM_VIEW;
	}
	else
	{
		return ViewType::VIEW_NONE;
	}
}
