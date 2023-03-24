#include "pch.h"
#include "InputEditor.h"

InputEditor::InputEditor(int _x, int _y, int _width, int _height, int _maxSize, bool _focused, ID2D1SolidColorBrush* _colorBrush, IDWriteTextFormat* _textformat) : UIComponent(_x, _y, _width, _height, _focused), m_maxSize(_maxSize), m_colorBrush(_colorBrush), m_textformat(_textformat)
{
	Init();
}

InputEditor::~InputEditor()
{
}

void InputEditor::Init()
{

}

void InputEditor::Update(WPARAM _key)
{
	if (!m_focused) return;
	const TCHAR BACKSPACE = 8;
	const TCHAR ENTER = 13;
	TCHAR k = (TCHAR)_key;
	if (m_index != 0 && k == BACKSPACE)
	{
		m_index--;
		m_text[m_index] = '\0';
		m_viewText[m_index] = '\0';
	}
	else
	{
		if (m_index >= m_maxSize) return;
		if (_key == BACKSPACE) return;
		if (_key == ENTER) return;
		m_text[m_index] = k;
		m_viewText[m_index] = k;
		m_index++;
	}
}

void InputEditor::Render()
{
	if (m_focused && m_cusorAnimation)
		m_viewText[m_index] = L'|';
	else
		m_viewText[m_index] = L'\0';

	D2D1Core::GetInstance()->GetCRT()->DrawTextW(m_viewText, wcslen(m_viewText), m_textformat, D2D1::RectF(m_x + 5, m_y + 2, m_x + m_width, m_y + m_height), m_colorBrush);

	m_viewText[m_index] = L'\0';

	m_cusorTick++;
	if (m_cusorTick >= 5)
	{
		m_cusorAnimation = !m_cusorAnimation;
		m_cusorTick = 0;
	}
}

bool InputEditor::ISFocus(int _x, int _y)
{
	int left = m_x;
	int top = m_y;
	int right = m_x + m_width;
	int bottom = m_y + m_height;

	// 클릭한 좌표가 컴포넌트안에 포함되는지 
	if (_x >= left && _x <= right && _y >= top && _y <= bottom)
	{
		m_focused = true;
		return true;
	}
	else
	{
		m_focused = false;
		return false;
	}
}

bool InputEditor::Validation()
{
	int size = wcslen(m_text);

	if (size == 0 || size >= 10)
		return false;

	return true;
}

void InputEditor::TextInit()
{
	int text_size = wcslen(m_text);
	int view_size = wcslen(m_viewText);

	memset(m_text, '\0', text_size * sizeof(WCHAR));
	memset(m_viewText, '\0', view_size * sizeof(WCHAR));

	m_index = 0;
}
