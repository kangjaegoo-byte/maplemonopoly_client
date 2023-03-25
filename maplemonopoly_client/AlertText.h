#pragma once
#include "UIComponent.h"
class AlertText : public UIComponent
{
private:
	AlertTextState m_textState = AlertTextState_NONE;
	IDWriteTextFormat*      m_textformat;
	ID2D1SolidColorBrush*   m_colorBrush;
	int m_money = 0;
public:
	AlertText(int _x, int _y, int _width, int _height, bool _focused);
	virtual ~AlertText();

	virtual void Init()						override;
	virtual void Update(WPARAM _key)		override;
	virtual void Render()					override;
	virtual bool ISFocus(int _x, int _y)	override;
	void Check(int _x, int _y);
	void SetState(AlertTextState _state);
	void SetMoney(int _money);
};