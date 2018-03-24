#ifndef __WIN32LETTERCONVERT_HPP__
#define __WIN32LETTERCONVERT_HPP__
#include <string>
#include <tchar.h>

std::string WStringToString(const std::wstring str);
std::wstring StringToWString(const std::string str);

#ifndef WIN32API_STATICLIB_EXPORTS
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
