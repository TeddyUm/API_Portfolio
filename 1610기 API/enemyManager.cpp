#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"


enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::Init()
{
	// 이미지 초기화
	IMAGE_Mgr->AddFrameImage("boss", "image/boss.bmp", 0, 0, 65, 65, 1, 1, true, RGB(255, 255, 255));
	IMAGE_Mgr->AddFrameImage("fairy", "image/enemy.bmp", 0, 0, 40, 40, 1, 1, true, RGB(255, 255, 255));
	IMAGE_Mgr->AddFrameImage("bfairy", "image/enemyBlue.bmp", 0, 0, 40, 40, 1, 1, true, RGB(255, 255, 255));
	IMAGE_Mgr->AddFrameImage("gfairy", "image/enemyGreen.bmp", 0, 0, 40, 40, 1, 1, true, RGB(255, 255, 255));
	IMAGE_Mgr->AddFrameImage("end", "image/gameover.bmp", CENTERX - 150, CENTERY - 150, 300, 300, 1, 1, true, RGB(0, 0, 0));
	IMAGE_Mgr->AddImage("enemyBullet", "image/enemyNormalBullet.bmp", 15, 15, true, RGB(255, 255, 255));
	IMAGE_Mgr->AddImage("enemyBossBullet1", "image/bossStarBullet.bmp", 25, 25, true, RGB(255, 255, 255));
	IMAGE_Mgr->AddImage("enemyBossBullet2", "image/bossNormalBullet.bmp", 10, 20, true, RGB(255, 255, 255));

	// 동적할당 및 기본값설정
	_bulletE = new bulletE;
	_bulletE->Init("enemyBullet", 3000, 1200);
	_bulletB1 = new bulletB1;
	_bulletB1->Init("enemyBossBullet1", 3000, 1000);
	_bulletB2 = new bulletB2 ;
	_bulletB2->Init("enemyBossBullet2", 3000, 1000);
	_hpBar = new progresBar;
	_hpBar->Init(CENTERX - 250, 30 - 20, 500, 5);
	_end = IMAGE_Mgr->FindImage("end");

	_currentHP = _maxHP = 3000; // 현재 보스 HP 초기화
	
	_hit = false;
	_bossLive = 0;				// 보스 등장여부 초기화
	_count = 0;
	_hitCount = 0;
	return S_OK;
}
void enemyManager::Release()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		SAFE_DELETE((*_viMinion));
	}

	_vMinion.clear();
	SAFE_REL_DEL(_hpBar);
}
void enemyManager::Update()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->Update();

		// 적 이동 타입 설정
		if ((*_viMinion)->GetMoveType() == 1)(*_viMinion)->Move(1);	
		if ((*_viMinion)->GetMoveType() == 2)(*_viMinion)->Move(2);
		if ((*_viMinion)->GetMoveType() == 3)(*_viMinion)->Move(3);
		if ((*_viMinion)->GetMoveType() == 4)(*_viMinion)->Move(4);
		if ((*_viMinion)->GetMoveType() == 5)(*_viMinion)->Move(5);
		if ((*_viMinion)->GetMoveType() == 7)(*_viMinion)->Move(7);
	}

	_spawnCount++;	// 스폰 타이머 증가

	if (_spawnCount % 150 == 0 && _spawnCount< 3000) // 스폰 타이머에 맞게 적 등장
	{
		SetMinion(1);
	}

	if (_spawnCount > 800 && _spawnCount % 150 == 0 && _spawnCount< 3000) // 스폰 타이머에 맞게 적 등장
	{
		SetMinion(2);
		SetMinion(3);
	}

	if (_spawnCount > 1800 && _spawnCount % 75 == 0 && _spawnCount< 3000)
	{
		SetMinion(4);
	}

	if (_spawnCount % 3500 == 0 && _bossLive == 0)	// 일정 시간 지나면 보스 등장
	{
		SetBoss();
		_bossLive = 1;
		_hpBar->SetGauge(_currentHP, _maxHP);
	}

	BulletFire();	// 총알 발사 업데이트

	if (_bossLive == 1)	// 보스가 등장하면 보스 탄 발사
	{
		BulletFire1();
		_bulletB1->Update();
		if (_currentHP < 1500)	// HP가 절반 이하가 되면 2차 패턴 발사
		{
			BulletFire2();
			_bulletB2->Update();
		}
		if (_currentHP < 0)		// HP가 바닥이 되면 보스 탄 삭제
		{
			for (int i = 0; i < _bulletE->GetVBullet().size(); i++)
			{
				_bulletE->RemoveBullet(i);
				break;
			}
			for (int i = 0; i < _bulletB1->GetVBullet().size(); i++)
			{
				_bulletB1->RemoveBullet(i);
				break;
			}
			for (int i = 0; i < _bulletB2->GetVBullet().size(); i++)
			{
				_bulletB2->RemoveBullet(i);
				break;
			}
		}
	}
	_bulletE->Update(); // 일반 탄 업데이트

	_hpBar->SetGauge(_currentHP, _maxHP);	// 프로그레스 게이지 설정
	_hpBar->Update();	// 프로그레스 게이지 업데이트
	Collision();		// 충돌 함수 가동
}
void enemyManager::Render()
{
	HFONT hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));
	HFONT OldFont = (HFONT)SelectObject(GetMemDC(), hFont);
	SetTextColor(GetMemDC(), RGB(250, 250, 50));
	SetBkMode(GetMemDC(), TRANSPARENT);

	// 탄 렌더
	_bulletE->Render();
	_bulletB1->Render();
	_bulletB2->Render();

	wsprintf(_text, TEXT("Hit Count  :  %d"), _hitCount);
	TextOut(GetMemDC(), WINSIZEX - 200, 100, _text, lstrlen(_text));

	// 적 렌더
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->Render();
	}

	if (_hit == true)
	{
		_count++;
		if (_count < 50)
		{
			TextOut(GetMemDC(), _player->GetPlayerRc().left, _player->GetPlayerRc().top - 50, "Hit!!", lstrlen("Hit!!"));
		}
		else
		{
			_count = 0;
			_hit = false;
		}
	}

	// 보스가 등장하면 프로그레스 바 생성
	if (_bossLive == 1)
	{
		_hpBar->Render();
	}

	if (_currentHP < 0)
	{
		_end->Render(GetMemDC());
	}
}

