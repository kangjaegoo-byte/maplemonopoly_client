#pragma once
#include "UIComponent.h"
class InputEditor : public UIComponent
{
private:
	WCHAR					m_text[100] = L"";
	WCHAR					m_viewText[100] = L"";
	int						m_index = 0;
	int						m_maxSize = 0;
	bool					m_cusorAnimation = false;
	int						m_cusorTick = 0;
	IDWriteTextFormat* m_textformat;
	ID2D1SolidColorBrush* m_colorBrush;

public:
	InputEditor(int _x, int _y, int _width, int _height, int _maxSize, bool _focused, ID2D1SolidColorBrush* _colorBrush, IDWriteTextFormat* _textformat);
	virtual ~InputEditor();

	virtual void Init()						override;
	virtual void Update(WPARAM _key)		override;
	virtual void Render()					override;
	virtual bool ISFocus(int _x, int _y)	override;
public:
	bool		 Validation();
	void		 TextInit();
	WCHAR* GetText() { return m_text; }
};

