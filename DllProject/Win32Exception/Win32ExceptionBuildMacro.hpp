#ifndef __WIN32EXCEPTIONBUILDMACRO_HPP__
#define __WIN32EXCEPTIONBUILDMACRO_HPP__
#ifdef WIN32EXCEPTION_EXPORTS
#define WIN32EXCEPTIONLIB __declspec(dllexport)
#else
#define WIN32EXCEPTIONLIB __declspec(dllimport)
#endif
#endif
