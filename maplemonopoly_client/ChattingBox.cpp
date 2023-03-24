#include "pch.h"
#include "ChattingBox.h"

ChattingBox::ChattingBox(int _x, int _y, int _width, int _height, bool _focused, ID2D1SolidColorBrush* _colorBrush, IDWriteTextFormat* _textFormat, int _chatLimt) : UIComponent(_x, _y, _width, _height, _focused), m_blackBrush(_colorBrush), m_textFormat(_textFormat), m_chatLimt(_chatLimt)
{
	Init();
}

ChattingBox::~ChattingBox()
{
	for (auto& item : m_chatList)
		if (item)
			delete item;
	DeleteCriticalSection(&m_chatLock);
}

void ChattingBox::Add(char* _buffer, int _dataSize)
{
	WCHAR* temp = new WCHAR[30];
	memset(temp, '\0', 30 * sizeof(WCHAR));
	WCHAR* dataPtr = (WCHAR*)_buffer;

	memcpy(temp, dataPtr, _dataSize);
	memset(_buffer, '\0', _dataSize);
	EnterCriticalSection(&m_chatLock);

	if (m_chatList.size() >= m_chatLimt)
	{
		delete m_chatList.front();
		m_chatList.pop_front();
	}

	m_chatList.push_back(temp);

	LeaveCriticalSection(&m_chatLock);
}

void ChattingBox::Init()
{
	InitializeCriticalSection(&m_chatLock);
}

void ChattingBox::Update(WPARAM _key)
{
}

void ChattingBox::Render()
{
	EnterCriticalSection(&m_chatLock);
	float heightsub = -13.0f;
	int index = m_chatList.size() - 1;
	for (auto& item : m_chatList)
	{
		const float bottom = m_y + m_height + (heightsub * index--);
		const float top = bottom - 10.0f;

		D2D1Core::GetInstance()->GetCRT()->DrawTextW(item, wcslen(item), m_textFormat, D2D1::RectF(m_x + 20.0f, top, m_width, bottom), m_blackBrush);
	}
	LeaveCriticalSection(&m_chatLock);
}

bool ChattingBox::ISFocus(int _x, int _y)
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

void ChattingBox::ClearChat()
{
	EnterCriticalSection(&m_chatLock);
	m_chatList.clear();
	LeaveCriticalSection(&m_chatLock);
}
