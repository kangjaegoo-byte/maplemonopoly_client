#pragma once
class UIComponent
{
protected:
	bool		m_focused = false;
	int			m_x;
	int			m_y;
	int			m_width;
	int         m_height;

public:
	UIComponent(int _x, int _y, int _width, int _height, bool _focused);
	UIComponent();
	virtual ~UIComponent();

	virtual void Init()					 abstract;
	virtual void Update(WPARAM _key)	 abstract;
	virtual void Render()				 abstract;
	virtual bool ISFocus(int _x, int _y) abstract;
	bool FocuseCheck();
};

