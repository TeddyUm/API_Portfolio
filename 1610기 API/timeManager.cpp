#include "stdafx.h"
#include "timeManager.h"


timeManager::timeManager() : _timer(NULL)
{
}


timeManager::~timeManager()
{
}

HRESULT timeManager::Init()
{
	_timer = new timer;
	_timer->Init();

	return S_OK;
}

void timeManager::Release()
{
	SAFE_DELETE( _timer );
}

void timeManager::Update( float lock )
{
	if ( _timer != NULL )
	{
		_timer->Tick( lock );
	}
}

void timeManager::Render( HDC hdc )
{
	char str[256];
	string strFrame;

	//글자 배경모드 ( TRANSPARENT : 투명, OPAQUE : 불투명(디폴트) )
	SetBkMode( hdc, TRANSPARENT );

	//글자 색상
	SetTextColor( hdc, RGB( 255, 100, 100 ) );

#ifdef _DEBUG
	{
		if ( _timer != NULL )
		{
			//프레임 찍어주자
			sprintf_s( str, "framePerSec : %d", _timer->GetFrameRate() );
			TextOut( hdc, 0, 0, str, strlen( str ) );

			//월드타임 찍어주자
			sprintf_s( str, "WorldTime : %f", _timer->GetWorldTime() );
			TextOut( hdc, 0, 20, str, strlen( str ) );

			//갱신 Tick 찍어주자
			sprintf_s( str, "elapsedTime : %f", _timer->GetElapsedTime() );
			TextOut( hdc, 0, 40, str, strlen( str ) );
		}
	}
#else
	{
		if ( _timer != NULL )
		{
			//프레임 찍어주자
			sprintf_s( str, "framePerSec : %d", _timer->GetFrameRate() );
			TextOut( hdc, 0, 0, str, strlen( str ) );
		}
	}

#endif


}
