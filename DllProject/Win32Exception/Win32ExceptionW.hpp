#ifndef __WIN32EXCEPTIONW_HPP__
#define __WIN32EXCEPTIONW_HPP__
#include "Win32ExceptionBuildMacro.hpp"
#include <Windows.h>
#include <stdexcept>
#include <string>
#include <memory>

class Win32ExceptionW {
private:
	std::shared_ptr<std::wstring> ExceptionMessage;
	WIN32EXCEPTIONLIB std::shared_ptr<std::wstring> GetErrorMessagePtr() const;
	WIN32EXCEPTIONLIB std::shared_ptr<std::wstring> GetErrorMessagePtr(const DWORD ErrorCode) const;
	WIN32EXCEPTIONLIB std::shared_ptr<std::wstring> GetErrorMessagePtr(const HRESULT ErrorCode) const;
	WIN32EXCEPTIONLIB std::wstring GetErrorMessage() const;
	WIN32EXCEPTIONLIB std::wstring GetErrorMessage(const DWORD ErrorCode) const;
	WIN32EXCEPTIONLIB std::wstring GetErrorMessage(const HRESULT ErrorCode) const;
public:
	WIN32EXCEPTIONLIB Win32ExceptionW();
	WIN32EXCEPTIONLIB Win32ExceptionW(const DWORD ErrorCode);
	WIN32EXCEPTIONLIB Win32ExceptionW(const HRESULT ErrorCode);
	WIN32EXCEPTIONLIB Win32ExceptionW(const std::wstring ExceptionAddMessage);
	WIN32EXCEPTIONLIB Win32ExceptionW(const std::wstring ExceptionAddMessage, const DWORD ErrorCode);
	WIN32EXCEPTIONLIB Win32ExceptionW(const std::wstring ExceptionAddMessage, const HRESULT ErrorCode);
	WIN32EXCEPTIONLIB const wchar_t* what() const;
	WIN32EXCEPTIONLIB int GraphOnMessageBox(HWND hWnd, LPCWSTR lpCaption, UINT uType) const;
	WIN32EXCEPTIONLIB void GraphOnConsole() const;
};
#endif
