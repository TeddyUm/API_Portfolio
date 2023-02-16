#include "stdafx.h"
#include "gameEvent.h"


gameEvent::gameEvent()
{
}


gameEvent::~gameEvent()
{
}

HRESULT gameEvent::Init(void)
{
	_opening = IMAGE_Mgr->AddImage("opening", "image/intro.bmp", WINSIZEX, WINSIZEY, false, false);
	_gameStart = false;

	return S_OK;
}
void gameEvent::Release(void)
{

}
void gameEvent::Update(void)
{
	while (true)
	{
		if (KEY->IsStayKeyDown(VK_LEFT))
		{
			_gameStart = true;
		}

		if (_gameStart == false)
		{
			break;
		}
	}
}
void gameEvent::Render(void)
{
	if (_gameStart == false)
	{
		_opening->Render(GetMemDC(), WINSIZEX, WINSIZEY);
	}
}
