#pragma once
#include "UIComponent.h"
class Ready : public UIComponent
{
private:
	bool m_ready = false;
	class Bitmap* m_readyBitmap = nullptr;

public:
	Ready(int _x, int _y, int _width, int _height, bool _focused);
	~Ready();

	virtual void Init()					 override;
	virtual void Update(WPARAM _key)	 override;
	virtual void Render()				 override;
	virtual bool ISFocus(int _x, int _y) override;
	void SetReady(bool _ready) { m_ready = _ready; };
	void Setting();
};

