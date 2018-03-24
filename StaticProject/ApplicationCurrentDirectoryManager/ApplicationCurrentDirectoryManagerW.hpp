#ifndef __APPLICATIONCURRENTDIRECTORYMANAGERW_HPP__
#define __APPLICATIONCURRENTDIRECTORYMANAGERW_HPP__
// commdlg.h��include����ۂ͐��Windows.h��include���K�v�̂悤�ł�
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
	// �A�v���P�[�V�����̃J�����g�f�B���N�g�����擾����
	std::wstring GetApplicationCurrentDirectory() const noexcept;
	// ���s�t�@�C���̃p�X���擾����
	std::wstring GetModuleFileDirectory() const noexcept;
	// �N���X�������������n�_�Ŏ擾���ꂽ�f�B���N�g�������擾����
	std::wstring GetDefaultDirectory() const noexcept;
	// �A�v���P�[�V�����̃J�����g�f�B���N�g�����w�肳�ꂽ�p�X�ւƕύX����
	void ChangeCurrentDirectory(const std::wstring NewCurrentDirectory);
	// �{�N���X�ȊO����J�����g�f�B���N�g�����ύX����Ă����ꍇ�A�N���X�̃J�����g�f�B���N�g�����̓������s��
	void SynchronizationCurrentDirectory();
	// ���΃p�X���J�����g�f�B���N�g�������g�p���ăt���p�X�ɕύX����
	std::wstring ChangeFullPath(const std::wstring Path) const;
	// Windows �G�N�X�v���[�����g�p���ă��[�U�[�Ƀt�@�C����I��������
	bool GetFileFromWindowsExplorer(OPENFILENAMEW* ofn, const bool RestoreCurrentDirectoryAfterExplorerClosed = true);
};
#endif
