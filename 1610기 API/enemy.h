#pragma once
#include "gameNode.h"

class enemy : public gameNode
{
protected:
	image* _image;
	RECT _rc;

	int _currentFrameX;			//에너미 현재 프레임X   
	int _currentFrameY;			//에너미 현재 프레임Y

	int _count;					//발사 딜레이를 위한 카운트   
	int _fireCountNormal;		//발사 시간을 위한 카운트   
	int _fireCountBoss1;		//발사 시간을 위한 카운트  
	int _fireCountBoss2;		//발사 시간을 위한 카운트
	int _rndFireTimeN;			//랜덤하게 발사시간을 조절할 카운트
	int _rndFireTimeB1;			//랜덤하게 발사시간을 조절할 카운트
	int _rndFireTimeB2;			//랜덤하게 발사시간을 조절할 카운트
	int _countMove;				//움직임중 방향을 바꿀 간격 카운트
	int _countMoveType;			//카운터 후 이동 체인지(큰타입안에서 카운터후 변경되는 타입)
	int _moveType;              //에너미의 움직임 타입(큰타입)
	int _bulletTyep;			//에너미의 총알 타입

	float aX;
	float aN;

public:
	HRESULT Init(const char* imageName, POINT position, int moveType);
	void Release(void);
	void Update(void);
	void Render(void);

	void Move(int moveType);		//적 움직임 함수
	void Draw(void);				//렌더 함수
	bool BulletCountFireN();		// 일반 탄 발사 카운트 함수
	bool BulletCountFireB1();		// 보스 탄 발사 카운트 함수
	bool BulletCountFireB2();		// 보스 2차 탄 발사 카운트 함수

	RECT GetRect() { return _rc; }				// 렉트 겟 함수
	int GetMoveType() { return _moveType; }		// 무브타입 겟 함수
	int GetBulletType() { return _bulletTyep; } // 총알타입 겟 함수
	image* GetImage() { return _image; }		// 이미지 겟 함수

	enemy();
	~enemy();
};

