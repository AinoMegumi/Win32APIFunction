#pragma once
#ifndef __APPLICATIONCURRENTDIRECTORYMANAGERA_HPP__
#define __APPLICATIONCURRENTDIRECTORYMANAGERA_HPP__
// commdlg.h��include����ۂ͐��Windows.h��include���K�v�̂悤�ł�
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
	// �A�v���P�[�V�����̃J�����g�f�B���N�g�����擾����
	std::string GetApplicationCurrentDirectory() const noexcept;
	// ���s�t�@�C���̃p�X���擾����
	std::string GetModuleFileDirectory() const noexcept;
	// �N���X�������������n�_�Ŏ擾���ꂽ�f�B���N�g�������擾����
	std::string GetDefaultDirectory() const noexcept;
	// �A�v���P�[�V�����̃J�����g�f�B���N�g�����w�肳�ꂽ�p�X�ւƕύX����
	void ChangeCurrentDirectory(const std::string NewCurrentDirectory);
	// �{�N���X�ȊO����J�����g�f�B���N�g�����ύX����Ă����ꍇ�A�N���X�̃J�����g�f�B���N�g�����̓������s��
	void SynchronizationCurrentDirectory();
	// ���΃p�X���J�����g�f�B���N�g�������g�p���ăt���p�X�ɕύX����
	std::string ChangeFullPath(const std::string Path) const;
	// Windows �G�N�X�v���[�����g�p���ă��[�U�[�Ƀt�@�C����I��������
	bool GetFileFromWindowsExplorer(OPENFILENAMEA* ofn, const bool RestoreCurrentDirectoryAfterExplorerClosed = true);
};
#endif
