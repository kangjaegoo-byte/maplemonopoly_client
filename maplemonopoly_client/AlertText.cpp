#include "pch.h"
#include "AlertText.h"
#include "D2D1Core.h"
AlertText::AlertText(int _x, int _y, int _width, int _height, bool _focused) :UIComponent(_x,_y,_width, _height, _focused)
{
	Init();
}

AlertText::~AlertText()
{
	m_textformat->Release();
	m_colorBrush->Release();
}

void AlertText::Init()
{
	D2D1Core::GetInstance()->SetFontFormat(&m_textformat, L"³ª´®°íµñ", 30.0f, DWRITE_FONT_WEIGHT_BOLD,DWRITE_TEXT_ALIGNMENT_CENTER);
	D2D1Core::GetInstance()->CreateColorBrush(&m_colorBrush,D2D1::ColorF::Red);
}

void AlertText::Update(WPARAM _key)
{
}

void AlertText::Render()
{

	switch (m_textState)
	{
	case AlertTextState_NONE:
		break;

	case AlertTextState_DOUBLE:
	{
		WCHAR text[256] = L"´õºí !";
		// D2D1Core::GetInstance()->GetCRT()->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(GAME_ALERT_TEXT_BITMAP)->GetBitmap(), D2D1_RECT_F{ (FLOAT)m_x,(FLOAT)m_y,(FLOAT)m_x + m_width,(FLOAT)m_y + m_height });
		D2D1Core::GetInstance()->GetCRT()->DrawTextW(text, wcslen(text), m_textformat, D2D1::RectF(m_x + 3, m_y + 3, m_x  + m_width, m_y + m_height ), m_colorBrush);
		break;
	}

	case AlertTextState_MONEY:
	{
		WCHAR text[1000];
		swprintf_s(text, _countof(text), L"%d ¾ï", m_money);
		// D2D1Core::GetInstance()->GetCRT()->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(GAME_ALERT_TEXT_BITMAP)->GetBitmap(), D2D1_RECT_F{ (FLOAT)m_x,(FLOAT)m_y,(FLOAT)m_x + m_width,(FLOAT)m_y + m_height });
		D2D1Core::GetInstance()->GetCRT()->DrawTextW(text, wcslen(text), m_textformat, D2D1::RectF(m_x + 3, m_y + 3, m_x + m_width, m_y + m_height), m_colorBrush);
		break;
	}
	}	
}

bool AlertText::ISFocus(int _x, int _y)
{
	return false;
}

void AlertText::Check(int _x, int _y)
{
}

void AlertText::SetState(AlertTextState _state)
{
	m_textState = _state;
}

void AlertText::SetMoney(int _money)
{
	if (_money == 0)
	{
		m_textState = AlertTextState_NONE;
	}
	else
	{
		m_textState = AlertTextState_MONEY;
	}

	m_money = _money;
}
