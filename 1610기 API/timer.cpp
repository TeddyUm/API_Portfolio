#include "stdafx.h"
#include "timer.h"
#include <mmsystem.h>

//timeGetTime 함수 사용하귀 위한 라이브러리
//윈도우가 실행중인 시간을 알려줌
#pragma comment(lib, "winmm.lib")

timer::timer()
{
}


timer::~timer()
{
}

HRESULT timer::Init()
{
	if ( QueryPerformanceFrequency( (LARGE_INTEGER*) &_periodFrequency ) )
	{
		_isHardware = true;
		QueryPerformanceCounter( (LARGE_INTEGER*) &_lastTime );

		//초당 시간을 계삭 할 수 있는 여력 //초당 시간 계산 범위
		_timeScale = 1.f / _periodFrequency;

	}
	else
	{
		_isHardware = false;

		_lastTime = timeGetTime();//밀리세컨드 단위로 1000카운드당 1초
		_timeScale = 0.001f;
	}

	_frameRate = 0.f;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0.f;
	_worldTime = 0.f;

	return S_OK;
}

void timer::Tick( float lockFPS )
{
	//고성능 타이머 지원하니?
	if ( _isHardware )
	{
		//초정밀 마이크로초 단위로 계산
		QueryPerformanceCounter( (LARGE_INTEGER*) &_curTime );
	}
	else
	{
		_curTime = timeGetTime();
	}

	//마지막 시간과 현재 시간의 경과량
	_timeElapsed = ( _curTime - _lastTime ) * _timeScale;

	//고정 프레임 처리(프레임 스키핑)
	if ( lockFPS > 0.f )
	{
		//고정 프레임의 시간을 만족할 때까지 루프
		while( _timeElapsed < (1.f / lockFPS ) )
		{
			if ( _isHardware ) QueryPerformanceCounter( (LARGE_INTEGER*) &_curTime );
			else _curTime = timeGetTime();

			//마지막 시간과 현재 시간의 경과량
			_timeElapsed = ( _curTime - _lastTime ) * _timeScale;
		}
	}

	_lastTime = _curTime;
	_FPSFrameCount++;
	_FPSTimeElapsed += _timeElapsed;
	_worldTime += _timeElapsed;

	//프레임 초기화 1초마다 진행
	if ( _FPSTimeElapsed > 1.f )
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.f;
	}
}

unsigned long timer::GetFrameRate( char * str ) const
{
	if ( str != NULL )
	{
		wsprintf( str, "FPS : %d", _frameRate );
	}

	return _frameRate;
}
