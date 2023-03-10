#include "pch.h"
#include "PagingList.h"

PagingList::PagingList(int _pageCount) : m_pageCount(_pageCount), m_nowPage(0)
{
}

PagingList::~PagingList()
{
}
