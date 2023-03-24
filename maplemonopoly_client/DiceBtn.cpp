#include "pch.h"
#include "DiceBtn.h"
#include "ResourceManager.h"
#include "Bitmap.h"
#include "Sprite.h"
DiceBtn::DiceBtn(int _x, int _y, int _width, int _height, bool _focused) : UIComponent(_x, _y, _width, _height, _focused)
{
}

DiceBtn::DiceBtn()
{
}

DiceBtn::~DiceBtn()
{
}

void DiceBtn::Init()
{
}

void DiceBtn::Update(WPARAM _key)
{
}

void DiceBtn::Render()
{
    if (m_visable == false)
        return;

    Setting();
    m_sprite->Render( D2D1_RECT_F{ m_x+0.0f,m_y+0.0f,m_x+m_width + 0.0f,m_y+m_height + 0.0f}, m_bitmap);
}

bool DiceBtn::ISFocus(int _x, int _y)
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

void DiceBtn::Setting()
{
    m_bitmap = ResourceManager::GetInstance()->GetBitmap(GAME_DICE_BTN_BITMAP);

    if (m_onClicked) 
    {
        m_sprite = ResourceManager::GetInstance()->GetSprite(GAME_DICE_BTN_PRESS_SPRITE);
    }
    else
    {
        m_sprite = ResourceManager::GetInstance()->GetSprite(GAME_DICE_BTN_PRESS_UP_SPRITE);
    }
}