void enemyManager::SetMinion(int setType)
{
	// 적 타입에 따라 위치 설정
	if (setType == 1) // 뭉쳐서 나오는 적
	{
		int rndX = RND->GetFromIntTo(100, WINSIZEX - 100);
		int ranEnemy = RND->GetFromIntTo(1, 5);

		for (int i = 0; i < 5; i++)
		{
			if (i % 2 == 0)
			{
				enemy* enemy1;
				enemy1 = new minion;
				enemy1->Init("fairy", PointMake(rndX, -100 - (i * 65)), 1);
				_vMinion.push_back(enemy1);
			}
			else 
			{
				enemy* enemy1;
				enemy1 = new minion;
				enemy1->Init("fairy", PointMake(rndX - 80, -100 - (i * 65)), 2);
				_vMinion.push_back(enemy1);
			}
		}
	}

	if (setType == 2)	// 옆에서 나오는 적
	{
		int rndY = RND->GetFromIntTo(50, WINSIZEY - 200);
		enemy* enemy2;
		enemy2 = new minion;
		enemy2->Init("bfairy", PointMake(-50, rndY), 3);
		_vMinion.push_back(enemy2);
	}

	if (setType == 3)	// 옆에서 나오는 적
	{
		int rndY = RND->GetFromIntTo(50, WINSIZEY - 200);
		enemy* enemy2;
		enemy2 = new minion;
		enemy2->Init("bfairy", PointMake(WINSIZEX + 50, rndY), 4);
		_vMinion.push_back(enemy2);
	}

	if (setType == 4)	// 빠르게 내려오는 적
	{
		int rndX = RND->GetFromIntTo(50, WINSIZEX - 50);
		enemy* enemy3;
		enemy3 = new minion;
		enemy3->Init("gfairy", PointMake(rndX, -50), 5);
		_vMinion.push_back(enemy3);

	}
}
void enemyManager::SetBoss(void)	// 보스 세팅
{
	enemy* boss1;
	boss1 = new boss;
	boss1->Init("boss", PointMake(WINSIZEX / 2, -50), 7);

	_vMinion.push_back(boss1);
}

void enemyManager::BulletFire(void)	// 적이 발사하는 유도탄
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->BulletCountFireN())
		{
			RECT rc = (*_viMinion)->GetRect();
			_bulletE->BulletFire(
				(rc.right + rc.left) / 2,  
				rc.bottom - 10,				
				MY_UTIL::GetAngle((rc.right + rc.left) / 2, rc.bottom - 10,
					_player->GetPlayerRc().left,
					_player->GetPlayerRc().top));
		}
	}
}

void enemyManager::BulletFire1(void)// 보스 탄막
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->BulletCountFireB1())
		{
			RECT rc = (*_viMinion)->GetRect();
			_bulletB1->BulletFire(
				(rc.right + rc.left) / 2,  
				rc.bottom - 20,				
				0, 0.1f, 0.01);
		}
	}
}

void enemyManager::BulletFire2(void)// 보스 2차 탄막
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->BulletCountFireB2())
		{
			RECT rc = (*_viMinion)->GetRect();
			_bulletB2->BulletFire(
				(rc.right + rc.left) / 2, 
				rc.bottom - 20,				
				RND->GetFromFloatTo(4.f, 5.5f), 0.f, 0.f);
		}
	}
}



void enemyManager::RemoveMinion(int arrNum)	// 적 삭제 함수
{
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin() + arrNum);
}
void enemyManager::Collision(void)
{
	for (int i = 0; i < _bulletE->GetVBullet().size(); i++)	//일반 총알 충돌체크
	{
		RECT rc;
		if (IntersectRect(&rc, &_bulletE->GetVBullet()[i].rc,
			&_player->GetPlayerRc()))
		{
			_hit = true;
			_hitCount++;
			_bulletE->RemoveBullet(i);
			break;
		}
	}

	for (int i = 0; i < _bulletB1->GetVBullet().size(); i++)//보스 1차 총알 충돌체크
	{
		RECT rc;
		if (IntersectRect(&rc, &_bulletB1->GetVBullet()[i].rc,
			&_player->GetPlayerRc()))
		{
			_hit = true;
			_hitCount++;
			_bulletB1->RemoveBullet(i);
			break;
		}
	}

	for (int i = 0; i < _bulletB2->GetVBullet().size(); i++)//보스 2차 총알 충돌체크
	{
		RECT rc2;
		if (IntersectRect(&rc2, &_bulletB2->GetVBullet()[i].rc,
			&_player->GetPlayerRc()))
		{
			_hit = true;
			_hitCount++;
			_bulletB2->RemoveBullet(i);
			break;
		}
	}

	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)// 미니언 삭제
	{
		if (WINSIZEY + 100 < (*_viMinion)->GetRect().bottom || WINSIZEX + 100 < (*_viMinion)->GetRect().right || -100 > (*_viMinion)->GetRect().left)
		{
			_vMinion.erase(_viMinion); 
			break;
		}
	}
}