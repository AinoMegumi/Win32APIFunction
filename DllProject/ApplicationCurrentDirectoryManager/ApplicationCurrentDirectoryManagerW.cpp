#include "stdafx.h"
#include "ApplicationCurrentDirectoryManagerW.hpp"
#include "../Win32Exception/Win32ExceptionW.hpp"
#ifdef _DEBUG
#pragma comment(lib, "Win32ExceptionDebug.lib")
#else
#pragma comment(lib, "Win32ExceptionRelease.lib")
#endif

ApplicationCurrentDirectoryManagerW ApplicationCurrentDirectoryManagerW::Initialize() {
	std::wstring DefaultDir, ModuleDir;
	DefaultDir.resize(MAX_PATH);
	ModuleDir.resize(MAX_PATH);
	if (0 == GetCurrentDirectoryW(MAX_PATH, &DefaultDir[0]) || 0 == GetModuleFileNameW(NULL, &ModuleDir[0], MAX_PATH)) throw Win32ExceptionW();
	DefaultDir.resize(std::wcslen(DefaultDir.c_str()));
	ModuleDir.resize(std::wcslen(ModuleDir.c_str()));
	return ApplicationCurrentDirectoryManagerW(DefaultDir, ModuleDir);
}
std::wstring ApplicationCurrentDirectoryManagerW::GetApplicationCurrentDirectory() const noexcept {
	return *this->CurrentDirectory;
}

std::wstring ApplicationCurrentDirectoryManagerW::GetModuleFileDirectory() const noexcept {
	return *this->ModuleFileDirectory;
}

std::wstring ApplicationCurrentDirectoryManagerW::GetDefaultDirectory() const noexcept {
	return *this->DefaultDirectory;
}

void ApplicationCurrentDirectoryManagerW::ChangeCurrentDirectory(const std::wstring NewCurrentDirectory) {
	if (FALSE == SetCurrentDirectoryW(NewCurrentDirectory.c_str())) throw Win32ExceptionW();
	this->CurrentDirectory = std::make_shared<std::wstring>(NewCurrentDirectory);
}

void ApplicationCurrentDirectoryManagerW::SynchronizationCurrentDirectory() {
	std::wstring CurrentDir;
	CurrentDir.resize(MAX_PATH);
	if (0 == GetCurrentDirectoryW(MAX_PATH, &CurrentDir[0])) throw Win32ExceptionW();
	CurrentDir.resize(std::wcslen(CurrentDir.c_str()));
	this->CurrentDirectory = std::make_shared<std::wstring>(CurrentDir);
}

std::wstring ApplicationCurrentDirectoryManagerW::ChangeFullPath(const std::wstring Path) const {
	if (Path.empty()) throw std::runtime_error("path is empty.");
	else if (L':' == Path.at(1)) return Path;
	else return Path.find_first_of(L"\\") > 2 || Path.find_first_of(L"\\") == std::wstring::npos
		? this->GetApplicationCurrentDirectory() + L"\\" + Path
		: this->GetApplicationCurrentDirectory() + Path;
}

bool ApplicationCurrentDirectoryManagerW::GetFileFromWindowsExplorer(OPENFILENAMEW* ofn, const bool RestoreCurrentDirectoryAfterExplorerClosed) {
	const bool Flag = (0 == GetOpenFileNameW(ofn));
	if (!RestoreCurrentDirectoryAfterExplorerClosed) return Flag;
	std::wstring CurrentDir;
	CurrentDir.resize(MAX_PATH);
	if (0 == GetCurrentDirectoryW(MAX_PATH, &CurrentDir[0])) throw Win32ExceptionW();
	CurrentDir.resize(std::wcslen(CurrentDir.c_str()));
	if (CurrentDir != *this->CurrentDirectory) this->ChangeCurrentDirectory(CurrentDir);
	return Flag;
}
