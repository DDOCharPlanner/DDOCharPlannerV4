//---------------------------------------------------------------------------
#ifndef AboutWindowClassH
#define AboutWindowClassH

#include "stdafx.h"
//---------------------------------------------------------------------------
class AboutWindowClass
    {
    public:
        AboutWindowClass();
        virtual ~AboutWindowClass();

        void Create(HINSTANCE Instance, HWND Parent);
        void Show(bool State);
        long HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
		HWND GetHandle();
        HWND AboutWindowHandle;

	private:

        HWND CloseButton;
        HWND AboutBox;

        //do not implement these two functions, instance  control!!
        AboutWindowClass(const AboutWindowClass &source);
        AboutWindowClass& operator=(const AboutWindowClass &source);
    };

extern long CALLBACK WndProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
extern DWORD CALLBACK EditStreamCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG FAR *pcb);

#endif
