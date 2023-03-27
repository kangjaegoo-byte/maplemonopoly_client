#pragma once
#include "UIComponent.h"
class Button;
class GameEndModal : public UIComponent
{
private:
	bool					m_display = false;
	WCHAR					m_text[256];
	IDWriteTextFormat* m_textformat;
	ID2D1SolidColorBrush* m_colorBrush;
	Button* m_button;
public:
	GameEndModal(int _x, int _y, int _width, int _height, bool _focused, const WCHAR* _text, ID2D1SolidColorBrush* _colorBrush, IDWriteTextFormat* _textformat);
	virtual ~GameEndModal();

	virtual void Init()						override;
	virtual void Update(WPARAM _key)		override;
	virtual void Render()					override;
	virtual bool ISFocus(int _x, int _y)	override;
	void Show() { m_display = true; }
	void Hide() { m_display = false; }
};

