#pragma once
class Sound
{
private:
	HRESULT					m_hr;
	IXAudio2* m_pXAudio2 = NULL;
	IXAudio2MasteringVoice* m_pMasterVoice = NULL;
	IXAudio2SourceVoice* m_pSourceVoice = NULL;
	XAUDIO2_BUFFER			m_buffer = { 0 };
	XAUDIO2_VOICE_STATE		m_state;
	bool					m_isRunning = TRUE;
	bool					m_stop = false;
	BYTE* m_datas;

public:
	Sound(WCHAR* _filePath);
	~Sound();

	void Init(WCHAR* _filePath);
	void Clean();

	void Playing(bool _bgm);
	void Play();
	void AutomicPlay();

	void End() { m_stop = true; };
};