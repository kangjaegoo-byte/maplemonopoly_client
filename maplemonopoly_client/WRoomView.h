#pragma once
#include "View.h"
#include "User.h"
class WRoomView : public View
{
	const int passTick = 1000;
	const int animationPassTick = 100;

	enum : int
	{
		WROOM_CHATINPUT = 0,
		WROOM_GAMESTART_BTN = 1,
		WROOM_USERPICK1_BTN = 2,
		WROOM_USERPICK2_BTN = 3,
		WROOM_USERPICK3_BTN = 4,
		WROOM_TITLE_STATICTEXT = 5,
		WROOM_USERNAME1_STATICTEXT = 6,
		WROOM_USERNAME2_STATICTEXT = 7,
		WROOM_USERNAME3_STATICTEXT = 8,
		WROOM_USERNAME4_STATICTEXT = 9,
		WROOM_EXIT_BTN = 10,
		WROOM_CHATTING_LIST = 11,
		WROOM_USER1_PICKVIEW = 12,
		WROOM_USER2_PICKVIEW = 13,
		WROOM_USER3_PICKVIEW = 14,
		WROOM_USER4_PICKVIEW = 15,

		WROOM_READY_P2 = 16,
		WROOM_READY_P3 = 17,
		WROOM_READY_P4 = 18,
		
		WROOM_UICOUNT = 19,
	};
private:
	std::vector<UIComponent*>		m_uiVector;
	ID2D1HwndRenderTarget* m_rt;
	ID2D1BitmapRenderTarget* m_crt;
	IDWriteTextFormat* m_textFormat;
	IDWriteTextFormat* m_staticTextFormat;
	ID2D1SolidColorBrush* m_blackBrush;
	int								m_sumTick = passTick;
	int								m_animationUpdateTick = 0;
	CRITICAL_SECTION				m_wroomLock;
	bool m_lobbyRoomChange = false;
	class User* m_users[4] = { nullptr, nullptr, nullptr, nullptr };
	std::vector<class Button*> buttons;

public:
	WRoomView(ID2D1HwndRenderTarget* _rt, ID2D1BitmapRenderTarget* _crt, IDWriteTextFormat* _textFormat, IDWriteTextFormat* _staticTextFormat, ID2D1SolidColorBrush* _brush);
	virtual ~WRoomView();

	virtual void	Init()		override;
	virtual void	Update(int _deltaTick)	override;
	virtual void	Render()	override;
	virtual void	Clean()		override;


	virtual void	MouseMoveEvent(int _x, int _y) override;
	virtual void	MouseClickEvent(int _x, int _y) override;
	virtual void	MouseClickUpEnvet(int _x, int _y) override;
	virtual void	CharEvent(WPARAM _key) override;
	virtual ViewType ChangeView() override;


	void			WRoomChatMsgRecv(WCHAR* _dataPtr, int _dataSize);
	void			PlayerWRoomExit(User* _user);
	void			PlayerWRoomEnter(User* _user);
	void			PlayerWRoomEnter(char* buffer);
	void			PlayerWRoomOtherEnter(char* buffer);
	void			PlayerReady(char* _buffer);
	void			PlayerPickChange(char* _buffer);
	void			WRoomTitleAsync(WCHAR* _dataPtr, int _dataSize);
	void			WRoomChat(char* buffer);
	void			WRoomAsync(char* buffer);
	void			WRoomPickChange(char* buffer);
	void			WRoomReady(char* buffer);

	void            ButtonEventHandelr(ButtonCommand command);
};

