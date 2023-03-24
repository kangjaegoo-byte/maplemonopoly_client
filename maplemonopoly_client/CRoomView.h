#pragma once
#include "View.h"
class CRoomView : public View
{
	enum : int
	{
		CROOM_TITLEINPUT = 0,
		CROOM_OKBTN = 1,
		CROOM_NOBTN = 2,
		CROOM_UICOUNT = 3
	};

private:
	std::vector<UIComponent*> m_uiVector;
	ID2D1HwndRenderTarget* m_rt;
	ID2D1BitmapRenderTarget* m_crt;
	IDWriteTextFormat* m_textFormat;
	ID2D1SolidColorBrush* m_blackBrush;
	bool m_change = false;

public:
	CRoomView(ID2D1HwndRenderTarget* _rt, ID2D1BitmapRenderTarget* _crt, IDWriteTextFormat* _textFormat, ID2D1SolidColorBrush* _brush);
	~CRoomView();

	virtual void	Init()		override;
	virtual void	Update(int _deltaTick)	override;
	virtual void	Render()	override;
	virtual void	Clean()		override;


	virtual void	MouseMoveEvent(int _x, int _y) override;
	virtual void	MouseClickUpEnvet(int _x, int _y) override;
	virtual void	MouseClickEvent(int _x, int _y) override;
	virtual void	CharEvent(WPARAM _key) override;
	virtual ViewType ChangeView() override;
};

