#pragma once
class UIComponent;
/**************************************************
	View : 화면 클래스
**************************************************/
class View
{
public:
	View() {};
 	virtual ~View() {};

	virtual void	Init()		abstract;
	virtual void	Update()	abstract;
	virtual void	Render()	abstract;
	virtual void	Clean()		abstract;


	virtual void	MouseMoveEvent(int _x, int _y) abstract;
	virtual void	MouseClickEnvet(int _x, int _y) abstract;
	virtual void	CharEvent(WPARAM _key) abstract;
};
