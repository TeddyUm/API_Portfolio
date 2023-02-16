#pragma once

template<typename T>
class singletonBase
{
protected:
	//싱글톤 인스턴스 선언
	static T* singleton;

	//숙제0. static 변수의 특징
	//숙제1. 클래스의 static 멤버 변수의 특징
	//숙제2. 클래스의 static 멤버 함수의 특징

	singletonBase( void ) {}
	~singletonBase( void ) {}

public:
	static T* GetSingleton( void );
	void ReleaseSingleton( void );

};

//싱글톤 초기화
template<typename T>
T* singletonBase<T>::singleton = 0;

//싱글톤 값 가져오기
template<typename T>
T* singletonBase<T>::GetSingleton()
{
	if ( singleton ) return singleton;
	else return singleton = new T;
}

//싱글톤 메모리 해제
template<typename T>
void singletonBase<T>::ReleaseSingleton()
{
	if ( singleton )
	{
		delete singleton;
		singleton = 0;
	}
}