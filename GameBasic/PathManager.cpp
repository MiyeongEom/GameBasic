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
	GetCurrentDirectory(255, contentPath);	

	int len = (int)wcslen(contentPath);
	for (int i = len - 1; 0 <= i; --i) {
		if ('\\' == contentPath[i]) {
			contentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(contentPath, 255, L"\\bin\\Content\\");

	SetWindowText(Core::Instance()->getMainHandle(), contentPath);
}