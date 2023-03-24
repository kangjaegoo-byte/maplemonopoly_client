#include "pch.h"
#include "UIComponent.h"

UIComponent::UIComponent(int _x, int _y, int _width, int _height, bool _focused) : m_width(_width), m_height(_height), m_x(_x), m_y(_y), m_focused(_focused)
{
}

UIComponent::UIComponent()
{
}

UIComponent::~UIComponent()
{
}

bool UIComponent::FocuseCheck()
{
	return m_focused;
}
