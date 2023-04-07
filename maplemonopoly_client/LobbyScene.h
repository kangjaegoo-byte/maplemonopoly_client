#pragma once
#include "Scene.h"
class LobbyScene : public Scene
{
private:
	ID2D1HwndRenderTarget* m_rt;
	ID2D1BitmapRenderTarget* m_crt;
	IDWriteTextFormat* m_textFormat;
	IDWriteTextFormat* m_boldTextAliginNormalForamt;
	IDWriteTextFormat* m_staticTextAlignFormat;
	ID2D1SolidColorBrush* m_blackBrush;
	ID2D1SolidColorBrush* m_blueBrush;
	ID2D1SolidColorBrush* m_redBrush;
	std::vector<class View*> m_viewVector;
	int	m_zindex = 0;
	bool m_change = false;

public:
	LobbyScene();
	~LobbyScene();

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
	void			LobbyUserListDataAsync(const std::vector<class User>& _data);
	void			LobbyRoomListDataAsync(const std::vector<class Room>& _data);
	void			LobbyChatMsgRecv(char* buffer);
	void			LobbyUsernameAsync(WCHAR* _text, int _size);

	void			WRoomChat(WCHAR* _text, int _size);
	void			WRoomChat(char* buffer);
	void			EnterGame() { m_change = true; };
	void			PlayerWRoomEnter(User* _user);
	void			PlayerWRoomEnter(char* buffer);
	void			PlayerWRoomExit(User* _user);
	void		    PlayerReady(char* buffer);
	void		    PlayerPickChange(char* buffer);
	void		    WRoomTitleAsync(WCHAR* _dataPtr, int _dataSize);
	void			LobbyAsync(char* buffer);
	void			PlayerWRoomOtherEnter(char* buffer);
	void			WRoomAsync(char* buffer);
	void			WRoomPickChange(char* buffer);
	void			WRoomReady(char* buffer);

}
;
