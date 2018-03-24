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
	// �A�v���P�[�V�����̃J�����g�f�B���N�g�����擾����
	APPDIR std::string GetApplicationCurrentDirectory() const noexcept;
	// ���s�t�@�C���̃p�X���擾����
	APPDIR std::string GetModuleFileDirectory() const noexcept;
	// �N���X�������������n�_�Ŏ擾���ꂽ�f�B���N�g�������擾����
	APPDIR std::string GetDefaultDirectory() const noexcept;
	// �A�v���P�[�V�����̃J�����g�f�B���N�g�����w�肳�ꂽ�p�X�ւƕύX����
	APPDIR void ChangeCurrentDirectory(const std::string NewCurrentDirectory);
	// �{�N���X�ȊO����J�����g�f�B���N�g�����ύX����Ă����ꍇ�A�N���X�̃J�����g�f�B���N�g�����̓������s��
	APPDIR void SynchronizationCurrentDirectory();
	// ���΃p�X���J�����g�f�B���N�g�������g�p���ăt���p�X�ɕύX����
	APPDIR std::string ChangeFullPath(const std::string Path) const;
	// Windows �G�N�X�v���[�����g�p���ă��[�U�[�Ƀt�@�C����I��������
	APPDIR bool GetFileFromWindowsExplorer(OPENFILENAMEA* ofn, const bool RestoreCurrentDirectoryAfterExplorerClosed = true);
};
#endif
