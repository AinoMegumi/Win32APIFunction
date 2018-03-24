#ifndef __WIN32EXCEPTIONA_HPP__
#define __WIN32EXCEPTIONA_HPP__
#include "Win32ExceptionBuildMacro.hpp"
#include <Windows.h>
#include <stdexcept>
#include <string>
#include <memory>

class Win32ExceptionA {
private:
	std::shared_ptr<std::string> ExceptionMessage;
	WIN32EXCEPTIONLIB std::shared_ptr<std::string> GetErrorMessagePtr() const;
	WIN32EXCEPTIONLIB std::shared_ptr<std::string> GetErrorMessagePtr(const DWORD ErrorCode) const;
	WIN32EXCEPTIONLIB std::shared_ptr<std::string> GetErrorMessagePtr(const HRESULT ErrorCode) const;
	WIN32EXCEPTIONLIB std::string GetErrorMessage() const;
	WIN32EXCEPTIONLIB std::string GetErrorMessage(const DWORD ErrorCode) const;
	WIN32EXCEPTIONLIB std::string GetErrorMessage(const HRESULT ErrorCode) const;
public:
	WIN32EXCEPTIONLIB Win32ExceptionA();
	WIN32EXCEPTIONLIB Win32ExceptionA(const DWORD ErrorCode);
	WIN32EXCEPTIONLIB Win32ExceptionA(const HRESULT ErrorCode);
	WIN32EXCEPTIONLIB Win32ExceptionA(const std::string ExceptionAddMessage);
	WIN32EXCEPTIONLIB Win32ExceptionA(const std::string ExceptionAddMessage, const DWORD ErrorCode);
	WIN32EXCEPTIONLIB Win32ExceptionA(const std::string ExceptionAddMessage, const HRESULT ErrorCode);
	WIN32EXCEPTIONLIB const char* what() const;
	WIN32EXCEPTIONLIB int GraphOnMessageBox(HWND hWnd, LPCSTR lpCaption, UINT uType) const;
	WIN32EXCEPTIONLIB void GraphOnConsole() const;
};
#endif
