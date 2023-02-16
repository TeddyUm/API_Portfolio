#include "stdafx.h"
#include "imageManager.h"


imageManager::imageManager()
{
}


imageManager::~imageManager()
{
}

HRESULT imageManager::Init()
{


	return S_OK;
}

void imageManager::Release()
{
	DeleteAll();
}

image * imageManager::AddImage( string strKey, int width, int height )
{
	//동일한 이미지가 있는지 체크
	image* img = FindImage( strKey );

	//키 값과 같은 이미지가 있으면 추가 하지 않고 기존의 이미지를 불러오자
	if ( img ) return img;

	//이미지 생성
	img = new image;

	//이미지가 제대로 초기화 되지 않았으면 처리
	if ( FAILED( img->Init( width, height ) ) )
	{
		SAFE_DELETE( img );
		return NULL;
	}

	//생성된 이미지를 맵에 추가해주자
	_mImageList.insert( make_pair( strKey, img ) );

	return img;
}

image * imageManager::AddImage( string strKey, const DWORD resID, 
	int width, int height, BOOL trans, COLORREF transColor )
{
	//동일한 이미지가 있는지 체크
	image* img = FindImage( strKey );

	//키 값과 같은 이미지가 있으면 추가 하지 않고 기존의 이미지를 불러오자
	if ( img ) return img;

	//이미지 생성
	img = new image;

	//이미지가 제대로 초기화 되지 않았으면 처리
	if ( FAILED( img->Init( resID, width, height, trans, transColor ) ) )
	{
		SAFE_DELETE( img );
		return NULL;
	}

	//생성된 이미지를 맵에 추가해주자
	_mImageList.insert( make_pair( strKey, img ) );

	return img;
}

image * imageManager::AddImage( string strKey, const char * fileName, 
	float x, float y, int width, int height, BOOL trans, COLORREF transColor )
{
	//동일한 이미지가 있는지 체크
	image* img = FindImage( strKey );

	//키 값과 같은 이미지가 있으면 추가 하지 않고 기존의 이미지를 불러오자
	if ( img ) return img;

	//이미지 생성
	img = new image;

	//이미지가 제대로 초기화 되지 않았으면 처리
	if ( FAILED( img->Init( fileName, x, y, width, height, trans, transColor ) ) )
	{
		SAFE_DELETE( img );
		return NULL;
	}

	//생성된 이미지를 맵에 추가해주자
	_mImageList.insert( make_pair( strKey, img ) );

	return img;
}

image * imageManager::AddImage( string strKey, const char * fileName, 
	int width, int height, BOOL trans, COLORREF transColor )
{
	//동일한 이미지가 있는지 체크
	image* img = FindImage( strKey );

	//키 값과 같은 이미지가 있으면 추가 하지 않고 기존의 이미지를 불러오자
	if ( img ) return img;

	//이미지 생성
	img = new image;

	//이미지가 제대로 초기화 되지 않았으면 처리
	if ( FAILED( img->Init( fileName, width, height, trans, transColor ) ) )
	{
		SAFE_DELETE( img );
		return NULL;
	}

	//생성된 이미지를 맵에 추가해주자
	_mImageList.insert( make_pair( strKey, img ) );

	return img;
}

image * imageManager::AddFrameImage( string strKey, const char * fileName, float x, float y, 
	int width, int height, int frameX, int frameY, bool trans, COLORREF transColor )
{
	//동일한 이미지가 있는지 체크
	image* img = FindImage( strKey );

	//키 값과 같은 이미지가 있으면 추가 하지 않고 기존의 이미지를 불러오자
	if ( img ) return img;

	//이미지 생성
	img = new image;

	//이미지가 제대로 초기화 되지 않았으면 처리
	if ( FAILED( img->Init( fileName, x, y, width, height, frameX, frameY, trans, transColor ) ) )
	{
		SAFE_DELETE( img );
		return NULL;
	}

	//생성된 이미지를 맵에 추가해주자
	_mImageList.insert( make_pair( strKey, img ) );

	return img;
}

image * imageManager::AddFrameImage( string strKey, const char * fileName, 
	int width, int height, int frameX, int frameY, bool trans, COLORREF transColor )
{
	//동일한 이미지가 있는지 체크
	image* img = FindImage( strKey );

	//키 값과 같은 이미지가 있으면 추가 하지 않고 기존의 이미지를 불러오자
	if ( img ) return img;

	//이미지 생성
	img = new image;

	//이미지가 제대로 초기화 되지 않았으면 처리
	if ( FAILED( img->Init( fileName, width, height, frameX, frameY, trans, transColor ) ) )
	{
		SAFE_DELETE( img );
		return NULL;
	}

	//생성된 이미지를 맵에 추가해주자
	_mImageList.insert( make_pair( strKey, img ) );

	return img;
}

image * imageManager::FindImage( string strKey )
{
	//해당 키가 있는지 검사
	mapImageIter iter = _mImageList.find( strKey );

	if ( iter != _mImageList.end() )
	{
		return iter->second;
	}

	return NULL;
}

BOOL imageManager::DeleteImage( string strKey )
{
	//해당 키 일단 검색
	mapImageIter iter = _mImageList.find( strKey );

	//키를 찾았으면
	if ( iter != _mImageList.end() )
	{
		//이미지 해제
		iter->second->Release();

		//메모리도 해제
		SAFE_DELETE( iter->second );

		//맵에 있는 방도 철거하자
		_mImageList.erase( iter );

		return true;
	}

	return false;
}

BOOL imageManager::DeleteAll()
{
	mapImageIter iter = _mImageList.begin();

	for ( ; iter != _mImageList.end(); )
	{
		if ( iter->second != NULL )
		{
			iter->second->Release();
			SAFE_DELETE( iter->second );
			iter = _mImageList.erase( iter );//반복문에서 erase 사용할 때는 증감문 사용X
		}
		else
		{
			++iter;
		}
	}

	_mImageList.clear();

	return true;
}

void imageManager::Render( string strKey, HDC hdc )
{
	image* img = FindImage( strKey );
	if ( img ) img->Render( hdc );
}

void imageManager::Render( string strKey, HDC hdc, int destX, int destY )
{
	image* img = FindImage( strKey );
	if ( img ) img->Render( hdc, destX, destY );
}

void imageManager::Render( string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight )
{
	image* img = FindImage( strKey );
	if ( img ) img->Render( hdc, destX, destY, sourX, sourY, sourWidth, sourHeight );
}

void imageManager::AlphaRender( string strKey, HDC hdc, BYTE alpha )
{
	image* img = FindImage( strKey );
	if ( img ) img->AlphaRender( hdc, alpha );
}

void imageManager::AlphaRender( string strKey, HDC hdc, int destX, int destY, BYTE alpha )
{
	image* img = FindImage( strKey );
	if ( img ) img->AlphaRender( hdc, destX, destY, alpha );
}

void imageManager::AlphaRender( string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha )
{
	image* img = FindImage( strKey );
	if ( img ) img->AlphaRender( hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void imageManager::FrameRender( string strKey, HDC hdc, int destX, int destY )
{
	image* img = FindImage( strKey );
	if ( img ) img->FrameRender( hdc , destX, destY);
}

void imageManager::FrameRender( string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY )
{
	image* img = FindImage( strKey );
	if ( img ) img->FrameRender( hdc, destX, destY, currentFrameX, currentFrameY );
}

void imageManager::LoopRender( string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY )
{
	image* img = FindImage( strKey );
	if ( img ) img->LoopRender( hdc, drawArea, offsetX, offsetY );
}
