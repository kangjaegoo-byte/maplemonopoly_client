#include "pch.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Animation.h"
#include "Bitmap.h"
#include "Sound.h"
ResourceManager* ResourceManager::m_instance = nullptr;

ResourceManager::~ResourceManager()
{
	for (auto it = m_resource.begin(); it != m_resource.end();)
		if (it->second)
			delete it->second;

	if (m_instance)
		delete m_instance;
}

ResourceManager* ResourceManager::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new ResourceManager();
	return m_instance;
}

void ResourceManager::DeleteResourceManager()
{
	delete m_instance;
}

Bitmap* ResourceManager::GetBitmap(ResourceName _key)
{
	if (m_resource.find(_key) != m_resource.end())
		return m_resource.find(_key)->second;
	else
		return nullptr;
}

Sound* ResourceManager::GetSound(ResourceName _key)
{
	if (m_sounds.find(_key) != m_sounds.end())
		return m_sounds.find(_key)->second;
	else
		return nullptr;
}

Sprite* ResourceManager::GetSprite(ResourceName _key)
{
	if (m_sprite.find(_key) != m_sprite.end())
		return m_sprite.find(_key)->second;
	else
		return nullptr;
}

Animation* ResourceManager::GetAnimation(ResourceName _key)
{
	if (m_animation.find(_key) != m_animation.end())
		return m_animation.find(_key)->second;
	else
		return nullptr;
}

void ResourceManager::Put(ResourceName _key, Bitmap* _value)
{
	m_resource.insert({ _key, _value });
}

void ResourceManager::Put(ResourceName _key, Sound* _value)
{
	m_sounds.insert({ _key, _value });
}

void ResourceManager::Put(ResourceName _key, Animation* _value)
{
	m_animation.insert({ _key, _value });
}

void ResourceManager::Put(ResourceName _key, Sprite* _value)
{
	m_sprite.insert({ _key, _value });
}

void ResourceManager::DeleteBitmap(ResourceName _key)
{
	Bitmap* bitmap = m_resource.find(_key)->second;
	delete bitmap;
	m_resource.erase(_key);
}

void ResourceManager::DeleteAnimation(ResourceName _key)
{
	Animation* ani = m_animation.find(_key)->second;
	delete ani;
	m_animation.erase(_key);
}

void ResourceManager::DeleteSprite(ResourceName _key)
{
	Sprite* spr = m_sprite.find(_key)->second;
	delete spr;
	m_sprite.erase(_key);
}

void ResourceManager::GetFileList(OUT std::vector<WCHAR*>& _fileList, const WCHAR* _path)
{
	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFileW(_path, &data);

	while (FindNextFileW(hFind, &data))
	{
		if ((data.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) &&  //파일이라면
			!(data.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)) //시스템파일은 제외
		{
			TCHAR* cha = new TCHAR[256];

			for (int i = 0; i <= _tcslen(data.cFileName); i++)
				cha[i] = data.cFileName[i];
			_fileList.push_back(cha);
		}
	}
	FindClose(hFind);
}

void ResourceManager::GetFileName(WCHAR* _path, OUT WCHAR* _fileName)
{
	int pathLen = wcslen(_path);
	for (int i = 0; i < pathLen; i++)
	{
		if (_path[i] == L'.')
		{
			_fileName[i] = '\0';
			break;
		}
		_fileName[i] = _path[i];
	}
}

void ResourceManager::GetFileExp(WCHAR* _path, OUT WCHAR* _exp)
{
	std::stack<WCHAR> s;
	int pathLen = wcslen(_path);

	for (int i = pathLen - 1; i >= 0; i--)
	{
		if (_path[i] == _T('.'))
			break;
		s.push(_path[i]);
	}

	int index = 0;

	while (s.empty() == false)
	{
		TCHAR t = s.top();
		s.pop();
		_exp[index] = t;
		index++;
	}
	_exp[index] = '\0';
}

void* ResourceManager::LoadBinaryData(WCHAR* _filePath)
{
	void* ret = nullptr;
	FILE* p_file = NULL;
	_wfopen_s(&p_file, _filePath, L"rb");

	if (p_file != NULL)
	{
		SpriteBinaryFileHeader* header = new SpriteBinaryFileHeader();
		fread(header, sizeof(SpriteBinaryFileHeader), 1, p_file);

		if (header)
		{
			SpriteBinaryFileData* bStream = new SpriteBinaryFileData[header->spriteCount];
			fread(bStream, sizeof(SpriteBinaryFileData), header->spriteCount, p_file);

			switch (header->resourceType)
			{
			case SPRITE:
				for (int i = 0; i < header->spriteCount; i++)
				{
					bStream[i].rect.right += 1;
					bStream[i].rect.bottom += 1;
					ret = new Sprite(bStream[i].rect, bStream[i].pivotPos);
				}
				break;
			case  ANIMATION:
			{
				ret = new Animation();
				for (int i = 0; i < header->spriteCount; i++)
				{
					bStream[i].rect.right += 1;
					bStream[i].rect.bottom += 1;
					Sprite* sprite = new Sprite(bStream[i].rect, bStream[i].pivotPos);
					reinterpret_cast<Animation*>(ret)->AddClip(sprite);
				}
				break;
			}
			}
			delete[] bStream;
		}
		delete header;
	}

	return ret;
}

void ResourceManager::DeleteSound(ResourceName _key)
{
	Sound* sound = m_sounds.find(_key)->second;
	sound->End();
	m_sounds.erase(_key);
}

void ResourceManager::DeleteSoundEx(ResourceName _key)
{
	Sound* sound = m_sounds.find(_key)->second;
	sound->End();
	delete sound;
	m_sounds.erase(_key);
}

Sprite* ResourceManager::GetPlayerHouse(int _playerIdx)
{
	switch (_playerIdx)
	{
	case 0:
		return GetSprite(GAME_ONEPICK_HOUSE);

	case 1:
		return GetSprite(GAME_TWOPICK_HOUSE);

	case 2:
		return GetSprite(GAME_THREEPICK_HOUSE);

	case 3:
		return GetSprite(GAME_FOURPICK_HOUSE);
	}
}

Sprite* ResourceManager::GetPlayerHotel(int _playerIdx)
{
	switch (_playerIdx)
	{
	case 0:
		return GetSprite(GAME_ONEPICK_HOTEL);

	case 1:
		return GetSprite(GAME_TWOPICK_HOTEL);

	case 2:
		return GetSprite(GAME_THREEPICK_HOTEL);

	case 3:
		return GetSprite(GAME_FOURPICK_HOTEL);
	}
}
