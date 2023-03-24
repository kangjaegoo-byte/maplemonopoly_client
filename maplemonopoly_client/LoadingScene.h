#pragma once
#include "Scene.h"
class LoadingScene : public Scene
{
private:
	ID2D1HwndRenderTarget* m_rt;
	ID2D1BitmapRenderTarget* m_crt;
	IDWriteTextFormat* m_textFormat;
	ID2D1SolidColorBrush* m_blackBrush;
	ID2D1SolidColorBrush* m_blueBrush;
	WCHAR* m_loadFilename = nullptr;
	int	m_percent = 0;
	SceneType m_loadScene;
	bool m_loadEnd = false;
	bool m_loadStart = false;

public:
	LoadingScene();
	~LoadingScene();

	virtual void	Init()		override;
	virtual void	Update(int _deltaTick)	override;
	virtual void	Render()	override;
	virtual void	Clean()		override;

	virtual void	MouseMoveEvent(int _x, int _y) override;
	virtual void	MouseClickEvent(int _x, int _y) override;
	virtual void	MouseClickUpEnvet(int _x, int _y) override;
	virtual void	CharEvent(WPARAM _key) override;
	virtual SceneChangeData	Change()	override;
public:
	void Add(int _percent);
	void Flush();
	void SetLoadFilename(WCHAR* _filename) { m_loadFilename = _filename; }
	SceneType GetLoadSceneType() { return m_loadScene; }
	void Load();
	void LoadInit();
	void SetLoadTargetScene(SceneType _type) { m_loadScene = _type; }
};

