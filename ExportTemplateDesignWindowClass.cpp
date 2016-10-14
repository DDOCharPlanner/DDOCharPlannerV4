#include "ExportTemplateDesignWindowClass.h"
#include "InterfaceManagerClass.h"

//---------------------------------------------------------------------------
ExportTemplateDesignWindowClass::ExportTemplateDesignWindowClass()
	{
	}

//---------------------------------------------------------------------------
ExportTemplateDesignWindowClass::~ExportTemplateDesignWindowClass()
	{
	}
	
//---------------------------------------------------------------------------
void ExportTemplateDesignWindowClass::Create(HINSTANCE Instance, HWND Parent)
	{
    WNDCLASSEX wc;
    int ScreenX;
    int ScreenY;
    RECT ParentRect;
    RECT WindowRect;
    int WindowX;
    int WindowY;
    static char WindowName[] = "Template Design Window";

	//fill in the class attributes for the main window
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
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
    ExportTemplateDesignWindowHandle = CreateWindowEx(NULL, WindowName, WindowName, WS_DLGFRAME | WS_POPUP, 0, 0, 1024, 768, Parent, NULL, Instance, NULL);
    SetClassLong(ExportTemplateDesignWindowHandle, 0, (long)EXPORTTEMPLATEDESIGNWINDOW);
    ParentRect = InterfaceManager.GetMainWindowExtents();
	ScreenX = GetSystemMetrics(SM_CXSCREEN);
	ScreenY = GetSystemMetrics(SM_CYSCREEN);
    GetWindowRect(ExportTemplateDesignWindowHandle, &WindowRect);
    WindowX = WindowRect.right - WindowRect.left;
    WindowY = WindowRect.bottom - WindowRect.top;
    SetWindowPos(ExportTemplateDesignWindowHandle, Parent, (ScreenX/2) - (WindowX/2), (ScreenY/2) - (WindowY/2), 0, 0, SWP_NOSIZE);

    //the child windows
    CloseButton = CreateWindowEx(NULL, "BUTTON", "Close", WS_CHILD | BS_PUSHBUTTON, 10, 600, 70, 20, ExportTemplateDesignWindowHandle, (HMENU)ETD_CLOSEBUTTON, Instance, NULL);
	SaveButton = CreateWindowEx(NULL, "BUTTON", "Save", WS_CHILD | BS_PUSHBUTTON, 90, 600, 70, 20, ExportTemplateDesignWindowHandle, (HMENU)ETD_SAVEBUTTON, Instance, NULL);
	SaveAsButton = CreateWindowEx(NULL, "BUTTON", "Save As", WS_CHILD | BS_PUSHBUTTON, 170, 600, 70, 20, ExportTemplateDesignWindowHandle, (HMENU)ETD_SAVEASBUTTON, Instance, NULL);
	LoadButton = CreateWindowEx(NULL, "BUTTON", "Load", WS_CHILD | BS_PUSHBUTTON, 250, 600, 70, 20, ExportTemplateDesignWindowHandle, (HMENU)ETD_LOADBUTTON, Instance, NULL);
	TemplateSelectBox = CreateWindowEx(NULL, "COMBOBOX", "Close", WS_CHILD | CBS_DROPDOWNLIST, 330, 600, 100, 200, ExportTemplateDesignWindowHandle, (HMENU)ETD_TEMPLATESELECTBOX, Instance, NULL);

    ExampleOutputBox = CreateWindowEx(NULL, "RichEdit", "RichEdit", WS_CHILD | ES_MULTILINE | ES_READONLY | WS_VSCROLL | WS_HSCROLL | WS_BORDER, 470, 5, 540, 485, ExportTemplateDesignWindowHandle, (HMENU)ETD_EXAMPLEOUTPUTBOX, Instance, NULL);
    CodeInputBox = CreateWindowEx(NULL, "RichEdit", "RichEdit", WS_CHILD | ES_MULTILINE | WS_VSCROLL | WS_BORDER, 10, 5, 450, 485, ExportTemplateDesignWindowHandle, (HMENU)ETD_CODEINPUTBOX, Instance, NULL);

	//rich edit background color
    SendMessage(ExampleOutputBox, EM_SETBKGNDCOLOR, 0, RGB(0,0,0));
    
    //turn off the auto-word wrapping functions of the rich edit boxes (just set the right margin to some super high value)
	SendMessage(ExampleOutputBox, EM_SETTARGETDEVICE, (WPARAM)GetWindowDC(ExampleOutputBox), (LPARAM)50000);    

	ResetTemplate();
	}
	
