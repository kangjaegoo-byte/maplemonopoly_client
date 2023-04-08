#include "pch.h"
#include "Button.h"

Button::Button(int _x, int _y, int _width, int _height, bool _focused) : UIComponent(_x, _y, _width, _height, _focused)
{

}

Button::Button(int _x, int _y, int _width, int _height, bool _focused, ButtonCommand command) : UIComponent(_x, _y, _width, _height, _focused), m_command(command)
{
}

Button::~Button()
{
}

void Button::Init()
{
}

void Button::Update(WPARAM _key)
{
}

void Button::Render()
{
}

bool Button::ISFocus(int _x, int _y)
{
	int left = m_x;
	int top = m_y;
	int right = m_x + m_width;
	int bottom = m_y + m_height;

	// 클릭한 좌표가 컴포넌트안에 포함되는지 
	if (_x >= left && _x <= right && _y >= top && _y <= bottom)
	{
		m_clicked = true;
		m_focused = true;
		return true;
	}
	else
	{
		m_focused = false;
		return false;
	}
}

bool Button::GetClicked()
{
	if (m_clicked == true)
	{
		m_clicked = false;
		return true;
	}
	else
	{
		return false;
	}
}

ButtonCommand Button::GetClickedCommand()
{
	if (m_clicked == true)
	{
		m_clicked = false;
		return m_command;
	}
	else
	{
		return EVENTNONE;
	}
}
