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
	// ���� ���α׷��� ����Ǵ� ��ġ�� �˾ƿ��� �Լ��� �ִ�.
	GetCurrentDirectory(255, contentPath);	// ���� ��� ä����

	// ���� �߻� F5, Ctrl + F5 �� ��ΰ� �ٸ� -> ������Ʈ �Ӽ� - ����� ��� ����

	// ����������
	// -> bin\\content\\

	// ���ڿ��� �� �� �����غ��� (���� �̰��� ������ �Լ��� �ֱ��ѵ�)
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