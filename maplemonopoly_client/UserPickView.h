#pragma once
#include "UIComponent.h"
class Animation;
class Bitmap;
/**************************************************
	UserPickView : 대기실 유저 픽 미리보기
**************************************************/
class UserPickView : public UIComponent
{
private:
	Animation*			m_ani;
	Bitmap*				m_bitmap;
	CPick				m_pick = CPick::NOUSER;
	CRITICAL_SECTION	m_pickViewLock;
	int					m_clip = 0;

public:
	UserPickView(int _x, int _y, int _width, int _height, bool _focused, CPick _pick);
	virtual ~UserPickView();

	virtual void Init()						override;
	virtual void Update(WPARAM _key)		override;
	virtual void Render()					override;
	virtual bool ISFocus(int _x, int _y)	override;
	void	     Refresh(CPick _pick);
};

