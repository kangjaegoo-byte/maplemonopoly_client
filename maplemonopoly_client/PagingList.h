#pragma once
#include "UIComponent.h"
class PagingList : public UIComponent
{
protected:
	int m_pageCount;		// ������ ����
	int	m_nowPage = 0;		// ���� ������

public:
	PagingList(int _pageCount);
	virtual ~PagingList();

	virtual void Init()					 abstract;
	virtual void Update(WPARAM _key)	 abstract;
	virtual void Render()				 abstract;
	virtual bool ISFocus(int _x, int _y) abstract;
};

