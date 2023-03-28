#pragma once
class Scene
{
protected:
	SceneType m_type;
	int m_sumTick = 0;
public:
	Scene(SceneType _type);
	virtual ~Scene();

	virtual void Init()		abstract;
	virtual void Update(int _deltaTick)	abstract;
	virtual void Render()	abstract;
	virtual void Clean()		abstract;
	virtual SceneChangeData	Change()	abstract;

	virtual void MouseMoveEvent(int _x, int _y) abstract;
	virtual void MouseClickEvent(int _x, int _y) abstract;
	virtual void MouseClickUpEnvet(int _x, int _y) abstract;
	virtual void CharEvent(WPARAM _key) abstract;

	SceneType GetType() { return m_type; }
};

