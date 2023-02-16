#pragma once
#include "gameNode.h"
#include <vector>
#include "minion.h"
#include "bullets.h"
#include "progresBar.h"

class player;//상호참조를 위한 전방선언

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;


	vEnemy _vMinion; //클래스형으로 동적할당 벡터형 미니언 변수
	viEnemy _viMinion;//반복자 미니언 변수

	enemy* _Boss;// 보스
	image* _end;
	bulletE* _bulletE;	 // 일반 적 탄환 동적 할당
	bulletB1* _bulletB1; // 보스 기본 탄환 동적 할당
	bulletB2* _bulletB2; // 보스 가변 탄환 동적 할당
	progresBar* _hpBar;	 // 보스 HP바

	player* _player; //상호참조를 위한 동적할당(할당만 해줌)

	int _maxHP;			// 최대 HP
	int _currentHP;		// 현재 HP
	int _spawnCount;	// 스폰 간격 카운트
	int _count;
	int _hitCount;
	float _angleCount;	// 각도 카운트
	bool _bossLive;		// 보스 등장 여부 카운트
	bool _hit;
	TCHAR _text[128];

public:

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	void SetMinion(int setType); // 적 종류 세팅
	void SetBoss(void);			 // 보스 세팅

	void BulletFire(void);	// 기본 적 탄환
	void BulletFire1(void);	// 보스 기본 탄환
	void BulletFire2(void);	// 보스 가변 탄환

	vector<enemy*> GetVMinion(void) { return _vMinion; }
	vector<enemy*>::iterator GetVIMinion(void) { return _viMinion; }

	void RemoveMinion(int arrNum);	//적 삭제 함수
	void Collision(void);			//적 충돌체크 함수

	inline progresBar* GetHPBar() { return _hpBar; } // 프로그레스 바 반환값

	inline int GetHP() { return _currentHP; }		// 프로그레스 HP 겟함수
	inline void SetHP(int hp) { _currentHP = hp; }	// 프로그레스 HP 셋함수
	inline int GetBossLive() { return _bossLive; }	// 보스 등장여부 겟함수
	void setplayerMemoryAddressLink(player* player) { _player = player; } //상호 참조를 위한 연결( 메인게임함수에서 실행)

	enemyManager();
	~enemyManager();
};

