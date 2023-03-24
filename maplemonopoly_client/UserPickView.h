#pragma once
#include "UIComponent.h"
class Animation;
class Bitmap;
class UserPickView : public UIComponent
{
private:
	Animation* m_ani;
	Bitmap* m_bitmap;
	Pick				m_pick = Pick::NOUSER;
	CRITICAL_SECTION	m_pickViewLock;
	int					m_clip = 0;

public:
	UserPickView(int _x, int _y, int _width, int _height, bool _focused, Pick _pick);
	virtual ~UserPickView();

	virtual void Init()						override;
	virtual void Update(WPARAM _key)		override;
	virtual void Render()					override;
	void ORender();
	virtual bool ISFocus(int _x, int _y)	override;
	void	     Refresh(Pick _pick);
};

