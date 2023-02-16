#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

player::player()
{
}


player::~player()
{
}

HRESULT player::Init()
{
	_reimu = IMAGE_Mgr->AddFrameImage("reimu", "image/playerMove.bmp", 150, 50, 3, 1, true, RGB(255, 255, 255));
	_rcPlayer = RectMakeCenter(CENTERX, 800, 10, 10);

	_bullet = new bullets;
	_bullet->Init(100, 1300);
	
	_state = isNormal;
	_speed = 5.f;
	_count = 0;

	return S_OK;
}
void player::Release(void)
{
}
void player::Update(void)
{
	_state = isNormal;	// 상태가 기본 상태 일때 프레임
	if (KEY->IsStayKeyDown(VK_LEFT) && (_rcPlayer.left > 20))
	{
		_rcPlayer.left -= _speed;
		_rcPlayer.right -= _speed;

		_state = isLeft;	// 왼쪽 이동 중 프레임
	}
	if (KEY->IsStayKeyDown(VK_RIGHT) && (_rcPlayer.right < WINSIZEX - 20))
	{
		_rcPlayer.left += _speed;
		_rcPlayer.right += _speed;

		_state = isRight;	// 오른쪽 이동 중 프레임
	}
	if (KEY->IsStayKeyDown(VK_UP) && (_rcPlayer.top > 20))
	{
		_rcPlayer.top -= _speed;
		_rcPlayer.bottom -= _speed;
	}
	if (KEY->IsStayKeyDown(VK_DOWN) && (_rcPlayer.bottom < WINSIZEY - 20))
	{
		_rcPlayer.top += _speed;
		_rcPlayer.bottom += _speed;
	}

	if (KEY->IsStayKeyDown(VK_SPACE))	// 탄 발사
	{
		if (_count > 3)
		{
			_bullet->BulletFire(_rcPlayer.left + 5, _rcPlayer.top - 20);
		}
		_count++;
		if (_count > 4) _count = 0;
	}

	_bullet->Update();
	Collision();
}
void player::Render(void)
{
	_reimu->FrameRender(GetMemDC(), _rcPlayer.left - 20, _rcPlayer.top - 20, _state, 0);
	//RectDraw(GetMemDC(), _rcPlayer);
	_bullet->Render();
}

void player::Collision()	// 충돌함수
{
	for (int i = 0; i < _bullet->GetVBullet().size(); i++)
	{
		for (int j = 0; j < _em->GetVMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_bullet->GetVBullet()[i].rc,
				&_em->GetVMinion()[j]->GetRect()))
			{		
				if (_em->GetBossLive() == 0)
				{
					_bullet->RemoveBullet(i);
					_em->RemoveMinion(j);
				}
				else if (_em->GetBossLive() == 1)
				{
					_bullet->RemoveBullet(i);

					_em->SetHP(_em->GetHP() - 7);
					{
						if (_em->GetHP() < 0)
						{
							_em->RemoveMinion(j);
						}
					}
				}
				break;
			}
		}
	}
} 