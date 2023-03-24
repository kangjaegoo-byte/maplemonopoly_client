#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "LoadingScene.h"
#include "LoginScene.h"
#include "GameScene.h"
#include "LobbyScene.h"
SceneManager* SceneManager::m_instnace = nullptr;

SceneManager* SceneManager::GetInstance()
{
	if (m_instnace == nullptr)
		m_instnace = new SceneManager();
	
	return m_instnace;
}

void SceneManager::DeleteInstance()
{
	if (m_instnace)
		delete m_instnace;
}

SceneType SceneManager::GetNowScene()
{
	return m_nowScene;
}

void SceneManager::MoveScene(SceneType _type)
{
	m_nowScene = _type;
}

SceneChangeData SceneManager::Change()
{
	return m_scenes[m_nowScene]->Change();
}

void SceneManager::Change(SceneType _type)
{
	m_nowScene = _type;
}

void SceneManager::Update()
{
	int currentTick = ::GetTickCount64();
	int deltaTick = currentTick - m_lastTick;
	m_scenes[m_nowScene]->Update(deltaTick);
	m_lastTick = currentTick;
}	

void SceneManager::Render()
{
	m_scenes[m_nowScene]->Render();
}

void SceneManager::Add(Scene* _scene)
{
	m_scenes.push_back(_scene);
}

Scene* SceneManager::GetScene(SceneType _type)
{
	return m_scenes[_type];
}

void SceneManager::MouseClickEvent(int _x, int _y)
{
	m_scenes[m_nowScene]->MouseClickEvent(_x,_y);
}

void SceneManager::MouseClickUpEnvet(int _x, int _y)
{
	m_scenes[m_nowScene]->MouseClickUpEnvet(_x, _y);
}

void SceneManager::CharEvent(WPARAM _key)
{
	m_scenes[m_nowScene]->CharEvent(_key);
}
