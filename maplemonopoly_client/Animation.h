#pragma once
class Sprite;
class Animation
{
protected:
	std::vector<Sprite*> m_clips;
	int					 m_nowFrame = 0;

public:
	Animation() = default;
	~Animation();

public:
	void	Init() { m_nowFrame = 0; }
	void	AddClip(Sprite* _sprite);
	Sprite* GetFrame();
	Sprite* GetFrameNoAuto();
	Sprite* GetFirst();
	Sprite* GetFrameP();
	int     GetFrameCount() { return m_clips.size(); }
	int     GetNowFrame() { return m_nowFrame; }

	Sprite* GetFrame(int _clip);
};

