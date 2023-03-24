#include "pch.h"
#include "StaticText.h"

StaticText::StaticText(int _x, int _y, int _width, int _height, bool _focused, ID2D1SolidColorBrush* _colorBrush, IDWriteTextFormat* _textformat) : UIComponent(_x, _y, _width, _height, _focused), m_colorBrush(_colorBrush), m_textformat(_textformat)
{
	Init();
}

StaticText::~StaticText()
{
}

void StaticText::Init()
{
}

void StaticText::Update(WPARAM _key)
{
}

void StaticText::Render()
{
	D2D1Core::GetInstance()->GetCRT()->DrawTextW(m_text, m_textSize / 2, m_textformat, D2D1::RectF(m_x, m_y, m_x + m_width, m_y + m_height), m_colorBrush);
}

bool StaticText::ISFocus(int _x, int _y)
{
	return false;
}

void StaticText::SetText(WCHAR* _text)
{
	if (_text == nullptr)
		memset(m_text, '\0', 100);
	else
		wcscpy_s(m_text, _text);
}

void StaticText::SetText(WCHAR* _text, int _dataSize)
{
	if (_text == nullptr)
		memset(m_text, '\0', 100);
	else
	{
		::memcpy(m_text, _text, _dataSize);
		m_textSize = _dataSize;
	}
}

void StaticText::SetText(int _data)
{
	WCHAR text[256] = L"";
	swprintf_s(text, _countof(text), L"%d¾ï", _data);
	SetText(text, wcslen(text) * sizeof(WCHAR));
}
