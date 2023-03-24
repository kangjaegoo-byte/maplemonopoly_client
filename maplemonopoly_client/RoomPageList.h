#pragma once
#include "PagingList.h"
class Room;
class RoomPageList : public PagingList
{
private:
	std::vector<Room>  m_data;
	ID2D1SolidColorBrush* m_blackBrush;
	ID2D1SolidColorBrush* m_blueBrush;
	ID2D1SolidColorBrush* m_redBrush;
	IDWriteTextFormat* m_textFormat;
	CRITICAL_SECTION	  m_roomListLock;

public:
	RoomPageList(int _pageCount, ID2D1SolidColorBrush* _black, ID2D1SolidColorBrush* _blue, ID2D1SolidColorBrush* _red, IDWriteTextFormat* _textformat);
	virtual ~RoomPageList();

	virtual void Init()					 override;
	virtual void Update(WPARAM _key)	 override;
	virtual void Render()				 override;
	virtual bool ISFocus(int _x, int _y) override;
	void		 AsyncData(const std::vector<Room>& _data);
	bool		 EnterRoomEvent(int _index);
};

