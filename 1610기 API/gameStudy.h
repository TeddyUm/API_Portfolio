#pragma once
#pragma comment (lib, "winmm.lib")

#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
#include <MMSystem.h>

class gameStudy : public gameNode
{
private:
	image* _background;
	image* _intro;
	player* _player;
	enemyManager* _em;

	bool _gameStart;
	int _offsetX, _offsetY;

public:
	gameStudy();
	virtual ~gameStudy();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render( void );

	//void Collision();
};

