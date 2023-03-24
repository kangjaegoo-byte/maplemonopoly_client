#pragma once
#include "UIComponent.h"
class ChattingBox : public UIComponent
{
private:
	ID2D1SolidColorBrush* m_blackBrush;
	IDWriteTextFormat* m_textFormat;
	std::list<WCHAR*>		m_chatList;
	int						m_chatLimt;
	CRITICAL_SECTION		m_chatLock;

public:
	ChattingBox(int _x, int _y, int _width, int _height, bool _focused, ID2D1SolidColorBrush* _colorBrush, IDWriteTextFormat* _textFormat, int _chatLimt);
	virtual ~ChattingBox();

	void         Add(char* _buffer, int _dataSize);
	virtual void Init()					 override;
	virtual void Update(WPARAM _key)	 override;
	virtual void Render()				 override;
	virtual bool ISFocus(int _x, int _y) override;
	void		 ClearChat();
};

