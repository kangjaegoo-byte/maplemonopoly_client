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
	Animation* m_ani;
	Bitmap*	   m_bitmap;
	CPick	   m_pick;
	bool	   m_visiable = false;

public:
	UserPickView(int _x, int _y, int _width, int _height, bool _focused, CPick _pick);
	virtual ~UserPickView();

	virtual void Init()						override;
	virtual void Update(WPARAM _key)		override;
	virtual void Render()					override;
	virtual bool ISFocus(int _x, int _y)	override;

	bool		 ISShow() { return m_visiable; }
	void		 Show() { m_visiable = true; }
	void		 Hide() { m_visiable = false; m_pick = CPick::ORANGE_MURSHROOM; }
};

