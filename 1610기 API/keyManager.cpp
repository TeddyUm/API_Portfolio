#include "stdafx.h"
#include "keyManager.h"


keyManager::keyManager()
{
}


keyManager::~keyManager()
{
}

HRESULT keyManager::Init()
{
	for ( int i = 0; i < KEYMAX; i++ )
	{
		_keyDown[i] = false;
		_keyUp[i] = false;

		//_keyDown.set( i, false );
		//_keyUp.set( i, false );
	}

	return S_OK;
}

void keyManager::Release()
{
}

bool keyManager::IsOnceKeyDown( int key )
{
	if ( GetAsyncKeyState( key ) & 0x8000 )//눌려져 있는지 체크
	{
		if ( !_keyDown[key] )
		{
			_keyDown.set( key, true );
			return true;
		}
	}
	else _keyDown.set( key, false );

	return false;
}

bool keyManager::IsOnceKeyUp( int key )
{
	if ( GetAsyncKeyState( key ) & 0x8000 ) _keyUp.set( key, true );
	else 
	{
		if ( _keyUp[key] ) 
		{
			_keyUp.set( key, false );
			return true;
		}
	}

	return false;
}

bool keyManager::IsStayKeyDown( int key )
{
	if ( GetAsyncKeyState( key ) & 0x8000 ) return true;
	else return false;
}

bool keyManager::IsToggleKey( int key )
{
	if ( GetKeyState( key ) & 0x0001 ) return true;
	else return false;
}
