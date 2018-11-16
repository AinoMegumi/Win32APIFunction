#ifndef __DLLFUNCTIONCALLMANAGER_HPP__
#define __DLLFUNCTIONCALLMANAGER_HPP__
#include <Windows.h>
#include <string>

class DllFunctionCallManager {
private:
	HMODULE hModule;
	FARPROC GetFunctionAddressImpl(const std::string& FunctionName) const;
	FARPROC GetFunctionAddressImpl(const std::wstring& FunctionName) const;
public:
	DllFunctionCallManager() : hModule(nullptr) {}
	DllFunctionCallManager(const std::string ModuleName);
	DllFunctionCallManager(const std::wstring ModuleName);
	~DllFunctionCallManager();
	DllFunctionCallManager(const DllFunctionCallManager&) = delete;
	DllFunctionCallManager(DllFunctionCallManager&& dcm);
	DllFunctionCallManager& operator = (const DllFunctionCallManager&) = delete;
	DllFunctionCallManager& operator = (DllFunctionCallManager&& dcm);
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

