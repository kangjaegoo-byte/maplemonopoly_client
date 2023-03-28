#pragma once
class UIComponent;
class View
{
protected:
	int m_sumTick = 0;
public:
	View() {};
	virtual ~View() {};
	virtual void Init()		abstract;
	virtual void Update(int _deltaTick)	abstract;
	virtual void Render()	abstract;
	virtual void Clean()		abstract;
	virtual void MouseMoveEvent(int _x, int _y) abstract;
	virtual void MouseClickEvent(int _x, int _y) abstract;
	virtual void MouseClickUpEnvet(int _x, int _y) abstract;
	virtual void CharEvent(WPARAM _key) abstract;
	virtual ViewType ChangeView() abstract;
};
