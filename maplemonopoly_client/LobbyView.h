#pragma once
#include "View.h"
class LobbyView : public View
{
	const int passTick = 1000;
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
	ID2D1HwndRenderTarget* m_rt;
	ID2D1BitmapRenderTarget* m_crt;
	IDWriteTextFormat* m_textFormat;
	IDWriteTextFormat* m_boldTextAliginNormalForamt;
	ID2D1SolidColorBrush* m_blackBrush;
	ID2D1SolidColorBrush* m_blueBrush;
	ID2D1SolidColorBrush* m_redBrush;
	int	m_sumTick = passTick;
	WCHAR m_username[30] = L"";
	bool m_croomChange = false;
	bool m_wroomChange = false;

public:
	LobbyView(ID2D1HwndRenderTarget* _rt, ID2D1BitmapRenderTarget* _crt, IDWriteTextFormat* _textFormat, IDWriteTextFormat* _boldTextFormat, ID2D1SolidColorBrush* _black, ID2D1SolidColorBrush* _blue, ID2D1SolidColorBrush* _red);
	virtual ~LobbyView();

	virtual void	Init()		override;
	virtual void	Update(int _deltaTick)	override;
	virtual void	Render()	override;
	virtual void	Clean()		override;

	virtual void	MouseMoveEvent(int _x, int _y) override;
	virtual void	MouseClickEvent(int _x, int _y) override;
	virtual void	MouseClickUpEnvet(int _x, int _y) override;
	virtual void	CharEvent(WPARAM _key) override;
	virtual ViewType ChangeView() override;
public:
	void			WRoomEnter(int _x, int _y);
	void			LobbyUserListDataAsync(const std::vector<class User>& _data);
	void			LobbyRoomListDataAsync(const std::vector<class Room>& _data);
	void			LobbyChatMsgRecv(char* buffer);
	void			LobbyUsernameAsync(WCHAR* _text, int _size);
	void			LobbyAsync(char* buffer);
};

