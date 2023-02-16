#pragma once


class timer
{
private:
	bool _isHardware;
	float _timeScale;
	float _timeElapsed;

	__int64 _curTime;
	__int64 _lastTime;
	__int64 _periodFrequency;

	unsigned long _frameRate;
	unsigned long _FPSFrameCount;
	float _FPSTimeElapsed;
	float _worldTime;

public:
	timer();
	~timer();

	HRESULT Init();
	void Tick( float lockFPS = 0.f );
	unsigned long GetFrameRate( char* str = NULL ) const;

	inline float GetElapsedTime() const { return _timeElapsed; }
	inline float GetWorldTime() const { return _worldTime; }
};

