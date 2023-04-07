#pragma once
#include "View.h"
class GameModalView : public View
{
	enum : int
	{
		OKBUTTON = 0,
		NOBUTTON = 1,
		UICOUNT = 2,
	};

private:
	ID2D1HwndRenderTarget* m_rt;
	ID2D1BitmapRenderTarget* m_crt;
	IDWriteTextFormat* m_textFormat;
	ID2D1SolidColorBrush* m_blackBrush;
	ID2D1SolidColorBrush* m_colorBrush1;
	ID2D1SolidColorBrush* m_colorBrush2;
	std::vector<UIComponent*>	m_uiVector;
	class Sprite* m_sprite = nullptr;
	class StaticText* m_text = nullptr;
	class StaticText* m_title = nullptr;
	int m_type;
	int			m_playerIndex;
	bool        m_changed = false;
	CRITICAL_SECTION				m_gameLock;
public:
	GameModalView(ID2D1HwndRenderTarget* _rt, ID2D1BitmapRenderTarget* _crt, IDWriteTextFormat* _textFormat, ID2D1SolidColorBrush* _black, ID2D1SolidColorBrush* _color1, ID2D1SolidColorBrush* _color2);
	~GameModalView();

	virtual void	Init()		override;
	virtual void	Update(int _deltaTick)	override;
	virtual void	Render()	override;
	virtual void	Clean()		override;
	virtual ViewType ChangeView() override;

	virtual void	MouseMoveEvent(int _x, int _y) override;
	virtual void	MouseClickEvent(int _x, int _y) override;
	virtual void	MouseClickUpEnvet(int _x, int _y) override;
	virtual void	CharEvent(WPARAM _key) override;

	void			GameBuyRegionModalOtherProcessResponseEx(Region* _dataPtr, int _playerIndex);
	void			GameBuyRegion(Region* dataPtr);
	void			GameUserNumber(int _dataPtr);
private:
	void			Clear();
};
