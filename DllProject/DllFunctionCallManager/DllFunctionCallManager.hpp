#ifndef __DLLFUNCTIONCALLMANAGER_HPP__
#define __DLLFUNCTIONCALLMANAGER_HPP__
#ifdef DLLFUNCTIONCALLMANAGER_EXPORTS
#define DLLFUNCMGR __declspec(dllexport)
#else
#define DLLFUNCMGR __declspec(dllimport)
#endif
#include <Windows.h>
#include <string>

class DllFunctionCallManager {
private:
	HMODULE hModule;
	DLLFUNCMGR FARPROC GetFunctionAddressImpl(const std::string& FunctionName) const;
	DLLFUNCMGR FARPROC GetFunctionAddressImpl(const std::wstring& FunctionName) const;
public:
	DLLFUNCMGR DllFunctionCallManager() : hModule(nullptr) {}
	DLLFUNCMGR DllFunctionCallManager(const std::string ModuleName);
	DLLFUNCMGR DllFunctionCallManager(const std::wstring ModuleName);
	DLLFUNCMGR ~DllFunctionCallManager();
	DllFunctionCallManager(const DllFunctionCallManager&) = delete;
	DLLFUNCMGR DllFunctionCallManager(DllFunctionCallManager&& dcm);
	DllFunctionCallManager& operator = (const DllFunctionCallManager&) = delete;
	DLLFUNCMGR DllFunctionCallManager& operator = (DllFunctionCallManager&& dcm);
	template<typename Func>
	Func GetFunctionAddress(const std::string& FunctionName) const {
		return reinterpret_cast<Func>(this->GetFunctionAddress());
	}
	template<typename Func>
	Func GetFunctionAddress(const std::wstring& FunctionName) const {
		return reinterpret_cast<Func>(this->GetFunctionAddress());
	}
};
#endif

