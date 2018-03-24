#ifndef __APPLICATIONCURRENTDIRECTORYMANAGERW_HPP__
#define __APPLICATIONCURRENTDIRECTORYMANAGERW_HPP__
#include "ApplicationCurrentDirectoryManagerBuildMacro.hpp"
#include <commdlg.h>
#include <string>
#include <memory>

class ApplicationCurrentDirectoryManagerW {
private:
	std::shared_ptr<std::wstring> CurrentDirectory;
	std::shared_ptr<std::wstring> DefaultDirectory;
	std::shared_ptr<std::wstring> ModuleFileDirectory;
	ApplicationCurrentDirectoryManagerW(const std::wstring DefaultDirectory, const std::wstring ModuleFileDirectory)
		: CurrentDirectory(std::make_shared<std::wstring>(DefaultDirectory)), DefaultDirectory(std::make_shared<std::wstring>(DefaultDirectory)),
		ModuleFileDirectory(std::make_shared<std::wstring>(ModuleFileDirectory)) {}
public:
	ApplicationCurrentDirectoryManagerW() = default;
	ApplicationCurrentDirectoryManagerW(const ApplicationCurrentDirectoryManagerW&) = delete;
	ApplicationCurrentDirectoryManagerW(ApplicationCurrentDirectoryManagerW&&) = default;
	ApplicationCurrentDirectoryManagerW& operator = (const ApplicationCurrentDirectoryManagerW&) = delete;
	ApplicationCurrentDirectoryManagerW& operator = (ApplicationCurrentDirectoryManagerW&&) = delete;
	APPDIR static ApplicationCurrentDirectoryManagerW Initialize();
	// アプリケーションのカレントディレクトリを取得する
	APPDIR std::wstring GetApplicationCurrentDirectory() const noexcept;
	// 実行ファイルのパスを取得する
	APPDIR std::wstring GetModuleFileDirectory() const noexcept;
	// クラスを初期化した地点で取得されたディレクトリ情報を取得する
	APPDIR std::wstring GetDefaultDirectory() const noexcept;
	// アプリケーションのカレントディレクトリを指定されたパスへと変更する
	APPDIR void ChangeCurrentDirectory(const std::wstring NewCurrentDirectory);
	// 本クラス以外からカレントディレクトリが変更されていた場合、クラスのカレントディレクトリ情報の同期を行う
	APPDIR void SynchronizationCurrentDirectory();
	// 相対パスをカレントディレクトリ情報を使用してフルパスに変更する
	APPDIR std::wstring ChangeFullPath(const std::wstring Path) const;
	// Windows エクスプローラを使用してユーザーにファイルを選択させる
	APPDIR bool GetFileFromWindowsExplorer(OPENFILENAMEW* ofn, const bool RestoreCurrentDirectoryAfterExplorerClosed = true);
};
#endif
