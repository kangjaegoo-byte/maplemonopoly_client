#include "pch.h"
#include "UserPickView.h"
#include "Animation.h"
#include "Sprite.h"
#include "Bitmap.h"
#include "ResourceManager.h"
UserPickView::UserPickView(int _x, int _y, int _width, int _height, bool _focused, CPick _pick) : UIComponent(_x, _y, _width, _height, _focused), m_pick(_pick)
{
	Init();
}

UserPickView::~UserPickView()
{
	delete m_ani;
}

void UserPickView::Init()
{
	switch (m_pick)
	{
	case HONY_MURSHROOM:
		m_bitmap = ResourceManager::GetInstance()->GetBitmap(Resourcename::HORNY_MURSHROOM_BITMAP);
		m_ani = ResourceManager::GetInstance()->GetAnimation(Resourcename::HORNY_MURSHROOM_ANIMATION);
		break;
	case ORANGE_MURSHROOM:
		m_bitmap = ResourceManager::GetInstance()->GetBitmap(Resourcename::ORANGE_MURSHROOM_BITMAP);
		m_ani = ResourceManager::GetInstance()->GetAnimation(Resourcename::ORANGE_MURSHROOM_IDLE_ANIMATION);
		break;
	case PIG:
		m_bitmap = ResourceManager::GetInstance()->GetBitmap(Resourcename::PIG_BITMAP);	
		m_ani = ResourceManager::GetInstance()->GetAnimation(Resourcename::PIG_IDLE_ANIMATION);
		break;
	}
}

void UserPickView::Update(WPARAM _key)
{
	if (m_visiable)
		m_ani->GetFrame();
}

void UserPickView::Render()
{
	if (m_visiable)
		m_ani->GetFrameP()->Render(D2D1::RectF(m_x, m_y, m_x + m_width, m_y+m_height), m_bitmap);
}

bool UserPickView::ISFocus(int _x, int _y)
{
	return false;
}
