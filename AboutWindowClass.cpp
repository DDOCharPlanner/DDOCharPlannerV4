//---------------------------------------------------------------------------
#include "AboutWindowClass.h"
#include "InterfaceManagerClass.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
AboutWindowClass::AboutWindowClass()
    {
    }

//---------------------------------------------------------------------------
AboutWindowClass::~AboutWindowClass()
    {
    }

//---------------------------------------------------------------------------
void AboutWindowClass::Create(HINSTANCE Instance, HWND Parent)
    {
    WNDCLASSEX wc;
    int ScreenX;
    int ScreenY;
    RECT WindowRect;
    int WindowX;
    int WindowY;
    static char WindowName[] = "About Window";
    LOGBRUSH lb;
    EDITSTREAM Stream;
    string AboutString;

    //fill in the class attributes for the main window
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;//CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 4;
    wc.cbWndExtra = 0;
    wc.hInstance = Instance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = WindowName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    //register
    RegisterClassEx(&wc);

    //create and center the window on screen
    AboutWindowHandle = CreateWindow(WindowName, WindowName, WS_DLGFRAME | WS_POPUP, 0, 0, 400, 300, Parent, NULL, Instance, NULL);
    SetClassLong(AboutWindowHandle, 0, (long)ABOUTWINDOW);
	ScreenX = GetSystemMetrics(SM_CXSCREEN);
	ScreenY = GetSystemMetrics(SM_CYSCREEN);
    GetWindowRect(AboutWindowHandle, &WindowRect);
    WindowX = WindowRect.right - WindowRect.left;
    WindowY = WindowRect.bottom - WindowRect.top;
    SetWindowPos(AboutWindowHandle, Parent, (ScreenX/2)-(WindowX/2), (int)(ScreenY/2)-(WindowY/2), 400, 300, SWP_NOSIZE);

    //the child windows
    AboutBox = CreateWindowEx(NULL, "RichEdit", "RichEdit", WS_CHILD | WS_VSCROLL | ES_MULTILINE | ES_READONLY, 5, 5, 383, 250, AboutWindowHandle, (HMENU)AB_ABOUTBOX, Instance, NULL);
    CloseButton = CreateWindowEx(NULL, "BUTTON", "Close", WS_CHILD | BS_PUSHBUTTON, 169, 262, 50, 25, AboutWindowHandle, (HMENU)AB_CLOSEBUTTON, Instance, NULL);

    GetObject(GetStockObject(DKGRAY_BRUSH), sizeof(LOGBRUSH), &lb);
    SendMessage(AboutBox, EM_SETBKGNDCOLOR, 0, lb.lbColor);

    AboutString = "{\\qc{\\b {\\cf1 {\\fs30  DDO Character Planner\\par}}} Version ";
    AboutString += VERSION;
//BUG:aboutwindowclass.cpp(95): warning C4129: 'p' : unrecognized character escape sequence
    AboutString += "\\par (C) 2006-2014 Ron Hiler\\par \
All rights reserverd\\par \
Graphics and text descriptions are property of {\\cf1 {\\b Standing Stone Games.}} (C) 2016, and are used with permission.\\par\\par \
A big thank you goes out to Ron Hiler the original creator of the first DDO Character Planner back in 2006. \\par \
{\\cf2 {\\b Programmer Hall of Fame:\\par}}\
	{\\cf1 Ron Hiler} (general messer upper of code)\\par \
	{\\cf1 DragonStar} (True messer upper of code :) )\\par \
    {\\cf1 Muiread} (aka plus10swordofpimp and/or Eric)\\par \
    {\\cf1 Ascendant Madness} (random tidbits for feats, item and enhancement data)\\par \
{\\cf2 {\\b contrubutor Hall of Fame:\\par}}\
   {\\cf1 Dworkin} (much equipment)\\par \
   {\\cf1 ChimRitchells} (general data input)\\par \
   {\\cf1 Valoir Wildfire} (Graphics Input)\\par \
   {\\cf1 Hordo} (grammar and syntax)\\par \
   {\\cf1 Kevin Larson aka'Martdon'} (Bugs/Data/Graphics)\\par \
   {\\cf1 Simon Sweetman } (Equipment)\\par \
   {\\cf1 Andrew Sessions aka 'Awaterujin'} (Data/Graphics)\\par \
   {\\cf1 Matt Lowery} \\par \
   {\\cf1 Shaun Woodruff} \\par \
   {\\cf1 BuckGB} \\par \
   {\\cf1 Cataclysm} \\par \
   {\\cf1 Garix} (new enhancements)\\par \
   {\\cf1 BlackDae} (new enhancements)\\par\\par\
   {\\cf2 {\\b Programmers:\\par}}\
   {\\cf1 Jonesth3} (Current Programmer and Data Input)\\par\\par\
      {\\cf1 Pax} (Programmer and Data Input)\\par\\par\
   {\\cf2 {\\b Data Input:\\par}}\
   {\\cf1 Tech13 aka 'Shoemaker'} (Equipment)\\par \
   {\\cf1 Shindoku} (enhancements and data updates)\\par\\par\
	{\\cf1 Thalamask} (Data updates)\\par\\par\
   {\\cf2 {\\b Special Thanks:\\par}}\
  A big \"Thanks\" go out to {\\cf1 Standing Stone Games} for creating an amazing \\par \
  game (and for allowing me to use their graphics and text).\\par \
And of course, thanks go out to {\\cf1 everyone} that offered their opinions, comments, and support for the project, not to mention all the bug reports! \
This project would not have been possible without you. Keep them coming, guys!\\par\\par \
Please don't hesitate to send comments, suggestions, bug reports, and hate mail to me. I can be reached on the official DDO forums (username {\\cf1 Ron})\
{\\fs15\"So Brain, what do you want to do today?\"\\par \
\"The same thing we do every day, Pinky, TRY TO TAKE OVER THE WORLD!\"}";
    Stream.dwCookie = (DWORD)AboutString.c_str();
    Stream.dwError = false;
    Stream.pfnCallback = EditStreamCallback;
    SendMessage(AboutBox, EM_STREAMIN, SF_RTF, (LPARAM)&Stream);
    }

