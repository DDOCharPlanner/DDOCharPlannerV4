//---------------------------------------------------------------------------
#include "MainScreenClass.h"
#include "DataClass.h"
#include "InterfaceManagerClass.h"
#include "CharacterClass.h"
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
MainScreenClass::MainScreenClass()
    {
    CurrentSelectedLevel = 1;
    Dragging = false;
    EquipmentScreenShown = false;
    EquipmentScreenCurrentSelectedSlot = NOSLOT;
	SetUp = true;
    }

//---------------------------------------------------------------------------
MainScreenClass::~MainScreenClass()
    {
    DeleteGraphics();
    DeleteObject(ArielFontSmall);
    DeleteObject(AbilityFontLarge);
    DeleteObject(AbilityFontSmall);
    DeleteObject(DefaultFont);
    DeleteObject(HighlightPen);
    DesubclassChildWindows();
    }

//---------------------------------------------------------------------------
void MainScreenClass::Create(HINSTANCE Instance, HWND Parent, bool UseSystemFont, string FN, long FH, long FW, UIComponentManager *UIComponent)
    {
    LOGBRUSH lb;
    LOGFONT lf;
	InterfaceComponentStruct *Component;
	RECT WindowRect;
    int WindowX;
    int WindowY;

    ParentWindow = Parent;
    LoadLibrary("RICHED32.DLL");
    
    UsingSystemFont = UseSystemFont;
	FontName = FN;
	FontHeight = FH;
	FontWeight = FW;

	GetWindowRect(Parent, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;	

    //Meta windows
    Component = UIComponent->GetComponentData("NameLabel", MAINWINDOW);
	NameLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("RaceClassLabel", MAINWINDOW);
	RaceClassLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("DisplayErrorsButton", MAINWINDOW);
	DisplayErrorsButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("ItemBuilderButton", MAINWINDOW);
	ItemBuilderButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("EquipmentScreenButton", MAINWINDOW);
	EquipmentScreenButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("LoadButton", MAINWINDOW);
	LoadButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("SaveButton", MAINWINDOW);
	SaveButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("ClearButton", MAINWINDOW);
	ClearButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("PrintButton", MAINWINDOW);
	PrintButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("ForumExportButton", MAINWINDOW);
	ForumExportButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("AboutButton", MAINWINDOW);
	AboutButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("QuitButton", MAINWINDOW);
	QuitButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);

	//Side Menu
	Component = UIComponent->GetComponentData("SideMenuTitle", MAINWINDOW);
	SideMenuTitle = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("SideRaceSexButton", MAINWINDOW);
	SideRaceSexButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("NameAndAlignmentButton", MAINWINDOW);
	NameAndAlignmentButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("SideClassButton", MAINWINDOW);
	SideClassButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("SideReincarnationButton", MAINWINDOW);
	SideReincarnationButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("SideAbilityButton", MAINWINDOW);
	SideAbilityButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("SideSkillButton", MAINWINDOW);
	SideSkillButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("SideSpellButton", MAINWINDOW);
	SideSpellButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("SideFeatsButton", MAINWINDOW);
	SideFeatsButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("SideDestinyButton", MAINWINDOW);
	SideDestinyButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("SideEnhancementButton", MAINWINDOW);
	SideEnhancementButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);



    //the ability box
    Component = UIComponent->GetComponentData("AbilityBoxFrame", MAINWINDOW);
	AbilityBoxFrame = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("AbilityLabel", MAINWINDOW);
	AbilityLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("AbilityModifierLabel", MAINWINDOW);
	AbilityModifierLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("StrLabel", MAINWINDOW);
	StrLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("StrLabel2", MAINWINDOW);
	StrLabel2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("DexLabel", MAINWINDOW);
	DexLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("DexLabel2", MAINWINDOW);
	DexLabel2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("ConLabel", MAINWINDOW);
	ConLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("ConLabel2", MAINWINDOW);
	ConLabel2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("IntLabel", MAINWINDOW);
	IntLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("IntLabel2", MAINWINDOW);
	IntLabel2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("WisLabel", MAINWINDOW);
	WisLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("WisLabel2", MAINWINDOW);
	WisLabel2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("ChaLabel", MAINWINDOW);
	ChaLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("ChaLabel2", MAINWINDOW);
	ChaLabel2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("StrNumber", MAINWINDOW);
	StrNumber = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("DexNumber", MAINWINDOW);
	DexNumber = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("ConNumber", MAINWINDOW);
	ConNumber = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("IntNumber", MAINWINDOW);
	IntNumber = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("WisNumber", MAINWINDOW);
	WisNumber = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("ChaNumber", MAINWINDOW);
	ChaNumber = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("StrModifier", MAINWINDOW);
	StrModifier = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("DexModifier", MAINWINDOW);
	DexModifier = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("ConModifier", MAINWINDOW);
	ConModifier = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("IntModifier", MAINWINDOW);
	IntModifier = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("WisModifier", MAINWINDOW);
	WisModifier = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("ChaModifier", MAINWINDOW);
	ChaModifier = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);

    //the ability statistics box
    Component = UIComponent->GetComponentData("AbilityStatBoxFrame", MAINWINDOW);
	AbilityStatBoxFrame = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("AbilityStatBox", MAINWINDOW);
	AbilityStatBox = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);


    //the skill box
    Component = UIComponent->GetComponentData("SkillBoxFrame", MAINWINDOW);
	SkillBoxFrame = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("SkillTitle", MAINWINDOW);
	SkillTitle = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("KeyAbilityTitle", MAINWINDOW);
	KeyAbilityTitle = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("TotalModTitle", MAINWINDOW);
	TotalModTitle = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("AbilityModTitle", MAINWINDOW);
	AbilityModTitle = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("MiscModTitle", MAINWINDOW);
	MiscModTitle = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("SkillsList", MAINWINDOW);
	SkillsList = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);

    //the instruction list box
    Component = UIComponent->GetComponentData("InstructionWindowFrame", MAINWINDOW);
	InstructionWindowFrame = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("InstructionWindowTitle", MAINWINDOW);
	InstructionWindowTitle = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("InstructionWindowList", MAINWINDOW);
	InstructionWindowList = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("HeroicPastRadioButton", MAINWINDOW);
	HeroicPastRadioButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("IconicPastRadioButton", MAINWINDOW);
	IconicPastRadioButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("EpicPastRadioButton", MAINWINDOW);
	EpicPastRadioButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);


	//Knownbox buttons
	Component = UIComponent->GetComponentData("FeatsPanelButton", MAINWINDOW);
	FeatsPanelButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("SpellsPanelButton", MAINWINDOW);
	SpellsPanelButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("EnhPanelButton", MAINWINDOW);
	EnhPanelButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("DestinyPanelButton", MAINWINDOW);
	DestinyPanelButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);

    //the feat list box
    Component = UIComponent->GetComponentData("FeatBoxFrame", MAINWINDOW);
	FeatBoxFrame = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("FeatListTitle", MAINWINDOW);
	FeatListTitle = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("FeatList", MAINWINDOW);
	FeatList = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);


	//the Enhancement List box
	Component = UIComponent->GetComponentData("EnhancementBoxFrame", MAINWINDOW);
	EnhancementBoxFrame = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("EnhancementTitle", MAINWINDOW);
	EnhancementTitle = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("EnhancementList", MAINWINDOW);
	EnhancementList = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
 
	//the spell box
    Component = UIComponent->GetComponentData("SpellBoxFrame", MAINWINDOW);
	SpellBoxFrame = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("SpellBoxTitle", MAINWINDOW);
	SpellBoxTitle = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("SpellList", MAINWINDOW);
	SpellList = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);

	//the destiny box
	Component = UIComponent->GetComponentData("DestinyBoxFrame", MAINWINDOW);
	DestinyBoxFrame = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("DestinyBoxTitle", MAINWINDOW);
	DestinyBoxTitle = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("DestinyList", MAINWINDOW);
	DestinyList = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);


    //the advancement box
    Component = UIComponent->GetComponentData("AdvancementWindowFrame", MAINWINDOW);
	AdvancementWindowFrame = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("AdvWinBonusAbilityPointsCheckBox", MAINWINDOW);
	AdvWinBonusAbilityPointsCheckBox = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("AdvWinFeatList", MAINWINDOW);
	AdvWinFeatList = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("AdvWinFirstNameInput", MAINWINDOW);
	AdvWinFirstNameInput = CreateWindowEx(WS_EX_CLIENTEDGE, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("AdvWinSurnameInput", MAINWINDOW);
	AdvWinSurnameInput = CreateWindowEx(WS_EX_CLIENTEDGE, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("AdvSkillPointSpendBox", MAINWINDOW);
	AdvSkillPointSpendBox = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("AdvWinSpellList", MAINWINDOW);
	AdvWinSpellList = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("AdvWinSpellClearButton", MAINWINDOW);
	AdvWinSpellClearButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("HeroicClassRadio", MAINWINDOW);
	HeroicClassRadioButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("IconicClassRadio", MAINWINDOW);
	IconicClassRadioButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIComponent->GetComponentData("HeroicLevelRadio", MAINWINDOW);
	HeroicLevelRadioButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIComponent->GetComponentData("EpicLevelRadio", MAINWINDOW);
	IconicLevelRadioButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);



    //the description box
    Component = UIComponent->GetComponentData("DescriptionWindow", MAINWINDOW);
	DescriptionWindow = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);

    //equipment select box
    Component = UIComponent->GetComponentData("EquipmentDisplayTitle", MAINWINDOW);
	EquipmentDisplayTitle = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("EquipmentDisplaySelectList", MAINWINDOW);
	EquipmentDisplaySelectList = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
	
	//additional Stats items
    Component = UIComponent->GetComponentData("AdditionalStatsTitle", MAINWINDOW);
	AdditionalStatsTitle = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);
    Component = UIComponent->GetComponentData("AdditionalStatsList", MAINWINDOW);
	AdditionalStatsList = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX*WindowX), static_cast<int>(Component->BaseLocationY*WindowY), static_cast<int>(Component->BaseWidth*WindowX), static_cast<int>(Component->BaseHeight*WindowY), Parent, (HMENU)Component->WindowID, Instance, nullptr);

    //background color changes
    SendMessage(DescriptionWindow, EM_SETBKGNDCOLOR, 0, RGB(0,0,0));
    GetObject(GetStockObject(DKGRAY_BRUSH), sizeof(LOGBRUSH), &lb);
    SendMessage(InstructionWindowList, EM_SETBKGNDCOLOR, 0, lb.lbColor);

    //item heights of the owner drawn list boxes
    SendMessage(AbilityStatBox, LB_SETITEMHEIGHT, 0, MAKELPARAM(20, 0));
    SendMessage(SpellList, LB_SETITEMHEIGHT, 0, MAKELPARAM(40, 0));
    SendMessage(SkillsList, LB_SETITEMHEIGHT, 0, MAKELPARAM(50, 0));
    SendMessage(FeatList, LB_SETITEMHEIGHT, 0, MAKELPARAM(50, 0));
	SendMessage(DestinyList, LB_SETITEMHEIGHT, 0, MAKELPARAM(50, 0));
	SendMessage(EnhancementList, LB_SETITEMHEIGHT, 0, MAKELPARAM(35, 0));
    SendMessage(AdvWinFeatList, LB_SETITEMHEIGHT, 0, MAKELPARAM(50, 0));
    SendMessage(AdvSkillPointSpendBox, LB_SETITEMHEIGHT, 0, MAKELPARAM(50, 0));
    SendMessage(AdvWinSpellList, LB_SETITEMHEIGHT, 0, MAKELPARAM(40, 0));
    SendMessage(EquipmentDisplaySelectList, LB_SETITEMHEIGHT, 0, MAKELPARAM(20, 0));
	SendMessage(AdditionalStatsList, LB_SETITEMHEIGHT, 0, MAKELPARAM(30, 0));

    //create some fonts
    lf.lfHeight = 20;
    lf.lfWidth = 0;
    lf.lfEscapement = 0;
    lf.lfOrientation = 0;
    lf.lfWeight = FW_MEDIUM;
    lf.lfItalic = false;
    lf.lfUnderline = false;
    lf.lfStrikeOut = false;
    lf.lfCharSet = ANSI_CHARSET;
    lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
    lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lf.lfQuality = DEFAULT_QUALITY;
    lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	StringCbCopy (lf.lfFaceName, LF_FACESIZE, TEXT("Times New Roman"));
	AbilityFontLarge = CreateFontIndirect(&lf);
	lf.lfHeight = 10;
	StringCbCopy (lf.lfFaceName, LF_FACESIZE, TEXT("Ariel"));
    AbilityFontSmall = CreateFontIndirect(&lf);
	lf.lfHeight = 14;
    ArielFontSmall = CreateFontIndirect(&lf);

    //create a default font
    lf.lfHeight = FontHeight;
    lf.lfWidth = 0;
    lf.lfEscapement = 0;
    lf.lfOrientation = 0;
    lf.lfWeight = FontWeight;
    lf.lfItalic = false;
    lf.lfUnderline = false;
    lf.lfStrikeOut = false;
    lf.lfCharSet = ANSI_CHARSET;
    lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
    lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lf.lfQuality = DEFAULT_QUALITY;
    lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	StringCbCopy (lf.lfFaceName, LF_FACESIZE, TEXT(FontName.c_str()));
	DefaultFont = CreateFontIndirect(&lf);

    //set default fonts unless the user has specified they want to use the system font
    if (UseSystemFont == false)
		{
	    SendMessage(NameLabel, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(RaceClassLabel, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(LoadButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(SaveButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(ClearButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(PrintButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(ForumExportButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(EquipmentScreenButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(AboutButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(QuitButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(ItemBuilderButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(DisplayErrorsButton, WM_SETFONT, (WPARAM)DefaultFont, 0);

		SendMessage(SideMenuTitle, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(SideRaceSexButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(NameAndAlignmentButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(SideClassButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(SideReincarnationButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(SideAbilityButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(SideSkillButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(SideSpellButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(SideFeatsButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(SideDestinyButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(SideEnhancementButton, WM_SETFONT, (WPARAM)DefaultFont, 0);

		SendMessage(DestinyPanelButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(FeatsPanelButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(SpellsPanelButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(EnhPanelButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(HeroicClassRadioButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(IconicClassRadioButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(HeroicLevelRadioButton, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(IconicLevelRadioButton, WM_SETFONT, (WPARAM)DefaultFont, 0);

	    SendMessage(StrNumber, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(DexNumber, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(ConNumber, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(IntNumber, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(WisNumber, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(ChaNumber, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(StrModifier, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(DexModifier, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(ConModifier, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(IntModifier, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(WisModifier, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(ChaModifier, WM_SETFONT, (WPARAM)DefaultFont, 0);

	    SendMessage(AbilityStatBox, WM_SETFONT, (WPARAM)DefaultFont, 0);

	    SendMessage(SpellBoxTitle, WM_SETFONT, (WPARAM)DefaultFont, 0);

	    SendMessage(SkillTitle, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(KeyAbilityTitle, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(TotalModTitle, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(AbilityModTitle, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(MiscModTitle, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(SkillsList, WM_SETFONT, (WPARAM)DefaultFont, 0);

	    SendMessage(FeatListTitle, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(FeatList, WM_SETFONT, (WPARAM)DefaultFont, 0);

		SendMessage(EnhancementTitle, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(EnhancementList, WM_SETFONT, (WPARAM)DefaultFont, 0);

		SendMessage(SpellBoxTitle, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(SpellList, WM_SETFONT, (WPARAM)DefaultFont, 0);

		SendMessage(DestinyBoxTitle, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(DestinyList, WM_SETFONT, (WPARAM)DefaultFont, 0);

	    SendMessage(InstructionWindowTitle, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(InstructionWindowList, WM_SETFONT, (WPARAM)DefaultFont, 0);

	    SendMessage(AdvWinBonusAbilityPointsCheckBox, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(AdvWinFeatList, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(AdvWinFirstNameInput, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(AdvWinSurnameInput, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(AdvSkillPointSpendBox, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(AdvWinSpellList, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(AdvWinSpellClearButton, WM_SETFONT, (WPARAM)DefaultFont, 0);

	    SendMessage(DescriptionWindow, WM_SETFONT, (WPARAM)DefaultFont, 0);

	    SendMessage(EquipmentDisplayTitle, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    SendMessage(EquipmentDisplaySelectList, WM_SETFONT, (WPARAM)DefaultFont, 0);

	    SendMessage(AdditionalStatsTitle, WM_SETFONT, (WPARAM)DefaultFont, 0);
		SendMessage(AdditionalStatsList, WM_SETFONT, (WPARAM)DefaultFont, 0);
	    }

    //set custom fonts
    SendMessage(AbilityLabel, WM_SETFONT, (WPARAM)ArielFontSmall, 0);
    SendMessage(AbilityModifierLabel, WM_SETFONT, (WPARAM)ArielFontSmall, 0);
    SendMessage(StrLabel, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
    SendMessage(DexLabel, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
    SendMessage(ConLabel, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
    SendMessage(IntLabel, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
    SendMessage(WisLabel, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
    SendMessage(ChaLabel, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
    SendMessage(StrLabel2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
    SendMessage(DexLabel2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
    SendMessage(ConLabel2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
    SendMessage(IntLabel2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
    SendMessage(WisLabel2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
    SendMessage(ChaLabel2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);

    
    //create the highlight pen
    HighlightPen = CreatePen(PS_SOLID, 0, RGB(230, 230, 30));

    //the instruction box needs to send mouse event notifications to the parent window
    SendMessage(InstructionWindowList, EM_SETEVENTMASK, 0, (LPARAM)ENM_MOUSEEVENTS);
    SendMessage(DescriptionWindow, EM_SETEVENTMASK, 0, (LPARAM)ENM_MOUSEEVENTS);

    //set limits on the name input boxes
    SendMessage(AdvWinFirstNameInput, EM_SETLIMITTEXT, 12, 0);
    SendMessage(AdvWinSurnameInput, EM_SETLIMITTEXT, 20, 0);

    //subclass windows so we can catch messages
    SubclassChildWindows();

    LoadGraphics(Parent);
	
	//Need to load the value of ASItemList Vector
	LoadASListItems();

	//disable Equipment Buttons
	EnableWindow(EquipmentScreenButton, false);
	EnableWindow(ItemBuilderButton, false);

	//disable the feature buttons not yet ready
	EnableWindow(SideAbilityButton, false);
	EnableWindow(SideSpellButton, false);
	EnableWindow(SideDestinyButton, false);
	EnableWindow(DestinyPanelButton, false);
	//EnableWindow(DestinyButton, false);


	//set Heroic Class Radio to on
	SendMessage(HeroicClassRadioButton, BM_SETCHECK, BST_CHECKED, 1);
	SendMessage(HeroicPastRadioButton, BM_SETCHECK, BST_CHECKED, 1);
    }

//---------------------------------------------------------------------------
void MainScreenClass::Show(bool State)
    {
    //meta windows
    ShowWindow(NameLabel, State);
    ShowWindow(RaceClassLabel, State);
    ShowWindow(LoadButton, State);
    ShowWindow(SaveButton, State);
    ShowWindow(ClearButton, State);
    ShowWindow(PrintButton, State);
    ShowWindow(ForumExportButton, State);
    ShowWindow(AboutButton, State);
    ShowWindow(QuitButton, State);
    ShowWindow(EquipmentScreenButton, State);
	ShowWindow(ItemBuilderButton, State);
	ShowWindow(DisplayErrorsButton, State);

	ShowWindow(HeroicClassRadioButton, false);
	ShowWindow(IconicClassRadioButton, false);
	ShowWindow(HeroicLevelRadioButton, false);
	ShowWindow(IconicLevelRadioButton, false);
	ShowWindow(HeroicPastRadioButton, false);
	ShowWindow(IconicPastRadioButton, false);
	ShowWindow(EpicPastRadioButton, false);

	//Side Menu
	ShowWindow(SideMenuTitle, State);
	ShowWindow(SideRaceSexButton, State);
	ShowWindow(NameAndAlignmentButton, State);
	ShowWindow(SideClassButton, State);
	ShowWindow(SideReincarnationButton, State);
	ShowWindow(SideAbilityButton, State);
	ShowWindow(SideSkillButton, State);
	ShowWindow(SideSpellButton, State);
	ShowWindow(SideFeatsButton, State);
	ShowWindow(SideDestinyButton, State);
	ShowWindow(SideEnhancementButton, State);

	
    //ability Box
    ShowWindow(AbilityBoxFrame, State);
    ShowWindow(AbilityLabel, State);
    ShowWindow(AbilityModifierLabel, State);
    ShowWindow(StrLabel, State);
    ShowWindow(DexLabel, State);
    ShowWindow(ConLabel, State);
    ShowWindow(IntLabel, State);
    ShowWindow(WisLabel, State);
    ShowWindow(ChaLabel, State);
    ShowWindow(StrLabel2, State);
    ShowWindow(DexLabel2, State);
    ShowWindow(ConLabel2, State);
    ShowWindow(IntLabel2, State);
    ShowWindow(WisLabel2, State);
    ShowWindow(ChaLabel2, State);
    ShowWindow(StrNumber, State);
    ShowWindow(DexNumber, State);
    ShowWindow(ConNumber, State);
    ShowWindow(IntNumber, State);
    ShowWindow(WisNumber, State);
    ShowWindow(ChaNumber, State);
    ShowWindow(StrModifier, State);
    ShowWindow(DexModifier, State);
    ShowWindow(ConModifier, State);
    ShowWindow(IntModifier, State);
    ShowWindow(WisModifier, State);
    ShowWindow(ChaModifier, State);

    //Ability Stat Box
    ShowWindow(AbilityStatBoxFrame, State);
    ShowWindow(AbilityStatBox, State);



    //Skill Box
    ShowWindow(SkillBoxFrame, State);
    ShowWindow(SkillTitle, State);
    ShowWindow(KeyAbilityTitle, State);
    ShowWindow(TotalModTitle, State);
    ShowWindow(AbilityModTitle, State);
    ShowWindow(MiscModTitle, State);
    ShowWindow(SkillsList, State);
    //Instruction Box
    ShowWindow(InstructionWindowFrame, State);
    ShowWindow(InstructionWindowTitle, State);
    ShowWindow(InstructionWindowList, State);

	//Known Panel
	ShowWindow(FeatsPanelButton, State);
	ShowWindow(SpellsPanelButton, State);
	ShowWindow(EnhPanelButton, State);
	ShowWindow(DestinyPanelButton, State);

    //Feat Box default panel to start
    ShowWindow(FeatBoxFrame, State);
    ShowWindow(FeatListTitle, State);
    ShowWindow(FeatList, State);

    //advancement box
    ShowWindow(AdvancementWindowFrame, State);

    //the description window
    ShowWindow(DescriptionWindow, State);

	if (State == true)
		DrawLevelBars(GetDC(ParentWindow));
    }

//---------------------------------------------------------------------------
long MainScreenClass::HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
    {
    PAINTSTRUCT ps;
    MSGFILTER *mf;
    char OutputString[1024];
    string String1;
    string String2;
    POINT Point;
    LRESULT Result;
    string First;
    string Sur;
    RECT Rect;
	int Length;


    switch (Message)
        {
		case WM_CREATE:
	        ResizeScreen(ParentWindow);
            return 0; 
        case WM_CLOSE:
            {
            PostQuitMessage(0);
            return 0;
            }




        case WM_COMMAND:
            {
            if (HIWORD(wParam) == EN_CHANGE)
                {
                if ((int)LOWORD(wParam) == MS_ADVWINFIRSTNAMEINPUT || (int)LOWORD(wParam) == MS_ADVWINSURNAMEINPUT)
                    {
                    *(LPWORD)OutputString = 32;
					Length = (int)SendMessage(AdvWinFirstNameInput, EM_GETLINE, 0, (LPARAM)(LPCSTR)OutputString);
					OutputString[Length] = '\0';
					String1 = OutputString;
					*(LPWORD)OutputString = 32;
					Length = (int)SendMessage(AdvWinSurnameInput, EM_GETLINE, 0, (LPARAM)(LPCSTR)OutputString);
					OutputString[Length] = '\0';
					String2 = OutputString;
                    Character.SetName(String1, String2);
                    UpdateMetaWindows();
                    return 0;
                    }
                }
            if (HIWORD(wParam) == BN_CLICKED)
                {
                if ((int)LOWORD(wParam) == MS_DISPLAYERRORBUTTON)
					{
					String1 = Character.GetErrorList();
					FillDescriptionBox(String1);
					return 0;
					}
                if ((int)LOWORD(wParam) == MS_ABOUTBUTTON)
                    {
                    InterfaceManager.ShowChild(ABOUTWINDOW, true);
                    return 0;
                    }
                if ((int)LOWORD(wParam) == MS_CLEARBUTTON)
                    {
                    CurrentSelectedLevel = 1;
                    Character.Reset();
                    FeatListParentHeading.clear();
                    FeatListSelectParentHeading.clear();
                    SpellListParentHeading.clear();
                    SpellListSelectParentHeading.clear();
                    RedrawWindow(ParentWindow, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
					SetUp = true;
                    ShowWindow(AdvWinBonusAbilityPointsCheckBox, false);
                    SendMessage(AdvWinBonusAbilityPointsCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);
                    ShowWindow(AdvWinFeatList, false);
                    ShowWindow(AdvWinFirstNameInput, false);
                    ShowWindow(AdvWinSurnameInput, false);
                    ShowWindow(AdvSkillPointSpendBox, false);
                    ShowWindow(AdvWinSpellList, false);
                    ShowWindow(AdvWinSpellClearButton, false);
					ShowWindow(HeroicClassRadioButton, false);
					ShowWindow(IconicClassRadioButton, false);
					//EnableWindow(DestinyPanelButton, false);
                    UpdateMetaWindows();
                    FillAbilityBox();
                    FillAbilityStatBox();
                    FillSpellBox();
                    FillSkillBox();
                    FillSkillSpendBox();
                    FillFeatBox();
                    FillInstructionBox();
					ResetEnhancementList();
					FillEnhancementBox();
                    SetWindowText(AdvWinFirstNameInput, "");
                    SetWindowText(AdvWinSurnameInput, "");
					ChangeInstructionWindowSelection(0);
					if (EquipmentScreenShown == true)
                        ToggleEquipmentScreen();
                    return 0;
					
                    }
                if ((int)LOWORD(wParam) == MS_LOADBUTTON)
                    {
                    Character.Load(ParentWindow);
                    FeatListParentHeading.clear();
                    FeatListSelectParentHeading.clear();
                    SpellListParentHeading.clear();
                    SpellListSelectParentHeading.clear();
                    CurrentSelectedLevel = 1;
					SetUp = true;
                    RedrawWindow(ParentWindow, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
                    ShowWindow(AdvWinBonusAbilityPointsCheckBox, false);
                    if (Character.GetAbilityFavorBonus() == false)
                        SendMessage(AdvWinBonusAbilityPointsCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);
                    else
                        SendMessage(AdvWinBonusAbilityPointsCheckBox, BM_SETCHECK, BST_CHECKED, 0);
                    ShowWindow(AdvWinFeatList, false);
                    ShowWindow(AdvWinFirstNameInput, false);
                    ShowWindow(AdvWinSurnameInput, false);
                    ShowWindow(AdvSkillPointSpendBox, false);
                    ShowWindow(AdvWinSpellList, false);
                    ShowWindow(AdvWinSpellClearButton, false);
					ShowWindow(HeroicClassRadioButton, false);
					ShowWindow(IconicClassRadioButton, false);
                    UpdateMetaWindows();
                    FillAbilityBox();
                    FillAbilityStatBox();
                    FillSpellBox();
                    FillSkillBox();
                    FillSkillSpendBox();
                    FillFeatBox();
                    FillInstructionBox();
					ResetEnhancementList();
                    Character.GetName(&First, &Sur);
                    SetWindowText(AdvWinFirstNameInput, First.c_str());
                    SetWindowText(AdvWinSurnameInput, Sur.c_str());
					ChangeInstructionWindowSelection(0);
                    return 0;
                    }
                if ((int)LOWORD(wParam) == MS_SAVEBUTTON)
                    {
                    Character.Save(ParentWindow);
                    return 0;
                    }
                if ((int)LOWORD(wParam) == MS_PRINTBUTTON)
                    {
                    InterfaceManager.ShowChild(PRINTWINDOW, true);
                    return 0;
                    }
                if ((int)LOWORD(wParam) == MS_FORUMEXPORTBUTTON)
                    {
                    InterfaceManager.SetForumExportLevel(CurrentSelectedLevel);
                    InterfaceManager.ShowChild(FORUMEXPORTWINDOW, true);
                    String1 = "{\\b {\\cf1 Forum Export:}}\\par\\par ";
                    String1 += "Your character has been {\\b {\\cf1 saved to the system clipboard}} for export to the official DDO forums. ";
                    String1 += "Note that your character has been exported {\\b {\\cf1 at the level you have currently selected}} ";
                    String1 += "(for example if you have the Level 3 bar selected in green, your character will display on the forums ";
                    String1 += "up to Level 3). To place your character on the forums, simply start a new post and in the input box, press ";
                    String1 += "{\\b {\\cf1Control-V.}} A lot of code will appear in the box. Feel free to input any text you like before or ";
                    String1 += "after the code (unless you know what you are doing, I don't recommend you place anything inside ";
                    String1 += "the pasted code). When you submit your post, {\\b {\\cf1 a nicely formatted character display will appear}} ";
                    String1 += "within your post.";
                    FillDescriptionBox(String1);
                    return 0;
                    }
                if ((int)LOWORD(wParam) == MS_QUITBUTTON)
                    {
                    PostQuitMessage(0);
                    return 0;
                    }
                if ((int)LOWORD(wParam) == MS_EQUIPMENTSCREENBUTTON)
                    {
                    ToggleEquipmentScreen();
                    return 0;
                    }
				if ((int)LOWORD(wParam) == MS_ITEMBUILDERBUTTON)
					{
					InterfaceManager.ShowChild(ITEMBUILDERWINDOW, true);
					InterfaceManager.ActivateItemBuilderWindow();
					return 0;
					}

				if ((int)LOWORD(wParam) == MS_DESTINYPANELBUTTON)
					{

						SelectKnownPanel(Destiny);
						return 0;
					}
				if ((int)LOWORD(wParam) == MS_FEATSPANELBUTTON)
				{
					SelectKnownPanel(Feats);
					return 0;
				}
				if ((int)LOWORD(wParam) == MS_SPELLSPANELBUTTON)
				{
					SelectKnownPanel(Spells);
					return 0;
				}
				if ((int)LOWORD(wParam) == MS_ENHPANELBUTTON)
				{
					SelectKnownPanel(Enh);
					return 0;
				}
				if ((int)LOWORD(wParam) == MS_SIDEREINCARNATION)
				{
					SetToReincarnation();
					return 0;
				}
				if ((int)LOWORD(wParam) == MS_SIDERACESEX)
				{
					SetToRaceAndSex();
					return 0;
				}
				if ((int)LOWORD(wParam) == MS_NAMEANDALIGNMENTBUTTON)
				{
					SetToNameAlignment();
					return 0;
				}
				if ((int)LOWORD(wParam) == MS_SIDECLASS)
				{
					Character.EnableValidations(false);
					InterfaceManager.ShowChild(MULTICLASSWINDOW, true);
					Character.EnableValidations(true);
				}
				if ((int)LOWORD(wParam) == MS_SIDEABILITY)
				{
					Character.EnableValidations(false);
					InterfaceManager.ShowChild(MULTIABILITYWINDOW, true);
					Character.EnableValidations(true);

				}
				if ((int)LOWORD(wParam) == MS_SIDESKILL)
				{
					if (Character.GetClass(20, false) != CLASSNONE)
					{
						Character.EnableValidations(false);
						InterfaceManager.ShowChild(MULTISKILLSWINDOW, true);
						Character.EnableValidations(true);
					}
					else
					{
						string Text = "Set Classes at all Levels first";
						FillDescriptionBox(Text);
					}


				}
				if ((int)LOWORD(wParam) == MS_SIDESPELL)
				{
					Character.EnableValidations(false);
					InterfaceManager.ShowChild(MULTISPELLSWINDOW, true);
					Character.EnableValidations(true);
				}
				if ((int)LOWORD(wParam) == MS_SIDEFEATS)
				{
					Character.EnableValidations(false);
					InterfaceManager.MultiFeatWindowSetIcons(FeatIcon);
					InterfaceManager.MultiFeatWindowSetLevel(CurrentSelectedLevel);
					InterfaceManager.ShowChild(MULTIFEATWINDOW, true);
					Character.EnableValidations(true);

				}
				if ((int)LOWORD(wParam) == MS_SIDEDESTINY)
				{
					Character.EnableValidations(false);
					InterfaceManager.ActivateDestinyWindow(CurrentSelectedLevel);
					InterfaceManager.ShowChild(DESTINYWINDOW, true);
					Character.EnableValidations(true);
				}
				if ((int)LOWORD(wParam) == MS_SIDEENHANCEMENTS)
				{
					Character.EnableValidations(false);
					InterfaceManager.SetEnhancementWindowLevel(CurrentSelectedLevel);
					InterfaceManager.ShowChild(ENHANCEMENTWINDOW, true);
					InterfaceManager.ActivateEnhancementWindow();
					Character.EnableValidations(true);
					return 0;
				}
                if ((int)LOWORD(wParam) == MS_ADVWINBONUSABILITY)
                    {
                    if (SendMessage(AdvWinBonusAbilityPointsCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
                        Character.SetAbilityFavorBonus(true);
                    else
                        Character.SetAbilityFavorBonus(false);
                    FillInstructionBox();
                    //InvalidateRect(Wnd, NULL, TRUE);
                    return 0;
                    }
                if ((int)LOWORD(wParam) == MS_ES_ADVWINSPELLCLEARBUTTON)
                    {
                    Character.ClearSpells();
					//erase old text
					FillSpellBox();
					FillSpellSelectBox();
                    //InvalidateRect(Wnd, NULL, TRUE);
                    return 0;
                    }
				if ((int)LOWORD(wParam) == MS_HEROICCLASS)
				{
					ClearAdvancementBox();
					DrawGraphics(Wnd, &ps);
					return 0;
				}
				if ((int)LOWORD(wParam) == MS_ICONICCLASS)
				{
					ClearAdvancementBox();
					DrawGraphics(Wnd, &ps);
					return 0;
				}
				if ((int)LOWORD(wParam) == MS_HERIOCPASTLIFE)
				{
					ClearAdvancementBox();
					DrawGraphics(Wnd, &ps);
					return 0;
				}
				if ((int)LOWORD(wParam) == MS_ICONICPASTLIFE)
				{
					ClearAdvancementBox();
					DrawGraphics(Wnd, &ps);
					return 0;
				}
				if ((int)LOWORD(wParam) == MS_EPICPASTLIFE)
				{
					ClearAdvancementBox();
					DrawGraphics(Wnd, &ps);
					return 0;
				}
                }
            return DefWindowProc(Wnd, Message, wParam, lParam);
            }
        case WM_CTLCOLORLISTBOX:
            {
            SetBkMode((HDC)wParam, TRANSPARENT);
            return (long)GetStockObject(DKGRAY_BRUSH);
            }
        case WM_CTLCOLORSTATIC:
            {
            SetBkMode((HDC)wParam, TRANSPARENT);
            if ((HWND)lParam == StrLabel || (HWND)lParam == DexLabel || (HWND)lParam == ConLabel ||
                (HWND)lParam == IntLabel || (HWND)lParam == WisLabel || (HWND)lParam == ChaLabel)
                SetTextColor((HDC)wParam, RGB(230,230,30));
            else
                SetTextColor((HDC)wParam, RGB(255,255,255));
            return (long)GetStockObject(DKGRAY_BRUSH);
            }
        case WM_DRAWITEM:
            {
            if (InterfaceManager.ChildWindowVisible() == true)
                return true;
            if ((unsigned int)wParam == MS_ABILITYSTATBOX)
                {
                DrawAbilityStatBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemID, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
                return true;
                }
            if ((unsigned int)wParam == MS_SPELLLIST)
                {
                DrawSpellBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemID, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
                return true;
                }
            if ((unsigned int)wParam == MS_SKILLSLIST)
                {
                DrawSkillBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
                return true;
                }
            if ((unsigned int)wParam == MS_FEATSLIST)
                {
                DrawFeatBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemID, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
                return true;
                }
			if ((unsigned int)wParam == MS_ENHANCEMENTLIST)
                {
                DrawEnhancementBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemID, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
                return true;
                }
            if ((unsigned int)wParam == MS_EQUIPMENTSELECTLIST)
                {
                return true;
                }
            if ((unsigned int)wParam == MS_EQUIPMENTDISPLAYSELECTLIST)
                {
                DrawEquipmentDisplaySelectBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
                return true;
                }
            if ((unsigned int)wParam == MS_ADVWINFEATSLIST)
                {
				DrawFeatSelectBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemID, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
                return true;
                }
            if ((unsigned int)wParam == MS_ADVWINSKILLSPEND)
                {
                DrawSkillSpendBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
                return true;
                }
            if ((unsigned int)wParam == MS_ADVWINSPELLLIST)
                {
                DrawSpellSelectBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemID, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
                return true;
                }
			if ((unsigned int)wParam == MS_ASLIST)
				{
				DrawAdditionalStatsBoxItem(((LPDRAWITEMSTRUCT)lParam)->hDC, ((LPDRAWITEMSTRUCT)lParam)->itemID, ((LPDRAWITEMSTRUCT)lParam)->itemData, ((LPDRAWITEMSTRUCT)lParam)->rcItem.top, ((LPDRAWITEMSTRUCT)lParam)->rcItem.left);
				return true;
				}
            return false;
            }

		case WM_KEYDOWN:
		{		
			//wchar_t test[25];
			//	swprintf(test,L"%d\n",(int)wParam);

			//	OutputDebugStringW(test);
            if ((int)wParam == VK_DOWN)	
                {
                ChangeInstructionWindowSelection(CurrentInstructionSelection+1);
                return 0;
                }
            if ((int)wParam == VK_UP)
                {
                ChangeInstructionWindowSelection(CurrentInstructionSelection-1);
                return 0;
                }
			if ((int)wParam == (VK_F9))
			{
					//enable feature buttons that are being worked on
					EnableWindow(DestinyPanelButton, true);
					EnableWindow(SideDestinyButton, true);

					EnableWindow(SideAbilityButton, true);
					EnableWindow(SideSkillButton, true);
					EnableWindow(SideSpellButton, true);
					return 0;


			}
            }

        case WM_LBUTTONDOWN:
            {
				HandleLeftMouseButtonClick(LOWORD(lParam), HIWORD(lParam));
				
            return 0;
            }
        case WM_LBUTTONUP:
            {
            if (Dragging == true)
            {
                Character.EnableValidations(false); // CDE: Avoid too many redraw of UI
                EndDragAndDropOperation((int)LOWORD(lParam), (int)HIWORD(lParam));
                Character.EnableValidations(true);
            }
            return 0;
            }
        case WM_MOUSEWHEEL:
            {
            GetWindowRect(AbilityStatBox, &Rect);
            if ((short)LOWORD(lParam) >= Rect.left && (short)LOWORD(lParam) <= Rect.right && (short)HIWORD(lParam) >= Rect.top && (short)HIWORD(lParam) <= Rect.bottom)
                {
                if ((short)HIWORD(wParam) > 0)
                    SendMessage(AbilityStatBox, WM_VSCROLL, SB_LINEUP, 0);
                else
                    SendMessage(AbilityStatBox, WM_VSCROLL, SB_LINEDOWN, 0);
                }
            GetWindowRect(SkillsList, &Rect);
            if ((short)LOWORD(lParam) >= Rect.left && (short)LOWORD(lParam) <= Rect.right && (short)HIWORD(lParam) >= Rect.top && (short)HIWORD(lParam) <= Rect.bottom)
                {
                if ((short)HIWORD(wParam) > 0)
                    SendMessage(SkillsList, WM_VSCROLL, SB_LINEUP, 0);
                else
                    SendMessage(SkillsList, WM_VSCROLL, SB_LINEDOWN, 0);
                }
            GetWindowRect(FeatList, &Rect);
            if ((short)LOWORD(lParam) >= Rect.left && (short)LOWORD(lParam) <= Rect.right && (short)HIWORD(lParam) >= Rect.top && (short)HIWORD(lParam) <= Rect.bottom)
                {
                if ((short)HIWORD(wParam) > 0)
                    SendMessage(FeatList, WM_VSCROLL, SB_LINEUP, 0);
                else
                    SendMessage(FeatList, WM_VSCROLL, SB_LINEDOWN, 0);
                }
            GetWindowRect(SpellList, &Rect);
            if ((short)LOWORD(lParam) >= Rect.left && (short)LOWORD(lParam) <= Rect.right && (short)HIWORD(lParam) >= Rect.top && (short)HIWORD(lParam) <= Rect.bottom)
                {
                if ((short)HIWORD(wParam) > 0)
                    SendMessage(SpellList, WM_VSCROLL, SB_LINEUP, 0);
                else
                    SendMessage(SpellList, WM_VSCROLL, SB_LINEDOWN, 0);
                }
			GetWindowRect(EnhancementList, &Rect);
			if ((short)LOWORD(lParam) >= Rect.left && (short)LOWORD(lParam) <= Rect.right && (short)HIWORD(lParam) >= Rect.top && (short)HIWORD(lParam) <= Rect.bottom)
				{
				if ((short)HIWORD(wParam) > 0)
					SendMessage(EnhancementList, WM_VSCROLL, SB_LINEUP, 0);
				else
					SendMessage(EnhancementList, WM_VSCROLL, SB_LINEDOWN, 0);
				}
            GetWindowRect(AdvWinFeatList, &Rect);
            if ((short)LOWORD(lParam) >= Rect.left && (short)LOWORD(lParam) <= Rect.right && (short)HIWORD(lParam) >= Rect.top && (short)HIWORD(lParam) <= Rect.bottom)
                {
                if ((short)HIWORD(wParam) > 0)
                    SendMessage(AdvWinFeatList, WM_VSCROLL, SB_LINEUP, 0);
                else
                    SendMessage(AdvWinFeatList, WM_VSCROLL, SB_LINEDOWN, 0);
                }
            GetWindowRect(AdvSkillPointSpendBox, &Rect);
            if ((short)LOWORD(lParam) >= Rect.left && (short)LOWORD(lParam) <= Rect.right && (short)HIWORD(lParam) >= Rect.top && (short)HIWORD(lParam) <= Rect.bottom)
                {
                if ((short)HIWORD(wParam) > 0)
                    SendMessage(AdvSkillPointSpendBox, WM_VSCROLL, SB_LINEUP, 0);
                else
                    SendMessage(AdvSkillPointSpendBox, WM_VSCROLL, SB_LINEDOWN, 0);
                }
            GetWindowRect(AdvWinSpellList, &Rect);
            if ((short)LOWORD(lParam) >= Rect.left && (short)LOWORD(lParam) <= Rect.right && (short)HIWORD(lParam) >= Rect.top && (short)HIWORD(lParam) <= Rect.bottom)
                {
                if ((short)HIWORD(wParam) > 0)
                    SendMessage(AdvWinSpellList, WM_VSCROLL, SB_LINEUP, 0);
                else
                    SendMessage(AdvWinSpellList, WM_VSCROLL, SB_LINEDOWN, 0);
                }
            GetWindowRect(DescriptionWindow, &Rect);
            if ((short)LOWORD(lParam) >= Rect.left && (short)LOWORD(lParam) <= Rect.right && (short)HIWORD(lParam) >= Rect.top && (short)HIWORD(lParam) <= Rect.bottom)
                {
                if ((short)HIWORD(wParam) > 0)
                    SendMessage(DescriptionWindow, WM_VSCROLL, SB_LINEUP, 0);
                else
                    SendMessage(DescriptionWindow, WM_VSCROLL, SB_LINEDOWN, 0);
                }
            GetWindowRect(EquipmentDisplaySelectList, &Rect);
            if ((short)LOWORD(lParam) >= Rect.left && (short)LOWORD(lParam) <= Rect.right && (short)HIWORD(lParam) >= Rect.top && (short)HIWORD(lParam) <= Rect.bottom)
                {
                if ((short)HIWORD(wParam) > 0)
                    SendMessage(EquipmentDisplaySelectList, WM_VSCROLL, SB_LINEUP, 0);
                else
                    SendMessage(EquipmentDisplaySelectList, WM_VSCROLL, SB_LINEDOWN, 0);
                }
            return 0;
            }
        case WM_NOTIFY:
            {
            if (wParam == MS_IW_LIST)
                {
                if (InterfaceManager.ChildWindowVisible() == true)
                    return -1;
                if (((NMHDR*)lParam)->code == EN_MSGFILTER)
                    {
                    //don't change if the equipment window is up
                    if (EquipmentScreenShown == true)
                        return -1;
                    mf = (MSGFILTER*)lParam;
                    if (mf->msg == WM_LBUTTONDOWN)
                        {
                        Point.x = LOWORD(mf->lParam);
                        Point.y = HIWORD(mf->lParam);
                        Result = SendMessage(InstructionWindowList, EM_CHARFROMPOS, 0, (long)&Point);
                        ChangeInstructionWindowSelection(SendMessage(InstructionWindowList, EM_EXLINEFROMCHAR, 0, LOWORD(Result)));
                        return -1;
                        }
                    }
                }
            if (wParam == MS_DESCRIPTIONWINDOW)
                {
                if (((NMHDR*)lParam)->code == EN_MSGFILTER)
                    {
                    mf = (MSGFILTER*)lParam;
                    if (mf->msg == WM_LBUTTONDOWN)
                        return -1;
                    }
                }
            return 0;
            }
	    case WM_ERASEBKGND:
			{
			return 1;
			}
        case WM_PAINT:
            {
            BeginPaint(Wnd, &ps);
            DrawGraphics(Wnd, &ps);
            EndPaint(Wnd, &ps);
            return 1;
            }
        case WM_SETCURSOR:
            {
            if (Dragging == true)
                {
                SetCursor(Cursor);
                return 1;
                }
            if ((HWND)wParam == InstructionWindowList || (HWND)wParam == DescriptionWindow)
                {
                SetCursor(LoadCursor(NULL, IDC_ARROW));
                return 1;
                }
            return DefWindowProc(Wnd, Message, wParam, lParam);
            }
		case WM_EXITSIZEMOVE:
		{
			CheckChildWindows();
			return 0;
		}
		case WM_SIZE: // CDE: For maximize
		{
			CheckChildWindows();
		}


		case WM_SIZING:
			{
			if (Wnd == ParentWindow)
				{
				ResizeScreen(Wnd);
				}
			return 0;
			}
			
		case WM_DESTROY: 
			{
            // Free the bitmap resources. 
			DeleteObject(hdcMem); 
            DeleteObject(hbmMem);
			return 0; 
			}
            

			
        default:
            {
            return DefWindowProc(Wnd, Message, wParam, lParam);
            }
        }
   }
//---------------------------------------------------------------------------
   void MainScreenClass::CheckChildWindows()
   {
	   if (InterfaceManager.ChildWindowVisible(ABOUTWINDOW))
	   {
		   InterfaceManager.CenterChildWindow(ABOUTWINDOW);
	   }
	   if (InterfaceManager.ChildWindowVisible(FORUMEXPORTWINDOW))
	   {
		   InterfaceManager.CenterChildWindow(FORUMEXPORTWINDOW);
	   }
	   if (InterfaceManager.ChildWindowVisible(ITEMBUILDERWINDOW))
	   {
		   InterfaceManager.CenterChildWindow(ITEMBUILDERWINDOW);
	   }
	   if (InterfaceManager.ChildWindowVisible(PRINTWINDOW))
	   {
		   InterfaceManager.CenterChildWindow(PRINTWINDOW);
	   }
	   if (InterfaceManager.ChildWindowVisible(ENHANCEMENTWINDOW))
	   {
		   InterfaceManager.CenterChildWindow(ENHANCEMENTWINDOW);
	   }
	   if (InterfaceManager.ChildWindowVisible(MULTIENHANCEMENTWINDOW))
	   {
		   InterfaceManager.CenterChildWindow(MULTIENHANCEMENTWINDOW);
	   }
	   if (InterfaceManager.ChildWindowVisible(TOOLTIPWINDOW))
	   {
		   InterfaceManager.CenterChildWindow(TOOLTIPWINDOW);
	   }
	   if (InterfaceManager.ChildWindowVisible(DESTINYWINDOW))
	   {
		   InterfaceManager.CenterChildWindow(DESTINYWINDOW);
	   }
	   if (InterfaceManager.ChildWindowVisible(MULTIDESTINYWINDOW))
	   {
		   InterfaceManager.CenterChildWindow(MULTIDESTINYWINDOW);
	   }
	   if (InterfaceManager.ChildWindowVisible(MULTIFEATWINDOW))
	   {
		   InterfaceManager.CenterChildWindow(MULTIFEATWINDOW);
	   }
	   if (InterfaceManager.ChildWindowVisible(MULTICLASSWINDOW))
	   {
		   InterfaceManager.CenterChildWindow(MULTICLASSWINDOW);
	   }
	   if (InterfaceManager.ChildWindowVisible(MULTIABILITYWINDOW))
	   {
		   InterfaceManager.CenterChildWindow(MULTIABILITYWINDOW);
	   }
	   if (InterfaceManager.ChildWindowVisible(MULTISKILLSWINDOW))
	   {
		   InterfaceManager.CenterChildWindow(MULTISKILLSWINDOW);
	   }
	   if (InterfaceManager.ChildWindowVisible(MULTISPELLSWINDOW))
	   {
		   InterfaceManager.CenterChildWindow(MULTISPELLSWINDOW);

	   }
	   if (InterfaceManager.ChildWindowVisible(FORUMEXPORTWINDOW))
	   {
		   InterfaceManager.CenterChildWindow(FORUMEXPORTWINDOW);

	   }

   }

//---------------------------------------------------------------------------
long MainScreenClass::HandleSubclassedMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
    {
    WNDPROC OriginalProc;
    DWORD Selection;
    string Description;
    int xPos;
    float PointsSpent;
    float PointLimit;
    float PointRaise;
    int Item;
    int PointsRemain;
    string Text;
    int Position;
	int FeatCount;
    ostringstream ss;
    FeatDataClass *Feat;

    switch (Message)
        {
        case WM_CHAR:
			{
			if (LOWORD(wParam) == VK_TAB)
				return 0;		//prevent the annoying 'ding' sound when tabbing
			break;
			}
        case WM_KEYDOWN:
			{
			//handle the TAB key for the input boxes
			if (Wnd == AdvWinFirstNameInput)
				{
				if (LOWORD(wParam) == VK_TAB)
					{
					SetFocus(AdvWinSurnameInput);
					return 0;
					}
				}
			if (Wnd == AdvWinSurnameInput)
				{
				if (LOWORD(wParam) == VK_TAB)
					{
					SetFocus(AdvWinFirstNameInput);
					return 0;
					}
				}
			break;
			}
        case WM_LBUTTONDBLCLK:
            {
            if (Wnd == AbilityStatBox)
                return 0;
            if (Wnd == InstructionWindowList)
                return 0;
            if (Wnd == DescriptionWindow)
                return 0;
            if (Wnd == SpellList)
                return 0;
            if (Wnd == FeatList)
                return 0;
			if (Wnd == EnhancementList)
				return 0;
            if (Wnd == SkillsList)
                return 0;
            if (Wnd == AdvWinFeatList)
                return 0;
            if (Wnd == AdvWinSpellList)
                return 0;
            if (Wnd == AdvSkillPointSpendBox)
                return 0;
            if (Wnd == EquipmentDisplaySelectList)
                return 0;
            break;
            }
        case WM_LBUTTONDOWN:
            {
            if (InterfaceManager.ChildWindowVisible() == true)
                return 0;
            if (Wnd == AbilityStatBox)
                return 0;
            if (Wnd == AdvWinFeatList)
                {
				FeatCount = 0;
                Selection = SendMessage(AdvWinFeatList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(AdvWinFeatList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                if (IconDrag == 999999)
                    {
                    //click on a parent heading. change the collapse state
                    for (unsigned int i=0; i<FeatListSelectParentHeading.size(); i++)
                        {
                        if (FeatListSelectParentHeading[i].ListIndex == Selection)
                            {
                            FeatListSelectParentHeading[i].Collapsed = !FeatListSelectParentHeading[i].Collapsed;
                            break;
                            }
                        }
                    Position = SendMessage(AdvWinFeatList, LB_GETTOPINDEX, 0, 0);
                    FillFeatSelectBox();
                    SendMessage(AdvWinFeatList, LB_SETTOPINDEX, (WPARAM)Position, 0);
                    IconDrag = -1;
                    return 0;
                    }
                if (IconDrag > 999999)
                    IconDrag -= 1000000;
                Feat = Data.GetFeatPointer(IconDrag);
                Description = "{\\b ";
                Description += Feat->GetFeatName(true);
                Description += "} \\par\\par ";

				Description += Feat->GetFeatDescription();
				//replace any string placeholders with their appropriate descriptions
				while (Description.find("$RACE") != std::string::npos)
					Description.replace(Description.find("$RACE"), 5, Character.GetRaceString(true));
				//add the feat prereqs
                Description += " \\par\\par ";
				Description += Feat->GetPrereqString(CurrentSelectedLevel);
				FillDescriptionBox(Description, FeatIcon[Feat->GetFeatIconIndex()].Graphic);
                if (Feat->HaveAllFeatPrereqs(CurrentSelectedLevel) != PREREQ_PASS)
                    {
                    IconDrag = -1;
                    return 0;
                    }
                Dragging = true;
                Cursor = CreateCursorFromBitmap(ParentWindow, Palette, &FeatIcon[Feat->GetFeatIconIndex()], RGB(0,0,0), 16, 16);
                SetCursor(Cursor);
                return 0;
                }
            if (Wnd == AdvWinSpellList)
                {
                Selection = SendMessage(AdvWinSpellList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(AdvWinSpellList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                if (IconDrag == 999999)
                    {
                    //click on a parent heading. change the collapse state
                    for (unsigned int i=0; i<SpellListSelectParentHeading.size(); i++)
                        {
                        if (SpellListSelectParentHeading[i].ListIndex == Selection)
                            {
                            SpellListSelectParentHeading[i].Collapsed = !SpellListSelectParentHeading[i].Collapsed;
                            break;
                            }
                        }
                    Position = SendMessage(AdvWinSpellList, LB_GETTOPINDEX, 0, 0);
                    FillSpellSelectBox();
                    SendMessage(AdvWinSpellList, LB_SETTOPINDEX, (WPARAM)Position, 0);
                    IconDrag = -1;
                    return 0;
                    }
                Description = CreateSpellDescription(IconDrag);
                FillDescriptionBox(Description);
                Cursor = CreateCursorFromBitmap(ParentWindow, Palette, &SpellIcon[Data.GetSpellIconIndex(IconDrag)], RGB(0,0,0), 16, 16);
                Dragging = true;
                SetCursor(Cursor);
                return 0;
                }
            if (Wnd == SpellList)
                {
                Selection = SendMessage(SpellList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(SpellList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                if (IconDrag == 999999)
                    {
                    //click on a parent heading. change the collapse state
                    for (unsigned int i=0; i<SpellListParentHeading.size(); i++)
                        {
                        if (SpellListParentHeading[i].ListIndex == Selection)
                            {
                            SpellListParentHeading[i].Collapsed = !SpellListParentHeading[i].Collapsed;
                            break;
                            }
                        }
                    Position = SendMessage(SpellList, LB_GETTOPINDEX, 0, 0);
                    FillSpellBox();
                    SendMessage(SpellList, LB_SETTOPINDEX, (WPARAM)Position, 0);
                    IconDrag = -1;
                    return 0;
                    }
                Description = CreateSpellDescription(IconDrag);
                FillDescriptionBox(Description);
                return 0;
                }
			if (Wnd == EnhancementList)
				{
				Selection = SendMessage(EnhancementList, LB_ITEMFROMPOINT, 0, lParam);
				IconDrag = SendMessage(EnhancementList, LB_GETITEMDATA, Selection, 0);
				if (IconDrag == -1)
					return 0;
				if (IconDrag == 999999)
					{
					//click on a parent heading, change the collapse state
					for (unsigned int i=0; i<SelectedEnhancementsParentHeading.size(); i++)
						{
						if (SelectedEnhancementsParentHeading[i].ListIndex == Selection)
							{
							SelectedEnhancementsParentHeading[i].Collapsed = !SelectedEnhancementsParentHeading[i].Collapsed;
							break;
							}
						}
					Position = SendMessage(EnhancementList, LB_GETTOPINDEX, 0, 0);
					FillEnhancementBox();
					SendMessage(EnhancementList, LB_SETTOPINDEX, (WPARAM)Position, 0);
					IconDrag = -1;
					return 0;
					}
				//TODO: Code to fill Description Box
				return 0;
				}
            if (Wnd == FeatList)
                {
				FeatCount = 0;
                Selection = SendMessage(FeatList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(FeatList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                if (IconDrag == 999999)
                    {
                    //click on a parent heading. change the collapse state
                    for (unsigned int i=0; i<FeatListParentHeading.size(); i++)
                        {
                        if (FeatListParentHeading[i].ListIndex == Selection)
                            {
                            FeatListParentHeading[i].Collapsed = !FeatListParentHeading[i].Collapsed;
                            break;
                            }
                        }
                    Position = SendMessage(FeatList, LB_GETTOPINDEX, 0, 0);
                    FillFeatBox();
                    SendMessage(FeatList, LB_SETTOPINDEX, (WPARAM)Position, 0);
                    IconDrag = -1;
                    return 0;
                    }
                if (IconDrag > 999999)
                    IconDrag -= 1000000;
                Feat = Data.GetFeatPointer(IconDrag);
                Description = "{\\b ";
                Description += Feat->GetFeatName(true);
                Description += "} \\par";
				FeatCount = Character.CountFeat(Feat->GetFeatName(true), CurrentSelectedLevel);
				if (FeatCount > 1)
				{
					Description += " {\\b Aquired: ";
					Description += to_string(FeatCount);
					Description += " times} \\par\\par ";
				}
				else
					Description += "\\par ";
				Description += Feat->GetFeatDescription();


//                if (Data.GetFeatPrereqDescription(IconDrag).size() > 0)
//                    {
//                    Description += "\\par\\par {\\ul REQUIRES:} \\par ";
//                    Description += Data.GetFeatPrereqDescription(IconDrag);
//                    }
				//replace any string placeholders with their appropriate descriptions
				while (Description.find("$RACE") != std::string::npos)
					Description.replace(Description.find("$RACE"), 5, Character.GetRaceString(true));
				//add in the prereqs lists
                Description += " \\par\\par ";
				Description += Feat->GetPrereqString(CurrentSelectedLevel);
				FillDescriptionBox(Description);
                return 0;
                }
            if (Wnd == SkillsList)
                {
                Selection = LOWORD(SendMessage(SkillsList, LB_ITEMFROMPOINT, 0, lParam));
                Item = SendMessage(SkillsList, LB_GETITEMDATA, Selection, 0);
                if (Item > 99)
                    Item -= 100;
                Description = "{\\b ";
                Description += Data.GetSkillName(Item);
                Description += "} \\par\\par ";
                Description += Data.GetSkillDescription(Item);
                FillDescriptionBox(Description);
                return 0;
                }
            if (Wnd == AdvSkillPointSpendBox)
                {
                Selection = LOWORD(SendMessage(AdvSkillPointSpendBox, LB_ITEMFROMPOINT, 0, lParam));
                Item = SendMessage(AdvSkillPointSpendBox, LB_GETITEMDATA, Selection, 0);
                if (Item > 99)
                    Item -= 100;
                Description = "{\\b ";
                Description += Data.GetSkillName(Item);
                Description += "} \\par\\par ";
                Description += Data.GetSkillDescription(Item);
                FillDescriptionBox(Description);
                xPos = (int)LOWORD(lParam);
                if (xPos >=185 && xPos <=206)
                    {
                    PointsSpent = (float)Character.GetLevelSkillPointsSpent(static_cast<SKILLS>(Item), CurrentSelectedLevel);
                    if (PointsSpent > 0)
                        {
                        Character.SpendSkillPoint(static_cast<SKILLS>(Item), CurrentSelectedLevel, -1);
                        RedrawWindow(SkillsList, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
                        RedrawWindow(AdvSkillPointSpendBox, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
						ClearAdvancementBox();
                        FillInstructionBox();
						//InvalidateRect(Wnd, NULL, TRUE);
                        }
                    }
                if (xPos >=235 && xPos <=256)
                    {
                    PointsSpent = Character.GetTotalSkillPointsSpentDisplay(static_cast<SKILLS>(Item), CurrentSelectedLevel);
                    if (Data.IsSkillPrimary(Character.GetClass(CurrentSelectedLevel), Item) == true)
						PointRaise = 1.0f;
                    else
						PointRaise = 0.5f;
                    PointLimit = Character.GetSkillPointSpendLimit(static_cast<SKILLS>(Item), CurrentSelectedLevel);
                    PointsRemain = Character.CalculateAvailableSkillPoints(CurrentSelectedLevel);
                    if ((PointsSpent + PointRaise) <= PointLimit && PointsRemain > 0)
                        {
                        Character.SpendSkillPoint(static_cast<SKILLS>(Item), CurrentSelectedLevel, 1);
                        RedrawWindow(SkillsList, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
                        RedrawWindow(AdvSkillPointSpendBox, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
						ClearAdvancementBox();
                        FillInstructionBox();
						//InvalidateRect(Wnd, NULL, TRUE);
                        }
                    }
                return 0;
                }
           if (Wnd == EquipmentDisplaySelectList)
                {
                Selection = SendMessage(EquipmentDisplaySelectList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(EquipmentDisplaySelectList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                ChangeCurrentActiveEquipment(IconDrag);
                return 0;
                }
            if (Wnd == AdditionalStatsList)
                {
                Selection = SendMessage(AdditionalStatsList, LB_ITEMFROMPOINT, 0, lParam);
                IconDrag = SendMessage(AdditionalStatsList, LB_GETITEMDATA, Selection, 0);
                if (IconDrag == -1)
                    return 0;
                if (IconDrag == 999999)
                    {
                    //click on a parent heading. change the collapse state
                    for (unsigned int i=0; i<ASListParentHeading.size(); i++)
                        {
                        if (ASListParentHeading[i].ListIndex == Selection)
                            {
                            ASListParentHeading[i].Collapsed = !ASListParentHeading[i].Collapsed;
                            break;
                            }
                        }
                    Position = SendMessage(AdditionalStatsList, LB_GETTOPINDEX, 0, 0);
                    FillAdditionalStatsBox();
                    SendMessage(AdditionalStatsList, LB_SETTOPINDEX, (WPARAM)Position, 0);
                    IconDrag = -1;
                    return 0;
                    }
                if (IconDrag > 999999)
                    IconDrag -= 1000000;
                return 0;
                }
            break;
            }
        case WM_RBUTTONUP:
            {
            if (Wnd == InstructionWindowList)
                return 0;
            if (Wnd == DescriptionWindow)
                return 0;
            break;
            }
        case WM_LBUTTONUP:
            {
            if (Dragging == true)
                EndDragAndDropOperation((int)LOWORD(lParam), (int)HIWORD(lParam));
            break;
            }
        }

    OriginalProc = GetOriginalWinProc(Wnd);
    return CallWindowProc(OriginalProc, Wnd, Message, wParam, lParam);
    }
//--------------------------------------------------------------------------
	void MainScreenClass::SelectKnownPanel(int PanelType)
	{
		ClearKnownBox();
		///turn off all panel items
		ShowWindow(FeatBoxFrame, false);
		ShowWindow(FeatListTitle, false);
		ShowWindow(FeatList, false);
		ShowWindow(EnhancementBoxFrame, false);
		ShowWindow(EnhancementTitle, false);
		ShowWindow(EnhancementList, false);
		ShowWindow(SpellBoxFrame, false);
		ShowWindow(SpellBoxTitle, false);
		ShowWindow(SpellList, false);
		ShowWindow(DestinyBoxFrame, false);
		ShowWindow(DestinyBoxTitle, false);
		ShowWindow(DestinyList, false);
		switch (PanelType)
		{
		case (int)Feats:
			{
				ShowWindow(FeatBoxFrame, true);
				ShowWindow(FeatListTitle, true);
				ShowWindow(FeatList, true);
				FillFeatBox();
				break;
			}
		case (int)Enh:
			{
				ShowWindow(EnhancementBoxFrame, true);
				ShowWindow(EnhancementTitle, true);
				ShowWindow(EnhancementList, true);
				FillEnhancementBox();
				break;
			}
		case (int)Spells:
			{
				ShowWindow(SpellBoxFrame, true);
				ShowWindow(SpellBoxTitle, true);
				ShowWindow(SpellList, true);
				FillSpellBox();
				break;
			}
		case (int)Destiny:
			{
				ShowWindow(DestinyBoxFrame, true);
				ShowWindow(DestinyBoxTitle, true);
				ShowWindow(DestinyList, true);
				break;
			}
		default:
			break;
		}

			

	}



//---------------------------------------------------------------------------
void MainScreenClass::SetToDefault()
    {
    int CurrentRace;

    CurrentRace = Character.GetRace();
    CurrentSelectedLevel = 1;
    CurrentInstructionSelection=0;
	SetUp = true;
    UpdateMetaWindows();
    FillAbilityBox();
    FillAbilityStatBox();
    //FillSpellBox();
    FillSkillBox();
    FillSkillSpendBox();
    FillFeatBox();
	FillInstructionBox();
	ChangeInstructionWindowSelection(0);
	FillDescriptionBox(Data.GetRaceDescription(CurrentRace));
    SetWindowText(AdvWinFirstNameInput, "");
    SetWindowText(AdvWinSurnameInput, "");
    }
//------------------------------------------------------------------------
void MainScreenClass::SetToRaceAndSex()
{
	int CurrentRace;
	string NewInstruction;
	int Index;
	int  Value;
	Index = 0;
	Character.EnableValidations(false);
	RedrawWindow(ParentWindow, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

	CurrentSelectedLevel = 1;
	NewInstruction = Character.GetInstructionString(CurrentSelectedLevel, Index, &Value);
	while (NewInstruction != "")
	{
		if (NewInstruction == "Select a Race and Sex")
			break;
		Index += 1;
		NewInstruction = Character.GetInstructionString(CurrentSelectedLevel, Index, &Value);
	}

	CurrentInstructionSelection = Index;
	ShowWindow(AdvWinBonusAbilityPointsCheckBox, false);
	ShowWindow(AdvWinFeatList, false);
	ShowWindow(AdvWinFirstNameInput, false);
	ShowWindow(AdvWinSurnameInput, false);
	ShowWindow(AdvSkillPointSpendBox, false);
	ShowWindow(AdvWinSpellList, false);
	ShowWindow(AdvWinSpellClearButton, false);
	ShowWindow(HeroicClassRadioButton, true);
	ShowWindow(IconicClassRadioButton, true);
	CurrentRace = Character.GetRace();
	FillInstructionBox();
	FillAbilityBox();
	FillAbilityStatBox();
	FillSpellBox();
	FillSkillBox();
	FillSkillSpendBox();
	FillFeatBox();
	UpdateSelectedEnhancements();
	FillEnhancementBox();
	UpdateMetaWindows();
	Character.EnableValidations(true);
}

//------------------------------------------------------------------------

void MainScreenClass::SetToReincarnation()
{
	int CurrentRace;

	string NewInstruction;
	int Index;
	int  Value;
	Index = 0;

	CurrentSelectedLevel = 1;
	NewInstruction = Character.GetInstructionString(CurrentSelectedLevel, Index, &Value);
	while (NewInstruction != "")
	{
		if (NewInstruction == "Set Past Lives")
			break;
		Index += 1;
		NewInstruction = Character.GetInstructionString(CurrentSelectedLevel, Index, &Value);
	}
	CurrentInstructionSelection = Index;
	Character.EnableValidations(false);
	RedrawWindow(ParentWindow, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	ShowWindow(AdvWinBonusAbilityPointsCheckBox, false);
	ShowWindow(AdvWinFeatList, false);
	ShowWindow(AdvWinFirstNameInput, false);
	ShowWindow(AdvWinSurnameInput, false);
	ShowWindow(AdvSkillPointSpendBox, false);
	ShowWindow(AdvWinSpellList, false);
	ShowWindow(AdvWinSpellClearButton, false);
	ShowWindow(HeroicClassRadioButton, false);
	ShowWindow(IconicClassRadioButton, false);
	CurrentRace = Character.GetRace();
	FillInstructionBox();
	FillAbilityBox();
	FillAbilityStatBox();
	FillSpellBox();
	FillSkillBox();
	FillSkillSpendBox();
	FillFeatBox();
	UpdateSelectedEnhancements();
	FillEnhancementBox();
	UpdateMetaWindows();
	Character.EnableValidations(true);



}


//-------------------------------------------------------------------------

void MainScreenClass::SetToNameAlignment()
{
	int CurrentRace;

	string NewInstruction;
	int Index;
	int  Value;
	Index = 0;

	CurrentSelectedLevel = 1;
	NewInstruction = Character.GetInstructionString(CurrentSelectedLevel, Index, &Value);
	while (NewInstruction != "")
	{
		if (NewInstruction == "Select a Name and Alignment")
			break;
		Index += 1;
		NewInstruction = Character.GetInstructionString(CurrentSelectedLevel, Index, &Value);
	}
	CurrentInstructionSelection = Index;
	Character.EnableValidations(false);
	RedrawWindow(ParentWindow, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

	ShowWindow(AdvWinBonusAbilityPointsCheckBox, false);
	ShowWindow(AdvWinFeatList, false);
	ShowWindow(AdvWinFirstNameInput, true);
	ShowWindow(AdvWinSurnameInput, true);
	ShowWindow(AdvSkillPointSpendBox, false);
	ShowWindow(AdvWinSpellList, false);
	ShowWindow(AdvWinSpellClearButton, false);
	ShowWindow(HeroicClassRadioButton, false);
	ShowWindow(IconicClassRadioButton, false);
	CurrentRace = Character.GetRace();
	FillInstructionBox();
	FillAbilityBox();
	FillAbilityStatBox();
	FillSpellBox();
	FillSkillBox();
	FillSkillSpendBox();
	FillFeatBox();
	UpdateSelectedEnhancements();
	FillEnhancementBox();
	UpdateMetaWindows();
	Character.EnableValidations(true);
}


//---------------------------------------------------------------------------
void MainScreenClass::UpdateMetaWindows()
    {
    string Text;
    ostringstream ss;
	int ClassLevel[NUMCLASSES];
   // bool First;
    string FirstName;
    string SurName;

    Character.GetName(&FirstName, &SurName);
    ss << FirstName << " " << SurName;
    Text = ss.str();
    SendMessage(NameLabel, WM_SETTEXT, 0, (LPARAM)Text.c_str());
    for (unsigned int i=0; i<NUMCLASSES; i++)
        ClassLevel[i] = Character.GetClassLevel(CLASS(i), CurrentSelectedLevel);
    ss.str("");
    ss << "Level " << CurrentSelectedLevel << " ";
    ss << Data.GetAlignmentString(Character.GetAlignment()) << " ";
    ss << Character.GetRaceString();
    if (Character.GetSex() == MALE)
        ss << " Male (";
    else
        ss << " Female (";
 //   First = true;
 //   if (ClassLevel[0] > 0)
 //       {
 //       ss << ClassLevel[0] << " Fighter";
 //       First = false;
 //       }
 //   if (ClassLevel[1] > 0)
 //       {
 //       if (First == false)
 //           ss << " \\ ";
 //       ss << ClassLevel[1] << " Paladin";
 //       First = false;
 //       }
 //   if (ClassLevel[2] > 0)
 //       {
 //       if (First == false)
 //           ss << " \\ ";
 //       ss << ClassLevel[2] << " Barbarian";
 //       First = false;
	//	}
	//if (ClassLevel[3] > 0)
	//	{
	//	if (First == false)
	//		ss << " \\ ";
	//	ss << ClassLevel[3] << " Monk";
	//	First = false;
	//	}
	//if (ClassLevel[4] > 0)
	//	{
	//	if (First == false)
	//		ss << " \\ ";
	//	ss << ClassLevel[4] << " Rogue";
	//	First = false;
	//	}
	//if (ClassLevel[5] > 0)
 //       {
 //       if (First == false)
 //           ss << " \\ ";
	//	ss << ClassLevel[5] << " Ranger";
 //       First = false;
 //       }
	//if (ClassLevel[6] > 0)
 //       {
 //       if (First == false)
 //           ss << " \\ ";
	//	ss << ClassLevel[6] << " Cleric";
 //       First = false;
 //       }
	//if (ClassLevel[7] > 0)
 //       {
 //       if (First == false)
 //           ss << " \\ ";
	//	ss << ClassLevel[7] << " Wizard";
 //       First = false;
 //       }
	//if (ClassLevel[8] > 0)
 //       {
 //       if (First == false)
 //           ss << " \\ ";
	//	ss << ClassLevel[8] << " Sorcerer";
 //       First = false;
 //       }
	//if (ClassLevel[9] > 0)
 //       {
 //       if (First == false)
 //           ss << " \\ ";
	//	ss << ClassLevel[9] << " Bard";
 //       First = false;
 //       }
	//if (ClassLevel[10] > 0)
 //       {
 //       if (First == false)
 //           ss << " \\ ";
	//	ss << ClassLevel[10] << " Favored Soul";
 //       First = false;
 //       }
	//if (ClassLevel[11] > 0)
 //       {
 //       if (First == false)
 //           ss << " \\ ";
	//	ss << ClassLevel[11] << " Artificer";
 //       First = false;
 //       }
	//if (ClassLevel[12] > 0)
 //       {
 //       if (First == false)
 //           ss << " \\ ";
	//	ss << ClassLevel[12] << " Druid";
 //       First = false;
 //       }
	//if (ClassLevel[13] > 0)
 //       {
 //       if (First == false)
 //           ss << " \\ ";
	//	ss << ClassLevel[13] << " Warlock";
 //       First = false;
 //       }
	////epic levels
	//if (CurrentSelectedLevel > 20)
	//	{
	//	ss << " \\ ";
	//	ss << CurrentSelectedLevel-20 << " Epic";
	//	}
	ss << Character.GetClassString(CurrentSelectedLevel);
    ss << ")";

    Text = ss.str();
    SendMessage(RaceClassLabel, WM_SETTEXT, 0, (LPARAM)Text.c_str());
    }

//---------------------------------------------------------------------------
void MainScreenClass::UpdateSelectedEnhancements()
	{
	//This function should be called anytime you need to update the EnhancementList Box or when pulling selectedEnhancement Data
	Character_Enhancements_Class *CharacterEnhancements;
	Data_Enhancement_Tree_Class *EnhancementTree;
	SelectedEnhancementStruct NewSelectedEnhancement;

	SelectedEnhancements.clear();
	CharacterEnhancements = Character.GetCharacterEnhancementsPointer();
	for (int xTree=0; xTree<7; xTree++)
		{
		EnhancementTree = Data.GetEnhancementTreePointer(CharacterEnhancements->GetTreeIndex(xTree));
		if (EnhancementTree->DoesTreeHaveEnhancements() == false)
			continue;
		for (int xLevel=0; xLevel<6; xLevel++)
			{
			for (int xSlot=0; xSlot<6; xSlot++)
				{
				if (CharacterEnhancements->GetValid(xTree, xLevel, xSlot) == true && CharacterEnhancements->GetRanksTaken(xTree, xLevel, xSlot) > 0)
					{
					//ok we found an enhancement this is valid and has points spent into it
					//now we need to find the highest rank taken for our selected Character Level
					for (int xRank=2; xRank >=0; xRank--)
						{
						if (CharacterEnhancements->GetLevelTaken(xTree, xLevel, xSlot, xRank) <= (int)CurrentSelectedLevel && CharacterEnhancements->GetLevelTaken(xTree, xLevel, xSlot, xRank) !=0)
							{
							SelectedEnhancements.push_back(NewSelectedEnhancement);
							SelectedEnhancements[SelectedEnhancements.size()-1].TreeIndex = EnhancementTree->GetTreeIndex();
							SelectedEnhancements[SelectedEnhancements.size()-1].EnhancementIndex = CharacterEnhancements->GetEnhancementIndex(xTree,xLevel,xSlot, CharacterEnhancements->GetEnhancementIndexChosen(xTree, xLevel, xSlot));
							SelectedEnhancements[SelectedEnhancements.size()-1].EnhancementRank = xRank;
							break;
							}
						}
					}
				}//end for xslot

			}//end for xlevel

		}// end for xtree
	}

//---------------------------------------------------------------------------
void MainScreenClass::ChangeInstructionWindowSelection(int NewInstructionIndex)
    {
    RACE CurrentRace;
    CLASS CurrentClass;
    int Value;
    ADVANCEMENTTYPE AdvancementType;
    ostringstream ss;

    //sanity checks
    if (NewInstructionIndex < 0)
        NewInstructionIndex = 0;
    if (NewInstructionIndex >= (int)MaxInstructionSelection)
        NewInstructionIndex = MaxInstructionSelection-1;
    if (NewInstructionIndex == (int)CurrentInstructionSelection && SetUp == false)
        return;
	SetUp = false;
    CurrentInstructionSelection = NewInstructionIndex;
    //turn on or off the advancement box windows
    CurrentRace = Character.GetRace();
    CurrentClass = Character.GetClass(CurrentSelectedLevel);
    AdvancementType = Data.GetAdvancementType(CurrentSelectedLevel, CurrentRace, CurrentClass, CurrentInstructionSelection, &Value);
    ShowWindow(AdvWinBonusAbilityPointsCheckBox, false);
    ShowWindow(AdvWinFeatList, false);
    ShowWindow(AdvWinFirstNameInput, false);
    ShowWindow(AdvWinSurnameInput, false);
    ShowWindow(AdvSkillPointSpendBox, false);
    ShowWindow(AdvWinSpellList, false);
	ShowWindow(AdvWinSpellClearButton, false);
	ShowWindow(HeroicClassRadioButton, false);
	ShowWindow(IconicClassRadioButton, false);
	ShowWindow(HeroicPastRadioButton, false);
	ShowWindow(IconicPastRadioButton, false);
	ShowWindow(EpicPastRadioButton, false);
    if (AdvancementType == ADV_ABILITYPOINT)
        {
        if (CurrentRace != DROW && CurrentRace != BLADEFORGED && CurrentRace != MORNINGLORD && CurrentRace != PURPLEDRAGONKNIGHT && CurrentRace != SHADARKAI && CurrentRace != DEEPGNOME)
            ShowWindow(AdvWinBonusAbilityPointsCheckBox, true);
        }
    if (AdvancementType == ADV_FEATS)
        {
        FillFeatSelectBox();
        ShowWindow(AdvWinFeatList, true);
        }
    else if (AdvancementType == ADV_NAMEANDALIGNMENT)
        {
        ShowWindow(AdvWinFirstNameInput, true);
        ShowWindow(AdvWinSurnameInput, true);
        }
    else if (AdvancementType == ADV_SKILLS)
        {
        ShowWindow(AdvSkillPointSpendBox, true);
        }
    else if (AdvancementType == ADV_SPELLS)
        {
        FillSpellSelectBox();
        ShowWindow(AdvWinSpellList, true);
        ShowWindow(AdvWinSpellClearButton, true);
        }
	else if (AdvancementType == ADV_RACEANDSEX)
		{
			ShowWindow(HeroicClassRadioButton, true);
			ShowWindow(IconicClassRadioButton, true);
		}
	else if (AdvancementType == ADV_REINCARNATE)
	{
		ShowWindow(HeroicPastRadioButton, true);
		ShowWindow(IconicPastRadioButton, true);
		ShowWindow(EpicPastRadioButton, true);
	}
    FillInstructionBox();
	ClearAdvancementBox();
    //DrawAdvancementBoxGraphics();
    }

//---------------------------------------------------------------------------
void MainScreenClass::FillAbilityBox()
    {        
    int Ability;
    int ModAbility;
    ostringstream ss;
    int Modifier;

    //strength
    Ability = Character.GetAbility((int)STRENGTH, CurrentSelectedLevel);
    ss.str("");
    ss << Ability;
    ModAbility = Character.GetAbility((int)STRENGTH, CurrentSelectedLevel, true, true, true);
    if (ModAbility != Ability)
        ss << " (" << ModAbility << ")";
    SendMessage(StrNumber, WM_SETTEXT, 0, (LPARAM)ss.str().c_str());
    Modifier = Data.CalculateAbilityModifier(Ability);
    ss.str("");
    if (Modifier > 0)
        ss << "+";
    ss << Modifier;
    if (ModAbility != Ability)
		{
		ss << " (";
	    Modifier = Data.CalculateAbilityModifier(ModAbility);
	    if (Modifier > 0)
		    ss << "+";
        ss << Modifier << ")";
		}
    SendMessage(StrModifier, WM_SETTEXT, 0, (LPARAM)ss.str().c_str());

    //dexterity
	Ability = Character.GetAbility((int)DEXTERITY, CurrentSelectedLevel);
    ss.str("");
    ss << Ability;
    ModAbility = Character.GetAbility((int)DEXTERITY, CurrentSelectedLevel, true, true, true);
    if (ModAbility != Ability)
        ss << " (" << ModAbility << ")";
    SendMessage(DexNumber, WM_SETTEXT, 0, (LPARAM)ss.str().c_str());
    Modifier = Data.CalculateAbilityModifier(Ability);
    ss.str("");
    if (Modifier > 0)
        ss << "+";
    ss << Modifier;
    if (ModAbility != Ability)
		{
		ss << " (";
	    Modifier = Data.CalculateAbilityModifier(ModAbility);
	    if (Modifier > 0)
		    ss << "+";
        ss << Modifier << ")";
		}
    SendMessage(DexModifier, WM_SETTEXT, 0, (LPARAM)ss.str().c_str());

    //Constitution
    Ability = Character.GetAbility((int)CONSTITUTION, CurrentSelectedLevel);
    ss.str("");
    ss << Ability;
    ModAbility = Character.GetAbility((int)CONSTITUTION, CurrentSelectedLevel, true, true, true);
    if (ModAbility != Ability)
        ss << " (" << ModAbility << ")";
    SendMessage(ConNumber, WM_SETTEXT, 0, (LPARAM)ss.str().c_str());
    Modifier = Data.CalculateAbilityModifier(Ability);
    ss.str("");
    if (Modifier > 0)
        ss << "+";
    ss << Modifier;
    if (ModAbility != Ability)
		{
		ss << " (";
	    Modifier = Data.CalculateAbilityModifier(ModAbility);
	    if (Modifier > 0)
		    ss << "+";
        ss << Modifier << ")";
		}
    SendMessage(ConModifier, WM_SETTEXT, 0, (LPARAM)ss.str().c_str());

    //Intelligence
    Ability = Character.GetAbility((int)INTELLIGENCE, CurrentSelectedLevel);
    ss.str("");
    ss << Ability;
    ModAbility = Character.GetAbility((int)INTELLIGENCE, CurrentSelectedLevel, true, true, true);
    if (ModAbility != Ability)
        ss << " (" << ModAbility << ")";
    SendMessage(IntNumber, WM_SETTEXT, 0, (LPARAM)ss.str().c_str());
    Modifier = Data.CalculateAbilityModifier(Ability);
    ss.str("");
    if (Modifier > 0)
        ss << "+";
    ss << Modifier;
    if (ModAbility != Ability)
		{
		ss << " (";
	    Modifier = Data.CalculateAbilityModifier(ModAbility);
	    if (Modifier > 0)
		    ss << "+";
        ss << Modifier << ")";
		}
    SendMessage(IntModifier, WM_SETTEXT, 0, (LPARAM)ss.str().c_str());

    //Wisdom
    Ability = Character.GetAbility((int)WISDOM, CurrentSelectedLevel);
    ss.str("");
    ss << Ability;
    ModAbility = Character.GetAbility((int)WISDOM, CurrentSelectedLevel, true, true, true);
    if (ModAbility != Ability)
        ss << " (" << ModAbility << ")";
    SendMessage(WisNumber, WM_SETTEXT, 0, (LPARAM)ss.str().c_str());
    Modifier = Data.CalculateAbilityModifier(Ability);
    ss.str("");
    if (Modifier > 0)
        ss << "+";
    ss << Modifier;
    if (ModAbility != Ability)
		{
		ss << " (";
	    Modifier = Data.CalculateAbilityModifier(ModAbility);
	    if (Modifier > 0)
		    ss << "+";
        ss << Modifier << ")";
		}
    SendMessage(WisModifier, WM_SETTEXT, 0, (LPARAM)ss.str().c_str());

    //Charisma
    Ability = Character.GetAbility((int)CHARISMA, CurrentSelectedLevel);
    ss.str("");
    ss << Ability;
    ModAbility = Character.GetAbility((int)CHARISMA, CurrentSelectedLevel, true, true, true);
    if (ModAbility != Ability)
        ss << " (" << ModAbility << ")";
    SendMessage(ChaNumber, WM_SETTEXT, 0, (LPARAM)ss.str().c_str());
    Modifier = Data.CalculateAbilityModifier(Ability);
    ss.str("");
    if (Modifier > 0)
        ss << "+";
    ss << Modifier;
    if (ModAbility != Ability)
		{
		ss << " (";
	    Modifier = Data.CalculateAbilityModifier(ModAbility);
	    if (Modifier > 0)
		    ss << "+";
        ss << Modifier << ")";
		}
    SendMessage(ChaModifier, WM_SETTEXT, 0, (LPARAM)ss.str().c_str());
    }

//---------------------------------------------------------------------------
void MainScreenClass::FillAbilityStatBox()
    {
    int Value;
    string OutputString;
    ostringstream ss;

    SendMessage(AbilityStatBox, LB_RESETCONTENT, 0, 0);

    ss.str("");
    OutputString = "Hit Points: ";
    while (OutputString.size() < 20)
        OutputString.insert(0, " ");
    ss << OutputString;
    Value = Character.GetHitPoints(CurrentSelectedLevel);
    ss << Value;
    if (Character.GetItemHitPointChange(CurrentSelectedLevel) != 0)
        {
        ss << " (";
        Value += Character.GetItemHitPointChange(CurrentSelectedLevel);
        ss << Value;
        ss << ")";
        }
    OutputString = ss.str();
    SendMessage(AbilityStatBox, LB_ADDSTRING, 0, (LPARAM)OutputString.c_str());

    ss.str("");
    OutputString = "Spell Points: ";
    while (OutputString.size() < 18)
        OutputString.insert(0, " ");
    ss << OutputString;
    Value = Character.GetSpellPoints(CurrentSelectedLevel);
    ss << Value;
    if (Character.GetItemSpellPointChange(CurrentSelectedLevel) != 0)
        {
        ss << " (";
        Value += Character.GetItemSpellPointChange(CurrentSelectedLevel);
        ss << Value;
        ss << ")";
        }
    OutputString = ss.str();
    SendMessage(AbilityStatBox, LB_ADDSTRING, 0, (LPARAM)OutputString.c_str());

    ss.str("");
    OutputString = "Fortitude Save: ";
    while (OutputString.size() < 16)
        OutputString.insert(0, " ");
    ss << OutputString;
    Value = Character.GetSave(FORTITUDESAVE, CurrentSelectedLevel, false);
    if (Value > 0)
        ss << "+";
    ss << Value;
    if (Character.GetItemSaveChange(FORTITUDESAVE, CurrentSelectedLevel) != 0)
        {
        ss << " (";
        Value += Character.GetItemSaveChange(FORTITUDESAVE, CurrentSelectedLevel);
        if (Value > 0)
            ss << "+";
        ss << Value;
        ss << ")";
        }
    OutputString = ss.str();
    SendMessage(AbilityStatBox, LB_ADDSTRING, 0, (LPARAM)OutputString.c_str());

    ss.str("");
    OutputString = "Reflex Save: ";
    while (OutputString.size() < 17)
        OutputString.insert(0, " ");
    ss << OutputString;
    Value = Character.GetSave(REFLEXSAVE, CurrentSelectedLevel, false);
    if (Value > 0)
        ss << "+";
    ss << Value;
    if (Character.GetItemSaveChange(REFLEXSAVE, CurrentSelectedLevel) != 0)
        {
        ss << " (";
        Value += Character.GetItemSaveChange(REFLEXSAVE, CurrentSelectedLevel);
        if (Value > 0)
            ss << "+";
        ss << Value;
        ss << ")";
        }
    OutputString = ss.str();
    SendMessage(AbilityStatBox, LB_ADDSTRING, 0, (LPARAM)OutputString.c_str());

    ss.str("");
    OutputString = "Will Save: ";
    while (OutputString.size() < 19)
        OutputString.insert(0, " ");
    ss << OutputString;
    Value = Character.GetSave(WILLSAVE, CurrentSelectedLevel, false);
    if (Value > 0)
        ss << "+";
    ss << Value;
    if (Character.GetItemSaveChange(WILLSAVE, CurrentSelectedLevel) != 0)
        {
        ss << " (";
        Value += Character.GetItemSaveChange(WILLSAVE, CurrentSelectedLevel);
        if (Value > 0)
            ss << "+";
        ss << Value;
        ss << ")";
        }
    OutputString = ss.str();
    SendMessage(AbilityStatBox, LB_ADDSTRING, 0, (LPARAM)OutputString.c_str());

    ss.str("");
    OutputString = "BAB: ";
    while (OutputString.size() < 22)
        OutputString.insert(0, " ");
    ss << OutputString;
    Value = Character.CalculateBAB(CurrentSelectedLevel);
    ss << Value;
    if (Value > 0)
        {
        ss << " \\ ";
        ss << Value;
        }
    if (Value > 4)
        {
        ss << " \\ ";
        ss << (Value+5);
        }
    if (Value > 9)
        {
        ss << " \\ ";
        ss << (Value+10);
        }
    if (Value > 14)
        {
        ss << " \\ ";
        ss << (Value+10);
        }
    OutputString = ss.str();
    SendMessage(AbilityStatBox, LB_ADDSTRING, 0, (LPARAM)OutputString.c_str());
    }

//---------------------------------------------------------------------------
void MainScreenClass::DrawAbilityStatBoxItem(HDC hDC, unsigned int Index, DWORD, long top, long left)
    {
    char Text[256];
    COLORREF OriginalColor;

    SendMessage(AbilityStatBox, LB_GETTEXT, (WPARAM)Index, (LPARAM) (LPCTSTR)Text);
    OriginalColor = SetTextColor(hDC, RGB(255,255,255));
    TextOut(hDC, left, top, Text, strlen(Text));
    SetTextColor(hDC, OriginalColor);
    }

//---------------------------------------------------------------------------
void MainScreenClass::FillSpellBox()
    {
    int Index;
    int SpellIndex;
    int Level;
    CLASS Class;
    vector <SpellListSortStruct> SpellListSort;
    int ParentHeadingIndex;
    bool Used;
    SpellListSortStruct NewSpell;
    string ParentHeading;
    ostringstream ss;
    vector <string> UsedParentHeadings;
    ParentHeadingStruct NewParentHeading;
    vector <string> OldParentHeading;
    vector <bool> OldParentCollapse;

    //before we start, save the parent headings
    for (unsigned int i=0; i<SpellListParentHeading.size(); i++)
        {
        OldParentHeading.push_back(SpellListParentHeading[i].ParentHeading);
        OldParentCollapse.push_back(SpellListParentHeading[i].Collapsed);
        }
    SpellListParentHeading.clear();

    Index = 0;
    SendMessage(SpellList, LB_RESETCONTENT, 0, 0);
    SpellListSort.clear();
    SpellIndex = Character.GetSpellByLevelAquired(CurrentSelectedLevel, Index);
    while (SpellIndex != -1)
        {
        NewSpell.SpellName = Data.GetSpellName(SpellIndex);
        Level = Character.GetSpellLevelAquired(SpellIndex);
        Class = Character.GetClass(Level);
        NewSpell.SpellLevel = Data.GetSpellLevel(Class, SpellIndex);
        NewSpell.SpellIndex = SpellIndex;
        SpellListSort.push_back(NewSpell);
        Index++;
        SpellIndex = Character.GetSpellByLevelAquired(CurrentSelectedLevel, Index);
        }

    sort(SpellListSort.begin(), SpellListSort.end(), SpellCompare);

    for (unsigned int h=0; h<SpellListSort.size(); h++)
        {
        ss.str("");
        ss << "Level " << SpellListSort[h].SpellLevel;
        ParentHeading = ss.str();
        //find the parentheading index, or create it if not found
        ParentHeadingIndex = -1;
        for (unsigned int i=0; i<SpellListParentHeading.size(); i++)
            {
            if (SpellListParentHeading[i].ParentHeading == ParentHeading)
                {
                ParentHeadingIndex = i;
                break;
                }
            }
        if (ParentHeadingIndex == -1)
            {
            SpellListParentHeading.push_back(NewParentHeading);
            ParentHeadingIndex = SpellListParentHeading.size()-1;
            SpellListParentHeading[ParentHeadingIndex].ParentHeading = ParentHeading;
            SpellListParentHeading[ParentHeadingIndex].Collapsed = false;
            for (unsigned int j=0; j<OldParentHeading.size(); j++)
                {
                if (SpellListParentHeading[ParentHeadingIndex].ParentHeading == OldParentHeading[j])
                    {
                    SpellListParentHeading[ParentHeadingIndex].Collapsed = OldParentCollapse[j];
                    break;
                    }
                }
            }
        Used = false;
        for (unsigned int i=0; i<UsedParentHeadings.size(); i++)
            {
            if (UsedParentHeadings[i] == ParentHeading)
                {
                Used = true;
                break;
                }
            }
        if (Used == false)
            {
            SpellListParentHeading[ParentHeadingIndex].ListIndex = SendMessage(SpellList, LB_ADDSTRING, 0, 999999);
            UsedParentHeadings.push_back(ParentHeading);
            }

        if (SpellListParentHeading[ParentHeadingIndex].Collapsed == false)
            SendMessage(SpellList, LB_ADDSTRING, 0, SpellListSort[h].SpellIndex);
        }
    }

//---------------------------------------------------------------------------
void MainScreenClass::DrawSpellBoxItem(HDC hDC, unsigned int Index, DWORD Item, long top, long left)
    {
    string Text;
    COLORREF OriginalColor;

    if (Item == 999999)
        {
        for (unsigned int i=0; i<SpellListParentHeading.size(); i++)
            {
            if (SpellListParentHeading[i].ListIndex == Index)
                {
                if (SpellListParentHeading[i].Collapsed == true)
                    DrawGraphic(hDC, &PlusBox, left, top+13, 20, 20);
                else
                    DrawGraphic(hDC, &MinusBox, left, top+13, 20, 20);
                Text = SpellListParentHeading[i].ParentHeading;
                OriginalColor = SetTextColor(hDC, RGB(255,255,255));
                TextOut(hDC, left+25, top+15, Text.c_str(), Text.size());
                SetTextColor(hDC, OriginalColor);
                return;
                }
            }
        }

    DrawGraphic(hDC, &SpellIcon[Data.GetSpellIconIndex(Item)], left+15, top, 32, 32);
    Text = Data.GetSpellName(Item);
    OriginalColor = SetTextColor(hDC, RGB(255,255,255));
    TextOut(hDC, left+60, top+6, Text.c_str(), Text.size());
    SetTextColor(hDC, OriginalColor);
    }

//---------------------------------------------------------------------------
void MainScreenClass::FillSkillBox()
    {
    CLASS Class;
    int RogueLevel;
    int BardLevel;
	int ArtificerLevel;

    SendMessage(SkillsList, LB_RESETCONTENT, 0, 0);
    Class = Character.GetClass(CurrentSelectedLevel);
	RogueLevel = Character.GetClassLevel(ROGUE, CurrentSelectedLevel);
    BardLevel = Character.GetClassLevel(BARD, CurrentSelectedLevel);
    ArtificerLevel = Character.GetClassLevel(ARTIFICER, CurrentSelectedLevel);

	//primary class skills
    for (unsigned int i=0; i<NUMSKILLS; i++)
        {
        if (Data.IsSkillPrimary(Class, i) == true)
            SendMessage(SkillsList, LB_ADDSTRING, 0, i);
        }

	//cross class skills
    for (unsigned int i=0; i<NUMSKILLS; i++)
        {
        if (i == DISABLEDEVICE)
            {
            //disable device (only show if character has rogue or artificer levels)
			if ((Class != ROGUE && Class != ARTIFICER) && (RogueLevel > 0 || ArtificerLevel > 0))
                SendMessage(SkillsList, LB_ADDSTRING, 0, i+100);
            }
        else if (i == OPENLOCK)
            { 
            //open lock (only show if character has rogue or artificer levels)
			if ((Class != ROGUE && Class != ARTIFICER) && (RogueLevel > 0 || ArtificerLevel > 0))
                SendMessage(SkillsList, LB_ADDSTRING, 0, i+100);
            }
        else if (i == PERFORM)
            {
            //perform (only show if character has bard levels)
            if (Class != BARD && BardLevel > 0)
                SendMessage(SkillsList, LB_ADDSTRING, 0, i+100);
            }
        else if (Data.IsSkillCross(Class, i) == true)
            SendMessage(SkillsList, LB_ADDSTRING, 0, i+100);
        }
    }

//---------------------------------------------------------------------------
void MainScreenClass::DrawSkillBoxItem(HDC hDC, DWORD Item, long top, long left)
    {
    string Text;
    ostringstream ss;
	ABILITIES KeyAbility;
    int Ability;
    int AbilityMod;
    float TotalMod;
    int MiscMod;
    COLORREF OriginalColor;
    bool NAFlag;
    int EquipmentChange;
	RECT ScreenRect;
	int ScreenWidth;

	GetClientRect(ParentWindow, &ScreenRect);
	ScreenWidth = ScreenRect.right - ScreenRect.left;

    if (Item > 99)
        {
        Item -= 100;
        Data.GetSkillData(Item, &Text, &KeyAbility);
        Text += "*";
        DrawGraphic(hDC, &SkillIcon[Item], left, top, 40, 40);
        }
    else
        {
		Data.GetSkillData(Item, &Text, &KeyAbility);
        DrawGraphic(hDC, &SkillIcon[Item], left, top, 40, 40);
        }
    OriginalColor = SetTextColor(hDC, RGB(255,255,255));
    TextOut(hDC, left+45, top+5, Text.c_str(), Text.size());
    switch (KeyAbility)
        {
        case STRENGTH:
            {
            Text = "STR";
            Ability = Character.GetAbility(KeyAbility, CurrentSelectedLevel, true, true, true);
            AbilityMod = Data.CalculateAbilityModifier(Ability);
            break;
            }
        case DEXTERITY:
            {
            Text = "DEX";
            Ability = Character.GetAbility(KeyAbility, CurrentSelectedLevel, true, true, true);
            AbilityMod = Data.CalculateAbilityModifier(Ability);
            break;
            }
        case CONSTITUTION:
            {
            Text = "CON";
            Ability = Character.GetAbility(KeyAbility, CurrentSelectedLevel, true, true, true);
            AbilityMod = Data.CalculateAbilityModifier(Ability);
            break;
            }
        case INTELLIGENCE:
            {
            Text = "INT";
            Ability = Character.GetAbility(KeyAbility, CurrentSelectedLevel, true, true, true);
            AbilityMod = Data.CalculateAbilityModifier(Ability);
            break;
            }
        case WISDOM:
            {
            Text = "WIS";
            Ability = Character.GetAbility(KeyAbility, CurrentSelectedLevel, true, true, true);
            AbilityMod = Data.CalculateAbilityModifier(Ability);
            break;
            }
        case CHARISMA:
            {
            Text = "CHA";
            Ability = Character.GetAbility(KeyAbility, CurrentSelectedLevel, true, true, true);
            AbilityMod = Data.CalculateAbilityModifier(Ability);
            break;
            }
        }
	SetTextColor(hDC, RGB(245, 210, 35));
    TextOut(hDC, left+45, top+25, Text.c_str(), Text.size());
	SetTextColor(hDC, RGB(255, 255, 255));
    NAFlag = false;
    if (Item == DISABLEDEVICE && Character.GetTotalSkillPointsSpent(DISABLEDEVICE, CurrentSelectedLevel) == 0) 
        NAFlag = true;
    if (Item == OPENLOCK && Character.GetTotalSkillPointsSpent(OPENLOCK, CurrentSelectedLevel) == 0)
        NAFlag = true;
    if (Item == PERFORM && Character.GetTotalSkillPointsSpent(PERFORM, CurrentSelectedLevel) == 0)
        NAFlag = true;
    if (Item == TUMBLE && Character.GetTotalSkillPointsSpent(TUMBLE, CurrentSelectedLevel) == 0)
        NAFlag = true;
    if (Item == UMD && Character.GetTotalSkillPointsSpent(UMD, CurrentSelectedLevel) == 0)
        NAFlag = true;

    //total mod
    TotalMod = Character.CalculateSkillLevel(static_cast<SKILLS>(Item), CurrentSelectedLevel, true);
    if (TotalMod > 0)
        ss << "+" << TotalMod;
    else
        ss << TotalMod;
    EquipmentChange = Character.GetItemSkillChange(Item, CurrentSelectedLevel);
    if (EquipmentChange != 0)
        {
        ss << " (";
        if (TotalMod + EquipmentChange > 0)
            ss << "+";
        ss << (TotalMod + EquipmentChange);
        ss << ")";
        }
    Text = ss.str();
    if (NAFlag == true)
        Text = "n/a";
    TextOut(hDC, left+167*ScreenWidth/DEFAULTWIDTH, top+10, Text.c_str(), Text.size());

    //ability mod
    ss.str("");
    if (AbilityMod > 0)
        ss << "+" << AbilityMod;
    else
        ss << AbilityMod;
    Text = ss.str();
    if (NAFlag == true)
        Text = "n/a";
    TextOut(hDC, left+203*ScreenWidth/DEFAULTWIDTH, top+10, Text.c_str(), Text.size());

    //misc mod
    ss.str("");
    MiscMod = Character.CalculateSkillMiscMod(static_cast<SKILLS>(Item), CurrentSelectedLevel);
    if (MiscMod > 0)
        ss << "+";
    ss << MiscMod;
    EquipmentChange = Character.GetItemSkillChange(Item, CurrentSelectedLevel);
    if (EquipmentChange != 0)
        {
        ss << " (";
        if (MiscMod + EquipmentChange > 0)
            ss << "+";
        ss << (MiscMod + EquipmentChange);
        ss << ")";
        }
    Text = ss.str();
    if (NAFlag == true)
        Text = "n/a";
    TextOut(hDC, left+233*ScreenWidth/DEFAULTWIDTH, top+10, Text.c_str(), Text.size());
    SetTextColor(hDC, OriginalColor);
    }

//---------------------------------------------------------------------------
void MainScreenClass::FillEnhancementBox()
	{
	int Index;
	int ParentHeadingIndex;
	bool Used;
	vector <SelectedEnhancementSortStruct> EnhancementListSort;
	SelectedEnhancementSortStruct NewEnhancement;
	string ParentHeading;
	vector <string> UsedParentHeadings;
	ParentHeadingStruct NewParentHeading;
	vector <string> OldParentHeading;
	vector <bool> OldParentCollapse;
	Data_Enhancement_Tree_Class *EnhancementTree;
	Data_Enhancement_Class *Enhancement;


	//before we start, save the parent headings
	for (unsigned int i=0; i<SelectedEnhancementsParentHeading.size(); i++)
		{
		OldParentHeading.push_back(SelectedEnhancementsParentHeading[i].ParentHeading);
		OldParentCollapse.push_back(SelectedEnhancementsParentHeading[i].Collapsed);
		}
	SelectedEnhancementsParentHeading.clear();

	Index = 0;
	UsedParentHeadings.clear();
	SendMessage(EnhancementList, LB_RESETCONTENT, 0, 0);
	EnhancementListSort.clear();
	for (unsigned int i=0; i<SelectedEnhancements.size(); i++)
		{
		EnhancementTree = Data.GetEnhancementTreePointer(SelectedEnhancements[i].TreeIndex);
		Enhancement = EnhancementTree->GetEnhancementPointer(SelectedEnhancements[i].EnhancementIndex);
		if (Enhancement->GetEnhTypeActive() == true)
			NewEnhancement.ParentHeading = "Active";
		else
			NewEnhancement.ParentHeading = "Passive";
		NewEnhancement.EnhancementName = Enhancement->GetEnhancementName();
		NewEnhancement.SelectedEnhancementIndex = i;
		EnhancementListSort.push_back(NewEnhancement);
		}

	sort(EnhancementListSort.begin(), EnhancementListSort.end(), SelectedEnhancementCompareName);

	for (unsigned int i=0; i<EnhancementListSort.size(); i++)
		{
		//find the Parentheading index, or create it if not found
		ParentHeading = EnhancementListSort[i].ParentHeading;
		ParentHeadingIndex = -1;
		for (unsigned int j=0; j<SelectedEnhancementsParentHeading.size(); j++)
			{
			if (SelectedEnhancementsParentHeading[j].ParentHeading == ParentHeading)
				{
				ParentHeadingIndex = j;
				break;
				}
			}
		if (ParentHeadingIndex == -1)
			{
			SelectedEnhancementsParentHeading.push_back(NewParentHeading);
			ParentHeadingIndex = SelectedEnhancementsParentHeading.size()-1;
			SelectedEnhancementsParentHeading[ParentHeadingIndex].ParentHeading = ParentHeading;
			SelectedEnhancementsParentHeading[ParentHeadingIndex].Collapsed = false;
			for (unsigned int k=0; k<OldParentHeading.size(); k++)
				{
				if (SelectedEnhancementsParentHeading[ParentHeadingIndex].ParentHeading == OldParentHeading[k])
					{
					SelectedEnhancementsParentHeading[ParentHeadingIndex].Collapsed = OldParentCollapse[k];
					break;
					}
				}
			}
		Used = false;
		for (unsigned int j=0; j<UsedParentHeadings.size(); j++)
			{
			if (UsedParentHeadings[j] == ParentHeading)
				{
				Used = true;
				break;
				}
			}
		if (Used == false)
			{
			SelectedEnhancementsParentHeading[ParentHeadingIndex].ListIndex = SendMessage(EnhancementList, LB_ADDSTRING, 0, 999999);
			UsedParentHeadings.push_back(ParentHeading);
			}
		if (SelectedEnhancementsParentHeading[ParentHeadingIndex].Collapsed == false)
			SendMessage(EnhancementList, LB_ADDSTRING, 0, EnhancementListSort[i].SelectedEnhancementIndex);
		}
	}

//---------------------------------------------------------------------------
void MainScreenClass::DrawEnhancementBoxItem(HDC hDC, unsigned int Index, DWORD Item, long top, long left)
    {
    string Text;
    COLORREF OriginalColor;
    int XOffset;
	Data_Enhancement_Tree_Class *EnhancementTree;
	Data_Enhancement_Class *Enhancement;
	GraphicStruct Icon;

    if (Item == 999999)
        {
        for (unsigned int i=0; i<SelectedEnhancementsParentHeading.size(); i++)
            {
            if (SelectedEnhancementsParentHeading[i].ListIndex == Index)
                {
                if (SelectedEnhancementsParentHeading[i].Collapsed == true)
                    DrawGraphic(hDC, &PlusBox, left, top+3, 20, 20);
                else
                    DrawGraphic(hDC, &MinusBox, left, top+3, 20, 20);
                Text = SelectedEnhancementsParentHeading[i].ParentHeading;
                OriginalColor = SetTextColor(hDC, RGB(255,255,255));
                TextOut(hDC, left+25, top+5, Text.c_str(), Text.size());
                SetTextColor(hDC, OriginalColor);
                return;
                }
            }
        }

    XOffset = 23;
        
	EnhancementTree = Data.GetEnhancementTreePointer(SelectedEnhancements[Item].TreeIndex);
	Enhancement = EnhancementTree->GetEnhancementPointer(SelectedEnhancements[Item].EnhancementIndex);
	Icon = Enhancement->GetEnhancementIcon();
	DrawGraphic(hDC, &Icon, left+15, top+1, 32, 32);
    Text = Enhancement->GetEnhancementName();
    OriginalColor = SetTextColor(hDC, RGB(255,255,255));
    TextOut(hDC, left+55, top+8, Text.c_str(), Text.size());
	//TextOut(hDC, left+60, top+6, Text.c_str(), Text.size());
    SetTextColor(hDC, OriginalColor);
    }

//---------------------------------------------------------------------------
void MainScreenClass::FillFeatBox()
    {
    int Index;
    int FeatIndex;
	int LastFeatIndex;
    int ParentHeadingIndex;
    bool Used;
    string ParentHeading;
    vector <string> UsedParentHeadings;
    ParentHeadingStruct NewParentHeading;
    vector <string> OldParentHeading;
    vector <bool> OldParentCollapse;
    FeatDataClass *Feat;

    //before we start, save the parent headings
    for (unsigned int i=0; i<FeatListParentHeading.size(); i++)
        {
        OldParentHeading.push_back(FeatListParentHeading[i].ParentHeading);
        OldParentCollapse.push_back(FeatListParentHeading[i].Collapsed);
        }
    FeatListParentHeading.clear();

    Index = 0;
    UsedParentHeadings.clear();
    SendMessage(FeatList, LB_RESETCONTENT, 0, 0);
    FeatIndex = Character.GetFeat(CurrentSelectedLevel, Index);
    while (FeatIndex != -1)
        {
		LastFeatIndex = FeatIndex;
        Feat = Data.GetFeatPointer(FeatIndex);
		//do not display Parent Feats that only control derived feats (like Simple Weapon Proficiency)
		if (Feat->GetFeatTag(FEATTAGPARENTFEAT) == true)
			{
	        Index++;
		    FeatIndex = Character.GetFeat(CurrentSelectedLevel, Index);
			continue;
			}

        ParentHeading = Feat->GetFeatParentHeading();
        if (ParentHeading != "")
            {
            //find the parentheading index, or create it if not found
            ParentHeadingIndex = -1;
            for (unsigned int i=0; i<FeatListParentHeading.size(); i++)
                {
                if (FeatListParentHeading[i].ParentHeading == ParentHeading)
                    {
                    ParentHeadingIndex = i;
                    break;
                    }
                }
            if (ParentHeadingIndex == -1)
                {
                FeatListParentHeading.push_back(NewParentHeading);
                ParentHeadingIndex = FeatListParentHeading.size()-1;
                FeatListParentHeading[ParentHeadingIndex].ParentHeading = ParentHeading;
                FeatListParentHeading[ParentHeadingIndex].Collapsed = false;
                for (unsigned int j=0; j<OldParentHeading.size(); j++)
                    {
                    if (FeatListParentHeading[ParentHeadingIndex].ParentHeading == OldParentHeading[j])
                        {
                        FeatListParentHeading[ParentHeadingIndex].Collapsed = OldParentCollapse[j];
                        break;
                        }
                    }
                }
            Used = false;
            for (unsigned int i=0; i<UsedParentHeadings.size(); i++)
                {
                if (UsedParentHeadings[i] == ParentHeading)
                    {
                    Used = true;
                    break;
                    }
                }
            if (Used == false)
                {
                FeatListParentHeading[ParentHeadingIndex].ListIndex = SendMessage(FeatList, LB_ADDSTRING, 0, 999999);
                UsedParentHeadings.push_back(ParentHeading);
                }
            }
        if (ParentHeading == "")
            SendMessage(FeatList, LB_ADDSTRING, 0, FeatIndex);
        else
            {
            if (FeatListParentHeading[ParentHeadingIndex].Collapsed == false)
                {
                SendMessage(FeatList, LB_ADDSTRING, 0, FeatIndex+1000000);
                }
            }
        
		while (FeatIndex == LastFeatIndex)
		{
		Index++;
        FeatIndex = Character.GetFeat(CurrentSelectedLevel, Index);
		}

        }
    }

//---------------------------------------------------------------------------
void MainScreenClass::DrawFeatBoxItem(HDC hDC, unsigned int Index, DWORD Item, long top, long left)
    {
    string Text;
    COLORREF OriginalColor;
    int XOffset;
    FeatDataClass *Feat;

    if (Item == 999999)
        {
        for (unsigned int i=0; i<FeatListParentHeading.size(); i++)
            {
            if (FeatListParentHeading[i].ListIndex == Index)
                {
                if (FeatListParentHeading[i].Collapsed == true)
                    DrawGraphic(hDC, &PlusBox, left, top+13, 20, 20);
                else
                    DrawGraphic(hDC, &MinusBox, left, top+13, 20, 20);
                Text = FeatListParentHeading[i].ParentHeading;
                OriginalColor = SetTextColor(hDC, RGB(255,255,255));
                TextOut(hDC, left+25, top+15, Text.c_str(), Text.size());
                SetTextColor(hDC, OriginalColor);
                return;
                }
            }
        }

    XOffset = 0;
    if (Item > 999999)
        {
        XOffset = 15;
        Item -= 1000000;
        }
        
    Feat = Data.GetFeatPointer(Item);
    DrawGraphic(hDC, &FeatIcon[Feat->GetFeatIconIndex()], left+XOffset, top, 40, 40);
    Text = Feat->GetFeatName();
    OriginalColor = SetTextColor(hDC, RGB(255,255,255));
    TextOut(hDC, left+45+XOffset, top+10, Text.c_str(), Text.size());
    SetTextColor(hDC, OriginalColor);
    }

//---------------------------------------------------------------------------
void MainScreenClass::FillFeatSelectBox()
    {
    int FeatIndex;
    RACE CurrentRace;
    CLASS CurrentClass;
    vector <unsigned int> FeatVector;
    FEATSLOTTYPE F1, F2, F3;
    unsigned int Index1, Index2;
    unsigned int CurrentFeatIndex;
	int ClassLevel[NUMCLASSES];
    int ParentHeadingIndex;
    bool Used;
    string ParentHeading;
    vector <string> UsedParentHeadings;
    ParentHeadingStruct NewParentHeading;
    vector <string> OldParentHeading;
    vector <bool> OldParentCollapse;
    FeatDataClass *Feat;

    //before we start, save the parent heading settings so that we can restore them again
    for (unsigned int i=0; i<FeatListSelectParentHeading.size(); i++)
        {
        OldParentHeading.push_back(FeatListSelectParentHeading[i].ParentHeading);
        OldParentCollapse.push_back(FeatListSelectParentHeading[i].Collapsed);
        }
    FeatListSelectParentHeading.clear();

	//figure out what slots are available to the player
    CurrentRace = Character.GetRace();
	CurrentClass = Character.GetClass(CurrentSelectedLevel);
	Character.DetermineFeatSlots(CurrentSelectedLevel, &F1, &F2, &F3);

	//get all the feats that are race related
    FeatVector.clear();
    SendMessage(AdvWinFeatList, LB_RESETCONTENT, 0, 0);
    FeatIndex = Data.GetRaceFeat(CurrentRace, CurrentSelectedLevel, 0);
    while (FeatIndex != -1)
        {
        Feat = Data.GetFeatPointer(FeatIndex);
        //don't show feats tagged as past life here
        if (Feat->GetFeatTag(FEATTAGPASTLIFE) == false)
			{
		    if (Character.HasFeat(CurrentSelectedLevel, FeatIndex) == false && Feat->HaveAllFeatPrereqs(CurrentSelectedLevel) != PREREQ_DISQUALIFY)
				{
				//exclude feats that are particular to a slot type if that slot type is not up
				if (Feat->GetFeatTag(FEATTAGHALFELFBONUS) == true)
					{
					if (F1 == FEATHALFELFBONUS || F2 == FEATHALFELFBONUS || F3 == FEATHALFELFBONUS)
						FeatVector.push_back(FeatIndex);
					}
				if (Feat->GetFeatTag(FEATTAGDESTINY) == true)
					{
					if (F1 == FEATDESTINY || F2 == FEATDESTINY || F3 == FEATDESTINY)
						FeatVector.push_back(FeatIndex);
					}
				if (Feat->GetFeatTag(FEATTAGLEGENDARY) == true)
				{
					if (F1 == FEATLEGENDARY || F2 == FEATLEGENDARY || F3 == FEATLEGENDARY)
						FeatVector.push_back(FeatIndex);
				}
			    else
					FeatVector.push_back(FeatIndex);
				}
			else if (Feat->GetFeatTag(FEATTAGMULTIPLE) == true)
				FeatVector.push_back(FeatIndex);
			}
        FeatIndex = Data.GetRaceFeat(CurrentRace, CurrentSelectedLevel, FeatIndex+1);
        }

	//get all the feats that are class related
	for (unsigned int i=0; i<NUMCLASSES; i++)
        ClassLevel[i] = Character.GetClassLevel((CLASS)i, CurrentSelectedLevel);
    for (unsigned int i=0; i<NUMCLASSES; i++)
        {
        if (ClassLevel[i] == 0)
            continue;
        FeatIndex = Data.GetClassFeat((CLASS)i, CurrentSelectedLevel, 0);
        while (FeatIndex != -1)
            {
	        Feat = Data.GetFeatPointer(FeatIndex);
            if (Character.HasFeat(CurrentSelectedLevel, FeatIndex) == false && Feat->HaveAllFeatPrereqs(CurrentSelectedLevel) != PREREQ_DISQUALIFY)
                {
				//exclude feats that are particular to a slot type if that slot type is not up
				if (Feat->GetFeatTag(FEATTAGFAVOREDENEMY) == true)
                    {
                    if (F1 == FEATRANGERFAVOREDENEMY || F2 == FEATRANGERFAVOREDENEMY || F3 == FEATRANGERFAVOREDENEMY)
                        FeatVector.push_back(FeatIndex);
                    }
				else if (Feat->GetFeatTag(FEATTAGROGUEBONUS) == true)
					{
					if (F1 == FEATROGUEBONUS || F2 == FEATROGUEBONUS || F3 == FEATROGUEBONUS)
						FeatVector.push_back(FeatIndex);
					}
				else if (Feat->GetFeatTag(FEATTAGMONKPATH) == true)
					{
					if (F1 == FEATMONKPATH || F2 == FEATMONKPATH || F3 == FEATMONKPATH)
						FeatVector.push_back(FeatIndex);
					}
				else if (Feat->GetFeatTag(FEATTAGDEITY) == true)
					{
					if (F1 == FEATDEITY || F2 == FEATDEITY || F3 == FEATDEITY)
						FeatVector.push_back(FeatIndex);
					}
				else if (Feat->GetFeatTag(FEATTAGFAVOREDSOULBONUS) == true)
					{
					if (F1 == FEATFAVOREDSOULBONUS || F2 == FEATFAVOREDSOULBONUS || F3 == FEATFAVOREDSOULBONUS)
						FeatVector.push_back(FeatIndex);
					}
				else if (Feat->GetFeatTag(FEATTAGMONKEXCLUSIVE) == true)
					{
					if (F1 == FEATMONKBONUS || F2 == FEATMONKBONUS || F3 == FEATMONKBONUS)
						FeatVector.push_back(FeatIndex);
					}
				if (Feat->GetFeatTag(FEATTAGDRUIDWILDSHAPE) == true)
                    {
                    if (F1 == FEATDRUIDWILDSHAPE || F2 == FEATDRUIDWILDSHAPE || F3 == FEATDRUIDWILDSHAPE)
                        FeatVector.push_back(FeatIndex);
                    }
				if (Feat->GetFeatTag(FEATTAGWARLOCKPACT) == true)
				{
					if (F1 == FEATWARLOCKPACT || F2 == FEATWARLOCKPACT || F3 == FEATWARLOCKPACT)
						FeatVector.push_back(FeatIndex);
				}
				else
					FeatVector.push_back(FeatIndex);
                }
            else if (Feat->GetFeatTag(FEATTAGMULTIPLE) == true && Feat->HaveAllFeatPrereqs(CurrentSelectedLevel) != PREREQ_DISQUALIFY)
                {
                if (Feat->GetFeatTag(FEATTAGFAVOREDENEMY) == true)
                    {
                    if (F1 == FEATRANGERFAVOREDENEMY || F2 == FEATRANGERFAVOREDENEMY || F3 == FEATRANGERFAVOREDENEMY)
                        FeatVector.push_back(FeatIndex);
                    }
                else if (Feat->GetFeatTag(FEATTAGROGUEBONUS) == true)
                    {
                    if (F1 == FEATROGUEBONUS || F2 == FEATROGUEBONUS || F3 == FEATROGUEBONUS)
                        FeatVector.push_back(FeatIndex);
                    }
                else
                    FeatVector.push_back(FeatIndex);
                }
            FeatIndex = Data.GetClassFeat((CLASS)i, CurrentSelectedLevel, FeatIndex+1);
            }
        }

    //make the list entries unique, then sort it
    Index1 = 0;
    while (Index1 < FeatVector.size())
        {
        CurrentFeatIndex = FeatVector[Index1];
        Index2 = Index1+1;
        while (Index2 < FeatVector.size())
            {
            if (FeatVector[Index2] == CurrentFeatIndex)
                FeatVector.erase(FeatVector.begin() + Index2);
            else
                Index2++;
            }
        Index1++;
        }
    sort(FeatVector.begin(), FeatVector.end());

    //add the list to the listbox
    for (unsigned int i=0; i<FeatVector.size(); i++)
        {
        Feat = Data.GetFeatPointer(FeatVector[i]);
        ParentHeading = Feat->GetFeatParentHeading();
        if (ParentHeading != "")
            {
            //find the parentheading index, or create it if not found
            ParentHeadingIndex = -1;
            for (unsigned int i=0; i<FeatListSelectParentHeading.size(); i++)
                {
                if (FeatListSelectParentHeading[i].ParentHeading == ParentHeading)
                    {
                    ParentHeadingIndex = i;
                    break;
                    }
                }
            if (ParentHeadingIndex == -1)
                {
                FeatListSelectParentHeading.push_back(NewParentHeading);
                ParentHeadingIndex = FeatListSelectParentHeading.size()-1;
                FeatListSelectParentHeading[ParentHeadingIndex].ParentHeading = ParentHeading;
                FeatListSelectParentHeading[ParentHeadingIndex].Collapsed = false;
                for (unsigned int j=0; j<OldParentHeading.size(); j++)
                    {
                    if (FeatListSelectParentHeading[ParentHeadingIndex].ParentHeading == OldParentHeading[j])
                        {
                        FeatListSelectParentHeading[ParentHeadingIndex].Collapsed = OldParentCollapse[j];
                        break;
                        }
                    }
                }
            Used = false;
            for (unsigned int i=0; i<UsedParentHeadings.size(); i++)
                {
                if (UsedParentHeadings[i] == ParentHeading)
                    {
                    Used = true;
                    break;
                    }
                }
            if (Used == false)
                {
                FeatListSelectParentHeading[ParentHeadingIndex].ListIndex = SendMessage(AdvWinFeatList, LB_ADDSTRING, 0, 999999);
                UsedParentHeadings.push_back(ParentHeading);
                }
            }
        if (ParentHeading == "")
            SendMessage(AdvWinFeatList, LB_ADDSTRING, 0, FeatVector[i]);
        else
            {
            if (FeatListSelectParentHeading[ParentHeadingIndex].Collapsed == false)
                {
                SendMessage(AdvWinFeatList, LB_ADDSTRING, 0, FeatVector[i]+1000000);
                }
            }
        }
    }

//---------------------------------------------------------------------------
void MainScreenClass::DrawFeatSelectBoxItem(HDC hDC, unsigned int Index, DWORD Item, long top, long left)
	{
    string Text;
    COLORREF OriginalColor;
    bool Metamagic;
    bool FighterBonus;
    bool ArtificerBonus;
    bool FavoredEnemy;
	bool RogueBonus;
	bool MonkBonus;
	bool MonkPath;
	bool Deity;
	bool FavoredSoulBonus;
	bool HalfElfBonus;
	bool DruidWildShape;
	bool WarlockPact;
	bool Destiny;
	bool Legendary;
    int XOffset;
	PREREQRESULT FeatPrereqStatus;
	FeatDataClass *Feat;

    if (Item == 999999)
        {
        for (unsigned int i=0; i<FeatListSelectParentHeading.size(); i++)
            {
            if (FeatListSelectParentHeading[i].ListIndex == Index)
                {
                if (FeatListSelectParentHeading[i].Collapsed == true)
                    DrawGraphic(hDC, &PlusBox, left, top+13, 20, 20);
                else
                    DrawGraphic(hDC, &MinusBox, left, top+13, 20, 20);
				Text = FeatListSelectParentHeading[i].ParentHeading;
                OriginalColor = SetTextColor(hDC, RGB(255,255,255));
                TextOut(hDC, left+25, top+15, Text.c_str(), Text.size());
                SetTextColor(hDC, OriginalColor);
                return;
                }
            }
        }

    XOffset = 0;
    if (Item > 999999)
        {
        XOffset = 15;
        Item -= 1000000;
        }

    FighterBonus = false;
    ArtificerBonus = false;
    Metamagic = false;
    FavoredEnemy = false;
	RogueBonus = false;
	MonkBonus = false;
	MonkPath = false;
	Deity = false;
	FavoredSoulBonus = false;
	DruidWildShape = false;
	HalfElfBonus = false;
	WarlockPact = false;
	Destiny = false;
	Legendary = false;

    for (unsigned int i=0; i<3; i++)
        {
        if (FeatSlot[i] == FEATFIGHTERBONUS)
            FighterBonus = true;
        if (FeatSlot[i] == FEATWIZARDBONUS)
            Metamagic = true;
        if (FeatSlot[i] == FEATARTIFICERBONUS)
            ArtificerBonus = true;
        if (FeatSlot[i] == FEATRANGERFAVOREDENEMY)
            FavoredEnemy = true;
        if (FeatSlot[i] == FEATROGUEBONUS)
            RogueBonus = true;
		if (FeatSlot[i] == FEATMONKBONUS)
			MonkBonus = true;
		if (FeatSlot[i] == FEATMONKPATH)
			MonkPath = true;
		if (FeatSlot[i] == FEATDEITY)
			Deity = true;
		if (FeatSlot[i] == FEATFAVOREDSOULBONUS)
			FavoredSoulBonus = true;
		if (FeatSlot[i] == FEATHALFELFBONUS)
			HalfElfBonus = true;
		if (FeatSlot[i] == FEATDRUIDWILDSHAPE)
			DruidWildShape = true;
		if (FeatSlot[i] == FEATWARLOCKPACT)
			WarlockPact = true;
		if (FeatSlot[i] == FEATDESTINY)
			Destiny = true;
		if (FeatSlot[i] == FEATLEGENDARY)
			Legendary = true;
		}
		
	//grab a pointer to the feat
	Feat = Data.GetFeatPointer(Item);

	FeatPrereqStatus = Feat->HaveAllFeatPrereqs(CurrentSelectedLevel);
    if (FeatPrereqStatus == PREREQ_PASS)
        {
        DrawGraphic(hDC, &FeatIcon[Feat->GetFeatIconIndex()], left+XOffset, top, 40, 40);
		Text = Feat->GetFeatName();
		if (Metamagic == true && Feat->GetFeatTag(FEATTAGMETAMAGIC) == true)
			OriginalColor = SetTextColor(hDC, RGB(230,230,30));
		else if (FighterBonus == true && Feat->GetFeatTag(FEATTAGFIGHTERBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(230,230,30));
		else if (ArtificerBonus == true && Feat->GetFeatTag(FEATTAGARTIFICERBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(230,230,30));
		else if (FavoredEnemy == true && Feat->GetFeatTag(FEATTAGFAVOREDENEMY) == true)
			OriginalColor = SetTextColor(hDC, RGB(230,230,30));
		else if (RogueBonus == true && Feat->GetFeatTag(FEATTAGROGUEBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(230,230,30));
		else if (MonkBonus == true && Feat->GetFeatTag(FEATTAGMONKBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(230,230,30));
		else if (MonkPath == true && Feat->GetFeatTag(FEATTAGMONKPATH) == true)
			OriginalColor = SetTextColor(hDC, RGB(230,230,30));
		else if (Deity == true && Feat->GetFeatTag(FEATTAGDEITY) == true)
			OriginalColor = SetTextColor(hDC, RGB(100,255,0));
		else if (FavoredSoulBonus == true && Feat->GetFeatTag(FEATTAGFAVOREDSOULBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(230,230,30));
		else if (HalfElfBonus == true && Feat->GetFeatTag(FEATTAGHALFELFBONUS) == true)
			OriginalColor = SetTextColor(hDC, RGB(255,0,155));
		else if (MonkBonus == true && Feat->GetFeatTag(FEATTAGMONKEXCLUSIVE) == true)
			OriginalColor = SetTextColor(hDC, RGB(230,230,30));
		else if (DruidWildShape == true && Feat->GetFeatTag(FEATTAGDRUIDWILDSHAPE) == true)
			OriginalColor = SetTextColor(hDC, RGB(230,230,30));
		else if (WarlockPact == true && Feat->GetFeatTag(FEATTAGWARLOCKPACT) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (Destiny == true && Feat->GetFeatTag(FEATTAGDESTINY) == true)
			OriginalColor = SetTextColor(hDC, RGB(230,230,30));
		else if (Destiny == true && Feat->GetFeatTag(FEATTAGDESTINYNOTEXCLUSIVE) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else if (Legendary == true && Feat->GetFeatTag(FEATTAGLEGENDARY) == true)
			OriginalColor = SetTextColor(hDC, RGB(230, 230, 30));
		else
			OriginalColor = SetTextColor(hDC, RGB(255,255,255));
		TextOut(hDC, left+45+XOffset, top+10, Text.c_str(), Text.size());
		SetTextColor(hDC, OriginalColor);
		}
	else if (FeatPrereqStatus == PREREQ_FAIL)
		{
		DrawGraphicGreyscale(hDC, &FeatIcon[Feat->GetFeatIconIndex()], left+XOffset, top, 40, 40);
		Text = Feat->GetFeatName();
		OriginalColor = SetTextColor(hDC, RGB(150,150,150));
        TextOut(hDC, left+45+XOffset, top+10, Text.c_str(), Text.size());
        SetTextColor(hDC, OriginalColor);
        }
    }

//---------------------------------------------------------------------------
void MainScreenClass::FillSkillSpendBox()
    {
    CLASS Class;
    int RogueLevel;
    int BardLevel;
	int ArtificerLevel;

    SendMessage(AdvSkillPointSpendBox, LB_RESETCONTENT, 0, 0);
    Class = Character.GetClass(CurrentSelectedLevel);
	RogueLevel = Character.GetClassLevel(ROGUE, CurrentSelectedLevel);
    BardLevel = Character.GetClassLevel(BARD, CurrentSelectedLevel);
	ArtificerLevel = Character.GetClassLevel(ARTIFICER, CurrentSelectedLevel);

	//show primary skills first
    for (unsigned int i=0; i<NUMSKILLS; i++)
        {
        if (Data.IsSkillPrimary(Class, i) == true)
            SendMessage(AdvSkillPointSpendBox, LB_ADDSTRING, 0, i);
        }

	//cross class skills
    for (unsigned int i=0; i<NUMSKILLS; i++)
        {
        if (i == DISABLEDEVICE)
            {
            //disable device (only show if character has rogue or artificer levels)
			if ((Class != ROGUE && Class != ARTIFICER) && (RogueLevel > 0 || ArtificerLevel > 0))
                SendMessage(AdvSkillPointSpendBox, LB_ADDSTRING, 0, i+100);
            }
        else if (i == OPENLOCK)
            { 
            //open lock (only show if character has rogue or artificer levels)
			if ((Class != ROGUE && Class != ARTIFICER) && (RogueLevel > 0 || ArtificerLevel > 0))
                SendMessage(AdvSkillPointSpendBox, LB_ADDSTRING, 0, i+100);
            }
        /*commented out: As of update 19 the perform skill is availbable to all classes now since it grant spell power to sonic spells.
		else if (i == PERFORM)
            {
            //perform (only show if character has bard levels)
            if (Class != BARD && BardLevel > 0)
                SendMessage(AdvSkillPointSpendBox, LB_ADDSTRING, 0, i+100);
            }*/
        else if (Data.IsSkillCross(Class, i) == true)
            SendMessage(AdvSkillPointSpendBox, LB_ADDSTRING, 0, i+100);
        }
    }

//---------------------------------------------------------------------------
void MainScreenClass::DrawSkillSpendBoxItem(HDC hDC, DWORD Item, long top, long left)
    {
    string Text;
    ostringstream ss;
	ABILITIES KeyAbility;
    float AbilityMod;
    COLORREF OriginalColor;
    float PointsSpent;
    float PointLimit;
    float PointRaise;
    int PointsRemain;
    bool NAFlag;

    if (Item > 99)
        {
        Item -= 100;
		Data.GetSkillData(Item, &Text, &KeyAbility);
        Text += "*";
        DrawGraphic(hDC, &SkillIcon[Item], left, top, 40, 40);
        }
    else
        {
        Data.GetSkillData(Item, &Text, &KeyAbility);
        DrawGraphic(hDC, &SkillIcon[Item], left, top, 40, 40);
        }

    //the arrows
    PointsSpent = (float)Character.GetLevelSkillPointsSpent(static_cast<SKILLS>(Item), CurrentSelectedLevel);
    if (PointsSpent == 0)
        DrawGraphicGreyscale(hDC, &LeftArrow, left+185, top+8, 21, 21);
    else
        DrawGraphic(hDC, &LeftArrow, left+185, top+8, 21, 21);

    PointsSpent = Character.GetTotalSkillPointsSpentDisplay(static_cast<SKILLS>(Item), CurrentSelectedLevel);
    if (Data.IsSkillPrimary(Character.GetClass(CurrentSelectedLevel), Item) == true)
		PointRaise = 1.0f;
    else
        PointRaise = 0.5f;
    PointLimit = Character.GetSkillPointSpendLimit(static_cast<SKILLS>(Item), CurrentSelectedLevel);
    PointsRemain = Character.CalculateAvailableSkillPoints(CurrentSelectedLevel);
    if ((PointsSpent + PointRaise) <= PointLimit && PointsRemain > 0)
        DrawGraphic(hDC, &RightArrow, left+235, top+8, 21, 21);
    else
        DrawGraphicGreyscale(hDC, &RightArrow, left+235, top+8, 21, 21);

    OriginalColor = SetTextColor(hDC, RGB(255,255,255));
    if (Text == "Use Magic Device")
        {
        Text = "Use Magic";
        TextOut(hDC, left+45, top+3, Text.c_str(), Text.size());
        Text = "Device";
        TextOut(hDC, left+45, top+17, Text.c_str(), Text.size());
        }
    else if (Text == "Use Magic Device*")
        {
        Text = "Use Magic";
        TextOut(hDC, left+45, top+3, Text.c_str(), Text.size());
        Text = "Device*";
        TextOut(hDC, left+45, top+17, Text.c_str(), Text.size());
        }
    else if (Text == "Move Silently")
        {
        Text = "Move";
        TextOut(hDC, left+45, top+3, Text.c_str(), Text.size());
        Text = "Silently";
        TextOut(hDC, left+45, top+17, Text.c_str(), Text.size());
        }
    else if (Text == "Move Silently*")
        {
        Text = "Move";
        TextOut(hDC, left+45, top+3, Text.c_str(), Text.size());
        Text = "Silently*";
        TextOut(hDC, left+45, top+17, Text.c_str(), Text.size());
        }
    else if (Text == "Disable Device")
        {
        Text = "Disable";
        TextOut(hDC, left+45, top+3, Text.c_str(), Text.size());
        Text = "Device";
        TextOut(hDC, left+45, top+17, Text.c_str(), Text.size());
        }
    else if (Text == "Disable Device*")
        {
        Text = "Disable";
        TextOut(hDC, left+45, top+3, Text.c_str(), Text.size());
        Text = "Device*";
        TextOut(hDC, left+45, top+17, Text.c_str(), Text.size());
        }
    else
        TextOut(hDC, left+45, top+10, Text.c_str(), Text.size());

    NAFlag = false;
    if (Item == 4 && Character.GetTotalSkillPointsSpent(DISABLEDEVICE, CurrentSelectedLevel) == 0)  //disable device
        NAFlag = true;
    if (Item == 12 && Character.GetTotalSkillPointsSpent(OPENLOCK, CurrentSelectedLevel) == 0)  //open lock
        NAFlag = true;
    if (Item == 13 && Character.GetTotalSkillPointsSpent(PERFORM, CurrentSelectedLevel) == 0)  //perform
        NAFlag = true;
    if (Item == 19 && Character.GetTotalSkillPointsSpent(TUMBLE, CurrentSelectedLevel) == 0)  //tumble
        NAFlag = true;
    if (Item == 20 && Character.GetTotalSkillPointsSpent(UMD, CurrentSelectedLevel) == 0)  //use Magic Device
        NAFlag = true;

    //total mod
    AbilityMod = Character.CalculateSkillLevel(static_cast<SKILLS>(Item), CurrentSelectedLevel, true);
    if (AbilityMod > 0)
        ss << "+" << AbilityMod;
    else
        ss << AbilityMod;
    Text = ss.str();
    if (NAFlag == true)
        Text = "n/a";
    TextOut(hDC, left+150, top+10, Text.c_str(), Text.size());

    //Points
    ss.str("");
    AbilityMod = Character.GetTotalSkillPointsSpentDisplay(static_cast<SKILLS>(Item), CurrentSelectedLevel);
    ss << AbilityMod;
    Text = ss.str();
    if (NAFlag == true)
        Text = "n/a";
    TextOut(hDC, left+210, top+10, Text.c_str(), Text.size());

    SetTextColor(hDC, OriginalColor);
    }

//---------------------------------------------------------------------------
void MainScreenClass::FillSpellSelectBox()
    {
    int SpellLevel[3];
    int NumSpells[3];
    int Index;
    int SpellIndex;
    CLASS ClassType;
    vector <SpellListSortStruct> SpellListSort;
    int ParentHeadingIndex;
    bool Used;
    SpellListSortStruct NewSpell;
    string ParentHeading;
    ostringstream ss;
    vector <string> UsedParentHeadings;
    ParentHeadingStruct NewParentHeading;
    vector <string> OldParentHeading;
    vector <bool> OldParentCollapse;

    //before we start, save the parent headings
    for (unsigned int i=0; i<SpellListSelectParentHeading.size(); i++)
        {
        OldParentHeading.push_back(SpellListSelectParentHeading[i].ParentHeading);
        OldParentCollapse.push_back(SpellListSelectParentHeading[i].Collapsed);
        }
    SpellListSelectParentHeading.clear();

    SendMessage(AdvWinSpellList, LB_RESETCONTENT, 0, 0);
    ClassType = Character.GetClass(CurrentSelectedLevel);
    Character.GetSpellSelectionSlots(CurrentSelectedLevel, SpellLevel, NumSpells);
	//wizards and artificers can select a spell from any level lower than the max level they know
	if (ClassType == WIZARD || ClassType == ARTIFICER)
        {
        for (int i=1; i<=SpellLevel[0]; i++)
            {
            Index = 0;
            SpellIndex = Data.GetSpellIndex(ClassType, i, Index);
            while (SpellIndex != -1)
                {
                if (Character.HasSpell(SpellIndex, CurrentSelectedLevel) == false)
                    {
                    NewSpell.SpellName = Data.GetSpellName(SpellIndex);
                    NewSpell.SpellLevel = Data.GetSpellLevel(ClassType, SpellIndex);
                    NewSpell.SpellIndex = SpellIndex;
                    SpellListSort.push_back(NewSpell);
                    }
                Index++;
                SpellIndex = Data.GetSpellIndex(ClassType, i, Index);
                }
            }
        }
	else
        {
        for (unsigned int i=0; i<3; i++)
            {
            if (SpellLevel[i] == 0)
                continue;
            Index = 0;
            SpellIndex = Data.GetSpellIndex(ClassType, SpellLevel[i], Index);
            while (SpellIndex != -1)
                {
                if (Character.HasSpell(SpellIndex, CurrentSelectedLevel) == false)
                    {
                    NewSpell.SpellName = Data.GetSpellName(SpellIndex);
                    NewSpell.SpellLevel = Data.GetSpellLevel(ClassType, SpellIndex);
                    NewSpell.SpellIndex = SpellIndex;
                    SpellListSort.push_back(NewSpell);
                    }
                Index++;
                SpellIndex = Data.GetSpellIndex(ClassType, SpellLevel[i], Index);
                }
            }
        }

    sort(SpellListSort.begin(), SpellListSort.end(), SpellCompare);

    for (unsigned int h=0; h<SpellListSort.size(); h++)
        {
        ss.str("");
        ss << "Level " << SpellListSort[h].SpellLevel;
        ParentHeading = ss.str();
        //find the parentheading index, or create it if not found
        ParentHeadingIndex = -1;
        for (unsigned int i=0; i<SpellListSelectParentHeading.size(); i++)
            {
            if (SpellListSelectParentHeading[i].ParentHeading == ParentHeading)
                {
                ParentHeadingIndex = i;
                break;
                }
            }
        if (ParentHeadingIndex == -1)
            {
            SpellListSelectParentHeading.push_back(NewParentHeading);
            ParentHeadingIndex = SpellListSelectParentHeading.size()-1;
            SpellListSelectParentHeading[ParentHeadingIndex].ParentHeading = ParentHeading;
            SpellListSelectParentHeading[ParentHeadingIndex].Collapsed = false;
            for (unsigned int j=0; j<OldParentHeading.size(); j++)
                {
                if (SpellListSelectParentHeading[ParentHeadingIndex].ParentHeading == OldParentHeading[j])
                    {
                    SpellListSelectParentHeading[ParentHeadingIndex].Collapsed = OldParentCollapse[j];
                    break;
                    }
                }
            }
        Used = false;
        for (unsigned int i=0; i<UsedParentHeadings.size(); i++)
            {
            if (UsedParentHeadings[i] == ParentHeading)
                {
                Used = true;
                break;
                }
            }
        if (Used == false)
            {
            SpellListSelectParentHeading[ParentHeadingIndex].ListIndex = SendMessage(AdvWinSpellList, LB_ADDSTRING, 0, 999999);
            UsedParentHeadings.push_back(ParentHeading);
            }

        if (SpellListSelectParentHeading[ParentHeadingIndex].Collapsed == false)
            SendMessage(AdvWinSpellList, LB_ADDSTRING, 0, SpellListSort[h].SpellIndex);
        }
    }

//---------------------------------------------------------------------------
void MainScreenClass::DrawSpellSelectBoxItem(HDC hDC, unsigned int Index, DWORD Item, long top, long left)
    {
    string Text;
    COLORREF OriginalColor;

    if (Item == 999999)
        {
        for (unsigned int i=0; i<SpellListSelectParentHeading.size(); i++)
            {
            if (SpellListSelectParentHeading[i].ListIndex == Index)
                {
                if (SpellListSelectParentHeading[i].Collapsed == true)
                    DrawGraphic(hDC, &PlusBox, left, top+13, 20, 20);
                else
                    DrawGraphic(hDC, &MinusBox, left, top+13, 20, 20);
                Text = SpellListSelectParentHeading[i].ParentHeading;
                OriginalColor = SetTextColor(hDC, RGB(255,255,255));
                TextOut(hDC, left+25, top+15, Text.c_str(), Text.size());
                SetTextColor(hDC, OriginalColor);
                return;
                }
            }
        }

    DrawGraphic(hDC, &SpellIcon[Data.GetSpellIconIndex(Item)], left+15, top, 32, 32);
    Text = Data.GetSpellName(Item);
    OriginalColor = SetTextColor(hDC, RGB(255,255,255));
    TextOut(hDC, left+60, top+6, Text.c_str(), Text.size());
    SetTextColor(hDC, OriginalColor);
    }

//---------------------------------------------------------------------------
void MainScreenClass::FillEquipmentDisplaySelectBox()
    {
	unsigned int Index;
	unsigned int ItemIndex;
	unsigned int ItemEffect1;
	unsigned int ItemEffect2;
	unsigned int ItemEffect3;
	unsigned int ItemEffect4;
	unsigned int ItemEffect5;
	unsigned int ItemEffect6;
	unsigned int Eldritch;
	ItemClass *ptItem;

	SendMessage(EquipmentDisplaySelectList, LB_RESETCONTENT, 0, 0);
	Index = 0;
	while (Character.GetItemData(Index, &ItemIndex, &ItemEffect1, &ItemEffect2, &ItemEffect3, &ItemEffect4, &ItemEffect5, &ItemEffect6, &Eldritch) == 0)
		{
		ptItem = Data.GetItemPointer(ItemIndex);
		if (EquipmentScreenCurrentSelectedSlot == NOSLOT)
			SendMessage(EquipmentDisplaySelectList, LB_ADDSTRING, 0, Index);
		else if (ptItem->DoesItemFitSelectedSlot(EquipmentScreenCurrentSelectedSlot))
			SendMessage(EquipmentDisplaySelectList, LB_ADDSTRING, 0, Index);
		Index ++;
		}
	}

//---------------------------------------------------------------------------
void MainScreenClass::DrawEquipmentDisplaySelectBoxItem(HDC hDC, DWORD Item, long top, long left)
    {
    string Text;
    COLORREF OriginalColor;

	OriginalColor = SetTextColor(hDC, RGB(255,255,255));

	if (Character.IsItemEquipped(Item) == true)
		SetTextColor(hDC, RGB(230, 230, 0));

	Text = Character.GetItemDisplayName(Item);

    TextOut(hDC, left+5, top+6, Text.c_str(), Text.size());
    SetTextColor(hDC, OriginalColor);
    }

//---------------------------------------------------------------------------
void MainScreenClass::FillInstructionBox()
    {
    unsigned int Index;
    unsigned int Selection;
    int Value;
    char ValueString[10];
    EDITSTREAM Stream;
    string NewInstruction;
    string TotalInstruction;
    string TitleString;
    ostringstream ss;
    FEATSLOTTYPE F1, F2, F3;
    int SpellLevel[3];
    int NumSpells[3];
	CHARFORMAT cf;	
	CHARRANGE cr;	
	HDC hDC;

    MaxInstructionSelection = 0;
    Index = 0;
    TotalInstruction = "";
    Selection = CurrentInstructionSelection;



    NewInstruction = Character.GetInstructionString(CurrentSelectedLevel, Index, &Value);
    while (NewInstruction != "")
        {
        if (NewInstruction.find("%i") != NewInstruction.npos)
            {
			StringCbPrintf(ValueString, 10, "%i", Value);
            NewInstruction.replace(NewInstruction.find("%i"), 2, ValueString);
            }
        //dump feat selection if there are no feats to select at this level
        if (NewInstruction == "Select Feats")
            {
            Character.DetermineFeatSlots(CurrentSelectedLevel, &F1, &F2, &F3);
            if (F1 == FEATNONE)
                {
                Index++;
                NewInstruction = Character.GetInstructionString(CurrentSelectedLevel, Index, &Value);
                Selection++;
                continue;
                }
            }
        //dump spell selection if there are no spells to select (Bards only)
        if (NewInstruction == "Select Spells")
            {
            Character.GetSpellSelectionSlots(CurrentSelectedLevel, SpellLevel, NumSpells);
            if (SpellLevel[0] == 0)
                {
                Index++;
                NewInstruction = Character.GetInstructionString(CurrentSelectedLevel, Index, &Value);
                Selection++;
                continue;
                }
            }
        if (Index != 0)
            TotalInstruction += "\\par ";
        if (Selection == Index)
            TotalInstruction += "{\\cf1 {\\b ";
        TotalInstruction += NewInstruction;
        if (Selection == Index)
            TotalInstruction += "}}";
        MaxInstructionSelection++;
        Index++;
        NewInstruction = Character.GetInstructionString(CurrentSelectedLevel, Index, &Value);
        }
    Stream.dwCookie = (DWORD)TotalInstruction.c_str();
    Stream.dwError = false;
    Stream.pfnCallback = EditStreamCallback;
    SendMessage(InstructionWindowList, EM_STREAMIN, SF_RTF, (LPARAM)&Stream);

    //update the window label
    ss.str("");
	if (CurrentSelectedLevel < 21)
	    ss << "Level " << Character.GetClassLevel(CurrentSelectedLevel) << " ";
	else 
		ss << "Level " << CurrentSelectedLevel - 20 << " ";
    ss << Data.GetRaceName(Character.GetRace()) << " ";
	if (CurrentSelectedLevel < 21)
	    ss << Data.GetClassName(Character.GetClass(CurrentSelectedLevel));
	else
		ss << "Epic";
    TitleString = ss.str();
    SendMessage(InstructionWindowTitle, WM_SETTEXT, 0, (LPARAM)TitleString.c_str());
	//the instruction box should respect the font choice of the user
	if (UsingSystemFont == false)
	{
		//set up the default size for rich edit box (instruction panel)
		//((we are going to use a slightly smaller font than the default))
		memset(&cf, 0, sizeof(cf));
		cf.cbSize = sizeof(cf);
		cf.dwMask = CFM_CHARSET | CFM_FACE | CFM_SIZE;
		cf.bCharSet = ANSI_CHARSET;
		cf.bPitchAndFamily = DEFAULT_PITCH | FF_ROMAN;
		hDC = GetDC(InstructionWindowList);
		cf.yHeight = (FontHeight - 2) * 72 * 20 / GetDeviceCaps(hDC, LOGPIXELSY);
		ReleaseDC(InstructionWindowList, hDC);
		StringCbCopy(cf.szFaceName, LF_FACESIZE, TEXT(FontName.c_str()));

		// Set char format and goto end of text	
		cr.cpMin = INT_MAX;
		cr.cpMax = INT_MAX;
		SendMessage(InstructionWindowList, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cf);
		SendMessage(InstructionWindowList, EM_EXSETSEL, 0, (LPARAM)&cr);
	}

	}

//---------------------------------------------------------------------------
void MainScreenClass::FillDescriptionBox(string Description, HBITMAP Bitmap)
    {
    EDITSTREAM Stream;
    
    Stream.dwCookie = (DWORD)Description.c_str();
    Stream.dwError = false;
    Stream.pfnCallback = EditStreamCallback;
    SendMessage(DescriptionWindow, EM_STREAMIN, SF_RTF, (LPARAM)&Stream);

    //test the rich edit box graphics drawer
    if (Bitmap != NULL)
	    RichEditBitmap.InsertBitmap(DescriptionWindow, Bitmap);
    }

//---------------------------------------------------------------------------
void MainScreenClass::LoadGraphics(HWND Parent)
    {
    HDC hdc;

    //palette for halftone work
    hdc = GetDC(Parent);
    Palette = CreateHalftonePalette(hdc);
    ReleaseDC(Parent, hdc);

	LoadBitmap("ArrowLeft", "UserInterface", &LeftArrow);
    //LoadBitmap("ArrowRight", "UserInterface", &RightArrow, NULL, 20, 0);
	LoadBitmap("ArrowRight", "UserInterface", &RightArrow);
    LoadBitmap("PlusBox", "UserInterface", &PlusBox);
    LoadBitmap("MinusBox", "UserInterface", &MinusBox);

    //the race icons (16 of these)
    LoadBitmap("MaleHumanOff", "Races", &MaleHumanOff);
    LoadBitmap("FemaleHumanOff", "Races", &FemaleHumanOff);
    LoadBitmap("MaleElfOff", "Races", &MaleElfOff);
    LoadBitmap("FemaleElfOff", "Races", &FemaleElfOff);
    LoadBitmap("MaleDwarfOff", "Races", &MaleDwarfOff);
    LoadBitmap("FemaleDwarfOff", "Races", &FemaleDwarfOff);
    LoadBitmap("MaleHalflingOff", "Races", &MaleHalflingOff);
    LoadBitmap("FemaleHalflingOff", "Races", &FemaleHalflingOff);
    LoadBitmap("MaleWarforgedOff", "Races", &MaleWarforgedOff);
    LoadBitmap("FemaleWarforgedOff", "Races", &FemaleWarforgedOff);
    LoadBitmap("MaleDrowOff", "Races", &MaleDrowOff);
    LoadBitmap("FemaleDrowOff", "Races", &FemaleDrowOff);
    LoadBitmap("MaleHalfelfOff", "Races", &MaleHalfelfOff);
    LoadBitmap("FemaleHalfelfOff", "Races", &FemaleHalfelfOff);
    LoadBitmap("MaleHalforcOff", "Races", &MaleHalforcOff);
    LoadBitmap("FemaleHalforcOff", "Races", &FemaleHalforcOff);
	LoadBitmap("BladeforgedMaleOff", "Races", &MaleBladeforgedOff);
	LoadBitmap("BladeforgedFemaleOff", "Races", &FemaleBladeforgedOff);
	LoadBitmap("MorninglordMaleOff", "Races", &MaleMorninglordOff);
	LoadBitmap("MorninglordFemaleOff", "Races", &FemaleMorninglordOff);
	LoadBitmap("PDKMaleOff", "Races", &MalePurpleDragonKnightOff);
	LoadBitmap("PDKFemaleOff", "Races", &FemalePurpleDragonKnightOff);
	LoadBitmap("ShadarKaiMaleOff", "Races", &MaleShadarKaiOff);
	LoadBitmap("ShadarKaiFemaleOff", "Races", &FemaleShadarKaiOff);
	LoadBitmap("MaleGnomeOff", "Races", &MaleGnomeOff);
	LoadBitmap("FemaleGnomeOff", "Races", &FemaleGnomeOff);
	LoadBitmap("MaleDeepGnomeOff", "Races", &MaleDeepGnomeOff);
	LoadBitmap("FemaleDeepGnomeOff", "Races", &FemaleDeepGnomeOff);

    LoadBitmap("MaleHumanOn", "Races", &MaleHumanOn);
    LoadBitmap("FemaleHumanOn", "Races", &FemaleHumanOn);
    LoadBitmap("MaleElfOn", "Races", &MaleElfOn);
    LoadBitmap("FemaleElfOn", "Races", &FemaleElfOn);
    LoadBitmap("MaleDwarfOn", "Races", &MaleDwarfOn);
    LoadBitmap("FemaleDwarfOn", "Races", &FemaleDwarfOn);
    LoadBitmap("MaleHalflingOn", "Races", &MaleHalflingOn);
    LoadBitmap("FemaleHalflingOn", "Races", &FemaleHalflingOn);
    LoadBitmap("MaleWarforgedOn", "Races", &MaleWarforgedOn);
    LoadBitmap("FemaleWarforgedOn", "Races", &FemaleWarforgedOn);
    LoadBitmap("MaleDrowOn", "Races", &MaleDrowOn);
    LoadBitmap("FemaleDrowOn", "Races", &FemaleDrowOn);
    LoadBitmap("MaleHalfelfOn", "Races", &MaleHalfelfOn);
    LoadBitmap("FemaleHalfelfOn", "Races", &FemaleHalfelfOn);
    LoadBitmap("MaleHalforcOn", "Races", &MaleHalforcOn);
    LoadBitmap("FemaleHalforcOn", "Races", &FemaleHalforcOn);
	LoadBitmap("BladeforgedMaleOn", "Races", &MaleBladeforgedOn);
	LoadBitmap("BladeforgedFemaleOn", "Races", &FemaleBladeforgedOn);
	LoadBitmap("MorninglordMaleOn", "Races", &MaleMorninglordOn);
	LoadBitmap("MorninglordFemaleOn", "Races", &FemaleMorninglordOn);
	LoadBitmap("PDKMaleOn", "Races", &MalePurpleDragonKnightOn);
	LoadBitmap("PDKFemaleOn", "Races", &FemalePurpleDragonKnightOn);
	LoadBitmap("ShadarKaiMaleOn", "Races", &MaleShadarKaiOn);
	LoadBitmap("ShadarKaiFemaleOn", "Races", &FemaleShadarKaiOn);
	LoadBitmap("MaleGnomeOn", "Races", &MaleGnomeOn);
	LoadBitmap("FemaleGnomeOn", "Races", &FemaleGnomeOn);
	LoadBitmap("MaleDeepGnomeOn", "Races", &MaleDeepGnomeOn);
	LoadBitmap("FemaleDeepGnomeOn", "Races", &FemaleDeepGnomeOn);

	//male/female buttons
	LoadBitmap("MaleOn", "Races", &MaleOn);
	LoadBitmap("MaleOff", "Races", &MaleOff);
	LoadBitmap("FemaleOn", "Races", &FemaleOn);
	LoadBitmap("FemaleOff", "Races", &FemaleOff);

	//the class icons (13 of these)
    LoadBitmap("Fighter", "Classes", &ClassIcon[0]);
    LoadBitmap("Paladin", "Classes", &ClassIcon[1]);
    LoadBitmap("Barbarian", "Classes", &ClassIcon[2]);
	LoadBitmap("Monk", "Classes", &ClassIcon[3]);
	LoadBitmap("Rogue", "Classes", &ClassIcon[4]);
	LoadBitmap("Ranger", "Classes", &ClassIcon[5]);
	LoadBitmap("Cleric", "Classes", &ClassIcon[6]);
	LoadBitmap("Wizard", "Classes", &ClassIcon[7]);
	LoadBitmap("Sorcerer", "Classes", &ClassIcon[8]);
	LoadBitmap("Bard", "Classes", &ClassIcon[9]);
	LoadBitmap("Favored Soul", "Classes", &ClassIcon[10]);
	LoadBitmap("Artificer", "Classes", &ClassIcon[11]);
	LoadBitmap("Druid", "Classes", &ClassIcon[12]);
	LoadBitmap("Warlock", "Classes", &ClassIcon[13]);

    //the level boxes
    LoadBitmap("LevelBoxBlue", "UserInterface", &BlueLevelBox);
    LoadBitmap("LevelBoxGreen", "UserInterface", &GreenLevelBox);
    LoadBitmap("LevelBoxRed", "UserInterface", &RedLevelBox);

    //empty feat/spell box
    LoadBitmap("EmptyFeatSlot", "UserInterface", &EmptyFeatSlot);
    LoadBitmap("EmptySpellSlot", "UserInterface", &EmptySpellSlot);

    //equipment screen
    LoadBitmap("CharacterDollScreen", "UserInterface", &EquipmentScreen);
    LoadBitmap("EquipmentSlotHighlight", "UserInterface", &EquipmentSlotHighlight, NULL, 20, 20);

	//No Feat Found
	LoadBitmap("NoImage", "Feats", &NoImage);

    }

//---------------------------------------------------------------------------
unsigned int MainScreenClass::LoadIcon(ICONTYPE IconType, string Name)
    {
    GraphicStruct NewIcon;

    switch (IconType)
        {
        case SKILLICON:
            {
            LoadBitmap(Name, "Skills", &NewIcon);
            SkillIcon.push_back(NewIcon);
            break;
            }
        case FEATICON:
            {
            for (unsigned int i=0; i<FeatIcon.size(); i++)
                {
                if (FeatIcon[i].Name == Name)
                    return i;
                }
            LoadBitmap(Name, "Feats", &NewIcon);
            NewIcon.Name = Name;
            FeatIcon.push_back(NewIcon);
            return FeatIcon.size()-1;
            }
        case SPELLICON:
            {
            for (unsigned int i=0; i<SpellIcon.size(); i++)
                {
                if (SpellIcon[i].Name == Name)
                    return i;
                }
            LoadBitmap(Name, "Spells", &NewIcon);
            NewIcon.Name = Name;
            SpellIcon.push_back(NewIcon);
            return SpellIcon.size()-1;
            }
        }

    return 0;
    }

//---------------------------------------------------------------------------
void MainScreenClass::DeleteGraphics()
    {
    DeleteObject(LeftArrow.Graphic);
    DeleteObject(LeftArrow.Mask);
    DeleteObject(RightArrow.Graphic);
    DeleteObject(RightArrow.Mask);
    DeleteObject(EmptyFeatSlot.Graphic);
    DeleteObject(EmptyFeatSlot.Mask);
    DeleteObject(EmptySpellSlot.Graphic);
    DeleteObject(EmptySpellSlot.Mask);
    DeleteObject(BlueLevelBox.Graphic);
    DeleteObject(BlueLevelBox.Mask);
    DeleteObject(GreenLevelBox.Graphic);
    DeleteObject(GreenLevelBox.Mask);
    DeleteObject(RedLevelBox.Graphic);
    DeleteObject(RedLevelBox.Mask);
    DeleteObject(PlusBox.Graphic);
    DeleteObject(PlusBox.Mask);
    DeleteObject(MinusBox.Graphic);
    DeleteObject(MinusBox.Mask);

    DeleteObject(MaleHumanOff.Graphic);
    DeleteObject(MaleHumanOff.Mask);
    DeleteObject(FemaleHumanOff.Graphic);
    DeleteObject(FemaleHumanOff.Mask);
    DeleteObject(MaleElfOff.Graphic);
    DeleteObject(MaleElfOff.Mask);
    DeleteObject(FemaleElfOff.Graphic);
    DeleteObject(FemaleElfOff.Mask);
    DeleteObject(MaleDwarfOff.Graphic);
    DeleteObject(MaleDwarfOff.Mask);
    DeleteObject(FemaleDwarfOff.Graphic);
    DeleteObject(FemaleDwarfOff.Mask);
    DeleteObject(MaleHalflingOff.Graphic);
    DeleteObject(MaleHalflingOff.Mask);
    DeleteObject(FemaleHalflingOff.Graphic);
    DeleteObject(FemaleHalflingOff.Mask);
    DeleteObject(MaleWarforgedOff.Graphic);
    DeleteObject(MaleWarforgedOff.Mask);
    DeleteObject(FemaleWarforgedOff.Graphic);
    DeleteObject(FemaleWarforgedOff.Mask);
    DeleteObject(MaleDrowOff.Graphic);
    DeleteObject(MaleDrowOff.Mask);
    DeleteObject(FemaleDrowOff.Graphic);
    DeleteObject(FemaleDrowOff.Mask);
    DeleteObject(MaleHalfelfOff.Graphic);
    DeleteObject(MaleHalfelfOff.Mask);
    DeleteObject(FemaleHalfelfOff.Graphic);
    DeleteObject(FemaleHalfelfOff.Mask);
    DeleteObject(MaleHalforcOff.Graphic);
    DeleteObject(MaleHalforcOff.Mask);
    DeleteObject(FemaleHalforcOff.Graphic);
    DeleteObject(FemaleHalforcOff.Mask);
    DeleteObject(MaleBladeforgedOff.Graphic);
    DeleteObject(MaleBladeforgedOff.Mask);
    DeleteObject(FemaleBladeforgedOff.Graphic);
    DeleteObject(FemaleBladeforgedOff.Mask);
    DeleteObject(MaleMorninglordOff.Graphic);
    DeleteObject(MaleMorninglordOff.Mask);
    DeleteObject(FemaleMorninglordOff.Graphic);
    DeleteObject(FemaleMorninglordOff.Mask);
    DeleteObject(MalePurpleDragonKnightOff.Graphic);
    DeleteObject(MalePurpleDragonKnightOff.Mask);
    DeleteObject(FemalePurpleDragonKnightOff.Graphic);
    DeleteObject(FemalePurpleDragonKnightOff.Mask);
    DeleteObject(MaleShadarKaiOff.Graphic);
    DeleteObject(MaleShadarKaiOff.Mask);
    DeleteObject(FemaleShadarKaiOff.Graphic);
    DeleteObject(FemaleShadarKaiOff.Mask);
	DeleteObject(MaleGnomeOff.Graphic);
	DeleteObject(MaleGnomeOff.Mask);
	DeleteObject(FemaleGnomeOff.Graphic);
	DeleteObject(FemaleGnomeOff.Mask);
	DeleteObject(MaleDeepGnomeOff.Graphic);
	DeleteObject(MaleDeepGnomeOff.Mask);
	DeleteObject(FemaleDeepGnomeOff.Graphic);
	DeleteObject(FemaleDeepGnomeOff.Mask);

    DeleteObject(MaleHumanOn.Graphic);
    DeleteObject(MaleHumanOn.Mask);
    DeleteObject(FemaleHumanOn.Graphic);
    DeleteObject(FemaleHumanOn.Mask);
    DeleteObject(MaleElfOn.Graphic);
    DeleteObject(MaleElfOn.Mask);
    DeleteObject(FemaleElfOn.Graphic);
    DeleteObject(FemaleElfOn.Mask);
    DeleteObject(MaleDwarfOn.Graphic);
    DeleteObject(MaleDwarfOn.Mask);
    DeleteObject(FemaleDwarfOn.Graphic);
    DeleteObject(FemaleDwarfOn.Mask);
    DeleteObject(MaleHalflingOn.Graphic);
    DeleteObject(MaleHalflingOn.Mask);
    DeleteObject(FemaleHalflingOn.Graphic);
    DeleteObject(FemaleHalflingOn.Mask);
    DeleteObject(MaleWarforgedOn.Graphic);
    DeleteObject(MaleWarforgedOn.Mask);
    DeleteObject(FemaleWarforgedOn.Graphic);
    DeleteObject(FemaleWarforgedOn.Mask);
    DeleteObject(MaleDrowOn.Graphic);
    DeleteObject(MaleDrowOn.Mask);
    DeleteObject(FemaleDrowOn.Graphic);
    DeleteObject(FemaleDrowOn.Mask);
    DeleteObject(MaleHalfelfOn.Graphic);
    DeleteObject(MaleHalfelfOn.Mask);
    DeleteObject(FemaleHalfelfOn.Graphic);
    DeleteObject(FemaleHalfelfOn.Mask);
    DeleteObject(MaleHalforcOn.Graphic);
    DeleteObject(MaleHalforcOn.Mask);
    DeleteObject(FemaleHalforcOn.Graphic);
    DeleteObject(FemaleHalforcOn.Mask);
    DeleteObject(MaleBladeforgedOn.Graphic);
    DeleteObject(MaleBladeforgedOn.Mask);
    DeleteObject(FemaleBladeforgedOn.Graphic);
    DeleteObject(FemaleBladeforgedOn.Mask);
    DeleteObject(MaleMorninglordOn.Graphic);
    DeleteObject(MaleMorninglordOn.Mask);
    DeleteObject(FemaleMorninglordOn.Graphic);
    DeleteObject(FemaleMorninglordOn.Mask);
    DeleteObject(MalePurpleDragonKnightOn.Graphic);
    DeleteObject(MalePurpleDragonKnightOn.Mask);
    DeleteObject(FemalePurpleDragonKnightOn.Graphic);
    DeleteObject(FemalePurpleDragonKnightOn.Mask);
    DeleteObject(MaleShadarKaiOn.Graphic);
    DeleteObject(MaleShadarKaiOn.Mask);
    DeleteObject(FemaleShadarKaiOn.Graphic);
    DeleteObject(FemaleShadarKaiOn.Mask);
	DeleteObject(MaleGnomeOn.Graphic);
	DeleteObject(MaleGnomeOn.Mask);
	DeleteObject(FemaleGnomeOn.Graphic);
	DeleteObject(FemaleGnomeOn.Mask);
	DeleteObject(MaleDeepGnomeOn.Graphic);
	DeleteObject(MaleDeepGnomeOn.Mask);
	DeleteObject(FemaleDeepGnomeOn.Graphic);
	DeleteObject(FemaleDeepGnomeOn.Mask);

    DeleteObject(MaleOn.Graphic);
    DeleteObject(MaleOn.Mask);
    DeleteObject(MaleOff.Graphic);
    DeleteObject(MaleOff.Mask);
    DeleteObject(FemaleOn.Graphic);
    DeleteObject(FemaleOn.Mask);
    DeleteObject(FemaleOff.Graphic);
    DeleteObject(FemaleOff.Mask);
    DeleteObject(EquipmentScreen.Graphic);
    DeleteObject(EquipmentScreen.Mask);
    DeleteObject(EquipmentSlotHighlight.Graphic);
    DeleteObject(EquipmentSlotHighlight.Mask);
    for (unsigned int i=0; i<NUMCLASSES; i++)
        {
        DeleteObject(ClassIcon[i].Graphic);
        DeleteObject(ClassIcon[i].Mask);
        }
    for (unsigned int i=0; i<SkillIcon.size(); i++)
        {
        DeleteObject(SkillIcon[i].Graphic);
        DeleteObject(SkillIcon[i].Mask);
        }
    for (unsigned int i=0; i<FeatIcon.size(); i++)
        {
        DeleteObject(FeatIcon[i].Graphic);
        DeleteObject(FeatIcon[i].Mask);
        }
    for (unsigned int i=0; i<SpellIcon.size(); i++)
        {
        DeleteObject(SpellIcon[i].Graphic);
        DeleteObject(SpellIcon[i].Mask);
        }
    DeleteObject(Palette);
    }

//---------------------------------------------------------------------------
void MainScreenClass::DrawGraphics(HWND hWnd, LPPAINTSTRUCT lpPS)
   {
	RECT rc;
	LOGBRUSH lb;

    // Select the bitmap into the off-screen DC.
    HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);

    // Erase the whole bitmap background.
	GetClientRect(hWnd, &rc);
    GetObject(GetStockObject(DKGRAY_BRUSH), sizeof(LOGBRUSH), &lb);
	HBRUSH hbrBkGnd = CreateSolidBrush(lb.lbColor);
	FillRect(hdcMem, &rc, hbrBkGnd);
	//SetBkMode(hdcMem, TRANSPARENT);

    //general stuff
    if(IsWindowVisible(NameLabel)) // CDE: Only show when necessary
		DrawLevelBars(hdcMem);

    //box specific stuff
    DrawAdvancementBoxGraphics(hdcMem);

    // Blt the changes to the screen DC.
    BitBlt(lpPS->hdc,
           rc.left, rc.top,
           rc.right-rc.left, rc.bottom-rc.top,
           hdcMem,
           0, 0,
           SRCCOPY);

    // Done with off-screen bitmap and DC.
    SelectObject(hdcMem, hbmOld);
    }

//---------------------------------------------------------------------------
void MainScreenClass::DrawLevelBars(HDC hdc)
    {
    COLORREF OldColor;
    HFONT OldFont;
	ostringstream ss;
	UIComponentManager *UIManager;
    InterfaceGraphicStruct *Graphic;
	int X, Y;
	int Width, Height;
	RECT ScreenRect;
	SIZE ScreenSize;

	GetClientRect(ParentWindow, &ScreenRect);

	ScreenSize.cx = ScreenRect.right - ScreenRect.left;
	ScreenSize.cy = ScreenRect.bottom - ScreenRect.top;

    SetBkMode(hdc, TRANSPARENT);
	if (UsingSystemFont == false)
		OldFont = (HFONT)SelectObject(hdc, ArielFontSmall);
    SetTextAlign(hdc, TA_CENTER);

	UIManager = InterfaceManager.GetUIComponents();
    for (unsigned int i=0; i<MAXLEVEL; i++)
        {
		ss.str("");
		ss << "LevelBar" << i+1;
		Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (Character.GetLevelError(i) == true)
            DrawGraphic(hdc, &RedLevelBox, X, Y, Width, Height);
        else if (CurrentSelectedLevel == i+1)
            DrawGraphic(hdc, &GreenLevelBox, X, Y, Width, Height);
        else
            DrawGraphic(hdc, &BlueLevelBox, X, Y, Width, Height);
        OldColor = SetTextColor(hdc, RGB(255,255,255));
		ss.str("");
		ss << "L" << i+1;
		TextOut(hdc, X+20*ScreenSize.cx/DEFAULTWIDTH, Y+6*ScreenSize.cy/DEFAULTHEIGHT, ss.str().c_str(), ss.str().size());
        SetTextColor(hdc, OldColor);
        }

	if (UsingSystemFont == false)
	    SelectObject(hdc, OldFont);
    SetTextAlign(hdc, TA_LEFT);
    }

//---------------------------------------------------------------------------
void MainScreenClass::ClearAdvancementBox()
	{
	//RECT ScreenRect;
	RECT PanelRect;

	GetClientRect(AdvancementWindowFrame, &PanelRect);
	MapWindowPoints(AdvancementWindowFrame, ParentWindow, (LPPOINT)&PanelRect, 2);
   RedrawWindow(ParentWindow, &PanelRect, NULL, RDW_ERASE | RDW_INVALIDATE);
	}

//--------------------------------------------------------------------------
void MainScreenClass::ClearKnownBox()
{
		//RECT ScreenRect;
		RECT PanelRect;

		GetClientRect(FeatBoxFrame, &PanelRect);
		MapWindowPoints(FeatBoxFrame, ParentWindow, (LPPOINT)&PanelRect, 2);
		RedrawWindow(ParentWindow, &PanelRect, NULL, RDW_ERASE | RDW_INVALIDATE);
	}


//---------------------------------------------------------------------------
void MainScreenClass::DrawAdvancementBoxGraphics(HDC hdc)
    {
    RACE CurrentRace;
    CLASS CurrentClass;
	SEX CurrentSex;
    int Value;
    ADVANCEMENTTYPE AdvancementType;
    string OutputString;
    ostringstream ss;
    COLORREF OldColor;
    HPEN OldPen;
    int Ability;
    int Modifier;
    int Cost;
    int PointsSpent;
    int Index;
    ALIGNMENT Alignment;
    CLASS Classes[3];
    int FeatIndex;
    int SpellIndex;
    int SpellLevel[3];
    int NumSpells[3];
    int NumSelected;
    int MaxPoints;
    FeatDataClass *Feat;
    int Count;
	int X, Y;
	int Width, Height;
	int LAX, LAY;
	int LAWidth, LAHeight;
	int RAX, RAY;
	int RAWidth, RAHeight;
	RECT ScreenRect;
	SIZE ScreenSize;
	UIComponentManager *UIManager;
    InterfaceGraphicStruct *Graphic;

	GetClientRect(ParentWindow, &ScreenRect);
	ScreenSize.cx = ScreenRect.right - ScreenRect.left;
	ScreenSize.cy = ScreenRect.bottom - ScreenRect.top;
	UIManager = InterfaceManager.GetUIComponents();

    if (EquipmentScreenShown == true)
        {
		Graphic = UIManager->GetGraphicData("EquipmentPanel", MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
        DrawGraphic(hdc, &EquipmentScreen, X, Y, Width, Height);
        if (EquipmentScreenCurrentSelectedSlot == RIGHTHANDSLOT)
            {
			Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot1", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
			Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
			DrawGraphic(hdc, &EquipmentSlotHighlight, X, Y, Width, Height);
			}
        if (EquipmentScreenCurrentSelectedSlot == LEFTHANDSLOT)
            {
			Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot2", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
			Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
			DrawGraphic(hdc, &EquipmentSlotHighlight, X, Y, Width, Height);
			}
        if (EquipmentScreenCurrentSelectedSlot == AMMOSLOT)
            {
			Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot3", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
			Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
			DrawGraphic(hdc, &EquipmentSlotHighlight, X, Y, Width, Height);
			}
		if (EquipmentScreenCurrentSelectedSlot == QUIVERSLOT)
            {
			Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot4", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
			Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
			DrawGraphic(hdc, &EquipmentSlotHighlight, X, Y, Width, Height);
			}
        if (EquipmentScreenCurrentSelectedSlot == FACESLOT)
            {
			Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot5", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
			Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
			DrawGraphic(hdc, &EquipmentSlotHighlight, X, Y, Width, Height);
			}
        if (EquipmentScreenCurrentSelectedSlot == ARMORSLOT)
            {
			Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot6", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
			Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
			DrawGraphic(hdc, &EquipmentSlotHighlight, X, Y, Width, Height);
			}
        if (EquipmentScreenCurrentSelectedSlot == BRACERSLOT)
            {
			Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot7", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
			Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
			DrawGraphic(hdc, &EquipmentSlotHighlight, X, Y, Width, Height);
			}
        if (EquipmentScreenCurrentSelectedSlot == LEFTRINGSLOT)
            {
			Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot8", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
			Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
			DrawGraphic(hdc, &EquipmentSlotHighlight, X, Y, Width, Height);
			}
        if (EquipmentScreenCurrentSelectedSlot == HEADSLOT)
            {
			Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot9", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
			Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
			DrawGraphic(hdc, &EquipmentSlotHighlight, X, Y, Width, Height);
			}
        if (EquipmentScreenCurrentSelectedSlot == FEETSLOT)
            {
			Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot10", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
			Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
			DrawGraphic(hdc, &EquipmentSlotHighlight, X, Y, Width, Height);
			}
        if (EquipmentScreenCurrentSelectedSlot == NECKSLOT)
            {
			Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot11", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
			Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
			DrawGraphic(hdc, &EquipmentSlotHighlight, X, Y, Width, Height);
			}
        if (EquipmentScreenCurrentSelectedSlot == GLOVESSLOT)
            {
			Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot12", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
			Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
			DrawGraphic(hdc, &EquipmentSlotHighlight, X, Y, Width, Height);
			}
        if (EquipmentScreenCurrentSelectedSlot == TRINKETSLOT)
            {
			Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot13", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
			Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
			DrawGraphic(hdc, &EquipmentSlotHighlight, X, Y, Width, Height);
			}
        if (EquipmentScreenCurrentSelectedSlot == BACKSLOT)
            {
			Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot14", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
			Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
			DrawGraphic(hdc, &EquipmentSlotHighlight, X, Y, Width, Height);
			}
        if (EquipmentScreenCurrentSelectedSlot == WAISTSLOT)
            {
			Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot15", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
			Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
			DrawGraphic(hdc, &EquipmentSlotHighlight, X, Y, Width, Height);
			}
        if (EquipmentScreenCurrentSelectedSlot == RIGHTRINGSLOT)
            {
			Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot16", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
			Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
			DrawGraphic(hdc, &EquipmentSlotHighlight, X, Y, Width, Height);
			}
        ReleaseDC(ParentWindow, hdc);
        return;
        }

    CurrentRace = Character.GetRace();
    CurrentClass = Character.GetClass(CurrentSelectedLevel);
	CurrentSex = Character.GetSex();
    AdvancementType = Data.GetAdvancementType(CurrentSelectedLevel, CurrentRace, CurrentClass, CurrentInstructionSelection, &Value);

    switch (AdvancementType)
        {
		
        case ADV_RACEANDSEX:
            {
			LRESULT IsHeroicClassChecked = SendMessage(HeroicClassRadioButton, BM_GETCHECK, 0, 0);
			if (CurrentSex == MALE)
			{
				if (IsHeroicClassChecked == 1)
				{
					if (CurrentRace == HUMAN)
					{
						Graphic = UIManager->GetGraphicData("MaleHumanOn", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleHumanOn, X, Y, Width, Height);
					}
					else
					{
						Graphic = UIManager->GetGraphicData("MaleHumanOff", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleHumanOff, X, Y, Width, Height);
					}
					if (CurrentRace == ELF)
					{
						Graphic = UIManager->GetGraphicData("MaleElfOn", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleElfOn, X, Y, Width, Height);
					}
					else
					{
						Graphic = UIManager->GetGraphicData("MaleElfOff", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleElfOff, X, Y, Width, Height);
					}
					if (CurrentRace == HALFLING)
					{
						Graphic = UIManager->GetGraphicData("MaleHalflingOn", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleHalflingOn, X, Y, Width, Height);
					}
					else
					{
						Graphic = UIManager->GetGraphicData("MaleHalflingOff", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleHalflingOff, X, Y, Width, Height);
					}
					if (CurrentRace == DWARF)
					{
						Graphic = UIManager->GetGraphicData("MaleDwarfOn", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleDwarfOn, X, Y, Width, Height);
					}
					else
					{
						Graphic = UIManager->GetGraphicData("MaleDwarfOff", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleDwarfOff, X, Y, Width, Height);
					}
					if (CurrentRace == WARFORGED)
					{
						Graphic = UIManager->GetGraphicData("MaleWarforgedOn", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleWarforgedOn, X, Y, Width, Height);
					}
					else
					{
						Graphic = UIManager->GetGraphicData("MaleWarforgedOff", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleWarforgedOff, X, Y, Width, Height);
					}
					if (CurrentRace == HALFELF)
					{
						Graphic = UIManager->GetGraphicData("MaleHalfelfOn", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleHalfelfOn, X, Y, Width, Height);
					}
					else
					{
						Graphic = UIManager->GetGraphicData("MaleHalfelfOff", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleHalfelfOff, X, Y, Width, Height);
					}
					if (CurrentRace == DROW)
					{
						Graphic = UIManager->GetGraphicData("MaleDrowOn", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleDrowOn, X, Y, Width, Height);
					}
					else
					{
						Graphic = UIManager->GetGraphicData("MaleDrowOff", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleDrowOff, X, Y, Width, Height);
					}
					if (CurrentRace == HALFORC)
					{
						Graphic = UIManager->GetGraphicData("MaleHalforcOn", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleHalforcOn, X, Y, Width, Height);
					}
					else
					{
						Graphic = UIManager->GetGraphicData("MaleHalforcOff", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleHalforcOff, X, Y, Width, Height);
					}
					if (CurrentRace == GNOME)
					{
						Graphic = UIManager->GetGraphicData("MaleGnomeOn", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleGnomeOn, X, Y, Width, Height);
					}
					else
					{
						Graphic = UIManager->GetGraphicData("MaleGnomeOff", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleGnomeOff, X, Y, Width, Height);
					}
				}
				else
				{
					if (CurrentRace == BLADEFORGED)
					{
						Graphic = UIManager->GetGraphicData("MaleBladeforgedOn", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleBladeforgedOn, X, Y, Width, Height);
					}
					else
					{
						Graphic = UIManager->GetGraphicData("MaleBladeforgedOff", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleBladeforgedOff, X, Y, Width, Height);
					}
					if (CurrentRace == MORNINGLORD)
					{
						Graphic = UIManager->GetGraphicData("MaleMorninglordOn", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleMorninglordOn, X, Y, Width, Height);
					}
					else
					{
						Graphic = UIManager->GetGraphicData("MaleMorninglordOff", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleMorninglordOff, X, Y, Width, Height);
					}
					if (CurrentRace == PURPLEDRAGONKNIGHT)
					{
						Graphic = UIManager->GetGraphicData("MalePurpleDragonKnightOn", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MalePurpleDragonKnightOn, X, Y, Width, Height);
					}
					else
					{
						Graphic = UIManager->GetGraphicData("MalePurpleDragonKnightOff", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MalePurpleDragonKnightOff, X, Y, Width, Height);
					}
					if (CurrentRace == SHADARKAI)
					{
						Graphic = UIManager->GetGraphicData("MaleShadarKaiOn", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleShadarKaiOn, X, Y, Width, Height);
					}
					else
					{
						Graphic = UIManager->GetGraphicData("MaleShadarKaiOff", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleShadarKaiOff, X, Y, Width, Height);
					}


					if (CurrentRace == DEEPGNOME)
					{
						Graphic = UIManager->GetGraphicData("MaleDeepGnomeOn", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleDeepGnomeOn, X, Y, Width, Height);
					}
					else
					{
						Graphic = UIManager->GetGraphicData("MaleDeepGnomeOff", MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						DrawGraphic(hdc, &MaleDeepGnomeOff, X, Y, Width, Height);
					}
				}
				Graphic = UIManager->GetGraphicData("MaleOn", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
	            DrawGraphic(hdc, &MaleOn, X, Y, Width, Height);
				Graphic = UIManager->GetGraphicData("FemaleOff", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
	            DrawGraphic(hdc, &FemaleOff, X, Y, Width, Height);
				}
			else
				{
					if (IsHeroicClassChecked == 1)
					{
						if (CurrentRace == HUMAN)
						{
							Graphic = UIManager->GetGraphicData("FemaleHumanOn", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleHumanOn, X, Y, Width, Height);
						}
						else
						{
							Graphic = UIManager->GetGraphicData("FemaleHumanOff", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleHumanOff, X, Y, Width, Height);
						}
						if (CurrentRace == ELF)
						{
							Graphic = UIManager->GetGraphicData("FemaleElfOn", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleElfOn, X, Y, Width, Height);
						}
						else
						{
							Graphic = UIManager->GetGraphicData("FemaleElfOff", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleElfOff, X, Y, Width, Height);
						}
						if (CurrentRace == HALFLING)
						{
							Graphic = UIManager->GetGraphicData("FemaleHalflingOn", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleHalflingOn, X, Y, Width, Height);
						}
						else
						{
							Graphic = UIManager->GetGraphicData("FemaleHalflingOff", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleHalflingOff, X, Y, Width, Height);
						}
						if (CurrentRace == DWARF)
						{
							Graphic = UIManager->GetGraphicData("FemaleDwarfOn", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleDwarfOn, X, Y, Width, Height);
						}
						else
						{
							Graphic = UIManager->GetGraphicData("FemaleDwarfOff", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleDwarfOff, X, Y, Width, Height);
						}
						if (CurrentRace == WARFORGED)
						{
							Graphic = UIManager->GetGraphicData("FemaleWarforgedOn", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleWarforgedOn, X, Y, Width, Height);
						}
						else
						{
							Graphic = UIManager->GetGraphicData("FemaleWarforgedOff", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleWarforgedOff, X, Y, Width, Height);
						}
						if (CurrentRace == HALFELF)
						{
							Graphic = UIManager->GetGraphicData("FemaleHalfelfOn", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleHalfelfOn, X, Y, Width, Height);
						}
						else
						{
							Graphic = UIManager->GetGraphicData("FemaleHalfelfOff", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleHalfelfOff, X, Y, Width, Height);
						}
						if (CurrentRace == DROW)
						{
							Graphic = UIManager->GetGraphicData("FemaleDrowOn", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleDrowOn, X, Y, Width, Height);
						}
						else
						{
							Graphic = UIManager->GetGraphicData("FemaleDrowOff", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleDrowOff, X, Y, Width, Height);
						}
						if (CurrentRace == HALFORC)
						{
							Graphic = UIManager->GetGraphicData("FemaleHalforcOn", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleHalforcOn, X, Y, Width, Height);
						}
						else
						{
							Graphic = UIManager->GetGraphicData("FemaleHalforcOff", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleHalforcOff, X, Y, Width, Height);
						}
						if (CurrentRace == GNOME)
						{
							Graphic = UIManager->GetGraphicData("FemaleGnomeOn", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleGnomeOn, X, Y, Width, Height);
						}
						else
						{
							Graphic = UIManager->GetGraphicData("FemaleGnomeOff", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleGnomeOff, X, Y, Width, Height);
						}
					}
					else
					{
						if (CurrentRace == BLADEFORGED)
						{
							Graphic = UIManager->GetGraphicData("FemaleBladeforgedOn", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleBladeforgedOn, X, Y, Width, Height);
						}
						else
						{
							Graphic = UIManager->GetGraphicData("FemaleBladeforgedOff", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleBladeforgedOff, X, Y, Width, Height);
						}
						if (CurrentRace == MORNINGLORD)
						{
							Graphic = UIManager->GetGraphicData("MaleMorninglordOn", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleMorninglordOn, X, Y, Width, Height);
						}
						else
						{
							Graphic = UIManager->GetGraphicData("MaleMorninglordOff", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleMorninglordOff, X, Y, Width, Height);
						}
						if (CurrentRace == PURPLEDRAGONKNIGHT)
						{
							Graphic = UIManager->GetGraphicData("MalePurpleDragonKnightOn", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemalePurpleDragonKnightOn, X, Y, Width, Height);
						}
						else
						{
							Graphic = UIManager->GetGraphicData("MalePurpleDragonKnightOff", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemalePurpleDragonKnightOff, X, Y, Width, Height);
						}
						if (CurrentRace == SHADARKAI)
						{
							Graphic = UIManager->GetGraphicData("MaleShadarKaiOn", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleShadarKaiOn, X, Y, Width, Height);
						}
						else
						{
							Graphic = UIManager->GetGraphicData("MaleShadarKaiOff", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleShadarKaiOff, X, Y, Width, Height);
						}
						if (CurrentRace == DEEPGNOME)
						{
							Graphic = UIManager->GetGraphicData("FemaleDeepGnomeOn", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleDeepGnomeOn, X, Y, Width, Height);
						}
						else
						{
							Graphic = UIManager->GetGraphicData("FemaleDeepGnomeOff", MAINWINDOW);
							X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
							Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
							Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
							Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
							DrawGraphic(hdc, &FemaleDeepGnomeOff, X, Y, Width, Height);
						}
					}
				

				Graphic = UIManager->GetGraphicData("MaleOff", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
	            DrawGraphic(hdc, &MaleOff, X, Y, Width, Height);
				Graphic = UIManager->GetGraphicData("FemaleOn", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
	            DrawGraphic(hdc, &FemaleOn, X, Y, Width, Height);
				}
            break;
            }
        case ADV_CLASS:
            {

			//determine which classes go into each slot
			for (unsigned int i=0; i<NUMCLASSES; i++)
                {
                if (CurrentSelectedLevel == 1)
                    ClassSlot[i] = (CLASS)i;
                else
                    ClassSlot[i] = CLASSNONE;
                }

			//Character.GetMulticlassClasses(CurrentSelectedLevel, Classes);
			//if (Classes[2] != CLASSNONE)
			Character.GetMulticlassClasses(20, Classes);
			if (Classes[2] != CLASSNONE && Character.GetNumClassLevels(Character.GetClass(CurrentSelectedLevel, false)) > 1)
				{
				//we have the maximum number of classes already!
				for (unsigned int i=0; i<3; i++)
					ClassSlot[i] = Classes[i];
				}
            else if (CurrentSelectedLevel > 1)
                {
                Index = 0;
                Alignment = Character.GetAlignment();
				for (unsigned int i=0; i<NUMCLASSES; i++)
                    {
                    if (Data.IsAlignmentCompatable((CLASS)i, Alignment) == true)
                        {
                        ClassSlot[Index] = (CLASS)i;
                        Index++;
                        }
                    }
                }
			//draw the class icons
			for (unsigned int i=0; i<NUMCLASSES; i++)
                {
                if (ClassSlot[i] == CLASSNONE)
                    break;
				ss.str("");
				ss << "ClassSlot" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
				DrawGraphic(hdc, &ClassIcon[ClassSlot[i]], X, Y, Width, Height);
                }
            //highlight lines
            OldPen = (HPEN)SelectObject(hdc, HighlightPen);
            CurrentClass = Character.GetClass(CurrentSelectedLevel);
			for (unsigned int i=0; i<NUMCLASSES; i++)
                {
				if (ClassSlot[i] == CurrentClass)
					{
					ss.str("");
					ss << "ClassSlot" << i+1;
					Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
					break;
					}
				}
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx-2);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy-2);
			Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx+2);
			Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy+2);
			MoveToEx(hdc, X, Y, NULL);
			LineTo(hdc, X+Width, Y);
			LineTo(hdc, X+Width, Y+Height);
			LineTo(hdc, X, Y+Height);
            LineTo(hdc, X, Y);
            SelectObject(hdc, OldPen);
            break;
            }
        case ADV_NAMEANDALIGNMENT:
            {
            OldColor = SetTextColor(hdc, RGB(255,255,255));
            OutputString = "First Name";
			Graphic = UIManager->GetGraphicData("FirstNameText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
            OutputString = "Surname";
			Graphic = UIManager->GetGraphicData("SurnameText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
            for (unsigned int i=0; i<6; i++)
                AlignmentSlot[i] = NOALIGNMENT;
            Index = 0;
            if (Character.IsAlignmentLegal(LAWFULGOOD) == true)
                {
                AlignmentSlot[Index] = LAWFULGOOD;
                Index++;
                }
            if (Character.IsAlignmentLegal(LAWFULNEUTRAL) == true)
                {
                AlignmentSlot[Index] = LAWFULNEUTRAL;
                Index++;
                }
            if (Character.IsAlignmentLegal(NEUTRALGOOD) == true)
                {
                AlignmentSlot[Index] = NEUTRALGOOD;
                Index++;
                }
            if (Character.IsAlignmentLegal(TRUENEUTRAL) == true)
                {
                AlignmentSlot[Index] = TRUENEUTRAL;
                Index++;
                }
            if (Character.IsAlignmentLegal(CHAOTICGOOD) == true)
                {
                AlignmentSlot[Index] = CHAOTICGOOD;
                Index++;
                }
            if (Character.IsAlignmentLegal(CHAOTICNEUTRAL) == true)
                {
                AlignmentSlot[Index] = CHAOTICNEUTRAL;
                Index++;
                }
            for (unsigned int i=0; i<6; i++)
                {
                if (AlignmentSlot[i] == NOALIGNMENT)
                    break;
                OutputString = Data.GetAlignmentString(AlignmentSlot[i]);
                if (AlignmentSlot[i] == Character.GetAlignment())
                    SetTextColor(hdc, RGB(230,230,0));
                else
                    SetTextColor(hdc, RGB(255,255,255));
				ss.str("");
				ss << "AlignmentText" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
                }
            SetTextColor(hdc, OldColor);
            break;
            }
        case ADV_REINCARNATE:
            {
				LRESULT GetState;
			PastLifeRadioState = 0;
			GetState = SendMessage(HeroicPastRadioButton, BM_GETCHECK, 0, 0);
			if (GetState == 1)
				PastLifeRadioState = 0;
			GetState = SendMessage(IconicPastRadioButton, BM_GETCHECK, 0, 0);
			if (GetState == 1)
				PastLifeRadioState = 1;
			GetState = SendMessage(EpicPastRadioButton, BM_GETCHECK, 0, 0);
			if (GetState == 1)
				PastLifeRadioState = 2;
			switch (PastLifeRadioState)
			{
			case 0:
				//Heroic Past LIfes
			{				
				for (unsigned int i = 0; i < PASTLIFEFEAT; i++)
				{
					ss.str("");
					ss << "ReincarnateIcon" << i + 1;
					Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
					X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
					Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
					Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
					Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
					ss.str("");
					ss << "ReincarnateLA" << i + 1;
					Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
					LAX = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
					LAY = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
					LAWidth = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
					LAHeight = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
					ss.str("");
					ss << "ReincarnateRA" << i + 1;
					Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
					RAX = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
					RAY = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
					RAWidth = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
					RAHeight = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
					Count = Character.GetReincarnateCount(static_cast<CLASS>(i));
					if (Count == 0)
					{
						DrawGraphicGreyscale(hdc, &ClassIcon[i], X, Y, Width, Height);
						DrawGraphicGreyscale(hdc, &LeftArrow, LAX, LAY, LAWidth, LAHeight);
					}
					else
					{
						DrawGraphic(hdc, &ClassIcon[i], X, Y, Width, Height);
						DrawGraphic(hdc, &LeftArrow, LAX, LAY, LAWidth, LAHeight);
					}
					if (Count == 3)
						DrawGraphicGreyscale(hdc, &RightArrow, RAX, RAY, RAWidth, RAHeight);
					else
						DrawGraphic(hdc, &RightArrow, RAX, RAY, RAWidth, RAHeight);
					OldColor = SetTextColor(hdc, RGB(255, 255, 255));
					ss.str("");
					ss << "ReincarnateNumText" << i + 1;
					Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
					X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
					Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
					ss.str("");
					ss << Count;
					OutputString = ss.str();
					TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
					SetTextColor(hdc, OldColor);
				}
			break;
			}
			case 1:
				//Iconic Past Lifes
			{
				for (unsigned int i = 0; i < ICONICPASTLIFEFEAT; i++)
				{
					ss.str("");
					ss << "ReincarnateIcon" << i + 1;
					Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
					X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
					Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
					Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
					Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
					ss.str("");
					ss << "ReincarnateLA" << i + 1;
					Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
					LAX = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
					LAY = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
					LAWidth = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
					LAHeight = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
					ss.str("");
					ss << "ReincarnateRA" << i + 1;
					Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
					RAX = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
					RAY = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
					RAWidth = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
					RAHeight = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
					//Change for Iconic pastlife count
					
					Count = Character.GetReincarnateCount(static_cast<CLASS>(i));
					Count = Character.GetIconicPastLifeCount(static_cast<ICONICRACES>(i));
					int FeatIndex = Character.GetIconicFeatIndex(static_cast<ICONICRACES>(i));
					Feat = Data.GetFeatPointer(FeatIndex);
					int FeatIconIndex = Feat->GetFeatIconIndex();
					GraphicStruct CurrentIcon;
					if (FeatIndex == -1)
						CurrentIcon = NoImage;
					else
						CurrentIcon = FeatIcon[FeatIconIndex];
					if (Count == 0)
					{
						DrawGraphicGreyscale(hdc, &CurrentIcon, X, Y, Width, Height);
						DrawGraphicGreyscale(hdc, &LeftArrow, LAX, LAY, LAWidth, LAHeight);
					}
					else
					{
						DrawGraphic(hdc, &CurrentIcon, X, Y, Width, Height);
						DrawGraphic(hdc, &LeftArrow, LAX, LAY, LAWidth, LAHeight);
					}
					if (Count == 3)
						DrawGraphicGreyscale(hdc, &RightArrow, RAX, RAY, RAWidth, RAHeight);
					else
						DrawGraphic(hdc, &RightArrow, RAX, RAY, RAWidth, RAHeight);
					OldColor = SetTextColor(hdc, RGB(255, 255, 255));
					ss.str("");
					ss << "ReincarnateNumText" << i + 1;
					Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
					X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
					Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
					ss.str("");
					ss << Count;
					OutputString = ss.str();
					TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
					SetTextColor(hdc, OldColor);
				}
				break;
			}
			case 2:
				//Epic Past Lifes
			{
				for (unsigned int y1 = 0; y1 < EPICPASTLIFESPHERE; y1++)
				{
					for (unsigned int x1 = 0; x1 < 3; x1++)
					{
						unsigned int i;
						i = y1 * 4 + x1;
						ss.str("");
						ss << "ReincarnateIcon" << i + 1;
						Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						ss.str("");
						ss << "ReincarnateLA" << i + 1;
						Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
						LAX = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						LAY = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						LAWidth = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						LAHeight = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						ss.str("");
						ss << "ReincarnateRA" << i + 1;
						Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
						RAX = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						RAY = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						RAWidth = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						RAHeight = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
						//Change for Epic pastlife count
						Count = Character.GetReincarnateCount(static_cast<CLASS>(i));
						Count = Character.GetEpicFeatCount(static_cast<DESTINY_SPHERE>(y1), x1);
						int FeatIndex = Character.GetEpicFeatIndex(static_cast<DESTINY_SPHERE>(y1), x1);
						Feat = Data.GetFeatPointer(FeatIndex);
						int FeatIconIndex = Feat->GetFeatIconIndex();
						GraphicStruct CurrentIcon;
						if (FeatIndex == -1)
							CurrentIcon = NoImage;
						else
							CurrentIcon = FeatIcon[FeatIconIndex];
						if (Count == 0)
						{
							DrawGraphicGreyscale(hdc, &CurrentIcon, X, Y, Width, Height);
							DrawGraphicGreyscale(hdc, &LeftArrow, LAX, LAY, LAWidth, LAHeight);
						}
						else
						{
							DrawGraphic(hdc, &CurrentIcon, X, Y, Width, Height);
							DrawGraphic(hdc, &LeftArrow, LAX, LAY, LAWidth, LAHeight);
						}
						if (Count == 3)
							DrawGraphicGreyscale(hdc, &RightArrow, RAX, RAY, RAWidth, RAHeight);
						else
							DrawGraphic(hdc, &RightArrow, RAX, RAY, RAWidth, RAHeight);
						OldColor = SetTextColor(hdc, RGB(255, 255, 255));
						ss.str("");
						ss << "ReincarnateNumText" << i + 1;
						Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						ss.str("");
						ss << Count;
						OutputString = ss.str();
						TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
						SetTextColor(hdc, OldColor);
					}
				}
				break;
			}
			}
			break;
            }
        case ADV_ABILITYPOINT:
            {
            OldColor = SetTextColor(hdc, RGB(255,255,255));
			Graphic = UIManager->GetGraphicData("AbilityPointAbilityText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Ability";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("AbilityPointValueText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Value";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("AbilityPointCostText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Cost";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("AbilityPointModText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Mod";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("AbilityPointStrengthText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Strength";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("AbilityPointDexterityText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Dexterity";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("AbilityPointConstitutionText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Constitution";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("AbilityPointIntelligenceText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Intelligence";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("AbilityPointWisdomText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Wisdom";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("AbilityPointCharismaText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Charisma";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
            PointsSpent = 0;
            for (unsigned int i=0; i<6; i++)
                {
				ss.str("");
				ss << "AbilityPointValue" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
                ss.str("");
                Ability = Character.GetAbility(i, CurrentSelectedLevel, true, true, true);
                ss << Ability;
                OutputString = ss.str();
                TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
                ss.str("");
                Cost = Character.GetAbilityCost(i);
                if (Cost == -1)
                    OutputString = "MAX";
                else
                    {
                    ss << Cost;
                    OutputString = ss.str();
                    }
				X += static_cast<int>(65.0/DEFAULTWIDTH*ScreenSize.cx);
                TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
                ss.str("");
                Modifier = Data.CalculateAbilityModifier(Ability);
                if (Modifier > 0)
                    ss << "+" << Modifier;
                else
                    ss << Modifier;
                OutputString = ss.str();
				X += static_cast<int>(50.0/DEFAULTWIDTH*ScreenSize.cx);
                TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
                PointsSpent += Character.GetAbilityPointsSpent(i);
                }
			Graphic = UIManager->GetGraphicData("AbilityPointSpendRemain", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            ss.str("");
            MaxPoints = Character.CalculateTotalAbilityPoints();
            ss << "Remaining Points to Spend: " << MaxPoints - PointsSpent;
            OutputString = ss.str();
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
            SetTextColor(hdc, OldColor);
            for (unsigned int i=0; i<6; i++)
                {
				ss.str("");
				ss << "AbilityPointLA" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
                if (Character.GetAbilityPointsSpent(i) == 0)
                    DrawGraphicGreyscale(hdc, &LeftArrow, X, Y, Width, Height);
                else
                    DrawGraphic(hdc, &LeftArrow, X, Y, Width, Height);
				ss.str("");
				ss << "AbilityPointRA" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
                if (Character.GetAbilityPointsSpent(i) == 16)
                    DrawGraphicGreyscale(hdc, &RightArrow, X, Y, Width, Height);
                else if (Character.GetAbilityCost(i) > MaxPoints - PointsSpent)
                    DrawGraphicGreyscale(hdc, &RightArrow, X, Y, Width, Height);
                else
                    DrawGraphic(hdc, &RightArrow, X, Y, Width, Height);
                }
            break;
            }
        case ADV_ABILITYINCREASE:
            {
            OldColor = SetTextColor(hdc, RGB(255,255,255));
			Graphic = UIManager->GetGraphicData("AbilityPointAbilityText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Ability";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("AbilityPointValueText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Value";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("AbilityPointCostText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Mod";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("AbilityPointStrengthText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Strength";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("AbilityPointDexterityText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Dexterity";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("AbilityPointConstitutionText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Constitution";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("AbilityPointIntelligenceText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Intelligence";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("AbilityPointWisdomText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Wisdom";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("AbilityPointCharismaText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Charisma";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
            PointsSpent = 0;
            for (unsigned int i=0; i<6; i++)
                {
                ss.str("");
				ss << "AbilityPointValue" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				ss.str("");
                Ability = Character.GetAbility(i, CurrentSelectedLevel, true, true, true);
                ss << Ability;
                OutputString = ss.str();
                TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
                ss.str("");
                Modifier = Data.CalculateAbilityModifier(Ability);
                if (Modifier > 0)
                    ss << "+" << Modifier;
                else
                    ss << Modifier;
                OutputString = ss.str();
				X += static_cast<int>(65.0/DEFAULTWIDTH*ScreenSize.cx);
                TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
                }
			Graphic = UIManager->GetGraphicData("AbilityPointSpendRemain", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Increase any ability by 1 point";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
            SetTextColor(hdc, OldColor);
            if (Character.GetAbilityIncrease(CurrentSelectedLevel) == ABILITYNONE)
                {
                for (unsigned int i=0; i<6; i++)
                    {
					ss.str("");
					ss << "AbilityPointLA" << i+1;
					Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
					X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
					Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
					Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
					Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
                    DrawGraphicGreyscale(hdc, &LeftArrow, X, Y, Width, Height);
					ss.str("");
					ss << "AbilityPointRA" << i+1;
					Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
					X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
					Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
					Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
					Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
                    DrawGraphic(hdc, &RightArrow, X, Y, Width, Height);
                    }
                }
            else
                {
                for (unsigned int i=0; i<6; i++)
                    {
					ss.str("");
					ss << "AbilityPointLA" << i+1;
					Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
					X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
					Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
					Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
					Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
                    if (Character.GetAbilityIncrease(CurrentSelectedLevel) == (int)i)
		                DrawGraphic(hdc, &LeftArrow, X, Y, Width, Height);
                    else
		                DrawGraphicGreyscale(hdc, &LeftArrow, X, Y, Width, Height);
					ss.str("");
					ss << "AbilityPointRA" << i+1;
					Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
					X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
					Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
					Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
					Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
			        DrawGraphicGreyscale(hdc, &RightArrow, X, Y, Width, Height);
                    }
                }
            break;
            }
        case ADV_SKILLS:
            {
            OldColor = SetTextColor(hdc, RGB(255,255,255));
			Graphic = UIManager->GetGraphicData("SkillsSkillText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Skill";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("SkillsTotalText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Total";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("SkillsModText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Mod";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("SkillsPointsText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Points";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("SkillsSpentText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Spent";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("SkillsRemainingText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            ss.str("");
            ss << "Remaining Points to Spend: " << Character.CalculateAvailableSkillPoints(CurrentSelectedLevel);
            OutputString = ss.str();
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
            SetTextColor(hdc, OldColor);
            break;
            }
        case ADV_FEATS:
            {
            Character.DetermineFeatSlots(CurrentSelectedLevel, &FeatSlot[0], &FeatSlot[1], &FeatSlot[2]);
			InterfaceComponentStruct *Component = UIManager->GetComponentData("AdvancementWindowFrame", MAINWINDOW);
			int FrameBottom = static_cast<int>((Component->BaseLocationY+Component->BaseHeight)*ScreenSize.cy);

			for (unsigned int i = 0; i < 3; i++)
			{
				if (FeatSlot[i] == FEATNONE)
					break;
				ss.str("");
				ss << "FeatSlot" << i + 1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(FrameBottom - 80);
				Width = 45; // CDE: Avoid zomming slot box
				Height = 45; // CDE: Avoid zomming slot box
				DrawGraphic(hdc, &EmptyFeatSlot, X, Y, Width, Height);
				FeatIndex = Character.GetFeat(CurrentSelectedLevel, FeatSlot[i], 0);
				if (FeatIndex != -1)
				{
					Feat = Data.GetFeatPointer(FeatIndex);
					ss.str("");
					ss << "FeatFilled" << i + 1;
					Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
					X = static_cast<int>(X + 3);
					Y = static_cast<int>(Y + 2);
					Width = 40; // CDE: Avoid zomming filled feat
					Height = 40; // CDE: Avoid zomming filled feat
					DrawGraphic(hdc, &FeatIcon[Feat->GetFeatIconIndex()], X, Y, Width, Height);
				}
				if (FeatSlot[i] == FEATCHARACTER || FeatSlot[i] == FEATHUMANBONUS)
					OldColor = SetTextColor(hdc, RGB(255, 255, 255));
				if (FeatSlot[i] == FEATFIGHTERBONUS || FeatSlot[i] == FEATWIZARDBONUS || FeatSlot[i] == FEATARTIFICERBONUS || FeatSlot[i] == FEATROGUEBONUS || FeatSlot[i] == FEATMONKBONUS ||
					FeatSlot[i] == FEATFAVOREDSOULBONUS || FeatSlot[i] == FEATRANGERFAVOREDENEMY || FeatSlot[i] == FEATMONKPATH || FeatSlot[i] == FEATDRUIDWILDSHAPE || FeatSlot[i] == FEATDESTINY || FeatSlot[i] == FEATLEGENDARY)
					OldColor = SetTextColor(hdc, RGB(230, 230, 30));
				if (FeatSlot[i] == FEATHALFELFBONUS)
					OldColor = SetTextColor(hdc, RGB(255, 0, 155));
				if (FeatSlot[i] == FEATDEITY || FeatSlot[i] == FEATWARLOCKPACT)
					OldColor = SetTextColor(hdc, RGB(100, 255, 0));
				if (FeatSlot[i] == FEATCHARACTER)
				{
					Graphic = UIManager->GetGraphicData("FeatTextFeat1", MAINWINDOW);
					X = static_cast<int>((Graphic->BaseLocationX + 100.0*i / DEFAULTWIDTH)*ScreenSize.cx);
					Y = static_cast<int>(FrameBottom - 35);
					OutputString = "Feat";
					TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
				}
				if (FeatSlot[i] == FEATHUMANBONUS)
				{
					Graphic = UIManager->GetGraphicData("FeatTextHuman", MAINWINDOW);
					X = static_cast<int>((Graphic->BaseLocationX + 100.0*i / DEFAULTWIDTH)*ScreenSize.cx);
					Y = static_cast<int>(FrameBottom - 35);
					OutputString = "Human";
					TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
					Graphic = UIManager->GetGraphicData("FeatTextBonusFeat", MAINWINDOW);
					X = static_cast<int>(X - 15); // CDE: Keep second word aligned below
					Y = static_cast<int>(FrameBottom - 20);
					OutputString = "Bonus Feat";
					TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
				}
				if (FeatSlot[i] == FEATFIGHTERBONUS || FeatSlot[i] == FEATWIZARDBONUS || FeatSlot[i] == FEATARTIFICERBONUS || FeatSlot[i] == FEATROGUEBONUS || FeatSlot[i] == FEATMONKBONUS ||
					FeatSlot[i] == FEATDEITY || FeatSlot[i] == FEATFAVOREDSOULBONUS)
				{
					Graphic = UIManager->GetGraphicData("FeatTextClass", MAINWINDOW);
					X = static_cast<int>((Graphic->BaseLocationX + 100.0*i / DEFAULTWIDTH)*ScreenSize.cx);
					Y = static_cast<int>(FrameBottom - 35);
					OutputString = "Class";
					TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
					Graphic = UIManager->GetGraphicData("FeatTextFeat2", MAINWINDOW);
					X = static_cast<int>(X + 4); // CDE: Keep second word aligned below
					Y = static_cast<int>(FrameBottom - 20);
					OutputString = "Feat";
					TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
				}
				if (FeatSlot[i] == FEATRANGERFAVOREDENEMY)
				{
					Graphic = UIManager->GetGraphicData("FeatTextFavored", MAINWINDOW);
					X = static_cast<int>((Graphic->BaseLocationX + 100.0*i / DEFAULTWIDTH)*ScreenSize.cx);
					Y = static_cast<int>(FrameBottom - 35);
					OutputString = "Favored";
					TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
					Graphic = UIManager->GetGraphicData("FeatTextEnemy", MAINWINDOW);
					X = static_cast<int>(X + 5); // CDE: Keep second word aligned below
					Y = static_cast<int>(FrameBottom - 20);
					OutputString = "Enemy";
					TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
				}
				if (FeatSlot[i] == FEATWARLOCKPACT)
				{
					Graphic = UIManager->GetGraphicData("FeatTextWarlockPact", MAINWINDOW);
					X = static_cast<int>((Graphic->BaseLocationX + 100.0*i / DEFAULTWIDTH)*ScreenSize.cx);
					Y = static_cast<int>(FrameBottom - 35);
					OutputString = "Warlock";
					TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
					Graphic = UIManager->GetGraphicData("FeatTextWarlockPact2", MAINWINDOW);
					X = static_cast<int>(X + 15); // CDE: Keep second word aligned below
					Y = static_cast<int>(FrameBottom - 20);
					OutputString = "Pact";
					TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
				}
				if (FeatSlot[i] == FEATMONKPATH)
				{
					Graphic = UIManager->GetGraphicData("FeatTextMonk", MAINWINDOW);
					X = static_cast<int>((Graphic->BaseLocationX + 100.0*i / DEFAULTWIDTH)*ScreenSize.cx);
					Y = static_cast<int>(FrameBottom - 35);
					OutputString = "Monk";
					TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
					Graphic = UIManager->GetGraphicData("FeatTextPath", MAINWINDOW);
					X = static_cast<int>(X + 4); // CDE: Keep second word aligned below
					Y = static_cast<int>(FrameBottom - 20);
					OutputString = "Path";
					TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
				}
				if (FeatSlot[i] == FEATHALFELFBONUS)
				{
					Graphic = UIManager->GetGraphicData("FeatTextHalfElf", MAINWINDOW);
					X = static_cast<int>((Graphic->BaseLocationX + 100.0*i / DEFAULTWIDTH)*ScreenSize.cx);
					Y = static_cast<int>(FrameBottom - 35);
					OutputString = "Half-Elf";
					TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
					Graphic = UIManager->GetGraphicData("FeatTextDilettante", MAINWINDOW);
					X = static_cast<int>(X - 7); // CDE: Keep second word aligned below
					Y = static_cast<int>(FrameBottom - 20);
					OutputString = "Dilettante";
					TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
				}
				if (FeatSlot[i] == FEATDRUIDWILDSHAPE)
				{
					Graphic = UIManager->GetGraphicData("FeatTextDruid", MAINWINDOW);
					X = static_cast<int>((Graphic->BaseLocationX + 100.0*i / DEFAULTWIDTH)*ScreenSize.cx);
					Y = static_cast<int>(FrameBottom - 35);
					OutputString = "Druid";
					TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
					Graphic = UIManager->GetGraphicData("FeatTextWildShape", MAINWINDOW);
					X = static_cast<int>(X - 13); // CDE: Keep second word aligned below
					Y = static_cast<int>(FrameBottom - 20);
					OutputString = "Wild Shape";
					TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
				}
				if (FeatSlot[i] == FEATDESTINY)
				{
					Graphic = UIManager->GetGraphicData("FeatTextEpic", MAINWINDOW);
					X = static_cast<int>((Graphic->BaseLocationX + 100.0*i / DEFAULTWIDTH)*ScreenSize.cx);
					Y = static_cast<int>(FrameBottom - 35);
					OutputString = "Epic";
					TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
					Graphic = UIManager->GetGraphicData("FeatTextDestiny", MAINWINDOW);
					X = static_cast<int>(X - 13); // CDE: Keep second word aligned below
					Y = static_cast<int>(FrameBottom - 20);
					OutputString = "Destiny";
					TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
				}
				if (FeatSlot[i] == FEATLEGENDARY)
					{
						Graphic = UIManager->GetGraphicData("FeatTextLegendary", MAINWINDOW);
						X = static_cast<int>((Graphic->BaseLocationX + 100.0*i / DEFAULTWIDTH)*ScreenSize.cx);
						Y = static_cast<int>(FrameBottom - 35);
						OutputString = "Legendary";
						TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
						Graphic = UIManager->GetGraphicData("FeatTextLegendaryFeat", MAINWINDOW);
						X = static_cast<int>(X + 20);
						Y = static_cast<int>(FrameBottom - 20);
						OutputString = "Feat";
						TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
				}
				SetTextColor(hdc, OldColor);
                }
            break;
            }
        case ADV_SPELLS:
            {
            Character.GetSpellSelectionSlots(CurrentSelectedLevel, SpellLevel, NumSpells);
            CurrentClass = Character.GetClass(CurrentSelectedLevel);
            NumSelected = Character.GetNumSpellsSelected(CurrentSelectedLevel);
			if (CurrentClass == WIZARD || CurrentClass == ARTIFICER)
                {
                OldColor = SetTextColor(hdc, RGB(255,255,255));
				Graphic = UIManager->GetGraphicData("SpellsSelectText", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
                ss.str("");
                ss << "Select " << (NumSpells[0] - NumSelected) << " spells from the list.";
                OutputString = ss.str();
                TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
                SetTextColor(hdc, OldColor);
                for (int i=0; i<4; i++)
                    {
                    if (NumSpells[0] < i+1)
                        break;
					ss.str("");
					ss << "SpellsSelectSlot" << i+1;
					Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
					X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
					Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
					Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
					Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
                    DrawGraphic(hdc, &EmptySpellSlot, X, Y, Width, Height);
                    SpellIndex = Character.GetSpellBySlot(CurrentSelectedLevel, i);
                    if (SpellIndex != -1)
						{
						X = static_cast<int>((Graphic->BaseLocationX+2.0/DEFAULTWIDTH)*ScreenSize.cx);
						Y = static_cast<int>((Graphic->BaseLocationY+2.0/DEFAULTHEIGHT)*ScreenSize.cy);
						Width = static_cast<int>((Graphic->BaseWidth-4.0/DEFAULTWIDTH)*ScreenSize.cx);
						Height = static_cast<int>((Graphic->BaseHeight-4.0/DEFAULTHEIGHT)*ScreenSize.cy);
                        DrawGraphic(hdc, &SpellIcon[Data.GetSpellIconIndex(SpellIndex)], X, Y, Width, Height);
						}
                    }
                for (int i=4; i<8; i++)
                    {
                    if (NumSpells[0] < i+1)
                        break;
					ss.str("");
					ss << "SpellsSelectSlot" << i+1;
					Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
					X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
					Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
					Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
					Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
                    DrawGraphic(hdc, &EmptySpellSlot, X, Y, Width, Height);
                    SpellIndex = Character.GetSpellBySlot(CurrentSelectedLevel, i);
                    if (SpellIndex != -1)
						{
						X = static_cast<int>((Graphic->BaseLocationX+2.0/DEFAULTWIDTH)*ScreenSize.cx);
						Y = static_cast<int>((Graphic->BaseLocationY+2.0/DEFAULTHEIGHT)*ScreenSize.cy);
						Width = static_cast<int>((Graphic->BaseWidth-4.0/DEFAULTWIDTH)*ScreenSize.cx);
						Height = static_cast<int>((Graphic->BaseHeight-4.0/DEFAULTHEIGHT)*ScreenSize.cy);
                        DrawGraphic(hdc, &SpellIcon[Data.GetSpellIconIndex(SpellIndex)], X, Y, Width, Height);
						}
                    }
                for (int i=8; i<12; i++)
                    {
                    if (NumSpells[0] < i+1)
                        break;
					ss.str("");
					ss << "SpellsSelectSlot" << i+1;
					Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
					X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
					Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
					Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
					Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
                    DrawGraphic(hdc, &EmptySpellSlot, X, Y, Width, Height);
                    SpellIndex = Character.GetSpellBySlot(CurrentSelectedLevel, i);
                    if (SpellIndex != -1)
						{
						X = static_cast<int>((Graphic->BaseLocationX+2.0/DEFAULTWIDTH)*ScreenSize.cx);
						Y = static_cast<int>((Graphic->BaseLocationY+2.0/DEFAULTHEIGHT)*ScreenSize.cy);
						Width = static_cast<int>((Graphic->BaseWidth-4.0/DEFAULTWIDTH)*ScreenSize.cx);
						Height = static_cast<int>((Graphic->BaseHeight-4.0/DEFAULTHEIGHT)*ScreenSize.cy);
                        DrawGraphic(hdc, &SpellIcon[Data.GetSpellIconIndex(SpellIndex)], X, Y, Width, Height);
						}
                    }
                }
            else
                {
                //sorcs, bards, warlock
                OldColor = SetTextColor(hdc, RGB(255,255,255));
				Graphic = UIManager->GetGraphicData("SpellsSelectText", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
                ss.str("");
                ss << "Select " << (NumSpells[0] - NumSelected) << " spells from the list.";
                OutputString = ss.str();
                TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
                for (int i=0; i<3; i++)
                    {
                    if (NumSpells[i] > 0)
                        {
                        ss.str("");
						ss << "SpellsLevelText" << i+1;
						Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
						X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
                        ss.str("");
                        ss << "Level " << SpellLevel[i] << ":";
                        OutputString = ss.str();
                        TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
                        }
                    }
                SetTextColor(hdc, OldColor);
                for (int i=0; i<3; i++)
                    {
                    for (int j=0; j<NumSpells[i]; j++)
                        {
						ss.str("");
						ss << "SpellsSelectSlot" << 4*i+j+1;
						Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
						X = static_cast<int>((Graphic->BaseLocationX+60.0/DEFAULTWIDTH)*ScreenSize.cx);
						Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
						Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
						Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
                        DrawGraphic(hdc, &EmptySpellSlot, X, Y, Width, Height);
                        SpellIndex = Character.GetSpellBySlot(CurrentSelectedLevel, 4*i+j);
                        if (SpellIndex != -1)
							{
							X = static_cast<int>((Graphic->BaseLocationX+62.0/DEFAULTWIDTH)*ScreenSize.cx);
							Y = static_cast<int>((Graphic->BaseLocationY+2.0/DEFAULTHEIGHT)*ScreenSize.cy);
							Width = static_cast<int>((Graphic->BaseWidth-4.0/DEFAULTWIDTH)*ScreenSize.cx);
							Height = static_cast<int>((Graphic->BaseHeight-4.0/DEFAULTHEIGHT)*ScreenSize.cy);
                            DrawGraphic(hdc, &SpellIcon[Data.GetSpellIconIndex(SpellIndex)], X, Y, Width, Height);
							}
                        }
                    }
                }
            break;
            }
        case ADV_TOME:
            {
            OldColor = SetTextColor(hdc, RGB(255,255,255));
			Graphic = UIManager->GetGraphicData("TomeAbilityText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Ability";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("TomeValueText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Value";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("TomeChangeText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Change";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("TomeStrengthText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Strength";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("TomeDexterityText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Dexterity";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("TomeConstitutionText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Constitution";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("TomeIntelligenceText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Intelligence";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("TomeWisdomText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Wisdom";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("TomeCharismaText", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Charisma";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("TomeInstructionText1", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Increase any ability by 1 to 7 total points.";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("TomeInstructionText2", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "Requires tomes. NOTE: A tome added at";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("TomeInstructionText3", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "this level won't affect skills or feat pre-";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("TomeInstructionText4", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
            OutputString = "reqs until NEXT level. Reincarnations or";
            TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("TomeInstructionText5", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			OutputString = "New Tomes can be applied at level 1 and";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
			Graphic = UIManager->GetGraphicData("TomeInstructionText6", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			OutputString = "will apply when the correct level is taken.";
			TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
            PointsSpent = 0;
            for (unsigned int i=0; i<6; i++)
                {
				ss.str("");
				ss << "TomeAbilityLevelText" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
                ss.str("");
                Modifier = Character.GetTomeRaise(static_cast<ABILITIES>(i), CurrentSelectedLevel,true,true);
                Ability = Character.GetAbility(i, CurrentSelectedLevel, true);
                ss << Ability;
                OutputString = ss.str();
                TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
				ss.str("");
				ss << "TomeAbilityModText" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
                ss.str("");
                if (Modifier > 0)
                    ss << "+" << Modifier;
                else
                    ss << Modifier;
                OutputString = ss.str();
                TextOut(hdc, X, Y, OutputString.c_str(), OutputString.size());
                //arrows
				Modifier = Character.GetTomeRaise(static_cast<ABILITIES>(i), CurrentSelectedLevel, true, true) - Character.GetAbilityMod(static_cast<ABILITIES>(i), ABMOD_INHERENT, CurrentSelectedLevel - 1);
				ss.str("");
				ss << "TomeLeftArrow" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>((Graphic->BaseWidth-4.0/DEFAULTWIDTH)*ScreenSize.cx);
				Height = static_cast<int>((Graphic->BaseHeight-4.0/DEFAULTHEIGHT)*ScreenSize.cy);
                if (Modifier == 0)
                    DrawGraphicGreyscale(hdc, &LeftArrow, X, Y, Width, Height);
                else
                    DrawGraphic(hdc, &LeftArrow, X, Y, Width, Height);
				Modifier = Character.GetTomeRaise(static_cast<ABILITIES>(i), CurrentSelectedLevel, true, true);
				ss.str("");
				ss << "TomeRightArrow" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>((Graphic->BaseWidth-4.0/DEFAULTWIDTH)*ScreenSize.cx);
				Height = static_cast<int>((Graphic->BaseHeight-4.0/DEFAULTHEIGHT)*ScreenSize.cy);
                if (Modifier == 4)
                    DrawGraphicGreyscale(hdc, &RightArrow, X, Y, Width, Height);
                else
                    DrawGraphic(hdc, &RightArrow, X, Y, Width, Height);
                }
            SetTextColor(hdc, OldColor);
            break;
            }
        }
    }
//---------------------------------------------------------------------------
void MainScreenClass::DrawSelectFeatControls(InterfaceComponentStruct Component, CHILDWINDOW Window)
	{
	
	}
//---------------------------------------------------------------------------
void MainScreenClass::HandleLeftMouseButtonClick(int x, int y)
    {
    unsigned int OldSelectedLevel;
    string Description;
	UIComponentManager *UIManager;
    InterfaceGraphicStruct *Graphic;
	int X, Y;
	int Width, Height;
	RECT ScreenRect;
	SIZE ScreenSize;
	ostringstream ss;
	ADVANCEMENTTYPE AdvancementType;
	RACE CurrentRace;
	CLASS CurrentClass;
	int Value;

	GetClientRect(ParentWindow, &ScreenRect);
	ScreenSize.cx = ScreenRect.right - ScreenRect.left;
	ScreenSize.cy = ScreenRect.bottom - ScreenRect.top;

	POINT pt;
	pt.x = x;
	pt.y = y;
	RECT rc;
	GetClientRect(AdvancementWindowFrame, &rc);
	MapWindowPoints(AdvancementWindowFrame, ParentWindow, (LPPOINT) &rc, 2);
	if (PtInRect(&rc,pt))
	{
        //we're in the advancement box, this will be complex, so use a different routine for this
		Character.EnableValidations(false);
        HandleLeftMouseButtonClickAdvancementBox(x, y);
		Character.EnableValidations(true);
        return;
        }

    //check the level bars
	UIManager = InterfaceManager.GetUIComponents();
    OldSelectedLevel = CurrentSelectedLevel;
    for (unsigned int i=0; i<MAXLEVEL; i++)
        {
		ss.str("");
		ss << "LevelBar" << i+1;
		Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
        if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
            {
            if (i+1 == (int)CurrentSelectedLevel)
				return;
            CurrentSelectedLevel = i+1;
            }
		}

    if (CurrentSelectedLevel != OldSelectedLevel)
        {
		Character.EnableValidations(false);
        RedrawWindow(ParentWindow, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
        CurrentInstructionSelection = 0;
        ShowWindow(AdvWinBonusAbilityPointsCheckBox, false);
        ShowWindow(AdvWinFeatList, false);
        ShowWindow(AdvWinFirstNameInput, false);
        ShowWindow(AdvWinSurnameInput, false);
        ShowWindow(AdvSkillPointSpendBox, false);
        ShowWindow(AdvWinSpellList, false);
        ShowWindow(AdvWinSpellClearButton, false);
		ShowWindow(HeroicClassRadioButton, false);
		ShowWindow(IconicClassRadioButton, false);
	    CurrentRace = Character.GetRace();
		CurrentClass = Character.GetClass(CurrentSelectedLevel);
		AdvancementType = Data.GetAdvancementType(CurrentSelectedLevel, CurrentRace, CurrentClass, CurrentInstructionSelection, &Value);
	    if (AdvancementType == ADV_FEATS)
		    {
	        FillFeatSelectBox();
		    ShowWindow(AdvWinFeatList, true);
	        }
        FillInstructionBox();
        FillAbilityBox();
        FillAbilityStatBox();
        FillSpellBox();
        FillSkillBox();
        FillSkillSpendBox();
        FillFeatBox();
		UpdateSelectedEnhancements();
		FillEnhancementBox();
//		if (CurrentSelectedLevel > 19)
//			EnableWindow(DestinyButton, true);
//		else
//			EnableWindow(DestinyButton, false);
        UpdateMetaWindows();
		Character.EnableValidations(true);
        }
    }

//---------------------------------------------------------------------------
void MainScreenClass::HandleLeftMouseButtonClickAdvancementBox(int x, int y)
    {
    RACE CurrentRace;
    unsigned int CurrentClass;
    int Value;
    ADVANCEMENTTYPE AdvancementType;
    int Index;
    string Description;
    int Position;
    FeatDataClass *Feat;
	int X, Y;
	int Width, Height;
	RECT ScreenRect;
	SIZE ScreenSize;
	UIComponentManager *UIManager;
    InterfaceGraphicStruct *Graphic;
	ostringstream ss;

    if (InterfaceManager.ChildWindowVisible() == true)
        return;

	GetClientRect(ParentWindow, &ScreenRect);
	ScreenSize.cx = ScreenRect.right - ScreenRect.left;
	ScreenSize.cy = ScreenRect.bottom - ScreenRect.top;
	UIManager = InterfaceManager.GetUIComponents();

    CurrentRace = Character.GetRace();
    CurrentClass = Character.GetClass(CurrentSelectedLevel);
    AdvancementType = Data.GetAdvancementType(CurrentSelectedLevel, CurrentRace, CurrentClass, CurrentInstructionSelection, &Value);
	if (EquipmentScreenShown == true)
        {
        EquipmentScreenCurrentSelectedSlot = NOSLOT;
		Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot1", MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
            EquipmentScreenCurrentSelectedSlot = RIGHTHANDSLOT;
		Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot2", MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
            EquipmentScreenCurrentSelectedSlot = LEFTHANDSLOT;
		Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot3", MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
            EquipmentScreenCurrentSelectedSlot = AMMOSLOT;
		Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot4", MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
			EquipmentScreenCurrentSelectedSlot = QUIVERSLOT;
		Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot5", MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
            EquipmentScreenCurrentSelectedSlot = FACESLOT;
		Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot6", MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
            EquipmentScreenCurrentSelectedSlot = ARMORSLOT;
		Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot7", MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
            EquipmentScreenCurrentSelectedSlot = BRACERSLOT;
		Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot8", MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
            EquipmentScreenCurrentSelectedSlot = LEFTRINGSLOT;
		Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot9", MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
            EquipmentScreenCurrentSelectedSlot = HEADSLOT;
		Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot10", MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
            EquipmentScreenCurrentSelectedSlot = FEETSLOT;
		Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot11", MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
            EquipmentScreenCurrentSelectedSlot = NECKSLOT;
		Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot12", MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
            EquipmentScreenCurrentSelectedSlot = GLOVESSLOT;
		Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot13", MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
            EquipmentScreenCurrentSelectedSlot = TRINKETSLOT;
		Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot14", MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
            EquipmentScreenCurrentSelectedSlot = BACKSLOT;
		Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot15", MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
            EquipmentScreenCurrentSelectedSlot = WAISTSLOT;
		Graphic = UIManager->GetGraphicData("EquipmentHighlightSlot16", MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
            EquipmentScreenCurrentSelectedSlot = RIGHTRINGSLOT;
        //DrawAdvancementBoxGraphics();
        ChangeEquipmentSelectType();
        return;
		}
    switch (AdvancementType)
        {
        case ADV_RACEANDSEX:
            {
			//sex
			Graphic = UIManager->GetGraphicData("MaleOff", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
			Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
			if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
	            Character.SetSex(MALE);
			Graphic = UIManager->GetGraphicData("FemaleOff", MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
			Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
			Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
			if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
	            Character.SetSex(FEMALE);

			//race
			LRESULT IsHeroicClassChecked = SendMessage(HeroicClassRadioButton, BM_GETCHECK, 0, 0);
			if (IsHeroicClassChecked == 1)
			{
				Graphic = UIManager->GetGraphicData("MaleHumanOff", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
				if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
					Character.SetRace(HUMAN);
				Graphic = UIManager->GetGraphicData("MaleElfOff", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
				if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
					Character.SetRace(ELF);
				Graphic = UIManager->GetGraphicData("MaleHalflingOff", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
				if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
					Character.SetRace(HALFLING);
				Graphic = UIManager->GetGraphicData("MaleDwarfOff", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
				if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
					Character.SetRace(DWARF);
				Graphic = UIManager->GetGraphicData("MaleWarforgedOff", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
				if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
					Character.SetRace(WARFORGED);
				Graphic = UIManager->GetGraphicData("MaleHalfelfOff", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
				if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
					Character.SetRace(HALFELF);
				Graphic = UIManager->GetGraphicData("MaleGnomeOff", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
				if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
					Character.SetRace(GNOME);
				Graphic = UIManager->GetGraphicData("MaleDrowOff", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
				if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
				{
					Character.SetRace(DROW);
					Character.SetAbilityFavorBonus(false);
					SendMessage(AdvWinBonusAbilityPointsCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);
				}
				Graphic = UIManager->GetGraphicData("MaleHalforcOff", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
				if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
					Character.SetRace(HALFORC);
			}
			else
			{
				Graphic = UIManager->GetGraphicData("MaleBladeforgedOff", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
				if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
				{
					Character.SetRace(BLADEFORGED);
					Character.SetClass(PALADIN, 1);
					Character.SetAbilityFavorBonus(true);
					SendMessage(AdvWinBonusAbilityPointsCheckBox, BM_SETCHECK, BST_CHECKED, 0);
				}
				Graphic = UIManager->GetGraphicData("MaleMorninglordOff", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
				if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
				{
					Character.SetRace(MORNINGLORD);
					Character.SetClass(CLERIC, 1);
					Character.SetAbilityFavorBonus(true);
					SendMessage(AdvWinBonusAbilityPointsCheckBox, BM_SETCHECK, BST_CHECKED, 0);
				}
				Graphic = UIManager->GetGraphicData("MalePurpleDragonKnightOff", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
				if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
				{
					Character.SetRace(PURPLEDRAGONKNIGHT);
					Character.SetClass(FIGHTER, 1);
					Character.SetAbilityFavorBonus(true);
					SendMessage(AdvWinBonusAbilityPointsCheckBox, BM_SETCHECK, BST_CHECKED, 0);
				}
				Graphic = UIManager->GetGraphicData("MaleShadarKaiOff", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
				if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
				{
					Character.SetRace(SHADARKAI);
					Character.SetClass(ROGUE, 1);
					Character.SetAbilityFavorBonus(true);
					SendMessage(AdvWinBonusAbilityPointsCheckBox, BM_SETCHECK, BST_CHECKED, 0);
				}
				Graphic = UIManager->GetGraphicData("MaleDeepGnomeOff", MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
				if (x >= X && x <= X + Width && y >= Y && y <= Y + Height)
				{
					Character.SetRace(DEEPGNOME);
					Character.SetClass(WIZARD, 1);
					Character.SetAbilityFavorBonus(true);
					SendMessage(AdvWinBonusAbilityPointsCheckBox, BM_SETCHECK, BST_CHECKED, 0);
				}
			}
			ClearAdvancementBox();
            //DrawAdvancementBoxGraphics();
            FillAbilityBox();
            FillAbilityStatBox();
			FillSkillBox();
			FillSkillSpendBox();
            FillSpellBox();
			FillSpellSelectBox();
            FillFeatBox();
            FillInstructionBox();
            FillDescriptionBox(Data.GetRaceDescription(Character.GetRace()));
			UpdateSelectedEnhancements();
			FillEnhancementBox();
            UpdateMetaWindows();
            break;
            }
        case ADV_CLASS:
            {
			for (unsigned int i=0; i<NUMCLASSES; i++)
				{
				ss.str("");
				ss << "ClassSlot" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
				if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
					{
		            Character.SetClass(ClassSlot[i], CurrentSelectedLevel);
					break;
					}
				}
			if (CurrentSelectedLevel == 1)
				{
                //if we are at level 1, set to the first compatable alignment, if not already
                if (Data.IsAlignmentCompatable (Character.GetClass(1), Character.GetAlignment()) == false)
                    {
                    for (unsigned int i=0; i<6; i++)
                        {
                        if (Data.IsAlignmentCompatable(Character.GetClass(1), (ALIGNMENT)i) == true)
                            {
                            Character.SetAlignment((ALIGNMENT)i);
                            break;
                            }
                        }
                    }
                }
			ClearAdvancementBox();
            FillInstructionBox();
            FillAbilityStatBox();
            FillSpellBox();
            FillSkillBox();
            FillSkillSpendBox();
            FillFeatBox();
            FillDescriptionBox(Data.GetClassDescription(Character.GetClass(CurrentSelectedLevel)));
			UpdateSelectedEnhancements();
			FillEnhancementBox();
            UpdateMetaWindows();
            break;
            }
        case ADV_NAMEANDALIGNMENT:
            {
            for (int i=0; i<6; i++)
                {
				ss.str("");
				ss << "AlignmentText" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
                if (x >= X && x<= X+Width && y >= Y && y <= Y+Height)
                    {
                    if (AlignmentSlot[i] != NOALIGNMENT)
                        {
                        Character.SetAlignment(AlignmentSlot[i]);
                        UpdateMetaWindows();
						ClearAdvancementBox();
                        //DrawAdvancementBoxGraphics();
                        }
                    break;
                    }
                }
            break;
            }
        case ADV_REINCARNATE:
            {
			HandleLeftMouseButtonClickAdvancementBoxTrueReincarnation(x, y);
            break;
            }
        case ADV_ABILITYPOINT:
            {
            for (int i=0; i<6; i++)
                {
				ss.str("");
				ss << "AbilityPointLA" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
                if (x >= X && x<= X+Width && y >= Y && y <= Y+Height)
                    {
                    Character.AdjustAbilityRaise(i, -1);
					ClearAdvancementBox();
                    //DrawAdvancementBoxGraphics();
                    FillAbilityBox();
                    FillAbilityStatBox();
                    FillSkillBox();
                    FillInstructionBox();
                    return;
                    }
				ss.str("");
				ss << "AbilityPointRA" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
                if (x >= X && x<= X+Width && y >= Y && y <= Y+Height)
                    {
                    Character.AdjustAbilityRaise(i, 1);
					ClearAdvancementBox();
                    //DrawAdvancementBoxGraphics();
                    FillAbilityBox();
                    FillAbilityStatBox();
                    FillSkillBox();
                    FillInstructionBox();
                    break;
                    }
                }
            break;
            }
        case ADV_ABILITYINCREASE:
            {
            for (int i=0; i<6; i++)
                {
				ss.str("");
				ss << "AbilityPointLA" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
                if (x >= X && x<= X+Width && y >= Y && y <= Y+Height)
                    {
                    if ((int)Character.GetAbilityIncrease(CurrentSelectedLevel) != i)
                        return;
                    Character.SetAbilityIncrease(CurrentSelectedLevel, ABILITYNONE);
					ClearAdvancementBox();
                    //DrawAdvancementBoxGraphics();
                    FillAbilityBox();
                    FillAbilityStatBox();
                    FillSkillBox();
                    FillInstructionBox();
                    return;
                    }
				ss.str("");
				ss << "AbilityPointRA" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
                if (x >= X && x<= X+Width && y >= Y && y <= Y+Height)
                    {
                    if (Character.GetAbilityIncrease(CurrentSelectedLevel) != ABILITYNONE)
                        return;
                    Character.SetAbilityIncrease(CurrentSelectedLevel, (ABILITIES)i);
					ClearAdvancementBox();
                    //DrawAdvancementBoxGraphics();
                    FillAbilityBox();
                    FillAbilityStatBox();
                    FillSkillBox();
                    FillInstructionBox();
                    return;
                    }
                }
            break;
            }
        case ADV_FEATS:
            {
			InterfaceComponentStruct *Component = UIManager->GetComponentData("AdvancementWindowFrame", MAINWINDOW);
			int FrameBottom = static_cast<int>((Component->BaseLocationY+Component->BaseHeight)*ScreenSize.cy);
            Index = -1;
			for (unsigned int i=0; i<3; i++)
				{
				ss.str("");
				ss << "FeatSlot" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = FrameBottom-80;
				Width = 45;
				Height = 45;
			    if (x >= X && x<= X+Width && y >= Y && y <= Y+Height)
				    Index = i;
				}
            if (Index != -1)
                {
                IconDrag = Character.GetFeat(CurrentSelectedLevel, FeatSlot[Index], 0);
                if (IconDrag == -1)
                    break;
                Feat = Data.GetFeatPointer(IconDrag);
                Character.RemoveFeat(CurrentSelectedLevel, FeatSlot[Index]);
                Character.ReAddRemovedAutoFeat(IconDrag);
                Position = SendMessage(FeatList, LB_GETTOPINDEX, 0, 0);
                FillFeatBox();
                SendMessage(FeatList, LB_SETTOPINDEX, (WPARAM)Position, 0);
                Position = SendMessage(AdvWinFeatList, LB_GETTOPINDEX, 0, 0);
                FillFeatSelectBox();
                SendMessage(AdvWinFeatList, LB_SETTOPINDEX, (WPARAM)Position, 0);
                Position = SendMessage(SkillsList, LB_GETTOPINDEX, 0, 0);
                FillSkillBox();
                SendMessage(SkillsList, LB_SETTOPINDEX, (WPARAM)Position, 0);
                FillAbilityStatBox();
				ClearAdvancementBox();
                Description = "{\\b ";
                Description += Feat->GetFeatName(true);
                Description += "} \\par\\par ";
				Description += Feat->GetFeatDescription();
				//replace any string placeholders with their appropriate descriptions
				while (Description.find("$RACE") != std::string::npos)
					Description.replace(Description.find("$RACE"), 5, Character.GetRaceString(true));
                FillDescriptionBox(Description);
                Dragging = true;
                Cursor = CreateCursorFromBitmap(ParentWindow, Palette, &FeatIcon[Feat->GetFeatIconIndex()], RGB(0,0,0), 16, 16);
                SetCursor(Cursor);
                }
            break;
            }
        case ADV_SPELLS:
            {
            Index = -1;
			if (Character.GetClass(CurrentSelectedLevel) == WIZARD || Character.GetClass(CurrentSelectedLevel) == ARTIFICER)
                {
				for (unsigned int i=0; i<12; i++)
					{
					ss.str("");
					ss << "SpellsSelectSlot" << i+1;
					Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
					X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
					Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
					Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
					Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
					if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
						Index = i;
					}
                }
            else
                {
				for (unsigned int i=0; i<12; i++)
					{
					ss.str("");
					ss << "SpellsSelectSlot" << i+1;
					Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
					X = static_cast<int>((Graphic->BaseLocationX+62.0/DEFAULTWIDTH)*ScreenSize.cx);
					Y = static_cast<int>((Graphic->BaseLocationY+2.0/DEFAULTHEIGHT)*ScreenSize.cy);
					Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
					Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
					if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
						Index = i;
					}
                }
            if (Index != -1)
                {
                IconDrag = Character.GetSpellBySlot(CurrentSelectedLevel, Index);
                if (IconDrag == -1)
                    break;
                Description = CreateSpellDescription(IconDrag);
                FillDescriptionBox(Description);
                Dragging = true;
                Cursor = CreateCursorFromBitmap(ParentWindow, Palette, &SpellIcon[Data.GetSpellIconIndex(IconDrag)], RGB(0,0,0), 16, 16);
                SetCursor(Cursor);
                }
            break;
            }
        case ADV_TOME:
            {
            for (int i=0; i<6; i++)
                {
				ss.str("");
				ss << "TomeRightArrow" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
                if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
                    {
                    Character.ChangeTomeRaise((ABILITIES)i, CurrentSelectedLevel, 1);
					ClearAdvancementBox();
                    //DrawAdvancementBoxGraphics();
                    FillAbilityBox();
                    FillAbilityStatBox();
                    FillSkillBox();
                    return;
                    }
				ss.str("");
				ss << "TomeLeftArrow" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
                if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
                    {
                    Character.ChangeTomeRaise((ABILITIES)i, CurrentSelectedLevel, -1);
					ClearAdvancementBox();
                    //DrawAdvancementBoxGraphics();
                    FillAbilityBox();
                    FillAbilityStatBox();
                    FillSkillBox();
                    return;
                    }
                }
            break;
            }
        }
		HDC hdc;
		hdc = GetDC(ParentWindow);
		DrawAdvancementBoxGraphics(hdc);
		ReleaseDC(ParentWindow, hdc);
    }
    
//---------------------------------------------------------------------------
void MainScreenClass::HandleLeftMouseButtonClickAdvancementBoxTrueReincarnation(int x, int y)
	{
	string FeatName[NUMCLASSES];
    FeatDataClass *Feat;
	string Description;
	ostringstream ss;
	int X, Y;
	int Width, Height;
	RECT ScreenRect;
	SIZE ScreenSize;
	UIComponentManager *UIManager;
    InterfaceGraphicStruct *Graphic;
	int FeatIndex = -1;

	//FeatName[0] = "Past Life: Fighter";
	//FeatName[1] = "Past Life: Paladin";
	//FeatName[2] = "Past Life: Barbarian";
	//FeatName[3] = "Past Life: Monk";
	//FeatName[4] = "Past Life: Rogue";
	//FeatName[5] = "Past Life: Ranger";
	//FeatName[6] = "Past Life: Cleric";
	//FeatName[7] = "Past Life: Wizard";
	//FeatName[8] = "Past Life: Sorcerer";
	//FeatName[9] = "Past Life: Bard";
	//FeatName[10] = "Past Life: Favored Soul";
	//FeatName[11] = "Past Life: Artificer";
	//FeatName[12] = "Past Life: Druid";
	//FeatName[13] = "Past Life: Warlock";
	
    if (InterfaceManager.ChildWindowVisible() == true)
        return;
	Character.EnableValidations(false);
	GetClientRect(ParentWindow, &ScreenRect);
	ScreenSize.cx = ScreenRect.right - ScreenRect.left;
	ScreenSize.cy = ScreenRect.bottom - ScreenRect.top;
	UIManager = InterfaceManager.GetUIComponents();
	//HDC hdc;
	//hdc = GetDC(ParentWindow);
	int ClickedIcon = -1;
	bool ClickedRightArrow = false;
	bool ClickedLeftArrow = false;


	for (unsigned int i=0; i<16; i++)
		{
			
	    //first check the icons. All we need to do here is pull up the descriptions
		ss.str("");
		ss << "ReincarnateIcon" << i+1;
		Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
			{
				ClickedIcon = i;
				break;
			}
		//now check the arrows
		ss.str("");
		ss << "ReincarnateLA" << i+1;
		Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
			{
			ClickedIcon = i;
			ClickedLeftArrow = true;
			break;
			}
		ss.str("");
		ss << "ReincarnateRA" << i+1;
		Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
		Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
		Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
		Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
		if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
			{

			ClickedIcon = i;
			ClickedRightArrow = true;
			break;
			}
		}
	if (ClickedIcon >= 0)
	{
		switch (PastLifeRadioState)
		{
		case 0:
			//Herioc Radio Button
		{
			FeatIndex = Character.GetReincarnateFeatIndex(static_cast<CLASS>(ClickedIcon));
			if (FeatIndex != -1)
			{
				if (ClickedLeftArrow)
					Character.DecreasePastLife(static_cast<CLASS>(ClickedIcon));
				if (ClickedRightArrow)
					Character.IncreasePastLife(static_cast<CLASS>(ClickedIcon));
			}

			break;
		}
		case 1:
			//Iconic Radio Button
		{
			FeatIndex = Character.GetIconicFeatIndex(static_cast<ICONICRACES>(ClickedIcon));
			if (FeatIndex != -1)
			{
				if (ClickedLeftArrow)
					Character.DecreaseIconicPastLife(static_cast<ICONICRACES>(ClickedIcon));
				if (ClickedRightArrow)
					Character.IncreaseIconicPastLife(static_cast<ICONICRACES>(ClickedIcon));
			}

			break;
		}
		case 2:
			//Epic Radio Button
		{
			int Sphere;
			int FeatPos;

			FeatPos = ClickedIcon % 4;
			Sphere = (ClickedIcon - FeatPos) / 4;
			FeatIndex = Character.GetEpicFeatIndex(static_cast<DESTINY_SPHERE>(Sphere), FeatPos);
			if (FeatIndex != -1)
			{	
			if (ClickedLeftArrow)
				Character.DecreaseEpicFeat(static_cast<DESTINY_SPHERE>(Sphere), FeatPos);
			if (ClickedRightArrow)
				Character.IncreaseEpicFeat(static_cast<DESTINY_SPHERE>(Sphere), FeatPos);
			}

			break;
		}
			
		default:
			break;
		}

		if (FeatIndex != -1)
		{
			Feat = Data.GetFeatPointer(FeatIndex);
			Description = "{\\b ";
			Description += Feat->GetFeatName(true);
			Description += "} \\par\\par ";
			Description += Feat->GetFeatDescription();
			if (ClickedLeftArrow || ClickedRightArrow)
			{
				ClearAdvancementBox();
				FillFeatBox();
				FillAbilityStatBox();
				FillSkillBox();
				FillInstructionBox();
			}
			FillDescriptionBox(Description, FeatIcon[Feat->GetFeatIconIndex()].Graphic);
		}


	}
	Character.EnableValidations(true);
	//ReleaseDC(ParentWindow, hdc);
	}

//---------------------------------------------------------------------------
void MainScreenClass::EndDragAndDropOperation(int x, int y)
    {
    RACE CurrentRace;
    CLASS CurrentClass;
    int Value;
    ADVANCEMENTTYPE AdvancementType;
    int Index;
    int Position;
    int SpellLevel[3];
    int NumSpells[3];
    int Row;
    int Column;
    ICONINFO IconInfo;
    FeatDataClass *Feat;
	ostringstream ss;
	int X, Y;
	int Width, Height;
	UIComponentManager *UIManager;
    InterfaceGraphicStruct *Graphic;
	RECT ScreenRect;
	SIZE ScreenSize;

	GetClientRect(ParentWindow, &ScreenRect);
	ScreenSize.cx = ScreenRect.right - ScreenRect.left;
	ScreenSize.cy = ScreenRect.bottom - ScreenRect.top;
	UIManager = InterfaceManager.GetUIComponents();

    //figure out what we are dragging
    CurrentRace = Character.GetRace();
    CurrentClass = Character.GetClass(CurrentSelectedLevel);
    AdvancementType = Data.GetAdvancementType(CurrentSelectedLevel, CurrentRace, CurrentClass, CurrentInstructionSelection, &Value);
    
    if (AdvancementType == ADV_FEATS)
        {
		InterfaceComponentStruct *Component = UIManager->GetComponentData("AdvancementWindowFrame", MAINWINDOW);
		int FrameBottom = static_cast<int>((Component->BaseLocationY+Component->BaseHeight)*ScreenSize.cy);
        Index = -1;
		for (unsigned int i=0; i<3; i++)
			{
			ss.str("");
			ss << "FeatSlot" << i+1;
			Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
			X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
			Y = FrameBottom-80;
			Width = 45;
			Height = 45;
			if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
	            Index = i;
			}
        if (Index != -1)
            {
			//grab a pointer to the feat being dropped
		    Feat = Data.GetFeatPointer(IconDrag);
		    boolean valid = false;
			//note that favored enemy, deity, favored soul bonus, rogue bonus, half-elf dilettante, and druid wild shape feats are exclusive to their particular slots
			//do not allow them to be placed in other slot types
            if (FeatSlot[Index] == FEATCHARACTER || FeatSlot[Index] == FEATHUMANBONUS)
                {
				valid = Feat->GetFeatTag(FEATTAGFAVOREDENEMY) == false && Feat->GetFeatTag(FEATTAGMONKPATH) == false && Feat->GetFeatTag(FEATTAGDEITY) == false && Feat->GetFeatTag(FEATTAGFAVOREDSOULBONUS) == false && Feat->GetFeatTag(FEATTAGROGUEBONUS) == false && Feat->GetFeatTag(FEATTAGHALFELFBONUS) == false && Feat->GetFeatTag(FEATTAGMONKEXCLUSIVE) == false && Feat->GetFeatTag(FEATTAGDRUIDWILDSHAPE) == false && Feat->GetFeatTag(FEATTAGLEGENDARY) == false;
                }
            else switch (FeatSlot[Index])
				{
				case FEATHALFELFBONUS:
			        {
				    valid = Feat->GetFeatTag(FEATTAGHALFELFBONUS) == true;
					break;
			        }
				case FEATFIGHTERBONUS:
	                {
			        valid = Feat->GetFeatTag(FEATTAGFIGHTERBONUS) == true;
					break;
					}
				case FEATWIZARDBONUS:
			            {
				    valid = Feat->GetFeatTag(FEATTAGMETAMAGIC) == true;
					break;
	                }
				case FEATARTIFICERBONUS:
	                {
			        valid = Feat->GetFeatTag(FEATTAGMETAMAGIC) == true || Feat->GetFeatTag(FEATTAGARTIFICERBONUS) == true;
					break;
					}
				case FEATRANGERFAVOREDENEMY:
		            {
				    valid = Feat->GetFeatTag(FEATTAGFAVOREDENEMY) == true;
					break;
	                }
				case FEATROGUEBONUS:
					{
					valid = Feat->GetFeatTag(FEATTAGROGUEBONUS) == true;
					break;
					}
				case FEATMONKBONUS:
					{
					valid = Feat->GetFeatTag(FEATTAGMONKBONUS) == true || Feat->GetFeatTag(FEATTAGMONKEXCLUSIVE) == true;
					break;
					}
				case FEATMONKPATH:
					{
					valid = Feat->GetFeatTag(FEATTAGMONKPATH) == true;
					break;
					}
				case FEATDEITY:
					{
					valid = Feat->GetFeatTag(FEATTAGDEITY) == true;
					break;
					}
				case FEATFAVOREDSOULBONUS:
					{
					valid = Feat->GetFeatTag(FEATTAGFAVOREDSOULBONUS) == true;
					break;
					}
				case FEATDRUIDWILDSHAPE:
				    {
	                valid = Feat->GetFeatTag(FEATTAGDRUIDWILDSHAPE) == true;
					break;
			        }
				case FEATWARLOCKPACT:
					{
					valid = Feat->GetFeatTag(FEATTAGWARLOCKPACT) == true;
					break;
					}
				case FEATDESTINY:
				    {
	                valid = Feat->GetFeatTag(FEATTAGDESTINY) == true || Feat->GetFeatTag(FEATTAGDESTINYNOTEXCLUSIVE) == true;
					break;
			        }
				case FEATLEGENDARY:
					{
					valid = Feat->GetFeatTag(FEATTAGLEGENDARY) == true;
					break;
					}
				default:
					// Not valid
					break;
				}
			if (valid)
				{
				Character.AddFeat(CurrentSelectedLevel, IconDrag, FeatSlot[Index]);
				//because some automatic feats are now prereqs for other feats, do an auto feat reset
				Character.ResetAutoFeats(CurrentSelectedLevel);
				Position = SendMessage(FeatList, LB_GETTOPINDEX, 0, 0);
				FillFeatBox();
				SendMessage(FeatList, LB_SETTOPINDEX, (WPARAM)Position, 0);
				Position = SendMessage(AdvWinFeatList, LB_GETTOPINDEX, 0, 0);
				FillFeatSelectBox();
				SendMessage(AdvWinFeatList, LB_SETTOPINDEX, (WPARAM)Position, 0);
				Position = SendMessage(SkillsList, LB_GETTOPINDEX, 0, 0);
				FillSkillBox();
				SendMessage(SkillsList, LB_SETTOPINDEX, (WPARAM)Position, 0);
				FillAbilityBox();
				FillAbilityStatBox();
				ClearAdvancementBox();
				}
            }
        }

    if (AdvancementType == ADV_SPELLS)
        {
        Index = -1;
        CurrentClass = Character.GetClass(CurrentSelectedLevel);
		if (CurrentClass == WIZARD || CurrentClass == ARTIFICER)
            {
			for (unsigned int i=0; i<12; i++)
				{
				ss.str("");
				ss << "SpellsSelectSlot" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>(Graphic->BaseLocationX*ScreenSize.cx);
				Y = static_cast<int>(Graphic->BaseLocationY*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
				if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
					Index = i;
				}
            }
        else
            {
			for (unsigned int i=0; i<12; i++)
				{
				ss.str("");
				ss << "SpellsSelectSlot" << i+1;
				Graphic = UIManager->GetGraphicData(ss.str(), MAINWINDOW);
				X = static_cast<int>((Graphic->BaseLocationX+62.0/DEFAULTWIDTH)*ScreenSize.cx);
				Y = static_cast<int>((Graphic->BaseLocationY+2.0/DEFAULTHEIGHT)*ScreenSize.cy);
				Width = static_cast<int>(Graphic->BaseWidth*ScreenSize.cx);
				Height = static_cast<int>(Graphic->BaseHeight*ScreenSize.cy);
				if (x >= X && x <= X+Width && y >= Y && y <= Y+Height)
					Index = i;
				}
            }
        if (Index == -1)
            {
            //we've drug spell, but not put it into a slot, remove it from the known spell list
            Character.RemoveSelectedSpell(IconDrag);
            Position = SendMessage(SpellList, LB_GETTOPINDEX, 0, 0);
            FillSpellBox();
            SendMessage(SpellList, LB_SETTOPINDEX, (WPARAM)Position, 0);
            Position = SendMessage(AdvWinSpellList, LB_GETTOPINDEX, 0, 0);
            FillSpellSelectBox();
            SendMessage(AdvWinSpellList, LB_SETTOPINDEX, (WPARAM)Position, 0);
			ClearAdvancementBox();
            //DrawAdvancementBoxGraphics();
            //reset
            SetCursor(LoadCursor(NULL, IDC_ARROW));
            Dragging = false;
            IconDrag = -1;
            return;
            }

        //we've dropped into a spell slot
        Character.GetSpellSelectionSlots(CurrentSelectedLevel, SpellLevel, NumSpells);
		if (CurrentClass == WIZARD || CurrentClass == ARTIFICER)
            {
            if (NumSpells[0] > 4)
                {
                if (NumSpells[0] > 8)
                    {
                    SpellLevel[2] = SpellLevel[0];
                    NumSpells[2] = NumSpells[0]-8;
                    }
                SpellLevel[1] = SpellLevel[0];
                NumSpells[1] = NumSpells[0] - 4;
                NumSpells[0] = 4;
                }
            Row = Index/4;
            Column = Index%4;
            if (SpellLevel[Row] == 0)
                Index = -1;
            if (NumSpells[Row] < Column+1)
                Index = -1;
            if (Index != -1)
                {
                Character.AddSelectedSpell(CurrentSelectedLevel, IconDrag, Index);
                Position = SendMessage(SpellList, LB_GETTOPINDEX, 0, 0);
                FillSpellBox();
                SendMessage(SpellList, LB_SETTOPINDEX, (WPARAM)Position, 0);
                Position = SendMessage(AdvWinSpellList, LB_GETTOPINDEX, 0, 0);
                FillSpellSelectBox();
                SendMessage(AdvWinSpellList, LB_SETTOPINDEX, (WPARAM)Position, 0);
				ClearAdvancementBox();
                //DrawAdvancementBoxGraphics();
                }
            }
        else
            {
            //sorcs and bards and warlocks
            Row = Index/4;
            Column = Index%4;
            if (SpellLevel[Row] != Data.GetSpellLevel(CurrentClass, IconDrag))
                Index = -1;
            if (NumSpells[Row] < Column+1)
                Index = -1;
            if (Index != -1)
                {
                Character.AddSelectedSpell(CurrentSelectedLevel, IconDrag, Index);
                Position = SendMessage(SpellList, LB_GETTOPINDEX, 0, 0);
                FillSpellBox();
                SendMessage(SpellList, LB_SETTOPINDEX, (WPARAM)Position, 0);
                Position = SendMessage(AdvWinSpellList, LB_GETTOPINDEX, 0, 0);
                FillSpellSelectBox();
                SendMessage(AdvWinSpellList, LB_SETTOPINDEX, (WPARAM)Position, 0);
				ClearAdvancementBox();
                //DrawAdvancementBoxGraphics();
                }
            }
        }

    //reset
    GetIconInfo((HICON)IDC_ARROW, &IconInfo);
    IconInfo.fIcon = false;
    IconInfo.xHotspot = 0;
    IconInfo.yHotspot = 0;
    CreateIconIndirect(&IconInfo);
    SetCursor(CreateIconIndirect(&IconInfo));
    Dragging = false;
    IconDrag = -1;
    }

//---------------------------------------------------------------------------
void MainScreenClass::SubclassChildWindows()
    {
    WNDPROC OriginalProc;

    SubclassHWNDs.clear();
    OriginalProcs.clear();

    OriginalProc = (WNDPROC)SetWindowLong(AbilityStatBox, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(AbilityStatBox);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(SpellList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(SpellList);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(SkillsList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(SkillsList);
    OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(EnhancementList, GWL_WNDPROC, (LONG)SubclassWndProc);
	SubclassHWNDs.push_back(EnhancementList);
	OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(FeatList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(FeatList);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(InstructionWindowList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(InstructionWindowList);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(AdvWinFeatList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(AdvWinFeatList);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(AdvSkillPointSpendBox, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(AdvSkillPointSpendBox);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(AdvWinSpellList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(AdvWinSpellList);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(DescriptionWindow, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(DescriptionWindow);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(LoadButton, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(LoadButton);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(SaveButton, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(SaveButton);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(ClearButton, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(ClearButton);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(PrintButton, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(PrintButton);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(ForumExportButton, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(ForumExportButton);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(AboutButton, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(AboutButton);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(QuitButton, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(QuitButton);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(EquipmentScreenButton, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(EquipmentScreenButton);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(ItemBuilderButton, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(ItemBuilderButton);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(DisplayErrorsButton, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(DisplayErrorsButton);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(EquipmentDisplaySelectList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(EquipmentDisplaySelectList);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(AdvWinFirstNameInput, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(AdvWinFirstNameInput);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(AdvWinSurnameInput, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(AdvWinSurnameInput);
    OriginalProcs.push_back(OriginalProc);
    OriginalProc = (WNDPROC)SetWindowLong(AdditionalStatsList, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(AdditionalStatsList);
    OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(DestinyPanelButton, GWL_WNDPROC, (LONG)SubclassWndProc);
    SubclassHWNDs.push_back(DestinyPanelButton);
	OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(FeatsPanelButton, GWL_WNDPROC, (LONG)SubclassWndProc);
	SubclassHWNDs.push_back(FeatsPanelButton);
	OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(SpellsPanelButton, GWL_WNDPROC, (LONG)SubclassWndProc);
	SubclassHWNDs.push_back(SpellsPanelButton);
	OriginalProcs.push_back(OriginalProc);
	OriginalProc = (WNDPROC)SetWindowLong(EnhPanelButton, GWL_WNDPROC, (LONG)SubclassWndProc);
	SubclassHWNDs.push_back(EnhPanelButton);
    OriginalProcs.push_back(OriginalProc);
	
    }

//---------------------------------------------------------------------------
void MainScreenClass::DesubclassChildWindows()
    {
    for (unsigned int i=0; i<SubclassHWNDs.size(); i++)
        SetWindowLong(SubclassHWNDs[i], GWL_WNDPROC, (LONG)OriginalProcs[i]);
    }

//---------------------------------------------------------------------------
WNDPROC MainScreenClass::GetOriginalWinProc(HWND Window)
    {
    for (unsigned int i=0; i<SubclassHWNDs.size(); i++)
        {
        if (SubclassHWNDs[i] == Window)
            return OriginalProcs[i];
        }
    return 0;
    }

//---------------------------------------------------------------------------
void MainScreenClass::ToggleEquipmentScreen()
    {
    RECT Rect;
	SCROLLINFO si;
    int XOffset;
    int YOffset;

    if (EquipmentScreenShown == false)
        {
        EquipmentScreenShown = true;
        EquipmentScreenCurrentSelectedSlot = NOSLOT;
        ShowWindow(AdvWinBonusAbilityPointsCheckBox, false);
        ShowWindow(AdvWinFeatList, false);
        ShowWindow(AdvWinFirstNameInput, false);
        ShowWindow(AdvWinSurnameInput, false);
        ShowWindow(AdvSkillPointSpendBox, false);
        ShowWindow(AdvWinSpellList, false);
        ShowWindow(AdvWinSpellClearButton, false);
        ShowWindow(FeatListTitle, false);
        ShowWindow(FeatList, false);
        ShowWindow(EquipmentDisplayTitle, true);
        ShowWindow(EquipmentDisplaySelectList, true);
		ShowWindow(AdditionalStatsTitle, true);
		ShowWindow(AdditionalStatsList, true);
		ShowWindow(EnhancementTitle, false);
		ShowWindow(EnhancementList, false);

		//ShowWindow(SideEnhancementButton, false);
        SetWindowText(EquipmentScreenButton, "Build");
		FillAdditionalStatsBox();
        }
    else
        {
        EquipmentScreenShown = false;
        EquipmentScreenCurrentSelectedSlot = NOSLOT;
        ShowWindow(FeatListTitle, true);
        ShowWindow(FeatList, true);
        ShowWindow(EquipmentDisplayTitle, false);
        ShowWindow(EquipmentDisplaySelectList, false);
		ShowWindow(AdditionalStatsTitle, false);
		ShowWindow(AdditionalStatsList, false);
		ShowWindow(EnhancementTitle, true);
		//ShowWindow(SideEnhancementButton, true);
		ShowWindow(EnhancementList, true);
        SetWindowText(EquipmentScreenButton, "Equip.");
        }

	//get the scrollbar position so we can offset the graphics
	si.cbSize = sizeof(si);
	si.fMask = SIF_POS;
	GetScrollInfo (ParentWindow, SB_HORZ, &si);
	XOffset = si.nPos;
	GetScrollInfo (ParentWindow, SB_VERT, &si);
	YOffset = si.nPos;

    //reset the advancement box
	ClearAdvancementBox();

    //reset the enhancement box
    Rect.left = 310-XOffset;
    Rect.right = 600-XOffset;
    Rect.top = 350-YOffset;
    Rect.bottom = 540-YOffset;
    RedrawWindow(ParentWindow, &Rect, NULL, RDW_ERASE | RDW_INVALIDATE);

    ChangeEquipmentSelectType();       
    }

//---------------------------------------------------------------------------
void MainScreenClass::ChangeEquipmentSelectType()
    {
    switch (EquipmentScreenCurrentSelectedSlot)
        {
        case ARMORSLOT:
            {
            SetWindowText(EquipmentDisplayTitle, "Current Armor");
            break;
            }
        case RIGHTHANDSLOT:
            {
            SetWindowText(EquipmentDisplayTitle, "Current Right Hand Items");
            break;
            }
        case LEFTHANDSLOT:
            {
            SetWindowText(EquipmentDisplayTitle, "Current Left Hand Items");
            break;
            }
        case HEADSLOT:
            {
            SetWindowText(EquipmentDisplayTitle, "Current Helm Items");
            break;
            }
        case LEFTRINGSLOT:
        case RIGHTRINGSLOT:
            {
            SetWindowText(EquipmentDisplayTitle, "Current Ring Items");
            break;
            }
        case AMMOSLOT:
            {
            SetWindowText(EquipmentDisplayTitle, "Current Ammo Items");
            break;
            }
        case BRACERSLOT:
            {
            SetWindowText(EquipmentDisplayTitle, "Current Bracer Items");
            break;
            }
        case FEETSLOT:
            {
            SetWindowText(EquipmentDisplayTitle, "Current Boot Items");
            break;
            }
        case NECKSLOT:
            {
            SetWindowText(EquipmentDisplayTitle, "Current Necklace Items");
            break;
            }
        case GLOVESSLOT:
            {
            SetWindowText(EquipmentDisplayTitle, "Current Glove Items");
            break;
            }
        case TRINKETSLOT:
            {
            SetWindowText(EquipmentDisplayTitle, "Current Trinket Items");
            break;
            }
        case BACKSLOT:
            {
            SetWindowText(EquipmentDisplayTitle, "Current Cloak Items");
            break;
            }
        case WAISTSLOT:
            {
            SetWindowText(EquipmentDisplayTitle, "Current Belt Items");
            break;
            }
        case FACESLOT:
            {
            SetWindowText(EquipmentDisplayTitle, "Current Goggle Items");
            break;
            }
        default:
            {
            SetWindowText(EquipmentDisplayTitle, "Your Full Inventory");
            }
        }
    FillEquipmentDisplaySelectBox();
    }

//---------------------------------------------------------------------------
void MainScreenClass::ChangeCurrentActiveEquipment(unsigned int NewItem)
    {
    string Description;
	if (EquipmentScreenCurrentSelectedSlot != NOSLOT)
		Character.SetActiveEquipment(NewItem, EquipmentScreenCurrentSelectedSlot);

    RedrawWindow(EquipmentDisplaySelectList, NULL, NULL, RDW_INVALIDATE);

    //the description field
    Description = Character.BuildCharacterItemDescription(NewItem);
	FillDescriptionBox(Description);

    //changing the equipment may cause changes in ability, skills, and so on, so redraw those windows
    FillAbilityBox();
    FillAbilityStatBox();
    FillSkillBox();
	FillAdditionalStatsBox();
    }

//---------------------------------------------------------------------------
string MainScreenClass::ConvertOrdinalNumberToRoman(int Number)
    {
    switch (Number)
        {
        case 1:
            return "I";
        case 2:
            return "II";
        case 3:
            return "III";
        case 4:
            return "IV";
        case 5:
            return "V";
        case 6:
            return "VI";
        case 7:
            return "VII";
        case 8:
            return "VIII";
        case 9:
            return "IX";
        case 10:
            return "X";
        case 11:
            return "XI";
        case 12:
            return "XII";
        case 13:
            return "XIII";
        case 14:
            return "XIV";
        case 15:
            return "XV";
        case 16:
            return "XVI";
        case 17:
            return "XVII";
        case 18:
            return "XVIII";
        case 19:
            return "XIX";
        case 20:
            return "XX";
        }
    return "";
    }

//---------------------------------------------------------------------------
string MainScreenClass::ConvertOrdinalNumberToCardinal(int Number)
    {
    switch (Number)
        {
        case 1:
            return "1st";
        case 2:
            return "2nd";
        case 3:
            return "3rd";
        case 4:
            return "4th";
        case 5:
            return "5th";
        case 6:
            return "6th";
        case 7:
            return "7th";
        case 8:
            return "8th";
        case 9:
            return "9th";
        case 10:
            return "10th";
        }
    return "";
    }
    
//---------------------------------------------------------------------------
void MainScreenClass::ResizeScreen(HWND Wnd)
	{
	SIZE NewScreenSize;
	RECT NewScreenRect;
    UIComponentManager *UIComponent;

	UIComponent = InterfaceManager.GetUIComponents();

	GetClientRect(ParentWindow, &NewScreenRect);

	DeleteObject(hbmMem);
    DeleteDC(hdcMem);

	NewScreenSize.cx = NewScreenRect.right - NewScreenRect.left;
	NewScreenSize.cy = NewScreenRect.bottom - NewScreenRect.top;

	HDC hdc=GetDC(Wnd);
	hdcMem=CreateCompatibleDC(hdc);         
	hbmMem=CreateCompatibleBitmap(hdc, NewScreenSize.cx, NewScreenSize.cy);
	ReleaseDC(Wnd,hdc);

	//meta windows
	ResizeWindow("NameLabel", NameLabel, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("RaceClassLabel", RaceClassLabel, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("DisplayErrorsButton", DisplayErrorsButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);

	ResizeWindow("ItemBuilderButton", ItemBuilderButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("EquipmentScreenButton", EquipmentScreenButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("LoadButton", LoadButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("SaveButton", SaveButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("ClearButton", ClearButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("PrintButton", PrintButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("ForumExportButton", ForumExportButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("AboutButton", AboutButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("QuitButton", QuitButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);

	//Side Menu
	ResizeWindow("SideMenuTitle", SideMenuTitle, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("SideRaceSexButton", SideRaceSexButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("SideClassButton", SideClassButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("NameAndAlignmentButton", NameAndAlignmentButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("SideReincarnationButton", SideReincarnationButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("SideAbilityButton", SideAbilityButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("SideSkillButton", SideSkillButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("SideSpellButton", SideSpellButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("SideFeatsButton", SideFeatsButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("SideDestinyButton", SideDestinyButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("SideEnhancementButton", SideEnhancementButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);



     //the ability box
	ResizeWindow("AbilityBoxFrame", AbilityBoxFrame, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("AbilityLabel", AbilityLabel, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("AbilityModifierLabel", AbilityModifierLabel, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("StrLabel", StrLabel, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("DexLabel", DexLabel, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("ConLabel", ConLabel, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("IntLabel", IntLabel, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("WisLabel", WisLabel, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("ChaLabel", ChaLabel, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("StrLabel2", StrLabel2, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("DexLabel2", DexLabel2, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("ConLabel2", ConLabel2, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("IntLabel2", IntLabel2, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("WisLabel2", WisLabel2, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("ChaLabel2", ChaLabel2, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("StrNumber", StrNumber, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("DexNumber", DexNumber, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("ConNumber", ConNumber, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("IntNumber", IntNumber, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("WisNumber", WisNumber, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("ChaNumber", ChaNumber, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("StrModifier", StrModifier, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("DexModifier", DexModifier, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("ConModifier", ConModifier, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("IntModifier", IntModifier, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("WisModifier", WisModifier, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("ChaModifier", ChaModifier, NewScreenSize.cx, NewScreenSize.cy, UIComponent);

    //the ability statistics box
    ResizeWindow("AbilityStatBoxFrame", AbilityStatBoxFrame, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
    ResizeWindow("AbilityStatBox", AbilityStatBox, NewScreenSize.cx, NewScreenSize.cy, UIComponent);



    //the skill box
    ResizeWindow("SkillBoxFrame", SkillBoxFrame, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
    ResizeWindow("SkillTitle", SkillTitle, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
    ResizeWindow("KeyAbilityTitle", KeyAbilityTitle, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
    ResizeWindow("TotalModTitle", TotalModTitle, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
    ResizeWindow("AbilityModTitle", AbilityModTitle, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
    ResizeWindow("MiscModTitle", MiscModTitle, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
    ResizeWindow("SkillsList", SkillsList, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	
	//Known Panel Box
	ResizeWindow("FeatsPanelButton", FeatsPanelButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("SpellsPanelButton", SpellsPanelButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("EnhPanelButton", EnhPanelButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("DestinyPanelButton", DestinyPanelButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);

    //the feat list box
    ResizeWindow("FeatBoxFrame", FeatBoxFrame, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
    ResizeWindow("FeatListTitle", FeatListTitle, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
    ResizeWindow("FeatList", FeatList, NewScreenSize.cx, NewScreenSize.cy, UIComponent);

	//the enhancement list box
	ResizeWindow("EnhancementBoxFrame", EnhancementBoxFrame, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("EnhancementTitle", EnhancementTitle, NewScreenSize.cx, NewScreenSize.cy, UIComponent);

	ResizeWindow("EnhancementList", EnhancementList, NewScreenSize.cx, NewScreenSize.cy, UIComponent);

	//the spell box
	ResizeWindow("SpellBoxFrame", SpellBoxFrame, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("SpellBoxTitle", SpellBoxTitle, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("SpellList", SpellList, NewScreenSize.cx, NewScreenSize.cy, UIComponent);

	//the Destiny box
	ResizeWindow("DestinyBoxFrame", DestinyBoxFrame, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("DestinyBoxTitle", DestinyBoxTitle, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("DestinyList", DestinyList, NewScreenSize.cx, NewScreenSize.cy, UIComponent);


    //the instruction list box
    ResizeWindow("InstructionWindowFrame", InstructionWindowFrame, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
    ResizeWindow("InstructionWindowTitle",InstructionWindowTitle,  NewScreenSize.cx, NewScreenSize.cy, UIComponent);
    ResizeWindow("InstructionWindowList", InstructionWindowList, NewScreenSize.cx, NewScreenSize.cy, UIComponent);

    //the advancement box
    ResizeWindow("AdvancementWindowFrame", AdvancementWindowFrame, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
    ResizeWindow("AdvWinBonusAbilityPointsCheckBox", AdvWinBonusAbilityPointsCheckBox, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
    FitContent("AdvancementWindowFrame", "AdvWinFeatList", AdvWinFeatList, NewScreenSize.cx, NewScreenSize.cy, UIComponent, 10, 10, 10, 85);
    ResizeWindow("AdvWinFirstNameInput", AdvWinFirstNameInput, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
    ResizeWindow("AdvWinSurnameInput", AdvWinSurnameInput, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
    ResizeWindow("AdvSkillPointSpendBox", AdvSkillPointSpendBox, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
    ResizeWindow("AdvWinSpellList", AdvWinSpellList, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
    ResizeWindow("AdvWinSpellClearButton", AdvWinSpellClearButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("HeroicClassRadio", HeroicClassRadioButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	ResizeWindow("IconicClassRadio", IconicClassRadioButton, NewScreenSize.cx, NewScreenSize.cy, UIComponent);

    //the description box
    ResizeWindow("DescriptionWindow", DescriptionWindow, NewScreenSize.cx, NewScreenSize.cy, UIComponent);

    //equipment select box
    ResizeWindow("EquipmentDisplayTitle", EquipmentDisplayTitle, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
    ResizeWindow("EquipmentDisplaySelectList", EquipmentDisplaySelectList, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
	
	//additional Stats items
	ResizeWindow("AdditionalStatsTitle", AdditionalStatsTitle, NewScreenSize.cx, NewScreenSize.cy, UIComponent);
    ResizeWindow("AdditionalStatsList", AdditionalStatsList, NewScreenSize.cx, NewScreenSize.cy, UIComponent);


	

	//redraw the graphcs
    //InvalidateRect(Wnd, NULL, TRUE);
	}

//---------------------------------------------------------------------------
void MainScreenClass::ResizeWindow(string WindowName, HWND WindowID, int cx, int cy, UIComponentManager *UIComponent)
	{
	InterfaceComponentStruct *Component;

    Component = UIComponent->GetComponentData(WindowName, MAINWINDOW);
	MoveWindow(WindowID, static_cast<int>(Component->BaseLocationX*cx), static_cast<int>(Component->BaseLocationY*cy), static_cast<int>(Component->BaseWidth*cx),static_cast<int>( Component->BaseHeight*cy), TRUE);
	}

//---Resize the dest window botton relative to source window bottom plus offset---
void MainScreenClass::FitContent(string ContentWindowName, string DestWindowName, HWND DestWindowID, int cx, int cy, UIComponentManager *UIComponent, int OffsetLeft, int OffsetRight, int OffsetTop, int OffsetBottom)
	{
	InterfaceComponentStruct *Component = UIComponent->GetComponentData(ContentWindowName, MAINWINDOW);
	int Left = static_cast<int>(Component->BaseLocationX*cx)+OffsetLeft;
    int Right = static_cast<int>((Component->BaseLocationX+Component->BaseWidth)*cx)-OffsetRight;
	int Top = static_cast<int>(Component->BaseLocationY*cy)+OffsetTop;
	int Bottom = static_cast<int>((Component->BaseLocationY+Component->BaseHeight)*cy-OffsetBottom);

	Component = UIComponent->GetComponentData(DestWindowName, MAINWINDOW);
	MoveWindow(DestWindowID, Left, Top, Right-Left,Bottom-Top, TRUE);
	}

//---------------------------------------------------------------------------
void MainScreenClass::EnableErrorButton(bool State)
	{
	EnableWindow(DisplayErrorsButton, State);
	DrawLevelBars(GetDC(ParentWindow));
	}

//---------------------------------------------------------------------------
void MainScreenClass::RefreshMainScreen()
	{
	ResetEnhancementList();
	FillAbilityBox();
	FillAbilityStatBox();
	FillSkillBox();

	}
//---------------------------------------------------------------------------
void MainScreenClass::RefreshInstructionWindow()
{
	SetUp = TRUE;
	ChangeInstructionWindowSelection(CurrentInstructionSelection);

}


//---------------------------------------------------------------------------
void MainScreenClass::ResetEnhancementList()
	{
	UpdateSelectedEnhancements();
	FillEnhancementBox();
	}


//--------------------------------------------------------------
void MainScreenClass::ResetItemList()
	{
	FillEquipmentDisplaySelectBox();
	FillAbilityBox();
    FillAbilityStatBox();
    FillSkillBox();
	}

//----------------------------------------------------------------------
void MainScreenClass::FillAdditionalStatsBox()
	{
	int Index;
    unsigned int ASIndex;
    int ParentHeadingIndex;
    bool Used;
    string ParentHeading;
    vector <string> UsedParentHeadings;
    ParentHeadingStruct NewParentHeading;
    vector <string> OldParentHeading;
    vector <bool> OldParentCollapse;

    //before we start, save the parent headings
    for (unsigned int i=0; i<ASListParentHeading.size(); i++)
        {
        OldParentHeading.push_back(ASListParentHeading[i].ParentHeading);
        OldParentCollapse.push_back(ASListParentHeading[i].Collapsed);
        }
    ASListParentHeading.clear();

    Index = 0;
    UsedParentHeadings.clear();
    SendMessage(AdditionalStatsList, LB_RESETCONTENT, 0, 0);

	ASIndex = 0;
	while (ASIndex < ASListItems.size())
		{
		ParentHeading = ASListItems[ASIndex].ParentHeading;
		if (ParentHeading != "")
			{
			//find the parentheading index, or create it if not found
			ParentHeadingIndex = -1;
			for (unsigned int i=0; i<ASListParentHeading.size(); i++)
				{
				if (ASListParentHeading[i].ParentHeading == ParentHeading)
					{
					ParentHeadingIndex = i;
					break;
					}
				}
			if (ParentHeadingIndex == -1)
				{
				ASListParentHeading.push_back(NewParentHeading);
				ParentHeadingIndex = ASListParentHeading.size()-1;
				ASListParentHeading[ParentHeadingIndex].ParentHeading = ParentHeading;
				ASListParentHeading[ParentHeadingIndex].Collapsed = false;
				for (unsigned int j=0; j<OldParentHeading.size(); j++)
					{
					if (ASListParentHeading[ParentHeadingIndex].ParentHeading == OldParentHeading[j])
						{
						ASListParentHeading[ParentHeadingIndex].Collapsed = OldParentCollapse[j];
						break;
						}
					}
				}
			Used = false;
			for (unsigned int i=0; i<UsedParentHeadings.size(); i++)
				{
				if (UsedParentHeadings[i] == ParentHeading)
					{
					Used = true;
					break;
					}
				}
			if (Used == false)
				{
				ASListParentHeading[ParentHeadingIndex].ListIndex = SendMessage(AdditionalStatsList, LB_ADDSTRING, 0, 999999);
				UsedParentHeadings.push_back(ParentHeading);
				}
			}
		if (ParentHeading == "")
			SendMessage(AdditionalStatsList, LB_ADDSTRING, 0, ASIndex);
		else
			{
			if (ASListParentHeading[ParentHeadingIndex].Collapsed == false)
				{
				SendMessage(AdditionalStatsList, LB_ADDSTRING, 0, ASIndex+1000000);
				}
			}
		ASIndex++;
		}
	}

//---------------------------------------------------------------------------
void MainScreenClass::DrawAdditionalStatsBoxItem(HDC hDC, unsigned int Index, DWORD Item, long top, long left)
	{
	string Text;
	COLORREF OriginalColor;
	int XOffset;
	ostringstream ss;

	if (Item == 999999)
		{
		for (unsigned int i=0; i<ASListParentHeading.size(); i++)
			{
			if (ASListParentHeading[i].ListIndex == Index)
				{
				if (ASListParentHeading[i].Collapsed == true)
					DrawGraphic(hDC, &PlusBox, left, top+13, 20, 20);
				else
					DrawGraphic(hDC, &MinusBox, left, top+13, 20, 20);
				ss.str("");
				if (ASListParentHeading[i].ParentHeading == "Armor Class")
					ss << ASListParentHeading[i].ParentHeading << ":               " << Character.GetACMod(ACMOD_TOTAL, CurrentSelectedLevel);
				else
					ss << ASListParentHeading[i].ParentHeading;
				Text = ss.str();
				OriginalColor = SetTextColor(hDC, RGB(255,255,255));
				TextOut(hDC, left+25, top+15, Text.c_str(), Text.size());
				SetTextColor(hDC, OriginalColor);
				return;
				}
			}
		}
	XOffset = 0;
	if (Item > 999999)
		{
		XOffset = 15;
		Item -= 1000000;
		}
	ss.str("");
	ss << ASListItems[Item].ListItemName;
	if (ASListItems[Item].ParentHeading == "Armor Class")
		{
		if (ss.str() == "Base")
			ss << ":                 10";
		if (ss.str() == "Armor")
			{
			if (Character.GetItemBaseAC("Armor") > Character.GetItemACChange(ARMORMOD))
				ss << ":                " << Character.GetItemBaseAC("Armor");
			else
				ss << ":                " << Character.GetItemACChange(ARMORMOD);
			}
		if (ss.str() == "Shield")
			{
			if (Character.GetItemBaseAC("Shield") > Character.GetItemACChange(SHIELDMOD))
				ss << ":                " << Character.GetItemBaseAC("Shield");
			else
				ss << ":                " << Character.GetItemACChange(SHIELDMOD);
			}
		if (ss.str() == "Dex Bonus")
			ss << ":        " << Character.GetACMod(ACMOD_DEX, CurrentSelectedLevel);
		if (ss.str() == "Wis Bonus")
			{
			if (Character.GetNumClassLevels(MONK) >= 1)
				{//TODO: add armor and shield check error messages
				if (Character.CalculateTotalAbilityMod(WISDOM, CurrentSelectedLevel) >= 0)
					ss << ":        " << Character.CalculateTotalAbilityMod(WISDOM, CurrentSelectedLevel);
				else
					ss << ": Negative Modifier";
				}
			else
				ss << ":    Not a Monk!";
			}
		if (ss.str() == "Feats")
			ss << ":                 " << Character.GetArmorClassFeats(CurrentSelectedLevel);
		if (ss.str() == "Dodge")
			ss << ":               " << Character.GetItemACChange(DODGEMOD);
		if (ss.str() == "Deflection")
			ss << ":         " << Character.GetItemACChange(DEFLECTIONMOD);
		if (ss.str() == "Insight")
			ss << ":               " << Character.GetItemACChange(INSIGHTMOD);
		if (ss.str() == "Natural")
			ss << ":              " << Character.GetItemACChange(NATURALMOD);
		if (ss.str() == "Profane")
			ss << ":             " << Character.GetItemACChange(PROFANEMOD);
		if (ss.str() == "Paladin Aura")
			ss << ":     " << Character.GetPaladinAuraAC(CurrentSelectedLevel);
		}
	Text = ss.str();
	OriginalColor = SetTextColor(hDC, RGB(255,255,255));
	TextOut(hDC, left+45+XOffset, top+10, Text.c_str(), Text.size());
	SetTextColor(hDC, OriginalColor);
	}
	
//---------------------------------------------------------------------------
void MainScreenClass::LoadASListItems()
	{
	int NumOfItems;
	ASListItemStruct NewListItem;

	NumOfItems = 14;

	ASListItems.clear();
	for (int i=0; i<NumOfItems; i++)
		{
		ASListItems.push_back(NewListItem);
		switch (i)
			{
			case 0:
				{
				ASListItems[i].ParentHeading = "Armor Class";
				ASListItems[i].ListItemName = "Base";
				break;
				}
			case 1:
				{
				ASListItems[i].ParentHeading = "Armor Class";
				ASListItems[i].ListItemName = "Armor";
				break;
				}
			case 2:
				{
				ASListItems[i].ParentHeading = "Armor Class";
				ASListItems[i].ListItemName = "Shield";
				break;
				}
			case 3:
				{
				ASListItems[i].ParentHeading = "Armor Class";
				ASListItems[i].ListItemName = "Dex Bonus";
				break;
				}
			case 4:
				{
				ASListItems[i].ParentHeading = "Armor Class";
				ASListItems[i].ListItemName = "Wis Bonus";
				break;
				}
			case 5:
				{
				ASListItems[i].ParentHeading = "Armor Class";
				ASListItems[i].ListItemName = "Feats";
				break;
				}
			case 6:
				{
				ASListItems[i].ParentHeading = "Armor Class";
				ASListItems[i].ListItemName = "Dodge";
				break;
				}
			case 7:
				{
				ASListItems[i].ParentHeading = "Armor Class";
				ASListItems[i].ListItemName = "Deflection";
				break;
				}
			case 8:
				{
				ASListItems[i].ParentHeading = "Armor Class";
				ASListItems[i].ListItemName = "Insight";
				break;
				}
			case 9:
				{
				ASListItems[i].ParentHeading = "Armor Class";
				ASListItems[i].ListItemName = "Natural";
				break;
				}
			case 10:
				{
				ASListItems[i].ParentHeading = "Armor Class";
				ASListItems[i].ListItemName = "Profane";
				break;
				}
			case 11:
				{
				ASListItems[i].ParentHeading = "Armor Class";
				ASListItems[i].ListItemName = "Paladin Aura";
				break;
				}
			case 12:
				{
				ASListItems[i].ParentHeading = "Spell Resistance";
				ASListItems[i].ListItemName = "Race";
				break;
				}
			case 13:
				{
				ASListItems[i].ParentHeading = "Spell Resistance";
				ASListItems[i].ListItemName = "Enhancements";
				break;
				}
			}
		}


	}

//---------------------------------------------------------------------------
string MainScreenClass::CreateSpellDescription(unsigned int SpellIndex)
	{
	string Description;
	SpellStruct *SpellData;
	ostringstream ss;

	SpellData = Data.GetSpellData(SpellIndex);

	Description = "{\\b ";
	Description += SpellData->Name;
	Description += "} \\par\\par ";
	Description += SpellData->Description;
	Description += "\\par\\par {\\b School: } ";
	Description += SpellData->School;
	Description += "\\par {\\b Spell Point Cost: } ";
	Description += SpellData->Cost;
	Description += "\\par {\\b Components: } ";
	Description += SpellData->Components;
	Description += "\\par {\\b Meta Magic: } ";
	Description += SpellData->Meta;
	Description += "\\par {\\b Range: } ";
	Description += SpellData->Range;
	Description += "\\par {\\b Target: } ";
	Description += SpellData->Target;
	Description += "\\par {\\b Duration: } ";
	Description += SpellData->Duration;
	Description += "\\par {\\b Saving Throw: } ";
	Description += SpellData->Save;
	Description += "\\par {\\b Spell Resistance: } ";
	Description += SpellData->Resist;
	Description += "\\par {\\b Cooldown: } ";
	Description += SpellData->Cooldown;

	return Description;
	}
	
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
DWORD CALLBACK EditStreamCallback(DWORD dwCookie, LPBYTE pbBuff, LONG, LONG FAR *pcb)
    {
    string rtfPrefix = "{\\rtf1\\ansi\\deff0\\deftab720{\\fonttbl{\\f0\\froman "
		"Times New Roman;}}\n{\\colortbl\\red255\\green255\\blue255;\\red230\\green230\\blue0;"
		"\\red100\\green100\\blue255;\\red255\\green0\\blue0;\\red0\\green255\\blue0;"
		"\\red130\\green210\\blue255;}\n\\deflang1033\\pard\\plain\\f3\\fs20\\cf0 ";
	string rtfPostfix = "\n\\par }";
    string Final;

    Final = rtfPrefix;
    Final += (char*)dwCookie;
    Final += rtfPostfix;
    memcpy (pbBuff, Final.c_str(), strlen(Final.c_str()));
    *pcb = strlen(Final.c_str());
    return 0;
    }

//---------------------------------------------------------------------------
bool SpellCompare(SpellListSortStruct S1, SpellListSortStruct S2)
    {
    if (S1.SpellLevel != S2.SpellLevel)
        return S1.SpellLevel < S2.SpellLevel;
    return S1.SpellIndex < S2.SpellIndex;
    }

//---------------------------------------------------------------------------
bool EnhancementCompareName(EnhancementSortStruct E1, EnhancementSortStruct E2)
    {
    //sort enhancements by parent heading, then by name
    if (E1.ParentHeading != E2.ParentHeading)
        return E1.ParentHeading < E2.ParentHeading;
    return E1.EnhancementIndex < E2.EnhancementIndex;
    }

//---------------------------------------------------------------------------
bool EnhancementCompareLevel(EnhancementSortStruct E1, EnhancementSortStruct E2)
    {
    //sort enhancements by level taken, then by name
    if (E1.LevelTaken != E2.LevelTaken)
        return E1.LevelTaken < E2.LevelTaken;
    return E1.EnhancementIndex < E2.EnhancementIndex;
    }

//--------------------------------------------------------------------------
bool SelectedEnhancementCompareName(SelectedEnhancementSortStruct E1, SelectedEnhancementSortStruct E2)
	{
	//sort Selected Enhancements by Parent heading then by name
	if (E1.ParentHeading != E2.ParentHeading)
		return E1.ParentHeading < E2.ParentHeading;
	return E1.EnhancementName < E2.EnhancementName;
	}
