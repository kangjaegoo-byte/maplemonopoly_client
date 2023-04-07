#include "pch.h"
#include "RoomPageList.h"
#include "Room.h"
#include "SceneManager.h"
#include "MaplemonopolyApp.h"
#include "User.h"
RoomPageList::RoomPageList(int _pageCount, ID2D1SolidColorBrush* _black, ID2D1SolidColorBrush* _blue, ID2D1SolidColorBrush* _red, IDWriteTextFormat* _textformat) : PagingList(_pageCount), m_blackBrush(_black), m_blueBrush(_blue), m_redBrush(_red), m_textFormat(_textformat)
{
	Init();
}

RoomPageList::~RoomPageList()
{
	DeleteCriticalSection(&m_roomListLock);
}

void RoomPageList::Init()
{
	InitializeCriticalSection(&m_roomListLock);
}

void RoomPageList::Update(WPARAM _key)
{
}

void RoomPageList::Render()
{
	EnterCriticalSection(&m_roomListLock);
	float heightPlus = 0;
	const float top = 131.0f;
	const float bottom = 149.0f;

	int size = m_data.size() < (m_nowPage * m_pageCount) + m_pageCount ?
		m_data.size()
		: (m_nowPage * m_pageCount) + m_pageCount;
	for (int i = m_nowPage * m_pageCount; i < size; i++)
	{

		auto& roomData = m_data[i];

		// 번호	
		WCHAR text[1000];
		swprintf_s(text, _countof(text), L"%d", i + 1);
		D2D1Core::GetInstance()->GetCRT()->DrawTextW(text, wcslen(text), m_textFormat, D2D1::RectF(21.0f, top + heightPlus, 45.0f, bottom + heightPlus), m_blackBrush);

		// 레벨
		D2D1Core::GetInstance()->GetCRT()->DrawTextW(L"0", 2, m_textFormat, D2D1::RectF(52.0f, top + heightPlus, 84.0f, bottom + heightPlus), m_blackBrush);

		// 상태
		switch (roomData.GetStatus())
		{
		case Roomstatus::HOLD:
			D2D1Core::GetInstance()->GetCRT()->DrawTextW(L"대기", 3, m_textFormat, D2D1::RectF(91.0f, top + heightPlus, 122.0f, bottom + heightPlus), m_blackBrush);
			break;

		case Roomstatus::GAME:
			D2D1Core::GetInstance()->GetCRT()->DrawTextW(L"게임", 3, m_textFormat, D2D1::RectF(91.0f, top + heightPlus, 122.0f, bottom + heightPlus), m_redBrush);
			break;
		}

		// 제목
		D2D1Core::GetInstance()->GetCRT()->DrawTextW(roomData.GetTitle(), wcslen(roomData.GetTitle()), m_textFormat, D2D1::RectF(127.0f, top + heightPlus, 329.0f, bottom + heightPlus), m_blackBrush);

		// 방장
		D2D1Core::GetInstance()->GetCRT()->DrawTextW(roomData.GetRegBy(), wcslen(roomData.GetRegBy()), m_textFormat, D2D1::RectF(334.0f, top + heightPlus, 407.0f, bottom + heightPlus), m_blackBrush);

		// 인원
		WCHAR text2[1000];
		swprintf_s(text, _countof(text), L"%d", roomData.GetjoinCount());
		D2D1Core::GetInstance()->GetCRT()->DrawTextW(text, wcslen(text), m_textFormat, D2D1::RectF(413.0f, top + heightPlus, 471.0f, bottom + heightPlus), roomData.GetjoinCount() >= 4 ? m_redBrush : m_blackBrush);


		heightPlus += 27.2f;
	}
	LeaveCriticalSection(&m_roomListLock);
}

bool RoomPageList::ISFocus(int _x, int _y)
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

void RoomPageList::AsyncData(const std::vector<Room>& _data)
{
	EnterCriticalSection(&m_roomListLock);
	m_data.clear();
	for (auto& item : _data)
		m_data.push_back(item);
	LeaveCriticalSection(&m_roomListLock);
}
bool RoomPageList::EnterRoomEvent(int _index)
{
	EnterCriticalSection(&m_roomListLock);
	if (_index >= m_data.size())
	{
		LeaveCriticalSection(&m_roomListLock);
		return false;
	}
	LeaveCriticalSection(&m_roomListLock);
	Room enterRoom = m_data[_index];

	if (enterRoom.GetjoinCount() >= 4)
		return false;


	char buffer[256];
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	*(int*)(header + 1) = enterRoom.GetSq();
	header->size = 4 + 4;
	header->id = PKT_S_ENTERROOM;

	Network::GetInstance()->Send(buffer, header->size);
	LeaveCriticalSection(&m_roomListLock);
	return true;
}
