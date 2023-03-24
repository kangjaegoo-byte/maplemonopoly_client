#pragma once
class Bitmap
{
private:
	ID2D1Bitmap* m_bitmap;
	int								m_width;
	int								m_height;
	int								m_bitCount;
	BYTE* m_memory;
	WCHAR							m_fileName[256];

public:
	Bitmap(ID2D1Bitmap* _bitmap) : m_bitmap(_bitmap) {};
	Bitmap(ID2D1Bitmap* _bitmap, BYTE* _memory, int _width, int _height, int _bitCount) : m_bitmap(_bitmap), m_memory(_memory), m_width(_width), m_height(_height), m_bitCount(_bitCount) {};
	~Bitmap();
	TCHAR*		 GetFileName() { return m_fileName; }
	void		 SetFileName(const PCWSTR _fileName);
	int			 GetBitCount() { return m_bitCount; };
	ID2D1Bitmap* GetBitmap() { return m_bitmap; };
	BYTE*		 GetMemory() { return m_memory; };
	int			 GetWidht() { return m_width; };
	int			 GetHeight() { return m_height; };
};

