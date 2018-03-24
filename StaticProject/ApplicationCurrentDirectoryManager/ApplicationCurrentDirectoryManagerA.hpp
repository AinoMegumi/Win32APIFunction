#pragma once
#ifndef __APPLICATIONCURRENTDIRECTORYMANAGERA_HPP__
#define __APPLICATIONCURRENTDIRECTORYMANAGERA_HPP__
// commdlg.hをincludeする際は先にWindows.hのincludeが必要のようです
#include <Windows.h>
#include <commdlg.h>
#include <string>
#include <memory>

class ApplicationCurrentDirectoryManagerA {
private:
	std::string CurrentDirectory;
	std::string DefaultDirectory;
	std::string ModuleFileDirectory;
	ApplicationCurrentDirectoryManagerA(const std::string DefaultDirectory, const std::string ModuleFileDirectory)
		: CurrentDirectory(DefaultDirectory), DefaultDirectory(DefaultDirectory), ModuleFileDirectory(ModuleFileDirectory) {}
public:
	ApplicationCurrentDirectoryManagerA() = default;
	ApplicationCurrentDirectoryManagerA(const ApplicationCurrentDirectoryManagerA&) = delete;
	ApplicationCurrentDirectoryManagerA(ApplicationCurrentDirectoryManagerA&&) = default;
	ApplicationCurrentDirectoryManagerA& operator = (const ApplicationCurrentDirectoryManagerA&) = delete;
	ApplicationCurrentDirectoryManagerA& operator = (ApplicationCurrentDirectoryManagerA&&) = delete;
	static ApplicationCurrentDirectoryManagerA Initialize();
	// アプリケーションのカレントディレクトリを取得する
	std::string GetApplicationCurrentDirectory() const noexcept;
	// 実行ファイルのパスを取得する
	std::string GetModuleFileDirectory() const noexcept;
	// クラスを初期化した地点で取得されたディレクトリ情報を取得する
	std::string GetDefaultDirectory() const noexcept;
	// アプリケーションのカレントディレクトリを指定されたパスへと変更する
	void ChangeCurrentDirectory(const std::string NewCurrentDirectory);
	// 本クラス以外からカレントディレクトリが変更されていた場合、クラスのカレントディレクトリ情報の同期を行う
	void SynchronizationCurrentDirectory();
	// 相対パスをカレントディレクトリ情報を使用してフルパスに変更する
	std::string ChangeFullPath(const std::string Path) const;
	// Windows エクスプローラを使用してユーザーにファイルを選択させる
	bool GetFileFromWindowsExplorer(OPENFILENAMEA* ofn, const bool RestoreCurrentDirectoryAfterExplorerClosed = true);
};
#endif
