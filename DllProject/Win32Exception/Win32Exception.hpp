#ifndef __WIN32EXCEPTION_HPP__
#define __WIN32EXCEPTION_HPP__
#include "Win32ExceptionA.hpp"
#include "Win32ExceptionW.hpp"

#ifdef UNICODE
typedef Win32ExceptionW Win32Exception;
#else
typedef Win32ExceptionA Win32Exception;
#endif

#endif
