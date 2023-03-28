#include "pch.h"
#include "Marker.h"
#include "Sprite.h"
#include "Bitmap.h"


struct Pos
{
	int _x;
	int _y;
};

const Pos pos[32] = { {401,526},{358,485}, {327,453},{291,431},{255,406},{219,377},{187,353},{153,329},{98,296},{153,261},{188,237},{222,209},{256,186},{292,160},{326,132},{361,107},{399,70},{440,108},{476,133},{511,161},{543,188},{578,212},{610,237},{646,264},{701,295}, {645,325},{611,351},{576,378},{544,403},{509,431},{479,456},{442,478} };


Marker::Marker()
{

}

Marker::~Marker()
{

}

void Marker::SetPos(int _pos)
{
	Pos p = pos[_pos];

	m_x = p._x;
	m_y = p._y;
}

void Marker::SetVisiable(bool _flag)
{
	m_visiable = _flag;
}

void Marker::Init()
{
	m_visiable = false;
}

void Marker::Render()
{
	if (m_visiable)
		ResourceManager::GetInstance()->GetSprite(GAME_MARKER_SPRITE)->Render(ResourceManager::GetInstance()->GetBitmap(GAME_MARKER_BITMAP), D2D1_POINT_2F{ m_x + 0.0f,m_y + 0.0f },false,30,30);
}

void Marker::Update(int _tick)
{

}

void Marker::Clean()
{

}
