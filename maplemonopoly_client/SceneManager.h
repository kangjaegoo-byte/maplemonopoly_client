#pragma once

class SceneManager
{
private:
	static SceneManager* m_instnace;
public:
	static SceneManager* GetInstance();
	static void DeleteInstance();

private:
	std::vector<class Scene*> m_scenes;
	SceneType m_nowScene = LOADING_SCENE;
	int m_lastTick = 0;

public:
	SceneType GetNowScene();
	void MoveScene(SceneType _type);
	SceneChangeData Change();
	void Change(SceneType _type);
	void Update();
	void Render();
	void Add(Scene* _scene);
	Scene* GetScene(SceneType _type);
	void MouseClickEvent(int _x, int _y);
	void MouseClickUpEnvet(int _x, int _y);
	void CharEvent(WPARAM _key);
};

