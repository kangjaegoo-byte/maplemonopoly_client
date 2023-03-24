#pragma once
class Bitmap;
class Sprite
{
private:
	D2D1_RECT_F		m_rect;
	D2D1_POINT_2F	m_pivotPos;
public:
	Sprite(const D2D1_RECT_F& _rect, const D2D1_POINT_2F& _pivotPos) : m_rect(_rect), m_pivotPos(_pivotPos) {};
	Sprite() {};
	~Sprite() {};

	D2D1_RECT_F		GetRect() { return m_rect; }
	D2D1_POINT_2F	GetPivot() { return m_pivotPos; }
	void			SetPivot(const D2D1_POINT_2F& _pivot) { m_pivotPos = _pivot; }
	void			Render(const D2D1_RECT_F& _dest, Bitmap* _bitmap);
	void			Render(const D2D1_RECT_F& _dest, Bitmap* _bitmap, FLOAT _opacity);
	void			Render(Bitmap* _bitmap, D2D1_POINT_2F	_pivot);
	void			Render(Bitmap* _bitmap, D2D1_POINT_2F _pivot, bool _rotate);
	void			Render(Bitmap* _bitmap, int h_width, int _height);
	void			Render(Bitmap* _bitmap, D2D1_POINT_2F _pivot, bool _rotate, int h_width, int _height);
};
