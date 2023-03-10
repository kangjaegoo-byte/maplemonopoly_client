#pragma once
#include "Scene.h"
/**************************************************
	LoadingScene : ·Îµù¾À
**************************************************/
class LoadingScene : public Scene
{
private:
	ID2D1HwndRenderTarget*   m_rt;
	ID2D1BitmapRenderTarget* m_crt;
	IDWriteTextFormat*		 m_textFormat;
	ID2D1SolidColorBrush*	 m_blackBrush;
	ID2D1SolidColorBrush*	 m_blueBrush;
	WCHAR*					 m_loadFilename = nullptr;
	int						 m_percent;
	Scenetype				 m_loadSceneType;

public:
	LoadingScene(Scenetype _loading);
	~LoadingScene();

	virtual void	Init()		override;
	virtual void	Update()	override;
	virtual void	Render()	override;
	virtual void	Clean()		override;

	virtual void	MouseMoveEvent(int _x, int _y) override;
	virtual void	MouseClickEnvet(int _x, int _y) override;
	virtual void	CharEvent(WPARAM _key) override;

public:
	void            Add(int _percent);
	void			Flush();
	void			SetLoadFilename(WCHAR* _filename) { m_loadFilename = _filename; }
	Scenetype		GetLoadSceneType() { return m_loadSceneType; }
};

	