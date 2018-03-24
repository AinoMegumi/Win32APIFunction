#pragma once
#ifndef __APPLICATIONCURRENTDIRECTORYMANAGERA_HPP__
#define __APPLICATIONCURRENTDIRECTORYMANAGERA_HPP__
#include "ApplicationCurrentDirectoryManagerBuildMacro.hpp"
#include <commdlg.h>
#include <string>
#include <memory>

class ApplicationCurrentDirectoryManagerA {
private:
	std::shared_ptr<std::string> CurrentDirectory;
	std::shared_ptr<std::string> DefaultDirectory;
	std::shared_ptr<std::string> ModuleFileDirectory;
	ApplicationCurrentDirectoryManagerA(const std::string DefaultDirectory, const std::string ModuleFileDirectory)
		: CurrentDirectory(std::make_shared<std::string>(DefaultDirectory)), DefaultDirectory(std::make_shared<std::string>(DefaultDirectory)),
		ModuleFileDirectory(std::make_shared<std::string>(ModuleFileDirectory)) {}
public:
	ApplicationCurrentDirectoryManagerA() = default;
	ApplicationCurrentDirectoryManagerA(const ApplicationCurrentDirectoryManagerA&) = delete;
	ApplicationCurrentDirectoryManagerA(ApplicationCurrentDirectoryManagerA&&) = default;
	ApplicationCurrentDirectoryManagerA& operator = (const ApplicationCurrentDirectoryManagerA&) = delete;
	ApplicationCurrentDirectoryManagerA& operator = (ApplicationCurrentDirectoryManagerA&&) = delete;
	APPDIR static ApplicationCurrentDirectoryManagerA Initialize();
	// アプリケーションのカレントディレクトリを取得する
	APPDIR std::string GetApplicationCurrentDirectory() const noexcept;
	// 実行ファイルのパスを取得する
	APPDIR std::string GetModuleFileDirectory() const noexcept;
	// クラスを初期化した地点で取得されたディレクトリ情報を取得する
	APPDIR std::string GetDefaultDirectory() const noexcept;
	// アプリケーションのカレントディレクトリを指定されたパスへと変更する
	APPDIR void ChangeCurrentDirectory(const std::string NewCurrentDirectory);
	// 本クラス以外からカレントディレクトリが変更されていた場合、クラスのカレントディレクトリ情報の同期を行う
	APPDIR void SynchronizationCurrentDirectory();
	// 相対パスをカレントディレクトリ情報を使用してフルパスに変更する
	APPDIR std::string ChangeFullPath(const std::string Path) const;
	// Windows エクスプローラを使用してユーザーにファイルを選択させる
	APPDIR bool GetFileFromWindowsExplorer(OPENFILENAMEA* ofn, const bool RestoreCurrentDirectoryAfterExplorerClosed = true);
};
#endif
