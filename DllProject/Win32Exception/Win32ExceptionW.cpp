#include "stdafx.h"
#include "Win32ExceptionW.hpp"
#include <iostream>

Win32ExceptionW::Win32ExceptionW() : ExceptionMessage(this->GetErrorMessagePtr()) {}

Win32ExceptionW::Win32ExceptionW(const DWORD ErrorCode) : ExceptionMessage(this->GetErrorMessagePtr(ErrorCode)) {}

Win32ExceptionW::Win32ExceptionW(const HRESULT ErrorCode) : ExceptionMessage(this->GetErrorMessagePtr(ErrorCode)) {}

Win32ExceptionW::Win32ExceptionW(const std::wstring ExceptionAddMessage)
	: ExceptionMessage(std::make_shared<std::wstring>(ExceptionAddMessage + L"\n" + this->GetErrorMessage())) {}

Win32ExceptionW::Win32ExceptionW(const std::wstring ExceptionAddMessage, const DWORD ErrorCode)
	: ExceptionMessage(std::make_shared<std::wstring>(ExceptionAddMessage + L"\n" + this->GetErrorMessage(ErrorCode))) {}

Win32ExceptionW::Win32ExceptionW(const std::wstring ExceptionAddMessage, const HRESULT ErrorCode)
	: ExceptionMessage(std::make_shared<std::wstring>(ExceptionAddMessage + L"\n" + this->GetErrorMessage(ErrorCode))) {}

std::shared_ptr<std::wstring> Win32ExceptionW::GetErrorMessagePtr() const {
	return std::make_shared<std::wstring>(this->GetErrorMessage());
}

std::shared_ptr<std::wstring> Win32ExceptionW::GetErrorMessagePtr(const DWORD ErrorCode) const {
	return std::make_shared<std::wstring>(this->GetErrorMessage(ErrorCode));
}

std::shared_ptr<std::wstring> Win32ExceptionW::GetErrorMessagePtr(const HRESULT ErrorCode) const {
	return std::make_shared<std::wstring>(this->GetErrorMessage(ErrorCode));
}

std::wstring Win32ExceptionW::GetErrorMessage(const DWORD ErrorCode) const {
	wchar_t* lpMessageBuffer = nullptr;
	const DWORD length = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, ErrorCode, LANG_USER_DEFAULT, (LPWSTR)&lpMessageBuffer, 0, NULL);
	if (length == 0) throw std::runtime_error("エラーメッセージ取得時にエラーが発生しました。\nエラーコード : " + std::to_string(GetLastError()));
	DWORD i = length - 3;
	for (; '\r' != lpMessageBuffer[i] && '\n' != lpMessageBuffer[i] && L'\0' != lpMessageBuffer[i]; i++);//改行文字削除
	lpMessageBuffer[i] = '\0';
	std::wstring s = L"エラーコード : " + std::to_wstring(ErrorCode) + L"　" + lpMessageBuffer;
	LocalFree(lpMessageBuffer);
	return s;
}

std::wstring Win32ExceptionW::GetErrorMessage(const HRESULT ErrorCode) const {
	wchar_t* lpMessageBuffer = nullptr;
	const DWORD length = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, ErrorCode, LANG_USER_DEFAULT, (LPWSTR)&lpMessageBuffer, 0, NULL);
	if (length == 0) throw std::runtime_error("エラーメッセージ取得時にエラーが発生しました。\nエラーコード : " + std::to_string(GetLastError()));
	DWORD i = length - 3;
	for (; '\r' != lpMessageBuffer[i] && '\n' != lpMessageBuffer[i] && L'\0' != lpMessageBuffer[i]; i++);//改行文字削除
	lpMessageBuffer[i] = '\0';
	std::wstring s = L"エラーコード : " + std::to_wstring(ErrorCode) + L"　" + lpMessageBuffer;
	LocalFree(lpMessageBuffer);
	return s;
}

std::wstring Win32ExceptionW::GetErrorMessage() const {
	const DWORD Code = GetLastError();
	return this->GetErrorMessage(Code);
}

const wchar_t* Win32ExceptionW::what() const {
	return this->ExceptionMessage->c_str();
}

int Win32ExceptionW::GraphOnMessageBox(HWND hWnd, LPCWSTR lpCaption, UINT uType) const {
	return MessageBoxW(hWnd, this->what(), lpCaption, uType);
}

void Win32ExceptionW::GraphOnConsole() const {
	std::wcout.imbue(std::locale(""));
	std::wcout << this->what() << std::endl;
}
