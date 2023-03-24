#include "pch.h"
#include "Sound.h"
#include "SDKwavefile.h"

unsigned int _stdcall SoundProc(void* Args);
unsigned int _stdcall BgmProc(void* Args);
Sound::Sound(WCHAR* _filePath)
{
	Init(_filePath);
}

Sound::~Sound()
{
	Clean();
}

void Sound::Init(WCHAR* _filePath)
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	XAudio2Create(&m_pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	m_pXAudio2->CreateMasteringVoice(&m_pMasterVoice);

	CWaveFile wav;
	wav.Open(_filePath, NULL, WAVEFILE_READ);

	WAVEFORMATEX* pwfx = wav.GetFormat();
	DWORD cbWaveSize = wav.GetSize();

	m_datas = new BYTE[cbWaveSize];
	wav.Read(m_datas, cbWaveSize, &cbWaveSize);

	m_hr = m_pXAudio2->CreateSourceVoice(&m_pSourceVoice, pwfx);

	m_buffer.pAudioData = m_datas;
	m_buffer.Flags = XAUDIO2_END_OF_STREAM;
	m_buffer.AudioBytes = cbWaveSize;
	m_pSourceVoice->SubmitSourceBuffer(&m_buffer); // 음원장전
}

void Sound::Play()
{
	m_pSourceVoice->GetState(&m_state);
	if (m_state.BuffersQueued == 0)
	{
		m_isRunning = true;
		m_pSourceVoice->SubmitSourceBuffer(&m_buffer); // 음원장전
	}

	m_hr = m_pSourceVoice->Start(0);
	while (SUCCEEDED(m_hr) && m_isRunning)
	{
		m_pSourceVoice->GetState(&m_state);
		m_isRunning = (m_state.BuffersQueued > 0) != 0;

		if (m_stop)
		{
			m_pSourceVoice->Stop(0);
			break;
		}

		Sleep(10);
	}
}

void Sound::AutomicPlay()
{
	while (m_stop == false)
		Play();
}

void Sound::Clean()
{
	if (m_datas)
		delete[] m_datas;

	m_pSourceVoice->DestroyVoice();
	m_pMasterVoice->DestroyVoice();
	m_pXAudio2->Release();

	CoUninitialize();
}

void Sound::Playing(bool _bgm)
{
	unsigned int bgmThreadId = Threadid::BGM;
	unsigned int soundThreadId = Threadid::SOUND;
	if (_bgm)
	{
		_beginthreadex(NULL, 0, &BgmProc, this, 0, &bgmThreadId);
	}
	else
	{
		_beginthreadex(NULL, 0, &SoundProc, this, 0, &soundThreadId);
	}
}

unsigned int _stdcall SoundProc(void* Args)
{
	Sound* sound = reinterpret_cast<Sound*>(Args);
	sound->Play();
	return 0;
}

unsigned int _stdcall BgmProc(void* Args)
{
	Sound* sound = reinterpret_cast<Sound*>(Args);
	sound->AutomicPlay();
	delete sound;
	return 0;
}
