#include "pch.h"
#include "UserPageList.h"
#include "User.h"
UserPageList::UserPageList(int _pageCount, ID2D1SolidColorBrush* _black, ID2D1SolidColorBrush* _blue, ID2D1SolidColorBrush* _red, IDWriteTextFormat* _textformat) : PagingList(_pageCount), m_blackBrush(_black), m_blueBrush(_blue), m_redBrush(_red), m_textFormat(_textformat)
{
	Init();
}

UserPageList::~UserPageList()
{
	DeleteCriticalSection(&m_userListLock);
}

void UserPageList::Init()
{
	InitializeCriticalSection(&m_userListLock);
}

void UserPageList::Update(WPARAM _key)
{
}

void UserPageList::Render()
{
	EnterCriticalSection(&m_userListLock);
	float heightPlus = 0;
	const float top = 153.0f;
	const float bottom = 173.0f;

	int size = m_data.size() < (m_nowPage * m_pageCount) + m_pageCount ?
		m_data.size()
		: (m_nowPage * m_pageCount) + m_pageCount;
	for (int i = m_nowPage * m_pageCount; i < size; i++)
	{
		auto& userData = m_data[i];

		D2D1Core::GetInstance()->GetCRT()->DrawTextW(userData.GetUsername(), wcslen(userData.GetUsername()), m_textFormat, D2D1::RectF(573.0f, top + heightPlus, 668.0f, bottom + heightPlus), m_blackBrush);
		D2D1Core::GetInstance()->GetCRT()->DrawTextW(L"테", 2, m_textFormat, D2D1::RectF(674.0f, top + heightPlus, 699.0f, bottom + heightPlus), m_blackBrush);

		switch (userData.GetLocation())
		{
		case LOBBY_ROOM:
			D2D1Core::GetInstance()->GetCRT()->DrawTextW(L"로비", 3, m_textFormat, D2D1::RectF(707.0f, top + heightPlus, 748.0f, bottom + heightPlus), m_blackBrush);
			break;
		case WATING_ROOM:
			D2D1Core::GetInstance()->GetCRT()->DrawTextW(L"대기", 4, m_textFormat, D2D1::RectF(707.0f, top + heightPlus, 748.0f, bottom + heightPlus), m_blueBrush);
			break;
		case GAME_ROOM:
			D2D1Core::GetInstance()->GetCRT()->DrawTextW(L"게임", 4, m_textFormat, D2D1::RectF(707.0f, top + heightPlus, 748.0f, bottom + heightPlus), m_redBrush);
			break;
		}

		heightPlus += 27.2f;
	}
	LeaveCriticalSection(&m_userListLock);
}

bool UserPageList::ISFocus(int _x, int _y)
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

void UserPageList::AsyncData(const std::vector<User>& _data)
{
	EnterCriticalSection(&m_userListLock);
	m_data.clear();
	for (auto& item : _data)
		m_data.push_back(item);
	LeaveCriticalSection(&m_userListLock);
}
