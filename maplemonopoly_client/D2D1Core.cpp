#include "pch.h"
#include "D2D1Core.h"
#include "Bitmap.h"
D2D1Core* D2D1Core::m_instance = nullptr;

D2D1Core* D2D1Core::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new D2D1Core();
	return m_instance;
}

void D2D1Core::Init()
{
	CoInitialize(NULL);
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&g_pWICFactory));

	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2D1Factory);
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, _uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&g_pD2D1DWriteFactory));
}

void D2D1Core::CreateRenderTarget(HWND _hwnd)
{
	m_hwnd = _hwnd;
	RECT rc;
	GetClientRect(_hwnd, &rc);
	g_pD2D1Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE), D2D1::HwndRenderTargetProperties(_hwnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)), &m_rt);
}

void D2D1Core::CreateCompatibleRenderTarget()
{
	m_rt->CreateCompatibleRenderTarget(&m_crt);
}

Bitmap* D2D1Core::LoadBitmapByFileName(const PCWSTR _fileName)
{
	HRESULT hr = S_OK;
	IWICBitmapDecoder* pDecoder = nullptr;

	// Load Image
	hr = g_pWICFactory->CreateDecoderFromFilename(_fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);

	if (FAILED(hr))
		return nullptr;

	// 0 index Frame get
	IWICBitmapFrameDecode* pFrame = nullptr;
	hr = pDecoder->GetFrame(0, &pFrame);

	if (FAILED(hr))
		return nullptr;

	void* memory = ConvertFrameToBitmap(pFrame);

	IWICFormatConverter* pConverter = nullptr;
	hr = g_pWICFactory->CreateFormatConverter(&pConverter);

	if (FAILED(hr))
		return nullptr;

	hr = pConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	UINT width = 0;
	UINT height = 0;
	pConverter->GetSize(&width, &height);

	if (FAILED(hr))
		return nullptr;

	ID2D1Bitmap* temp;
	hr = m_rt->CreateBitmapFromWicBitmap(pConverter, NULL, &temp);

	if (FAILED(hr))
		return nullptr;

	if (pConverter) pConverter->Release();
	if (pFrame) pFrame->Release();
	if (pDecoder) pDecoder->Release();

	Bitmap* b = new Bitmap(temp, static_cast<BYTE*>(memory), width, height, 4);
	b->SetFileName(_fileName);
	return b;
}

void D2D1Core::SetFontFormat(IDWriteTextFormat** _textFormat, const WCHAR _fontName[], const FLOAT _fontSize, DWRITE_FONT_WEIGHT _fontWeight, DWRITE_TEXT_ALIGNMENT _alignment)
{
	g_pD2D1DWriteFactory->CreateTextFormat(_fontName, NULL, _fontWeight, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, _fontSize, L"en-us", _textFormat);
	if (_alignment != NULL)
		(*_textFormat)->SetTextAlignment(_alignment);
}

void D2D1Core::SetFontFormat(IDWriteTextFormat** _textFormat, const WCHAR _fontName[], const FLOAT _fontSize, DWRITE_TEXT_ALIGNMENT _alignment)
{
	g_pD2D1DWriteFactory->CreateTextFormat(_fontName, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, _fontSize, L"en-us", _textFormat);
	if (_alignment != NULL)
		(*_textFormat)->SetTextAlignment(_alignment);
}

void D2D1Core::SetFontFormat(IDWriteTextFormat** _textFormat, const WCHAR _fontName[], const FLOAT _fontSize)
{
	g_pD2D1DWriteFactory->CreateTextFormat(_fontName, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, _fontSize, L"en-us", _textFormat);
}

void* D2D1Core::ConvertFrameToBitmap(IWICBitmapFrameDecode* frame)
{
	IWICBitmapSource* bitmapSource = frame;
	if (FAILED(WICConvertBitmapSource(GUID_WICPixelFormat32bppPBGRA, frame, &bitmapSource)))
	{
		// could not convert bitmap
		return nullptr;
	}

	UINT width = 0;
	UINT height = 0;
	if (FAILED(bitmapSource->GetSize(&width, &height)) || width == 0 || height == 0)
	{
		// could not get image size
		return nullptr;
	}
	const int buffSize = width * height * 4;
	BYTE* buffer = new BYTE[width * height * 4];
	if (FAILED(bitmapSource->CopyPixels(NULL, width * 4, buffSize, buffer)))
	{
		// could not get image size
		return nullptr;
	}

	bitmapSource->Release();

	return buffer;
}

void D2D1Core::CreateColorBrush(ID2D1SolidColorBrush** _brush, D2D1::ColorF _color)
{
	m_rt->CreateSolidColorBrush(_color, _brush);
}