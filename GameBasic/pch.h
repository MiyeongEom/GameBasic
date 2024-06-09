#pragma once
#include <windows.h>
#include <iostream>

#include <vector>
using std::vector;

#include <map>
using std::map;
using std::make_pair;

#include <string>
using std::string;
using std::wstring;

#include <math.h>
#include <assert.h>

#pragma comment(lib, "Msimg32.lib")

#include "define.h"
#include "struct.h"
#include "func.h"

#ifdef _UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif