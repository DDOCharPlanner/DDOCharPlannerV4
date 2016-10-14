//---------------------------------------------------------------------------
#ifndef ControlWindowClassH
#define ControlWindowClassH

#include "stdafx.h"
//---------------------------------------------------------------------------
class ControlWindowClass
    {
    public:
        ControlWindowClass();
        virtual ~ControlWindowClass();

        void CreateControlWindow(HINSTANCE Instance, int Width, int Height);
        HWND GetControlWindowHandle();
        RECT GetWindowExtents();

    private:
        HWND ControlWindowHandle;
        int ScreenX;
        int ScreenY;
        int WindowX;
        int WindowY;
        int ClientX;
		int ClientY;

        //do not implement these two functions, instance  control!!
        ControlWindowClass(const ControlWindowClass &source);
        ControlWindowClass& operator=(const ControlWindowClass &source);
    };

extern long CALLBACK WndProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);

#endif
 