//---------------------------------------------------------------------------
#include "stdafx.h"
#include "InterfaceManagerClass.h"
#include "DataClass.h"
#include "CharacterClass.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CmdLine, int CmdShow)
    {
    MSG msg;
    bool FileRead;
    HINSTANCE MainInstance;
    char AppPath[MAX_PATH+1];
    char *pszTmp;
    int Width;
    int Height;
    string CommandLine;
    string SubString;
    bool UseSystemFont;
    string FontName;
    long FontHeight;
    long FontWeight;

	CoInitialize(NULL);

    //make sure the start directory is equal to the executable directory
    MainInstance = (HINSTANCE)GetModuleHandle(NULL);
    GetModuleFileName (MainInstance, AppPath, MAX_PATH);
    // Chop off the file name...
    pszTmp = strrchr (AppPath, '\\');
    *++pszTmp = '\0';
    SetCurrentDirectory(AppPath);  

    //Set the height and width of the main screen to 1024 x 768
    //unless the user has overridden this size with command line
    //values (-W and -H), in which case use those
    Width = DEFAULTWIDTH;
    Height = DEFAULTHEIGHT;
    CommandLine = CmdLine;
    if (CommandLine.find("-W ") != std::string::npos)
        {
        SubString = CommandLine.substr(CommandLine.find("-W ")+3, 4);
        if (atoi(SubString.c_str()) != 0)
            Width = atoi(SubString.c_str());
        }
    if (CommandLine.find("-H ") != std::string::npos)
        {
        SubString = CommandLine.substr(CommandLine.find("-H ")+3, 4);
        if (atoi(SubString.c_str()) != 0)
            Height = atoi(SubString.c_str());
        }
    if (CommandLine.find("-SYSTEMFONT") != std::string::npos)
		UseSystemFont = true;
	else
		{
		UseSystemFont = false;
		FontName = "Ariel";
		FontHeight = 16;
		FontWeight = 700;
	    if (CommandLine.find("-FONTNAME ") != std::string::npos)
		    {
			SubString = CommandLine.substr(CommandLine.find("-FONTNAME ")+10);
			if (SubString.find("-") != std::string::npos)
				SubString.erase(SubString.find("-")-1, SubString.size());
			FontName = SubString;				
			}
	    if (CommandLine.find("-FONTSIZE ") != std::string::npos)
		    {
			SubString = CommandLine.substr(CommandLine.find("-FONTSIZE ")+10, 4);
	        if (atoi(SubString.c_str()) != 0)
		        FontHeight = atoi(SubString.c_str());
			}
	    if (CommandLine.find("-FONTWEIGHT ") != std::string::npos)
		    {
			SubString = CommandLine.substr(CommandLine.find("-FONTWEIGHT ")+12, 5);
	        if (atoi(SubString.c_str()) != 0)
		        FontWeight = atoi(SubString.c_str());
			}
		}

    FileRead = false;

    //create the windows
    InterfaceManager.CreateMainWindow(Instance, Width, Height, UseSystemFont, FontName, FontHeight, FontWeight);
    InterfaceManager.CreateChildWindows();
    InterfaceManager.ShowChild(DATALOAD, true);

    //the message pump
    while (true)
        {
			
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
            if (msg.message == WM_QUIT)
                {
                break;
                }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
            }
        else
            {
            if (FileRead == false)
                {
                Data.LoadDataFiles();
                FileRead = true;
                InterfaceManager.ShowChild(DATALOAD, false);
                Character.Reset();
                InterfaceManager.SetMainToDefaults();
                InterfaceManager.ShowChild(MAINWINDOW, true);
                }

            Sleep(10);   //do not max out processor
            }
        }

	CoUninitialize();
    return 0;
    }

//---------------------------------------------------------------------------
long CALLBACK WndProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
    {
    return InterfaceManager.ForwardWindowsMessage(Wnd, Message, wParam, lParam);
    }

//---------------------------------------------------------------------------
long CALLBACK SubclassWndProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
    {
    return InterfaceManager.ForwardSubclassedMessage(Wnd, Message, wParam, lParam);
    }

