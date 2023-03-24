#include "pch.h"
#include "AlertModal.h"
#include "Button.h"
#include "ResourceManager.h"
#include "Bitmap.h"

#define TEXT_START_POS_X 24 
#define TEXT_START_POS_Y 71 

AlertModal::AlertModal(int _x, int _y, int _width, int _height, bool _focused, const WCHAR* _text, ID2D1SolidColorBrush* _colorBrush, IDWriteTextFormat* _textformat) : UIComponent(_x, _y, _width, _height, _focused), m_colorBrush(_colorBrush), m_textformat(_textformat)
{
	wcscpy_s(m_text, _text);
	Init();
}

AlertModal::~AlertModal()
{
	delete m_button;
}

void AlertModal::Init()
{
	m_button = new Button(m_x + 103, m_y + 206, 94, 28, false);
}

void AlertModal::Update(WPARAM _key)
{
}

void AlertModal::Render()
{
	if (m_display == false)
		return;

	D2D1Core::GetInstance()->GetCRT()->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(LOGIN_ALERTMODAL_BITMAP)->GetBitmap(), D2D1_RECT_F{ (FLOAT)m_x,(FLOAT)m_y,(FLOAT)m_x + m_width,(FLOAT)m_y + m_height });
	D2D1Core::GetInstance()->GetCRT()->DrawTextW(m_text, wcslen(m_text), m_textformat, D2D1::RectF(m_x + TEXT_START_POS_X, m_y + TEXT_START_POS_Y, m_x + 200, m_y + 100), m_colorBrush);
}

bool AlertModal::ISFocus(int _x, int _y)
{
	if (m_display == false)
		return false;

	if (m_button->ISFocus(_x, _y))
	{
		Hide();
		return true;
	}
}

void AlertModal::Check(int _x, int _y)
{
	if (m_display == false)
		return;

	if (m_button->ISFocus(_x, _y))
		Hide();
}
