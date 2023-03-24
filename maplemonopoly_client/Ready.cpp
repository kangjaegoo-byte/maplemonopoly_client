#include "pch.h"
#include "Ready.h"
#include "D2D1Core.h"
Ready::Ready(int _x, int _y, int _width, int _height, bool _focused) : UIComponent(_x, _y, _width, _height, _focused)
{
}

Ready::~Ready()
{
}

void Ready::Init()
{
}

void Ready::Update(WPARAM _key)
{
}

void Ready::Render()
{
	if (m_ready == false)
		return;

	Setting();

	D2D1_RECT_F f = { m_x + 0.0f, m_y + 0.0f, m_width + m_x + 0.0f, m_height + m_y + 0.0f };
	D2D1Core::GetInstance()->GetCRT()->DrawBitmap(m_readyBitmap->GetBitmap(), f);
}

bool Ready::ISFocus(int _x, int _y)
{
	return false;
}

void Ready::Setting()
{
	if (m_readyBitmap == nullptr)
		m_readyBitmap = ResourceManager::GetInstance()->GetBitmap(READY_BITMAP);
}
