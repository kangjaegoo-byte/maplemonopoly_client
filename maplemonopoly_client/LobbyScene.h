#pragma once
#include "Scene.h"
#include "UserDTO.h"
#include "RoomDTO.h"
class View;
/**************************************************
	LobbyScene : ·Îºñ¾À
**************************************************/
class LobbyScene : public Scene
{
	enum : int
	{
		LOBBY_VIEW = 0,
		CROOM_VIEW = 1,
		WROOM_VIEW = 2,
		VIEW_COUNT = 3
	};

private:
	ID2D1HwndRenderTarget*		m_rt;
	ID2D1BitmapRenderTarget*	m_crt;
	IDWriteTextFormat*			m_textFormat;
	IDWriteTextFormat*			m_boldTextAliginNormalForamt;
	IDWriteTextFormat*			m_staticTextAlignFormat;
	ID2D1SolidColorBrush*		m_blackBrush;
	ID2D1SolidColorBrush*		m_blueBrush;
	ID2D1SolidColorBrush*		m_redBrush;
	std::vector<View*>			m_viewVector;
	int							m_zindex = 0;
	
public:
	LobbyScene();
	~LobbyScene();

	virtual void	Init()		override;
	virtual void	Update()	override;
	virtual void	Render()	override;
	virtual void	Clean()		override;

	virtual void	MouseMoveEvent(int _x, int _y) override;
	virtual void	MouseClickEnvet(int _x, int _y) override;
	virtual void	CharEvent(WPARAM _key) override;

public:
	void			RecvLobbyChatMsg(WCHAR* _text, int _size);
	void			LobbyUserListDataAsync(const std::vector<UserDTO>& _data);
	void			LobbyRoomListDataAsync(const std::vector<RoomDTO>& _data);
	void			WatingRoomUserList(std::vector<UserDTO>& _data);
	void			ViewindexUp() { m_zindex++; }
	void			ViewindexDown() { m_zindex--; }
	void			WatingRoomTitle(WCHAR* _buffer, int _dataCnt);
	void			MoveViewIndex(int _index);
	void			WatingRoomBoom();
	void			WRoomChatMsgRecv(WCHAR* _buffer, int _dataSize);
};

	