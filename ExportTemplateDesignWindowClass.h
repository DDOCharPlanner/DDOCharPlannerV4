#pragma once

#include "stdafx.h"

//---------------------------------------------------------------------------
class ExportTemplateDesignWindowClass
	{
	public:
		ExportTemplateDesignWindowClass();
		virtual ~ExportTemplateDesignWindowClass();

        void Create(HINSTANCE Instance, HWND Parent);
		void Show(bool State);
		long HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);

	private:
        HWND ExportTemplateDesignWindowHandle;
        HWND CloseButton;
        HWND SaveButton;
        HWND SaveAsButton;
        HWND LoadButton;
        HWND TemplateSelectBox;
		HWND ExampleOutputBox;
		HWND CodeInputBox;
		
		bool TemplateModified;
		string TemplateCode;
		
		void ResetTemplate();
		void UpdateExampleWindow();
		string ConvertForumOutputToRichEditOutput(string ForumOutput);
		string ParseKeywords(string InputString);
		
        //do not implement these two functions, instance  control!!
        ExportTemplateDesignWindowClass(const ExportTemplateDesignWindowClass &source);
        ExportTemplateDesignWindowClass& operator=(const ExportTemplateDesignWindowClass &source);
	};
	
extern long CALLBACK WndProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
extern DWORD CALLBACK TemplateExampleStreamCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG FAR *pcb);
