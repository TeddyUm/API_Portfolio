#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::Init( int x, int y, int width, int height )
{
	_x = x;
	_y = y;

	_rcProgress = RectMake( x, y, width, height );

	_progressBarFront = IMAGE_Mgr->AddImage( "barFront", "image/hpBarTop.bmp", x, y, width, height, true, 0xff00ff );

	_progressBarBack = IMAGE_Mgr->AddImage( "barBack", "image/hpBarBottom.bmp", x, y, width, height, true, 0xff00ff );

	_width = (float)_progressBarFront->GetWidth();

	return S_OK;
}

void progressBar::Release()
{
}

void progressBar::Update()
{
	_rcProgress = RectMake( _x, _y, _progressBarBack->GetWidth(), _progressBarBack->GetHeight() );
}

void progressBar::Render()
{
	IMAGE_Mgr->Render( "barBack", GetMemDC(), _rcProgress.left, _rcProgress.top );

	IMAGE_Mgr->Render( "barFront", GetMemDC(), _rcProgress.left, _rcProgress.top,
		0, 0, _width, _progressBarFront->GetHeight() );
}

void progressBar::SetGauge( float currentGauge, float maxGauge )
{
	_width = (currentGauge / maxGauge) * (float)_progressBarBack->GetWidth();
}
