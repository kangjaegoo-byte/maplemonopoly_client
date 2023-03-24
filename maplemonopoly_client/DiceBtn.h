#pragma once
#include "Button.h"
class DiceBtn : public UIComponent
{
private:
	bool m_onClicked = false;
	bool m_visable = true;
	class Bitmap* m_bitmap = nullptr;
	class Sprite* m_sprite = nullptr;
public:
	DiceBtn(int _x, int _y, int _width, int _height, bool _focused);
	DiceBtn();
	virtual ~DiceBtn();

	virtual void Init()					 override;
	virtual void Update(WPARAM _key)	 override;
	virtual void Render()				 override;
	virtual bool ISFocus(int _x, int _y) override;
	void Setting();
	void MouseUp() { m_onClicked = false;  }
	void MouseDown() { m_onClicked = true;  }
};

