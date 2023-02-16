#pragma once

#include "singletonBase.h"
#include "image.h"
#include <map>

class imageManager : public singletonBase<imageManager>
{
public:
	typedef map<string, image*> mapImageList;
	typedef map<string, image*>::iterator mapImageIter;

private:
	mapImageList _mImageList;

public:
	imageManager();
	~imageManager();

	HRESULT Init();
	void Release();

	image* AddImage( string strKey, int width, int height );

	image* AddImage( string strKey, const DWORD resID,
		int width, int height, BOOL trans, COLORREF transColor );

	image* AddImage( string strKey, const char* fileName,
		float x, float y, int width, int height, BOOL trans, COLORREF transColor );

	image* AddImage( string strKey, const char* fileName,
		int width, int height, BOOL trans, COLORREF transColor );

	image* AddFrameImage( string strkey, const char* fileName, float x, float y,
		int width, int height, int frameX, int frameY, bool trans, COLORREF transColor );

	image* AddFrameImage( string strkey, const char* fileName, int width, int height,
		int frameX, int frameY, bool trans, COLORREF transColor );

	//이미지 찾는 함수
	image* FindImage( string strKey );

	//이미지 지운다
	BOOL DeleteImage( string strKey );

	//전체 이미지 지운다
	BOOL DeleteAll();

	//렌더 함수
	void Render( string strKey, HDC hdc );
	void Render( string strKey, HDC hdc, int destX, int destY);
	void Render( string strKey, HDC hdc, int destX, int destY, int sourX, int sourY,
		int sourWidth, int sourHeight);

	void AlphaRender( string strkey, HDC hdc, BYTE alpha );
	void AlphaRender( string strkey, HDC hdc, int destX, int destY, BYTE alpha);
	void AlphaRender( string strKey, HDC hdc, int destX, int destY, int sourX, int sourY,
		int sourWidth, int sourHeight, BYTE alpha);

	void FrameRender( string strKey, HDC hdc, int destX, int destY );
	void FrameRender( string strKey, HDC hdc, int destX, int destY, 
		int currentFrameX, int currentFrameY);

	void LoopRender( string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY );
};

