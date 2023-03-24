#include "pch.h"
#include "Sprite.h"
#include "D2D1Core.h"
#include "Bitmap.h"

void Sprite::Render(const D2D1_RECT_F& _dest, Bitmap* _bitmap)
{
	D2D1Core::GetInstance()->GetCRT()->DrawBitmap(_bitmap->GetBitmap(), _dest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_rect);
}

void Sprite::Render(const D2D1_RECT_F& _dest, Bitmap* _bitmap, FLOAT _opacity)
{
	D2D1Core::GetInstance()->GetCRT()->DrawBitmap(_bitmap->GetBitmap(), _dest, _opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_rect);
}

void Sprite::Render(Bitmap* _bitmap, D2D1_POINT_2F _pivot)
{
	int leftWidth = abs(m_pivotPos.x - m_rect.left);
	int rightWidth = abs(m_pivotPos.x - m_rect.right);
	int height = m_rect.bottom - m_rect.top;

	D2D1_RECT_F f = { _pivot.x - leftWidth , _pivot.y - height, _pivot.x + rightWidth, _pivot.y };
	D2D1Core::GetInstance()->GetCRT()->DrawBitmap(_bitmap->GetBitmap(), f, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_rect);
}

void Sprite::Render(Bitmap* _bitmap, D2D1_POINT_2F _pivot, bool _rotate)
{
	if (_rotate)
		D2D1Core::GetInstance()->GetCRT()->SetTransform(D2D1::Matrix3x2F::Scale(-1.0, 1.0, D2D1::Point2F(_pivot.x, _pivot.y)));
	Render(_bitmap, _pivot);
	D2D1Core::GetInstance()->GetCRT()->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Sprite::Render(Bitmap* _bitmap, int h_width, int _height)
{
	D2D1_RECT_F f = { m_pivotPos.x - h_width , m_pivotPos.y - _height, m_pivotPos.x + h_width, m_pivotPos.y };
	D2D1Core::GetInstance()->GetCRT()->DrawBitmap(_bitmap->GetBitmap(), f, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_rect);
}

void Sprite::Render(Bitmap* _bitmap, D2D1_POINT_2F _pivot, bool _rotate, int h_width, int _height)
{
	if (_rotate)
		D2D1Core::GetInstance()->GetCRT()->SetTransform(D2D1::Matrix3x2F::Scale(-1.0, 1.0, D2D1::Point2F(_pivot.x, _pivot.y)));
	D2D1_RECT_F f = { _pivot.x - h_width , _pivot.y - _height, _pivot.x + h_width, _pivot.y };
	D2D1Core::GetInstance()->GetCRT()->DrawBitmap(_bitmap->GetBitmap(), f, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_rect);
	D2D1Core::GetInstance()->GetCRT()->SetTransform(D2D1::Matrix3x2F::Identity());
}
