#pragma once
#include "UIComponent.h"
class StaticText : public UIComponent
{
private:
	WCHAR					m_text[100] = L"";
	IDWriteTextFormat* m_textformat;
	IDWriteTextFormat* m_textBigformat;
	ID2D1SolidColorBrush* m_colorBrush;
	int						m_textSize = 0;
public:
	StaticText(int _x, int _y, int _width, int _height, bool _focused, ID2D1SolidColorBrush* _colorBrush, IDWriteTextFormat* _textformat);
	virtual ~StaticText();

	virtual void Init()						override;
	virtual void Update(WPARAM _key)		override;
	virtual void Render()					override;
	virtual bool ISFocus(int _x, int _y)	override;

	void RankRender();

	void         SetText(WCHAR* _text);
	void         SetText(WCHAR* _text, int _dataSize);
	void         SetText(int _data);
	void         SetRank(int _rank);
};

