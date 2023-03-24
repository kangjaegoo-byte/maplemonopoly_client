#pragma once
class Bitmap;
class D2D1Core
{
private:
	D2D1Core() = default;
	~D2D1Core() {};

	static	D2D1Core* m_instance;
	ID2D1Factory* g_pD2D1Factory;
	ID2D1HwndRenderTarget* g_pD2D1RenderTarget;
	IDWriteFactory* g_pD2D1DWriteFactory;
	IWICImagingFactory* g_pWICFactory;
	ID2D1BitmapRenderTarget* g_pCompatibleRenderTarget;
	ID2D1HwndRenderTarget* m_rt;
	ID2D1BitmapRenderTarget* m_crt;
	HWND							m_hwnd; // WND HANDLE

public:
	void							Init();
	static							D2D1Core* GetInstance();
	void							CreateRenderTarget(HWND _hwnd);
	void							CreateCompatibleRenderTarget();
	Bitmap* LoadBitmapByFileName(const PCWSTR _fileName);
	void							SetFontFormat(IDWriteTextFormat** _textFormat, const WCHAR _fontName[], const FLOAT _fontSize, DWRITE_FONT_WEIGHT _fontWeight, DWRITE_TEXT_ALIGNMENT _alignment);
	void							SetFontFormat(IDWriteTextFormat** _textFormat, const WCHAR _fontName[], const FLOAT _fontSize, DWRITE_TEXT_ALIGNMENT _alignment);
	void							SetFontFormat(IDWriteTextFormat** _textFormat, const WCHAR _fontName[], const FLOAT _fontSize);
	void* ConvertFrameToBitmap(IWICBitmapFrameDecode* frame);
	IWICImagingFactory* GetIWICImangFactory() { return g_pWICFactory; }
	void							CreateColorBrush(ID2D1SolidColorBrush** _brush, D2D1::ColorF _color);
	ID2D1BitmapRenderTarget* GetCRT() { return m_crt; }
	ID2D1HwndRenderTarget* GetRT() { return m_rt; }
	HWND							GetHWND() { return m_hwnd; }
};

