#include "pch.h"
#include "PathManager.h"

#include "Core.h"

PathManager::PathManager()
	: contentPath{}
{

}

PathManager::~PathManager()
{

}

void PathManager::init()
{
	// 현재 프로그램이 실행되는 위치를 알아오는 함수가 있다.
	GetCurrentDirectory(255, contentPath);	// 현재 경로 채워짐

	// 문제 발생 F5, Ctrl + F5 가 경로가 다름 -> 프로젝트 속성 - 디버깅 경로 수정

	// 상위폴더로
	// -> bin\\content\\

	// 문자열로 한 번 구현해보자 (기존 이것을 얻어오는 함수가 있긴한데)
	int len = wcslen(contentPath);
	for (int i = len - 1; 0 <= i; --i) {
		if ('\\' == contentPath[i]) {
			contentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(contentPath, 255, L"\\bin\\Content\\");

	SetWindowText(Core::Instance()->getMainHandle(), contentPath);
}