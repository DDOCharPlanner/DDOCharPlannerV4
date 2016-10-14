#pragma once

#include "stdafx.h"

class ToolTipWindowClass
	{
	public:
		ToolTipWindowClass();
		~ToolTipWindowClass();

        void Create(HINSTANCE Instance, HWND Parent);
        void Show(bool State);
        long HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
		void SetToolTipText(string Text);
		ToolTipWindowClass* GetPointer();
		void SetConfiningWindow(HWND Window);

	private:
		HWND ToolTipWindow;
		HWND ToolTipText;
		HWND ConfiningWindow;

        //do not implement these two functions, instance  control!!
        ToolTipWindowClass(const ToolTipWindowClass &source);
        ToolTipWindowClass& operator=(const ToolTipWindowClass &source);
	};

extern long CALLBACK WndProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
extern DWORD CALLBACK EditStreamCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG FAR *pcb);
