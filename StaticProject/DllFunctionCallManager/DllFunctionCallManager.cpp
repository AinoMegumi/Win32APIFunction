// DllFunctionCallManager.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "../Win32Exception/Win32Exception.hpp"
#include "../Win32LetterConvert/Win32LetterConvert.hpp"
#include "DllFunctionCallManager.hpp"
#include <string>
#ifdef _DEBUG
#pragma comment(lib, "Win32ExceptionDebug.lib")
#pragma comment(lib, "Win32LetterConvertDebug.lib")
#else
#pragma comment(lib, "Win32ExceptionRelease.lib")
#pragma comment(lib, "Win32LetterConvertRelease.lib")
#endif

DllFunctionCallManager::DllFunctionCallManager(const std::string ModuleName) 
	: hModule(LoadLibraryA(ModuleName.c_str())) {
	if (this->hModule == NULL) throw Win32ExceptionA();
}

DllFunctionCallManager::DllFunctionCallManager(const std::wstring ModuleName)
	: hModule(LoadLibraryW(ModuleName.c_str())) { 
	if (this->hModule == NULL) throw Win32ExceptionW(); 
}

DllFunctionCallManager::DllFunctionCallManager(DllFunctionCallManager&& dcm) 
	: hModule(std::move(dcm.hModule)) {	if (dcm.hModule != nullptr) dcm.hModule = nullptr; }

DllFunctionCallManager::~DllFunctionCallManager() { FreeLibrary(this->hModule); }

DllFunctionCallManager& DllFunctionCallManager::operator = (DllFunctionCallManager&& dcm) {
	this->hModule = std::move(dcm.hModule);
	if (dcm.hModule != nullptr) dcm.hModule = nullptr;
	return *this;
}

FARPROC DllFunctionCallManager::GetFunctionAddressImpl(const std::string& FunctionName) const {
	FARPROC func = GetProcAddress(this->hModule, FunctionName.c_str());
	if (NULL == func) throw Win32ExceptionA();
	return func;
}

FARPROC DllFunctionCallManager::GetFunctionAddressImpl(const std::wstring& FunctionName) const {
	return this->GetFunctionAddressImpl(WStringToString(FunctionName));
}
