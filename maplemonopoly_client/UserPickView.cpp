#include "pch.h"
#include "UserPickView.h"
#include "Animation.h"
#include "Sprite.h"
#include "Bitmap.h"
#include "ResourceManager.h"
UserPickView::UserPickView(int _x, int _y, int _width, int _height, bool _focused, Pick _pick) : UIComponent(_x, _y, _width, _height, _focused), m_pick(_pick)
{
	Init();
}

UserPickView::~UserPickView()
{
	DeleteCriticalSection(&m_pickViewLock);
}

void UserPickView::Init()
{
	InitializeCriticalSection(&m_pickViewLock);

	switch (m_pick)
	{
	case HORN_MURSHROOM:
		m_bitmap = ResourceManager::GetInstance()->GetBitmap(ResourceName::HORN_MURSHROOM_BITMAP);
		m_ani = ResourceManager::GetInstance()->GetAnimation(ResourceName::HORN_MURSHROOM_IDLE_ANIMATION);
		break;
	case ORANGE_MURSHROOM:
		m_bitmap = ResourceManager::GetInstance()->GetBitmap(ResourceName::ORANGE_MURSHROOM_BITMAP);
		m_ani = ResourceManager::GetInstance()->GetAnimation(ResourceName::ORANGE_MURSHROOM_IDLE_ANIMATION);
		break;
	case PIG:
		m_bitmap = ResourceManager::GetInstance()->GetBitmap(ResourceName::PIG_BITMAP);
		m_ani = ResourceManager::GetInstance()->GetAnimation(ResourceName::PIG_IDLE_ANIMATION);
		break;
	}
}

void UserPickView::Update(WPARAM _key)
{
	EnterCriticalSection(&m_pickViewLock);
	if (m_pick == NOUSER)
	{
		LeaveCriticalSection(&m_pickViewLock);
		return;
	}
	
	Init();

	m_clip = (m_clip + 1) % m_ani->GetFrameCount();
	LeaveCriticalSection(&m_pickViewLock);
}

void UserPickView::Render()
{
	EnterCriticalSection(&m_pickViewLock);
	if (m_pick == NOUSER)
	{
		LeaveCriticalSection(&m_pickViewLock);
		return;
	}
	
	Init();

	m_ani->GetFrame(m_clip)->Render(D2D1::RectF(m_x, m_y, m_x + m_width, m_y + m_height), m_bitmap);
	LeaveCriticalSection(&m_pickViewLock);
}

void UserPickView::ORender()
{
	EnterCriticalSection(&m_pickViewLock);
	if (m_pick == NOUSER)
	{
		LeaveCriticalSection(&m_pickViewLock);
		return;
	}

	Init();

	m_ani->GetFrame(m_clip)->Render(D2D1::RectF(m_x, m_y, m_x + m_width, m_y + m_height), m_bitmap, 0.2f);
	LeaveCriticalSection(&m_pickViewLock);
}

bool UserPickView::ISFocus(int _x, int _y)
{
	return false;
}

void UserPickView::Refresh(Pick _pick)
{
	EnterCriticalSection(&m_pickViewLock);
	if (m_pick != _pick)
		m_clip = 0;

	m_pick = _pick;
	LeaveCriticalSection(&m_pickViewLock);
}
