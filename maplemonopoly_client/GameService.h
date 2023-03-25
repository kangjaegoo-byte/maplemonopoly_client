#pragma once
class GameService
{
private:
	static GameService* m_instance;
public:
	static GameService* GetInstance();
	void   Init();
	void   Clean();
	void   SceneChange();
	void   Recv(char* _buffer);
public:
	void   LobbyUserListAsync(char* _data, int _cnt);
	void   LobbyRoomListAsync(char* _data, int _cnt);
	void   LobbyChatMsgRecv(WCHAR* _text, int _size);
	void   LobbyUsernameAsync(WCHAR* _text, int _size);
	void   WRoomUserListAsync(char* _data, int _cnt);
	void   WRoomTitleAsync(WCHAR* _text, int _size);
	void   WRoomChat(WCHAR* _text, int _size);
	void   EnterGame();
	void   GameUserAsync(char* _data, int _cnt);
	void   GameUserNumber(int _idx);
	void   TurnSend(int _playerIdx);
	void   DiceDropResult(DiceData* _diceData);
	void   PlayerMove(char* _data);
	void   GameBuyRegion(Region* dataPtr);

	void					GameBuyRegionModalProcessResponse(char* _dataPtr);
	void					MoneyPassCost(char* _dataPtr);
	void					GameBuyRegionModalOtherProcessResponseEx(char* _dataPtr);
	void					GameOtherBuyResponse(char* _dataPtr);
};

