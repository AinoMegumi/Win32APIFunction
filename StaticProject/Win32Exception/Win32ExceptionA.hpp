#ifndef __WIN32EXCEPTIONA_HPP__
#define __WIN32EXCEPTIONA_HPP__
#include <Windows.h>
#include <stdexcept>
#include <string>
#include <memory>

class Win32ExceptionA {
private:
	std::string ExceptionMessage;
	std::string GetErrorMessage() const;
	std::string GetErrorMessage(const DWORD ErrorCode) const;
	std::string GetErrorMessage(const HRESULT ErrorCode) const;
public:
	Win32ExceptionA();
	Win32ExceptionA(const DWORD ErrorCode);
	Win32ExceptionA(const HRESULT ErrorCode);
	Win32ExceptionA(const std::string ExceptionAddMessage);
	Win32ExceptionA(const std::string ExceptionAddMessage, const DWORD ErrorCode);
	Win32ExceptionA(const std::string ExceptionAddMessage, const HRESULT ErrorCode);
	const char* what() const;
	int GraphOnMessageBox(HWND hWnd, LPCSTR lpCaption, UINT uType) const;
	void GraphOnConsole() const;
};
#endif
