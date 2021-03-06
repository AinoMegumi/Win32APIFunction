// Win32LetterConvert.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "../Win32Exception/Win32Exception.hpp"
#include "Win32LetterConvert.hpp"
#include <Windows.h>
#include <string>
#ifdef _DEBUG
#pragma comment(lib, "Win32ExceptionDebug.lib")
#else
#pragma comment(lib, "Win32ExceptionRelease.lib")
#endif

std::string WStringToString(std::wstring str) {
	int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, str.c_str(), -1, (char *)NULL, 0, NULL, NULL);
	if (0 == iBufferSize) throw Win32ExceptionA();
	char* cpMultiByte = new char[iBufferSize];
	WideCharToMultiByte(CP_OEMCP, 0, str.c_str(), -1, cpMultiByte, iBufferSize, NULL, NULL);
	std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);
	delete[] cpMultiByte;
	return oRet;
}

std::wstring StringToWString(std::string str) {
	const int iBufferSize = MultiByteToWideChar(CP_OEMCP, 0, str.c_str(), -1, (wchar_t*)NULL, 0);
	if (0 == iBufferSize) throw Win32ExceptionW();
	wchar_t* cpWideChar = new wchar_t[iBufferSize];
	MultiByteToWideChar(CP_OEMCP, 0, str.c_str(), -1, cpWideChar, iBufferSize);
	std::wstring oRet(cpWideChar, cpWideChar + iBufferSize - 1);
	delete[] cpWideChar;
	return oRet;
}

