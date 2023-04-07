#include "pch.h"
#include "GameEndView.h"
#include "AlertModal.h"
#include "GameEndModal.h"
GameEndView::GameEndView(ID2D1HwndRenderTarget* _rt, ID2D1BitmapRenderTarget* _crt, IDWriteTextFormat* _textFormat, ID2D1SolidColorBrush* _black, ID2D1SolidColorBrush* _color1, ID2D1SolidColorBrush* _color2) : m_rt(_rt), m_crt(_crt), m_textFormat(_textFormat), m_blackBrush(_black), m_colorBrush1(_color1), m_colorBrush2(_color2)
{
	Init();
}

GameEndView::~GameEndView()
{
	Clean();
	if (m_gameEndModal)
		delete m_gameEndModal;
}
void GameEndView::Init()
{

	m_gameEndModal = new GameEndModal(300, 180, 300, 250, false, L"°ÔÀÓ ½Â¸®!", m_colorBrush2, m_textFormat);
}

void GameEndView::Update(int _deltaTick)
{

}

void GameEndView::Render()
{
	m_gameEndModal->Render();
}

void GameEndView::Clean()
{

}

void GameEndView::MouseMoveEvent(int _x, int _y)
{

}

void GameEndView::MouseClickEvent(int _x, int _y)
{
	if (m_gameEndModal->ISFocus(_x, _y)) 
	{
		m_change = true;
	};
}

void GameEndView::MouseClickUpEnvet(int _x, int _y)
{
}

void GameEndView::CharEvent(WPARAM _key)
{
}

ViewType GameEndView::ChangeView()
{
	return ViewType::VIEW_NONE;
}

void GameEndView::Show()
{
	m_gameEndModal->Show();
}

void GameEndView::Hide()
{
	m_gameEndModal->Hide();
}

bool GameEndView::GameEnd()
{
	bool ret = m_change;
	m_change = false;
	return ret;
}
