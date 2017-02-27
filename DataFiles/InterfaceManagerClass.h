//---------------------------------------------------------------------------
#ifndef InterfaceManagerClassH
#define InterfaceManagerClassH

#include "stdafx.h"
#include "ControlWindowClass.h"
#include "MainScreenClass.h"
#include "LoadWindowClass.h"
#include "AboutWindowClass.h"
#include "ForumExportClass.h"
#include "ItemBuilderClass.h"
#include "ExportTemplateDesignWindowClass.h"
#include "PrintWindowClass.h"
#include "UIComponentManager.h"
#include "EnhancementWindowClass.h"
#include "MultiEnhancementWindowClass.h"
#include "ToolTipWindowCLass.h"
#include "Screen_Destiny_Class.h"
#include "MultiFeatWindowClass.h"
#include "MultiClassWindowClass.h"
#include "MultiAbilityWindowClass.h"
#include "MultiSkillsWindowClass.h"
#include "MultiSpellsWindowClass.h"
#include "Screen_Destiny_Class.h"

//---------------------------------------------------------------------------
class InterfaceManagerClass
    {
    public:
        InterfaceManagerClass();
        virtual ~InterfaceManagerClass();
			
        void CreateMainWindow(HINSTANCE Instance, int Width, int Height, bool UseSystemFont, string FontName, long FontHeight, long FontWeight);
        void CreateChildWindows();
        void ShowChild(CHILDWINDOW Child, bool State);
        RECT GetMainWindowExtents();
        long ForwardWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
        long ForwardSubclassedMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
        void UpdateLoadFileStatus(DATAFILE File, FILESTATE NewState);
        void SetMainToDefaults();
        unsigned int LoadIcon(ICONTYPE IconType, string Name);
        bool ChildWindowVisible();
        bool ChildWindowVisible(CHILDWINDOW Child);
        void DisplayLastError(string Class, string Function, string Command);
        void SetForumExportLevel(int NewLevel);

		void ActivateItemBuilderWindow();
		void ActivateEnhancementWindow();
		void ActivateMultiEnhancementWindow(int Tree, int level, int Slot, int APAvailable);
		void ActivateDestinyWindow(int Level);
		MainScreenClass* GetMainScreen();
		UIComponentManager* GetUIComponents();
		char* GetInitialDirectory();
		void SetEnhancementWindowLevel(int Level);
		void SetEnhancementChildWindowFlag(bool State);
		EnhancementWindowClass* GetEnhancementWindowPointer();
		ToolTipWindowClass* GetToolTipWindowPointer();
		void CenterChildWindow(CHILDWINDOW Child);
        ControlWindowClass ControlWindow;
		void MultiFeatWindowSetLevel(int Level);
		void MultiFeatWindowSetIcons(vector <GraphicStruct> FeatIcons);

    private:
        HINSTANCE ProgramInstance;

        MainScreenClass MainScreen;
        LoadWindowClass LoadWindow;
        AboutWindowClass AboutWindow;
        ForumExportClass ForumExportWindow;
		ItemBuilderClass ItemBuilderWindow;
		ExportTemplateDesignWindowClass ExportTemplateDesignWindow;
		PrintWindowClass PrintWindow;
		EnhancementWindowClass EnhancementWindow;
		MultiEnhancementWindowClass MultiEnhancementWindow;
		ToolTipWindowClass ToolTipWindow;
		Screen_Destiny_Class DestinyWindow;
		MultiFeatWindowClass MultiFeatWindow;
		MultiClassWindowClass MultiClassWindow;
		MultiAbilityWindowClass MultiAbilityWindow;
		MultiSkillsWindowClass MultiSkillsWindow;
		MultiSpellsWindowClass MultiSpellsWindow;

        UIComponentManager UIComponents;
		char PathName[MAX_PATH];

        bool DataLoadVisible;
        bool AboutWindowVisible;
        bool ForumExportWindowVisible;
		bool ItemBuilderWindowVisible;
		bool ExportTemplateDesignWindowVisible;
		bool PrintWindowVisible;
		bool EnhancementWindowVisible;
		bool MultiEnhancementWindowVisible;
		bool ToolTipWindowVisible;
		bool DestinyWindowVisible;
		bool MultiFeatWindowVisible;
		bool MultiClassWindowVisible;
		bool MultiAbilityWindowVisible;
		bool MultiSkillsWindowVisible;
		bool MultiSpellsWindowVisible;

        //do not implement these two functions, instance  control!!
        InterfaceManagerClass(const InterfaceManagerClass &source);
        InterfaceManagerClass& operator=(const InterfaceManagerClass &source);
    };

extern InterfaceManagerClass InterfaceManager;

#endif
 