//---------------------------------------------------------------------------
void AboutWindowClass::Show(bool State)
    {
    //pop it up
    ShowWindow(AboutWindowHandle, State);
    ShowWindow(AboutBox, State);
    ShowWindow(CloseButton, State);
    }

//---------------------------------------------------------------------------
long AboutWindowClass::HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
    {
    PAINTSTRUCT ps;
    RECT Rect;

    switch (Message)
        {
        case WM_COMMAND:
            {
            if (HIWORD(wParam) == BN_CLICKED)
                {
                if ((int)LOWORD(wParam) == AB_CLOSEBUTTON)
                    {
                    InterfaceManager.ShowChild(ABOUTWINDOW, false);
                    return 0;
                    }
                }
            }
        case WM_MOUSEWHEEL:
            {
            GetWindowRect(AboutBox, &Rect);
            if ((short)LOWORD(lParam) >= Rect.left && (short)LOWORD(lParam) <= Rect.right && (short)HIWORD(lParam) >= Rect.top && (short)HIWORD(lParam) <= Rect.bottom)
                {
                if ((short)HIWORD(wParam) > 0)
                    SendMessage(AboutBox, WM_VSCROLL, SB_LINEUP, 0);
                else
                    SendMessage(AboutBox, WM_VSCROLL, SB_LINEDOWN, 0);
                }
            return 0;
            }
        case WM_PAINT:
            {
            BeginPaint(Wnd, &ps);
            EndPaint(Wnd, &ps);
            return 0;
            }
        default:
            {
            return DefWindowProc(Wnd, Message, wParam, lParam);
            }
        }
    }
HWND AboutWindowClass::GetHandle()
{
	return AboutWindowHandle;
}

