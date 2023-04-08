#pragma once
#include "UIComponent.h"
class Button : public UIComponent
{
private:
	bool m_clicked = false;
	ButtonCommand m_command = EVENTNONE;
public:
	Button(int _x, int _y, int _width, int _height, bool _focused);
	Button(int _x, int _y, int _width, int _height, bool _focused, ButtonCommand command);
	virtual ~Button();

	virtual void Init()						override;
	virtual void Update(WPARAM _key)		override;
	virtual void Render()					override;
	virtual bool ISFocus(int _x, int _y)	override;

public:
	bool GetClicked();
	ButtonCommand GetClickedCommand();
};
