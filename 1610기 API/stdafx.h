// stdafx.h : ���� ��������� ���� ��������� �ʴ� 
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�. 
// 


#pragma once 


//====================================================== 
// ## ������� ���ش� ## 
//====================================================== 


#include "targetver.h" 


#define WIN32_LEAN_AND_MEAN //MFC�� �ƴ� ���� ���α׷��� ��쿡�� 
//WIN32_LEAN_AND_MEAN�� ������ commdlg.h��� 
//�ʿ���� ��������� ��Ŭ��� ���� �ʰ� ���ش�. 

#include <windows.h>    //������ ������� ��Ŭ��� 
#include <stdio.h>      //���Ĵٵ� ����� ��� ��Ŭ���~ (printf, scanf ���..) 
#include <tchar.h>      //�����쿡�� ����� ���ڿ� ��� ��� ��Ŭ���~ 
						//MBCS (Multi Byte Character Set) 
						//-> ������ ����Ѵ� ��Ƽ����Ʈ ������ ���ڿ�~ 
						//WBCS (Wide Byte Character Set) 
						//-> ��� ���ڸ� 2����Ʈ�� ó��~~, �����ڵ� ���...

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "utils.h"
#include "imageManager.h"
#include "timeManager.h"


using namespace MY_UTIL;

//====================================================== 
// ## �����ι� ���ش� ## 
//====================================================== 
#define WINNAME ( LPTSTR)(TEXT ("APIWindow")) 
#define WINSTARTX 600 
#define WINSTARTY 0 
#define WINSIZEX 768
#define WINSIZEY 1000
#define CENTERX (WINSIZEX / 2)
#define CENTERY (WINSIZEY / 2)
#define WINSTYLE WS_CAPTION | WS_SYSMENU 


#define SAFE_DELETE(p)			{ if(p) { delete (p);     (p)= NULL; } } 
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete [] (p);  (p)= NULL; } } 
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p)= NULL; } } 
#define SAFE_REL_DEL(p)			{ if(p) { (p)->Release(); delete(p); (p) = NULL;}}

//====================================================== 
// ## �̱��� ��ũ�� ���ش� ## 
//====================================================== 
#define RND randomFunction::GetSingleton()
#define KEY keyManager::GetSingleton()
#define IMAGE_Mgr imageManager::GetSingleton()
#define TIMEMGR timeManager::GetSingleton()

//====================================================== 
// ## �������� ���ش� ## 
//====================================================== 
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;