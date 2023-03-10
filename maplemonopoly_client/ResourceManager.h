#pragma once
class Bitmap;
class Sound;
/**************************************************
	ResourceManager : 데이터 로드 매니져
**************************************************/
class ResourceManager
{
private:
	static ResourceManager* m_instance;
	std::map<Resourcename, Bitmap*> m_resource;
	std::map<Resourcename, Sound*>  m_sounds;

	ResourceManager() = default;
	~ResourceManager();

public:
	static  ResourceManager* GetInstance();
	void	DeleteResourceManager();
	Bitmap* GetBitmap(Resourcename _key);
	Sound*  GetSound(Resourcename _key);
	void	Put(Resourcename _key, Bitmap* _value);
	void	Put(Resourcename _key, Sound* _value);
	void	Delete(Resourcename _key);

	void	GetFileList(OUT std::vector<WCHAR*>& _fileList, const WCHAR* _path);
	void	GetFileName(WCHAR* _path, OUT WCHAR* _fileName);
	void	GetFileExp(WCHAR* _path, OUT WCHAR* _exp);
};

