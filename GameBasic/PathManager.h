#pragma once
class PathManager{
	SINGLE(PathManager);
private:
	wchar_t		contentPath[255];

public:
	void init();
	const wchar_t* GetContentPath() { return contentPath; }
};

