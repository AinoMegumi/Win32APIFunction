#include "stdafx.h"
#include "Win32ExceptionA.hpp"
#include <iostream>

Win32ExceptionA::Win32ExceptionA() : ExceptionMessage(this->GetErrorMessagePtr()){}

Win32ExceptionA::Win32ExceptionA(const DWORD ErrorCode) : ExceptionMessage(this->GetErrorMessagePtr(ErrorCode)){}

Win32ExceptionA::Win32ExceptionA(const HRESULT ErrorCode) : ExceptionMessage(this->GetErrorMessagePtr(ErrorCode)) {}

Win32ExceptionA::Win32ExceptionA(const std::string ExceptionAddMessage)
	: ExceptionMessage(std::make_shared<std::string>(ExceptionAddMessage + "\n" + this->GetErrorMessage())) {}

Win32ExceptionA::Win32ExceptionA(const std::string ExceptionAddMessage, const DWORD ErrorCode)
	: ExceptionMessage(std::make_shared<std::string>(ExceptionAddMessage + "\n" + this->GetErrorMessage(ErrorCode))) {}

Win32ExceptionA::Win32ExceptionA(const std::string ExceptionAddMessage, const HRESULT ErrorCode)
	: ExceptionMessage(std::make_shared<std::string>(ExceptionAddMessage + "\n" + this->GetErrorMessage(ErrorCode))) {}

std::shared_ptr<std::string> Win32ExceptionA::GetErrorMessagePtr() const {
	return std::make_shared<std::string>(this->GetErrorMessage());
}

std::shared_ptr<std::string> Win32ExceptionA::GetErrorMessagePtr(const DWORD ErrorCode) const {
	return std::make_shared<std::string>(this->GetErrorMessage(ErrorCode));
}

std::shared_ptr<std::string> Win32ExceptionA::GetErrorMessagePtr(const HRESULT ErrorCode) const {
	return std::make_shared<std::string>(this->GetErrorMessage(ErrorCode));
}

std::string Win32ExceptionA::GetErrorMessage(const DWORD ErrorCode) const {
	char* lpMessageBuffer = nullptr;
	const DWORD length = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, ErrorCode, LANG_USER_DEFAULT, (LPSTR)&lpMessageBuffer, 0, NULL);
	if (length == 0) throw std::runtime_error("エラーメッセージ取得時にエラーが発生しました。\nエラーコード : " + std::to_string(GetLastError()));
	DWORD i = length - 3;
	for (; '\r' != lpMessageBuffer[i] && '\n' != lpMessageBuffer[i] && '\0' != lpMessageBuffer[i]; i++);//改行文字削除
	lpMessageBuffer[i] = '\0';
	std::string s = "エラーコード : " + std::to_string(ErrorCode) + "　" + lpMessageBuffer;
	LocalFree(lpMessageBuffer);
	return s;
}

std::string Win32ExceptionA::GetErrorMessage(const HRESULT ErrorCode) const {
	char* lpMessageBuffer = nullptr;
	const DWORD length = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, ErrorCode, LANG_USER_DEFAULT, (LPSTR)&lpMessageBuffer, 0, NULL);
	if (length == 0) throw std::runtime_error("エラーメッセージ取得時にエラーが発生しました。\nエラーコード : " + std::to_string(GetLastError()));
	DWORD i = length - 3;
	for (; '\r' != lpMessageBuffer[i] && '\n' != lpMessageBuffer[i] && '\0' != lpMessageBuffer[i]; i++);//改行文字削除
	lpMessageBuffer[i] = '\0';
	std::string s = "エラーコード : " + std::to_string(ErrorCode) + "　" + lpMessageBuffer;
	LocalFree(lpMessageBuffer);
	return s;
}

std::string Win32ExceptionA::GetErrorMessage() const {
	const DWORD Code = GetLastError();
	return this->GetErrorMessage(Code);
}

const char* Win32ExceptionA::what() const {
	return this->ExceptionMessage->c_str();
}

int Win32ExceptionA::GraphOnMessageBox(HWND hWnd, LPCSTR lpCaption, UINT uType) const {
	return MessageBoxA(hWnd, this->what(), lpCaption, uType);
}

void Win32ExceptionA::GraphOnConsole() const {
	std::cout << this->what() << std::endl;
}
