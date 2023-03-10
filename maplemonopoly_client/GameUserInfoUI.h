#pragma once
#include "UIComponent.h"
class StaticText;
class UserPickView;
class UserDTO;
/**************************************************
	GameUserInfoUI : 게임 유저 정보
**************************************************/
class GameUserInfoUI : public UIComponent
{
private:
	int					  m_money;
	StaticText*			  m_usernameText;
	StaticText*			  m_moneyText;
	D2D1_RECT_F			  m_moneyRect;
	UserPickView*		  m_pickView;
	ID2D1SolidColorBrush* m_brushFill;
	ID2D1SolidColorBrush* m_brushOut;
	IDWriteTextFormat*    m_textformat;
	ID2D1SolidColorBrush* m_blackBrush;
	bool				  m_visiable = false;
	int					  m_userId = 0;
public:
	GameUserInfoUI(int _x, int _y, int _width, int _height, bool _focused, ID2D1SolidColorBrush* _brush, ID2D1SolidColorBrush* _out, ID2D1SolidColorBrush* _black, IDWriteTextFormat* _textForamt);
	virtual ~GameUserInfoUI();

	virtual void Init()					 override;
	virtual void Update(WPARAM _key)	 override;
	virtual void Render()				 override;
	virtual bool ISFocus(int _x, int _y) override;
	void Hide(int _userID) { if (_userID == m_userId) m_visiable = false; };
	void Init(UserDTO& _dt);
};

