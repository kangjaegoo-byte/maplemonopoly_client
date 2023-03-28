#pragma once
#include "UIComponent.h"
class StaticText;
class UserPickView;
class User;
class UserInfo2 : public UIComponent
{
private:
	int					  m_money;
	StaticText* m_usernameText;
	StaticText* m_moneyText;
	D2D1_RECT_F			  m_moneyRect;
	UserPickView* m_pickView;
	ID2D1SolidColorBrush* m_brushFill;
	ID2D1SolidColorBrush* m_brushOut;
	IDWriteTextFormat* m_textformat;
	ID2D1SolidColorBrush* m_blackBrush;
	bool				  m_visiable = false;
	int					  m_userId = 0;
	bool				  m_opacity = false;
	int					  m_playerNumber;
	StaticText* m_rankText = nullptr;
public:
	UserInfo2(int _x, int _y, int _width, int _height, bool _focused, ID2D1SolidColorBrush* _brush, IDWriteTextFormat* _textForamt, int _playerNumber);
	virtual ~UserInfo2();

	virtual void Init()					 override;
	virtual void Update(WPARAM _key)	 override;
	virtual void Render()				 override;
	virtual bool ISFocus(int _x, int _y) override;
	void Hide(int _userID) { if (_userID == m_userId) m_visiable = false; };
	void Init(User& _dt);
	void		Opacity(bool _opacity) { m_opacity = _opacity; }
	void		SetMoney(int _money);
};

