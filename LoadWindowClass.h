//---------------------------------------------------------------------------
#ifndef LoadWindowClassH
#define LoadWindowClassH

#include "stdafx.h"
#include "IconClass.h"

//---------------------------------------------------------------------------
class LoadWindowClass : public IconClass
    {
    public:
        LoadWindowClass();
        virtual ~LoadWindowClass();

        void Create(HINSTANCE Instance, HWND Parent);
        void Show(bool State);
        long HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);
        void UpdateLoadFileState(DATAFILE File, FILESTATE NewState);

    private:
        HWND LoadWindowHandle;
        HWND LoadRaceLabel;
        HWND LoadClassLabel;
        HWND LoadFeatLabel;
        HWND LoadSkillLabel;
        HWND LoadEnhancementLabel;
        HWND LoadSpellLabel;
		HWND LoadItemEffectLabel;
		HWND LoadItemClickyEffectLabel;
		HWND LoadItemLabel;
		HWND LoadTemplateLabel;
		HWND LoadDestinyLabel;
        GraphicStruct CheckMark;
        GraphicStruct Diamond;
        GraphicStruct FilledDiamond;
        GraphicStruct Error;
        FILESTATE RaceFileState;
        FILESTATE ClassFileState;
        FILESTATE FeatFileState;
        FILESTATE SkillFileState;
        FILESTATE EnhancementFileState;
        FILESTATE SpellFileState;
		FILESTATE ItemEffectFileState;
		FILESTATE ItemClickyEffectFileState;
		FILESTATE ItemFileState;
		FILESTATE TemplateFileState;
		FILESTATE DestinyFileState;

        void LoadGraphics();
        void DeleteGraphics();
        void DrawGraphics(HDC hdc);

        //do not implement these two functions, instance  control!!
        LoadWindowClass(const LoadWindowClass &source);
        LoadWindowClass& operator=(const LoadWindowClass &source);
    };

extern long CALLBACK WndProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);


#endif
  
