#pragma once
#pragma once
#include "gameNode.h"

class gameEvent : public gameNode
{
private:
	image* _opening;
	RECT _rcReimu;
	RECT _rcMarisa;
	RECT _rcWindow;

	TCHAR str[128];

	bool _gameStart;


public:
	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	gameEvent();
	~gameEvent();
};

