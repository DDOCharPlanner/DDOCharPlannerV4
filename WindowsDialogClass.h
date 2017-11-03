#pragma once

#include "stdafx.h"


class WindowsDialogClass
{
private:
	char FiletoOpen[MAX_PATH + 1];
	bool xptest;
public:
	WindowsDialogClass();
	virtual ~WindowsDialogClass();
	bool LoadFileDialog(HWND hwnd);
	bool SaveFileDialog(HWND hwnd, bool Saveas = false);
	void ResetFiletoOpen();
	void ReturnFiletoOpen(char*& FiletoOpenin);
	bool File_Exists(const std::string& name);
};

extern WindowsDialogClass WindowsDialog;