#pragma once
#include "gameNode.h"
#include "bullets.h"

enum tagState		//플레이어 상태
{
	isNormal,
	isLeft,
	isRight
};

class enemyManager;

class player : public gameNode
{
private:
	image* _reimu;
	bullets* _bullet;

	RECT _rcPlayer;
	tagState _state;
	float _speed;
	int _count; 

	enemyManager* _em;

public:
	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	void Collision();

	inline bullets* GetBullet() { return _bullet; }
	inline image* GetPlayerImage() { return _reimu; }

	inline RECT GetPlayerRc() { return _rcPlayer; }

	inline void setEmMemoryAddressLink(enemyManager* em) { _em = em; }

	player();
	~player();
};

