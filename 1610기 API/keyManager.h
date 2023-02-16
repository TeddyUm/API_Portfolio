#pragma once

#include "singletonBase.h"
#include <bitset>

using namespace std;

#define KEYMAX 256

class keyManager : public singletonBase<keyManager>
{
private:
	bitset<KEYMAX> _keyDown;
	bitset<KEYMAX> _keyUp;

public:
	keyManager();
	~keyManager();

	HRESULT Init();
	void Release();

	bool IsOnceKeyDown( int key );
	bool IsOnceKeyUp( int key );
	bool IsStayKeyDown( int key );
	bool IsToggleKey( int key );

	bitset<KEYMAX> GetKeyUp() { return _keyUp; }
	bitset<KEYMAX> GetKeyDown() { return _keyDown; }

	void SetKeyDown( int key, bool state ) { _keyDown.set( key, state ); }
	void SetKeyUp( int key, bool state ) { _keyUp.set( key, state ); }
};