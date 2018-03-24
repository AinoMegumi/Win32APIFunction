#ifndef __WIN32LETTERCONVERT_HPP__
#define __WIN32LETTERCONVERT_HPP__
#ifdef WIN32LETTERCONVERT_EXPORTS
#define WIN32LETTER __declspec(dllexport)
#else
#define WIN32LETTER __declspec(dllimport)
#endif
#include <string>
#include <tchar.h>

WIN32LETTER std::string WStringToString(const std::wstring str);
WIN32LETTER std::wstring StringToWString(const std::string str);

#ifndef WIN32LETTERCONVERT_EXPORTS
std::basic_string<TCHAR> WStringToTString(const std::wstring str) {
#ifdef UNICODE
	return str;
#else
	return StringToWString();
#endif
}

std::basic_string<TCHAR> StringToTString(const std::string str) {
#ifdef UNICODE
	return StringToWString(str);
#else
	return str;
#endif
}
#endif
#endif
