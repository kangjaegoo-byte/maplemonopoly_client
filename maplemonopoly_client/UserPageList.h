#pragma once
#include "PagingList.h"
class UserDTO;
/**************************************************
	UserPageList : 사용자 접속 리스트 UI
**************************************************/
class UserPageList : public PagingList
{
private:
	std::vector<UserDTO>  m_data;
	ID2D1SolidColorBrush* m_blackBrush;
	ID2D1SolidColorBrush* m_blueBrush;
	ID2D1SolidColorBrush* m_redBrush;
	IDWriteTextFormat*	  m_textFormat;
	CRITICAL_SECTION	  m_userListLock;

public:
	UserPageList(int _pageCount, ID2D1SolidColorBrush* _black, ID2D1SolidColorBrush* _blue, ID2D1SolidColorBrush* _red, IDWriteTextFormat* _textformat);
	virtual ~UserPageList();

	virtual void Init()					 override;
	virtual void Update(WPARAM _key)	 override;
	virtual void Render()				 override;
	virtual bool ISFocus(int _x, int _y) override;
	void		 AsyncData(const std::vector<UserDTO>& _data);
};

