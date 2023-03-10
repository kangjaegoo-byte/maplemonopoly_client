#pragma once
/**************************************************
	Scene : 씬 추상화 클래스
**************************************************/
class Scene
{
protected:
	Scenetype m_type;

public:
	Scene(Scenetype _type);
	virtual ~Scene();

	virtual void	Init()		abstract;
	virtual void	Update()	abstract;
	virtual void	Render()	abstract;
	virtual void	Clean()		abstract;

	virtual void	MouseMoveEvent(int _x, int _y) abstract;
	virtual void	MouseClickEnvet(int _x, int _y) abstract;
	virtual void	CharEvent(WPARAM _key) abstract;

	Scenetype		GetType() { return m_type; }
};

