#include "pch.h"
#include "Bitmap.h"

void Bitmap::SetFileName(const PCWSTR _fileName)
{
	_tcscpy_s(m_fileName, _fileName);
}