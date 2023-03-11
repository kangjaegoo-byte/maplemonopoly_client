#pragma once
#include "View.h"
#include "UserDTO.h"
#include "RoomDTO.h"
/**************************************************
	LobbyView : 로비 화면
**************************************************/
class LobbyView : public View
{
	enum : int
	{
		LobbyView_CHATINPUT = 0,
		LobbyView_CROOMBTN = 1,
		LobbyView_USERLIST = 2,
		LobbyView_USERLIST_UPBTN = 3,
		LobbyView_USERLIST_DOWNBTN = 4,
		LobbyView_ROOMLIST = 5,
		LobbyView_ROOMLIST_UPBTN = 6,
		LobbyView_ROOMLIST_DOWNBTN = 7,
		LobbyView_CHATLIST = 8,
		LobbyView_UICOUNT = 9
	};
private:
	std::vector<UIComponent*>	m_uiVector;
	ID2D1HwndRenderTarget*		m_rt;
	ID2D1BitmapRenderTarget*	m_crt;
	IDWriteTextFormat*			m_textFormat;
	IDWriteTextFormat*			m_boldTextAliginNormalForamt;
	ID2D1SolidColorBrush*		m_blackBrush;
	ID2D1SolidColorBrush*		m_blueBrush;
	ID2D1SolidColorBrush*		m_redBrush;
	int							m_lastTick = 0;
	int							m_sumTick = 0;

public:
	LobbyView(ID2D1HwndRenderTarget* _rt, ID2D1BitmapRenderTarget* _crt, IDWriteTextFormat* _textFormat, IDWriteTextFormat* _boldTextFormat, ID2D1SolidColorBrush* _black, ID2D1SolidColorBrush* _blue, ID2D1SolidColorBrush* _red);
	virtual ~LobbyView();

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
	void			WatingRoomEnter(int _x, int _y);
};

