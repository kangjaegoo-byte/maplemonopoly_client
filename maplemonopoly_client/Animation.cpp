#include "pch.h"
#include "Animation.h"
#include "Sprite.h"

Animation::~Animation()
{
	for (auto& s : m_clips)
		if (s) delete s;
}

void Animation::AddClip(Sprite* _sprite)
{
	m_clips.push_back(_sprite);
}

Sprite* Animation::GetFrame()
{
	Sprite* ret = m_clips[m_nowFrame];
	m_nowFrame = (m_nowFrame + 1) % m_clips.size();
	return ret;
}

Sprite* Animation::GetFrameNoAuto()
{
	Sprite* ret = m_clips[m_nowFrame];
	m_nowFrame = (m_nowFrame + 1);
	return ret;
}

Sprite* Animation::GetFirst()
{
	return m_clips.front();
}

Sprite* Animation::GetFrameP()
{
	return m_clips[m_nowFrame];
}

Sprite* Animation::GetFrame(int _clip)
{
	return m_clips[_clip];
}
