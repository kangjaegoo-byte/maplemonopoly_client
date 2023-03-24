#pragma once
class Bitmap;
class Sound;
class Animation;
class Sprite;
class ResourceManager
{
private:
	static ResourceManager* m_instance;
	std::map<ResourceName, Bitmap*>		m_resource;
	std::map<ResourceName, Sound*>		m_sounds;
	std::map<ResourceName, Animation*>  m_animation;
	std::map<ResourceName, Sprite*>		m_sprite;

	ResourceManager() = default;
	~ResourceManager();

public:
	static  ResourceManager* GetInstance();
	void	DeleteResourceManager();
	Bitmap* GetBitmap(ResourceName _key);
	Sound* GetSound(ResourceName _key);
	Sprite* GetSprite(ResourceName _key);
	Animation* GetAnimation(ResourceName _key);
	void	Put(ResourceName _key, Bitmap* _value);
	void	Put(ResourceName _key, Sound* _value);
	void	Put(ResourceName _key, Animation* _value);
	void	Put(ResourceName _key, Sprite* _value);
	void	DeleteBitmap(ResourceName _key);
	void	DeleteAnimation(ResourceName _key);
	void	DeleteSprite(ResourceName _key);

	void	GetFileList(OUT std::vector<WCHAR*>& _fileList, const WCHAR* _path);
	void	GetFileName(WCHAR* _path, OUT WCHAR* _fileName);
	void	GetFileExp(WCHAR* _path, OUT WCHAR* _exp);
	void* LoadBinaryData(WCHAR* _filPath);
	void	DeleteSound(ResourceName _key);
	void	DeleteSoundEx(ResourceName _key);

	Sprite* GetPlayerHouse(int _playerIdx);
	Sprite* GetPlayerHotel(int _playerIdx);
};