//---------------------------------------------------------------------------
void ExportTemplateDesignWindowClass::Show(bool State)
    {
    //pop it up
    ShowWindow(ExportTemplateDesignWindowHandle, State);

    ShowWindow(CloseButton, State);
    ShowWindow(SaveButton, State);
    ShowWindow(SaveAsButton, State);
    ShowWindow(LoadButton, State);
    ShowWindow(TemplateSelectBox, State);
    
    ShowWindow(ExampleOutputBox, State);
    ShowWindow(CodeInputBox, State);
    }
    
//---------------------------------------------------------------------------
long ExportTemplateDesignWindowClass::HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
    {
    switch (Message)
        {
        case WM_COMMAND:
            {
            if (HIWORD(wParam) == BN_CLICKED)
                {
                if ((int)LOWORD(wParam) == ETD_CLOSEBUTTON)
                    {
                    InterfaceManager.ShowChild(EXPORTTEMPLATEDESIGNWINDOW, false);
                    InterfaceManager.ShowChild(FORUMEXPORTWINDOW, true);
                    return 0;
                    }
				}                   
            return 0;
            }
        default:
            {
            return DefWindowProc(Wnd, Message, wParam, lParam);
            }
        }
    }
    
//---------------------------------------------------------------------------
void ExportTemplateDesignWindowClass::ResetTemplate()
	{
	TemplateModified = false;

    TemplateCode = "[u][b]Character Plan by DDO Character Planner Version [VERSION][/b][/u]\r\n";
    TemplateCode += "[url=http://www.rjcyberware.com/DDO]DDO Character Planner Home Page[/url]\r\n\r\n";
    
    UpdateExampleWindow();
	}
	
//---------------------------------------------------------------------------
void ExportTemplateDesignWindowClass::UpdateExampleWindow()
	{
	string ExampleOutput;
	string Output;
    EDITSTREAM Stream;
    string rtfPrefix = "{\\rtf1\\ansi\\deff0\\deftab720{\\fonttbl{\\f0\\froman "
		"Courier;}}\n{\\colortbl\\red255\\green255\\blue255;\\red255\\green165\\blue0;"
        "\\red192\\green192\\blue192;\\red255\\green250\\blue205;"
        "\\red255\\green192\\blue203;\\red245\\green222\\blue179;"
        "\\red173\\green216\\blue230;\\red152\\green251\\blue152;}\n"
		"\\deflang1033\\pard\\plain\\f3\\fs22\\cf0 ";
	string rtfPostfix = "\n\\par }";
	
	ExampleOutput = ConvertForumOutputToRichEditOutput(TemplateCode);
	ExampleOutput = ParseKeywords(ExampleOutput);

    Output = rtfPrefix;
    Output += ExampleOutput;
    Output += rtfPostfix;

    Stream.dwCookie = (DWORD)&Output;
    Stream.dwError = false;
    Stream.pfnCallback = TemplateExampleStreamCallback;
    SendMessage(ExampleOutputBox, EM_STREAMIN, SF_RTF, (LPARAM)&Stream);
	}
	
//---------------------------------------------------------------------------
string ExportTemplateDesignWindowClass::ConvertForumOutputToRichEditOutput(string ForumOutput)
	{
	string RichEditOutput;
	
	//TODO: Conversions from Forum Output to RichEdit Box output
	RichEditOutput = ForumOutput;
	
	//convert carrige returns
	while (RichEditOutput.find("\r\n") != string::npos)
		RichEditOutput.replace(RichEditOutput.find("\r\n"), 2, "\\par ");

	return RichEditOutput;
	}
	
//---------------------------------------------------------------------------
string ExportTemplateDesignWindowClass::ParseKeywords(string InputString)
	{
	string OutputString;
	
	//TODO: Parse the keywords to use actual data
	OutputString = InputString;
	return OutputString;
	}
	
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
DWORD CALLBACK TemplateExampleStreamCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG FAR *pcb)
    {
    string &text = *(string*)dwCookie;

    //String smaller than buffer
	if( text.length() < (unsigned int)cb)
        {
		*pcb = text.length();
		memcpy(pbBuff,text.c_str(),*pcb);
	    }
	//String larger than buffer
	else
        {
		*pcb = cb;
		memcpy(pbBuff,text.c_str(),*pcb);
		text.erase(0,*pcb-1);
	    }

	return 0;
    }

