#pragma once
#include "View.h"
#include "UserDTO.h"
/**************************************************
	WRoomView : 게임 대기 화면
**************************************************/
class WRoomView : public View
{
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
		WROOM_UICOUNT = 12,
	};
private:
	std::vector<UIComponent*>		m_uiVector;
	ID2D1HwndRenderTarget*			m_rt;
	ID2D1BitmapRenderTarget*		m_crt;
	IDWriteTextFormat*				m_textFormat;
	IDWriteTextFormat*				m_staticTextFormat;
	ID2D1SolidColorBrush*			m_blackBrush;
	int								m_lastTick;
	int								m_sumTick;
	CRITICAL_SECTION				m_wroomLock;

public:
	WRoomView(ID2D1HwndRenderTarget* _rt, ID2D1BitmapRenderTarget* _crt, IDWriteTextFormat* _textFormat, IDWriteTextFormat* _staticTextFormat, ID2D1SolidColorBrush* _brush);
	~WRoomView();

	virtual void	Init()		override;
	virtual void	Update()	override;
	virtual void	Render()	override;
	virtual void	Clean()		override;


	virtual void	MouseMoveEvent(int _x, int _y) override;
	virtual void	MouseClickEnvet(int _x, int _y) override;
	virtual void	CharEvent(WPARAM _key) override;

	void			WatingRoomUserList(std::vector<UserDTO>& _data);
	void			WatingRoomTitle(WCHAR* _buffer, int _dataCnt);
	void			WatingRoomBoom();
	void			WRoomChatMsgRecv(WCHAR* _buffer, int _dataSize);
};

