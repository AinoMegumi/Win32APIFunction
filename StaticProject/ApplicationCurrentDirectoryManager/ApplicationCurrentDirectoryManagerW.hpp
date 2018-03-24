#ifndef __APPLICATIONCURRENTDIRECTORYMANAGERW_HPP__
#define __APPLICATIONCURRENTDIRECTORYMANAGERW_HPP__
// commdlg.hをincludeする際は先にWindows.hのincludeが必要のようです
#include <Windows.h>
#include <commdlg.h>
#include <string>
#include <memory>

class ApplicationCurrentDirectoryManagerW {
private:
	std::wstring CurrentDirectory;
	std::wstring DefaultDirectory;
	std::wstring ModuleFileDirectory;
	ApplicationCurrentDirectoryManagerW(const std::wstring DefaultDirectory, const std::wstring ModuleFileDirectory)
		: CurrentDirectory(DefaultDirectory), DefaultDirectory(DefaultDirectory),
		ModuleFileDirectory(ModuleFileDirectory) {}
public:
	ApplicationCurrentDirectoryManagerW() = default;
	ApplicationCurrentDirectoryManagerW(const ApplicationCurrentDirectoryManagerW&) = delete;
	ApplicationCurrentDirectoryManagerW(ApplicationCurrentDirectoryManagerW&&) = default;
	ApplicationCurrentDirectoryManagerW& operator = (const ApplicationCurrentDirectoryManagerW&) = delete;
	ApplicationCurrentDirectoryManagerW& operator = (ApplicationCurrentDirectoryManagerW&&) = delete;
	static ApplicationCurrentDirectoryManagerW Initialize();
	// アプリケーションのカレントディレクトリを取得する
	std::wstring GetApplicationCurrentDirectory() const noexcept;
	// 実行ファイルのパスを取得する
	std::wstring GetModuleFileDirectory() const noexcept;
	// クラスを初期化した地点で取得されたディレクトリ情報を取得する
	std::wstring GetDefaultDirectory() const noexcept;
	// アプリケーションのカレントディレクトリを指定されたパスへと変更する
	void ChangeCurrentDirectory(const std::wstring NewCurrentDirectory);
	// 本クラス以外からカレントディレクトリが変更されていた場合、クラスのカレントディレクトリ情報の同期を行う
	void SynchronizationCurrentDirectory();
	// 相対パスをカレントディレクトリ情報を使用してフルパスに変更する
	std::wstring ChangeFullPath(const std::wstring Path) const;
	// Windows エクスプローラを使用してユーザーにファイルを選択させる
	bool GetFileFromWindowsExplorer(OPENFILENAMEW* ofn, const bool RestoreCurrentDirectoryAfterExplorerClosed = true);
};
#endif
