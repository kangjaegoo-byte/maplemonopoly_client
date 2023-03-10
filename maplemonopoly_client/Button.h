#pragma once
#include "UIComponent.h"
/**************************************************
	Button : 이벤트 확인용 버튼
**************************************************/
class Button : public UIComponent
{
private:
	bool m_clicked = false;

public:
	Button(int _x, int _y, int _width, int _height, bool _focused);
	virtual ~Button();

	virtual void Init()						override;
	virtual void Update(WPARAM _key)		override;
	virtual void Render()					override;
	virtual bool ISFocus(int _x, int _y)	override;

public:
	bool GetClicked();
};
