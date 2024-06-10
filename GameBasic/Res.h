#pragma once

// 공통적으로 가져야 할 데이터

class Res {
private:
	wstring key;				// 고유 ID
	wstring strRelativePath;	// 리소스 상대 경로(폴더 내의 변하지 않는 경로)

public:
	Res();
	virtual ~Res();

	void SetKey(const wstring& _key) { key = _key; }
	void SetRelativePath(const wstring& _str) { strRelativePath = _str; }

	const wstring& GetKey() { return key; }
	const wstring& GetRelativePath() { return strRelativePath; }
};

