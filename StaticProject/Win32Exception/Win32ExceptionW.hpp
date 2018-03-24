#ifndef __WIN32EXCEPTIONW_HPP__
#define __WIN32EXCEPTIONW_HPP__
#include <Windows.h>
#include <stdexcept>
#include <string>
#include <memory>

class Win32ExceptionW {
private:
	std::wstring ExceptionMessage;
	std::wstring GetErrorMessage() const;
	std::wstring GetErrorMessage(const DWORD ErrorCode) const;
	std::wstring GetErrorMessage(const HRESULT ErrorCode) const;
public:
	Win32ExceptionW();
	Win32ExceptionW(const DWORD ErrorCode);
	Win32ExceptionW(const HRESULT ErrorCode);
	Win32ExceptionW(const std::wstring ExceptionAddMessage);
	Win32ExceptionW(const std::wstring ExceptionAddMessage, const DWORD ErrorCode);
	Win32ExceptionW(const std::wstring ExceptionAddMessage, const HRESULT ErrorCode);
	const wchar_t* what() const;
	int GraphOnMessageBox(HWND hWnd, LPCWSTR lpCaption, UINT uType) const;
	void GraphOnConsole() const;
};
#endif
