#include "pch.h"
#include "Sprite.h"
#include "D2D1Core.h"
#include "Bitmap.h"

void Sprite::Render(const D2D1_RECT_F& _dest, Bitmap* _bitmap)
{
	D2D1Core::GetInstance()->GetCRT()->DrawBitmap(_bitmap->GetBitmap(), _dest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_rect);
}
