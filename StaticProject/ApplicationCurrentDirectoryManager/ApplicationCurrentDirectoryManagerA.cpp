#include "stdafx.h"
#include "ApplicationCurrentDirectoryManagerA.hpp"
#include "../Win32Exception/Win32ExceptionA.hpp"
#ifdef _DEBUG
#pragma comment(lib, "Win32ExceptionDebug.lib")
#else
#pragma comment(lib, "Win32ExceptionRelease.lib")
#endif

ApplicationCurrentDirectoryManagerA ApplicationCurrentDirectoryManagerA::Initialize() {
	std::string DefaultDir, ModuleDir;
	DefaultDir.resize(MAX_PATH);
	ModuleDir.resize(MAX_PATH);
	if (0 == GetCurrentDirectoryA(MAX_PATH, &DefaultDir[0]) || 0 == GetModuleFileNameA(NULL, &ModuleDir[0], MAX_PATH)) throw Win32ExceptionA();
	DefaultDir.resize(std::strlen(DefaultDir.c_str()));
	ModuleDir.resize(std::strlen(ModuleDir.c_str()));
	return ApplicationCurrentDirectoryManagerA(DefaultDir, ModuleDir);
}
std::string ApplicationCurrentDirectoryManagerA::GetApplicationCurrentDirectory() const noexcept {
	return this->CurrentDirectory;
}

std::string ApplicationCurrentDirectoryManagerA::GetModuleFileDirectory() const noexcept {
	return this->ModuleFileDirectory;
}

std::string ApplicationCurrentDirectoryManagerA::GetDefaultDirectory() const noexcept {
	return this->DefaultDirectory;
}

void ApplicationCurrentDirectoryManagerA::ChangeCurrentDirectory(const std::string NewCurrentDirectory) {
	if (FALSE == SetCurrentDirectoryA(NewCurrentDirectory.c_str())) throw Win32ExceptionA();
	this->CurrentDirectory = NewCurrentDirectory;
}

void ApplicationCurrentDirectoryManagerA::SynchronizationCurrentDirectory() {
	std::string CurrentDir;
	CurrentDir.resize(MAX_PATH);
	if (0 == GetCurrentDirectoryA(MAX_PATH, &CurrentDir[0])) throw Win32ExceptionA();
	CurrentDir.resize(std::strlen(CurrentDir.c_str()));
	this->CurrentDirectory = CurrentDir;
}

std::string ApplicationCurrentDirectoryManagerA::ChangeFullPath(const std::string Path) const {
	if (Path.empty()) throw std::runtime_error("path is empty.");
	else if (L':' == Path.at(1)) return Path;
	else return Path.find_first_of("\\") > 2 || Path.find_first_of("\\") == std::string::npos
		? this->GetApplicationCurrentDirectory() + "\\" + Path
		: this->GetApplicationCurrentDirectory() + Path;
}

bool ApplicationCurrentDirectoryManagerA::GetFileFromWindowsExplorer(OPENFILENAMEA* ofn, const bool RestoreCurrentDirectoryAfterExplorerClosed) {
	const bool Flag = (0 == GetOpenFileNameA(ofn));
	if (!RestoreCurrentDirectoryAfterExplorerClosed) return Flag;
	std::string CurrentDir;
	CurrentDir.resize(MAX_PATH);
	if (0 == GetCurrentDirectoryA(MAX_PATH, &CurrentDir[0])) throw Win32ExceptionA();
	CurrentDir.resize(std::strlen(CurrentDir.c_str()));
	if (CurrentDir != this->CurrentDirectory) this->ChangeCurrentDirectory(CurrentDir);
	return Flag;
}
