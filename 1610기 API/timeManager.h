#pragma once

#include "singletonBase.h"
#include "timer.h"

class timeManager : public singletonBase<timeManager>
{
private:
	timer* _timer;


public:
	timeManager();
	~timeManager();

	HRESULT Init();
	void Release();
	void Update( float lock = 0.f );
	void Render( HDC hdc );

	//한 프레임
	inline float GetElapsedTime() const { return _timer->GetElapsedTime(); }
	inline float GetWorldTime() const { return _timer->GetWorldTime(); }
};

