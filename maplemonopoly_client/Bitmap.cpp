#include "pch.h"
#include "Bitmap.h"

Bitmap::~Bitmap()
{
	m_bitmap->Release();
	delete[] m_memory;
}

void Bitmap::SetFileName(const PCWSTR _fileName)
{
	_tcscpy_s(m_fileName, _fileName);
}