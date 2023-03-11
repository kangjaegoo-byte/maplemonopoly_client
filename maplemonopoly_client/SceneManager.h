#pragma once
class Scene;
/**************************************************
	SceneManager : 씬 관리 매니저
**************************************************/
class SceneManager
{
private:
	static SceneManager*	m_instance;
	std::vector<Scene*>		m_sceneVector;
	int						m_nowscene; // index
	CRITICAL_SECTION		m_sceneDeleteRequireLock;

public:
	static SceneManager*	GetInstance();
	void					DeleteInstance();

	void					Init();
	void					Update();
	void					MouseMoveEvent(int _x, int _y);
	void					MouseClickEnvet(int _x, int _y);
	void					CharEvent(WPARAM _key);

public:
	void					Recv(char* _buffer);
	void					LoadingPage(Scenetype _next);
	
	void					LoginPage();
	void					LobbyPage();
	void					GamePage();

	void					SceneChange(Scenetype _type);
	void					LobbyChatMsgRecv(WCHAR* _text, int _size);
	void					LobbyUserListDataAsync(char* _buffer, int _dataCnt);
	void					LobbyRoomListDataAsync(char* _buffer, int _dataCnt);
	void					CreateRoomResponse(WORD _roomSq);
	void					WatingRoomUserList(char* _buffer, int _dataCnt);
	void					WatingRoomTitle(WCHAR* _buffer, int _dataCnt);
	void					WRoomChatMsgRecv(WCHAR* _buffer, int _dataSize);
public:
	void					LobbyViewIndexUp();
	void					LobbyViewIndexDown();
	void					MoveViewIndex(int _index);
	void					WatingRoomBoom();
	void					GameEnter(char* _dataPtr, int _size, int _cnt);
};

