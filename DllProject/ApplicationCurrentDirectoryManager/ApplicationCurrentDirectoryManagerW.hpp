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
	// �A�v���P�[�V�����̃J�����g�f�B���N�g�����擾����
	APPDIR std::wstring GetApplicationCurrentDirectory() const noexcept;
	// ���s�t�@�C���̃p�X���擾����
	APPDIR std::wstring GetModuleFileDirectory() const noexcept;
	// �N���X�������������n�_�Ŏ擾���ꂽ�f�B���N�g�������擾����
	APPDIR std::wstring GetDefaultDirectory() const noexcept;
	// �A�v���P�[�V�����̃J�����g�f�B���N�g�����w�肳�ꂽ�p�X�ւƕύX����
	APPDIR void ChangeCurrentDirectory(const std::wstring NewCurrentDirectory);
	// �{�N���X�ȊO����J�����g�f�B���N�g�����ύX����Ă����ꍇ�A�N���X�̃J�����g�f�B���N�g�����̓������s��
	APPDIR void SynchronizationCurrentDirectory();
	// ���΃p�X���J�����g�f�B���N�g�������g�p���ăt���p�X�ɕύX����
	APPDIR std::wstring ChangeFullPath(const std::wstring Path) const;
	// Windows �G�N�X�v���[�����g�p���ă��[�U�[�Ƀt�@�C����I��������
	APPDIR bool GetFileFromWindowsExplorer(OPENFILENAMEW* ofn, const bool RestoreCurrentDirectoryAfterExplorerClosed = true);
};
#endif
