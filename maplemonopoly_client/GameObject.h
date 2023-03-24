#pragma once
class GameObject
{
protected:
	int m_x = 0;
	int m_y = 0;
public:
	GameObject(int _x, int _y) : m_x(_x), m_y(_y) {};
	GameObject() {};
	virtual ~GameObject() {};

	virtual void Init() abstract;
	virtual void Render() abstract;
	virtual void Update(int _tick) abstract;
	virtual void Clean() abstract;

};

