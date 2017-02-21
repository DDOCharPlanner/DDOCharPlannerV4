#include "PrintWindowClass.h"
#include "MultiAbilityWindowClass.h"
#include "InterfaceManagerClass.h"
#include "DataClass.h"
#include "CharacterClass.h"

//---------------------------------------------------------------------------
MultiAbilityWindowClass::MultiAbilityWindowClass()
{
}

//---------------------------------------------------------------------------
MultiAbilityWindowClass::~MultiAbilityWindowClass()
{
	DeleteObject(TitleFontLarge);
}

//---------------------------------------------------------------------------
void MultiAbilityWindowClass::Create(HINSTANCE Instance, HWND Parent)
{
	WNDCLASSEX wc;
	int ParentX;
	int ParentY;
	RECT ParentRect;
	RECT WindowRect;
	int WindowX;
	int WindowY;
	static char WindowName[] = "Ability Window";
	LOGBRUSH lb;
	LOGFONT lf;
	UIComponentManager *UIManager;
	InterfaceComponentStruct *Component;

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
	MultiAbilityHandle = CreateWindow(WindowName, WindowName, WS_DLGFRAME | WS_POPUP, 0, 0, 1000, 700, Parent, NULL, Instance, NULL);
	SetClassLong(MultiAbilityHandle, 0, (long)MULTIABILITYWINDOW);
	int TopBar = 25;
	GetWindowRect(Parent, &ParentRect);
	ParentX = ParentRect.right - ParentRect.left;
	ParentY = ParentRect.bottom - ParentRect.top - TopBar;

	GetWindowRect(MultiAbilityHandle, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;
	SetWindowPos(MultiAbilityHandle, Parent, ParentRect.left + (ParentX / 2) - (WindowX / 2), ParentRect.top + (int)(ParentY / 2) - (WindowY / 2) + TopBar, 400, 300, SWP_NOSIZE);

	UIManager = InterfaceManager.GetUIComponents();
	//the child windows
	//MultiAbilityLabel = CreateWindowEx(NULL, "STATIC", "Select Ability Advancement", WS_CHILD, 5, 5, 300, 20, MultiAbilityHandle, (HMENU)MAB_LABEL, Instance, NULL);
	//AcceptButton = CreateWindowEx(NULL, "BUTTON", "Accept", WS_CHILD | BS_PUSHBUTTON, 485, 5, 50, 25, MultiAbilityHandle, (HMENU)MAB_ACCEPT, Instance, NULL);
	//CancelButton = CreateWindowEx(NULL, "BUTTON", "Close", WS_CHILD | BS_PUSHBUTTON, 940, 5, 50, 25, MultiAbilityHandle, (HMENU)MAB_CLOSE, Instance, NULL);
	Component = UIManager->GetComponentData("MultiAbilityText", MULTIABILITYWINDOW);
	MultiAbilityText = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CloseButton", MULTIABILITYWINDOW);
	CloseButton = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("CreationFrame", MULTIABILITYWINDOW);
	CreationFrame = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationFrameLabel", MULTIABILITYWINDOW);
	CreationFrameLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationAvilablePointLabel", MULTIABILITYWINDOW);
	CreationAvilablePointLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationAvilablePoint", MULTIABILITYWINDOW);
	CreationAvilablePoint = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("PointBuild32", MULTIABILITYWINDOW);
	PointBuild32 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("BaseValueLabel", MULTIABILITYWINDOW);
	BaseValueLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("ModLabel", MULTIABILITYWINDOW);
	ModLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CostLabel", MULTIABILITYWINDOW);
	CostLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationStr", MULTIABILITYWINDOW);
	CreationStr = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationDex", MULTIABILITYWINDOW);
	CreationDex = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationCon", MULTIABILITYWINDOW);
	CreationCon = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationInt", MULTIABILITYWINDOW);
	CreationInt = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationWis", MULTIABILITYWINDOW);
	CreationWis = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationCha", MULTIABILITYWINDOW);
	CreationCha = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationStr2", MULTIABILITYWINDOW);
	CreationStr2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationDex2", MULTIABILITYWINDOW);
	CreationDex2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationCon2", MULTIABILITYWINDOW);
	CreationCon2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationInt2", MULTIABILITYWINDOW);
	CreationInt2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationWis2", MULTIABILITYWINDOW);
	CreationWis2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CreationCha2", MULTIABILITYWINDOW);
	CreationCha2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("LevelUpFrame", MULTIABILITYWINDOW);
	LevelUpFrame = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("LevelUpLabel", MULTIABILITYWINDOW);
	LevelUpLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("LevelUpStr", MULTIABILITYWINDOW);
	LevelUpStr = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("LevelUpStr2", MULTIABILITYWINDOW);
	LevelUpStr2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("LevelUpDex", MULTIABILITYWINDOW);
	LevelUpDex = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("LevelUpDex2", MULTIABILITYWINDOW);
	LevelUpDex2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("LevelUpCon", MULTIABILITYWINDOW);
	LevelUpCon = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("LevelUpCon2", MULTIABILITYWINDOW);
	LevelUpCon2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("LevelUpInt", MULTIABILITYWINDOW);
	LevelUpInt = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("LevelUpInt2", MULTIABILITYWINDOW);
	LevelUpInt2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("LevelUpWis", MULTIABILITYWINDOW);
	LevelUpWis = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("LevelUpWis2", MULTIABILITYWINDOW);
	LevelUpWis2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("LevelUpCha", MULTIABILITYWINDOW);
	LevelUpCha = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("LevelUpCha2", MULTIABILITYWINDOW);
	LevelUpCha2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("LevelLabel", MULTIABILITYWINDOW);
	LevelLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("Level4", MULTIABILITYWINDOW);
	Level4 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("Level8", MULTIABILITYWINDOW);
	Level8 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("Level12", MULTIABILITYWINDOW);
	Level12 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("Level6", MULTIABILITYWINDOW);
	Level6 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("Level20", MULTIABILITYWINDOW);
	Level20 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("Level24", MULTIABILITYWINDOW);
	Level24 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("Level28", MULTIABILITYWINDOW);
	Level28 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("TotalLabel", MULTIABILITYWINDOW);
	TotalLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("StrRadio4", MULTIABILITYWINDOW);
	StrRadio4 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("DexRadio4", MULTIABILITYWINDOW);
	DexRadio4 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("ConRadio4", MULTIABILITYWINDOW);
	ConRadio4 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("IntRadio4", MULTIABILITYWINDOW);
	IntRadio4 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("WisRadio4", MULTIABILITYWINDOW);
	WisRadio4 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("ChaRadio4", MULTIABILITYWINDOW);
	ChaRadio4 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("StrRadio8", MULTIABILITYWINDOW);
	StrRadio8 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("DexRadio8", MULTIABILITYWINDOW);
	DexRadio8 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("ConRadio8", MULTIABILITYWINDOW);
	ConRadio8 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("IntRadio8", MULTIABILITYWINDOW);
	IntRadio8 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("WisRadio8", MULTIABILITYWINDOW);
	WisRadio8 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("ChaRadio8", MULTIABILITYWINDOW);
	ChaRadio8 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	
	Component = UIManager->GetComponentData("StrRadio12", MULTIABILITYWINDOW);
	StrRadio12 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("DexRadio12", MULTIABILITYWINDOW);
	DexRadio12 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("ConRadio12", MULTIABILITYWINDOW);
	ConRadio12 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("IntRadio12", MULTIABILITYWINDOW);
	IntRadio12 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("WisRadio12", MULTIABILITYWINDOW);
	WisRadio12 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("ChaRadio12", MULTIABILITYWINDOW);
	ChaRadio12 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("StrRadio16", MULTIABILITYWINDOW);
	StrRadio16 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("DexRadio16", MULTIABILITYWINDOW);
	DexRadio16 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("ConRadio16", MULTIABILITYWINDOW);
	ConRadio16 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("IntRadio16", MULTIABILITYWINDOW);
	IntRadio16 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("WisRadio16", MULTIABILITYWINDOW);
	WisRadio16 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("ChaRadio16", MULTIABILITYWINDOW);
	ChaRadio16 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("StrRadio20", MULTIABILITYWINDOW);
	StrRadio20 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("DexRadio20", MULTIABILITYWINDOW);
	DexRadio20 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("ConRadio20", MULTIABILITYWINDOW);
	ConRadio20 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("IntRadio20", MULTIABILITYWINDOW);
	IntRadio20 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("WisRadio20", MULTIABILITYWINDOW);
	WisRadio20 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("ChaRadio20", MULTIABILITYWINDOW);
	ChaRadio20 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("StrRadio24", MULTIABILITYWINDOW);
	StrRadio24 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("DexRadio24", MULTIABILITYWINDOW);
	DexRadio24 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("ConRadio24", MULTIABILITYWINDOW);
	ConRadio24 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("IntRadio24", MULTIABILITYWINDOW);
	IntRadio24 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("WisRadio24", MULTIABILITYWINDOW);
	WisRadio24 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("ChaRadio24", MULTIABILITYWINDOW);
	ChaRadio24 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("StrRadio28", MULTIABILITYWINDOW);
	StrRadio28 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("DexRadio28", MULTIABILITYWINDOW);
	DexRadio28 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("ConRadio28", MULTIABILITYWINDOW);
	ConRadio28 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("IntRadio28", MULTIABILITYWINDOW);
	IntRadio28 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("WisRadio28", MULTIABILITYWINDOW);
	WisRadio28 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("ChaRadio28", MULTIABILITYWINDOW);
	ChaRadio28 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("CurrentFrame", MULTIABILITYWINDOW);
	CurrentFrame = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CurrentLabel", MULTIABILITYWINDOW);
	CurrentLabel = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("CurrentStr", MULTIABILITYWINDOW);
	CurrentStr = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CurrentStr2", MULTIABILITYWINDOW);
	CurrentStr2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CurrentDex", MULTIABILITYWINDOW);
	CurrentDex = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CurrentDex2", MULTIABILITYWINDOW);
	CurrentDex2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CurrentCon", MULTIABILITYWINDOW);
	CurrentCon = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CurrentCon2", MULTIABILITYWINDOW);
	CurrentCon2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CurrentInt", MULTIABILITYWINDOW);
	CurrentInt = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CurrentInt2", MULTIABILITYWINDOW);
	CurrentInt2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CurrentWis", MULTIABILITYWINDOW);
	CurrentWis = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CurrentWis2", MULTIABILITYWINDOW);
	CurrentWis2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CurrentCha", MULTIABILITYWINDOW);
	CurrentCha = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CurrentCha2", MULTIABILITYWINDOW);
	CurrentCha2 = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);

	Component = UIManager->GetComponentData("CurrentValue", MULTIABILITYWINDOW);
	CurrentValue = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);
	Component = UIManager->GetComponentData("CurrentMod", MULTIABILITYWINDOW);
	CurrentMod = CreateWindowEx(nullptr, Component->WindowType.c_str(), Component->WindowLabel.c_str(), Component->Style, static_cast<int>(Component->BaseLocationX), static_cast<int>(Component->BaseLocationY), static_cast<int>(Component->BaseWidth), static_cast<int>(Component->BaseHeight), MultiAbilityHandle, (HMENU)Component->WindowID, Instance, nullptr);


	GetObject(GetStockObject(DKGRAY_BRUSH), sizeof(LOGBRUSH), &lb);


	//create a font
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
	StringCbCopy(lf.lfFaceName, LF_FACESIZE, TEXT("Times New Roman"));
	TitleFontLarge = CreateFontIndirect(&lf);

	lf.lfHeight = 16;
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
	StringCbCopy(lf.lfFaceName, LF_FACESIZE, TEXT("Times New Roman"));
	DefaultFont = CreateFontIndirect(&lf);

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
	StringCbCopy(lf.lfFaceName, LF_FACESIZE, TEXT("Times New Roman"));
	AbilityFontLarge = CreateFontIndirect(&lf);
	lf.lfHeight = 10;
	StringCbCopy(lf.lfFaceName, LF_FACESIZE, TEXT("Ariel"));
	AbilityFontSmall = CreateFontIndirect(&lf);
	lf.lfHeight = 14;
	ArielFontSmall = CreateFontIndirect(&lf);


	//background color changes
	//SendMessage(DescPanel, EM_SETBKGNDCOLOR, 0, RGB(0, 0, 0));

	//create a default font


	SendMessage(MultiAbilityText, WM_SETFONT, (WPARAM)TitleFontLarge, 0);

	SendMessage(CreationFrameLabel, WM_SETFONT, (WPARAM)TitleFontLarge, 0);
	SendMessage(CreationStr, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(CreationDex, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(CreationCon, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(CreationInt, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(CreationWis, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(CreationCha, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(CreationStr2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(CreationDex2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(CreationCon2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(CreationInt2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(CreationWis2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(CreationCha2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);

	SendMessage(LevelUpLabel, WM_SETFONT, (WPARAM)TitleFontLarge, 0);
	SendMessage(LevelUpStr, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(LevelUpDex, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(LevelUpCon, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(LevelUpInt, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(LevelUpWis, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(LevelUpCha, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(LevelUpStr2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(LevelUpDex2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(LevelUpCon2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(LevelUpInt2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(LevelUpWis2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(LevelUpCha2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);

	SendMessage(CurrentLabel, WM_SETFONT, (WPARAM)TitleFontLarge, 0);
	SendMessage(CurrentStr, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(CurrentDex, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(CurrentCon, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(CurrentInt, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(CurrentWis, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(CurrentCha, WM_SETFONT, (WPARAM)AbilityFontLarge, 0);
	SendMessage(CurrentStr2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(CurrentDex2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(CurrentCon2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(CurrentInt2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(CurrentWis2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);
	SendMessage(CurrentCha2, WM_SETFONT, (WPARAM)AbilityFontSmall, 0);

	LoadGraphics(MultiAbilityHandle);


}

//---------------------------------------------------------------------------
void MultiAbilityWindowClass::Show(bool State)
{
	ostringstream Text;

	//pop it up
	ShowWindow(MultiAbilityHandle, State);
	ShowWindow(MultiAbilityText, State);
	ShowWindow(CloseButton, State);
	ShowWindow(CreationFrame, State);
	ShowWindow(CreationFrameLabel, State);
	ShowWindow(CreationAvilablePointLabel, State);
	ShowWindow(CreationAvilablePoint, State);
	ShowWindow(PointBuild32, State);
	ShowWindow(BaseValueLabel, State);
	ShowWindow(ModLabel, State);
	ShowWindow(CostLabel, State);
	ShowWindow(CreationStr, State);
	ShowWindow(CreationDex, State);
	ShowWindow(CreationCon, State);
	ShowWindow(CreationInt, State);
	ShowWindow(CreationWis, State);
	ShowWindow(CreationCha, State);
	ShowWindow(CreationStr2, State);
	ShowWindow(CreationDex2, State);
	ShowWindow(CreationCon2, State);
	ShowWindow(CreationInt2, State);
	ShowWindow(CreationWis2, State);
	ShowWindow(CreationCha2, State);

	ShowWindow(LevelUpFrame, State);
	ShowWindow(LevelUpLabel, State);
	ShowWindow(LevelUpStr, State);
	ShowWindow(LevelUpDex, State);
	ShowWindow(LevelUpCon, State);
	ShowWindow(LevelUpInt, State);
	ShowWindow(LevelUpWis, State);
	ShowWindow(LevelUpCha, State);
	ShowWindow(LevelUpStr2, State);
	ShowWindow(LevelUpDex2, State);
	ShowWindow(LevelUpCon2, State);
	ShowWindow(LevelUpInt2, State);
	ShowWindow(LevelUpWis2, State);
	ShowWindow(LevelUpCha2, State);

	ShowWindow(LevelLabel, State);
	ShowWindow(Level4, State);
	ShowWindow(Level8, State);
	ShowWindow(Level12, State);
	ShowWindow(Level6, State);
	ShowWindow(Level20, State);
	ShowWindow(Level24, State);
	ShowWindow(Level28, State);
	ShowWindow(TotalLabel, State);

	ShowWindow(StrRadio4, State);
	ShowWindow(StrRadio8, State);
	ShowWindow(StrRadio12, State);
	ShowWindow(StrRadio16, State);
	ShowWindow(StrRadio20, State);
	ShowWindow(StrRadio24, State);
	ShowWindow(StrRadio28, State);
	//ShowWindow(StrTotal, State);

	ShowWindow(DexRadio4, State);
	ShowWindow(DexRadio8, State);
	ShowWindow(DexRadio12, State);
	ShowWindow(DexRadio16, State);
	ShowWindow(DexRadio20, State);
	ShowWindow(DexRadio24, State);
	ShowWindow(DexRadio28, State);
	//ShowWindow(DexTotal, State);

	ShowWindow(ConRadio4, State);
	ShowWindow(ConRadio8, State);
	ShowWindow(ConRadio12, State);
	ShowWindow(ConRadio16, State);
	ShowWindow(ConRadio20, State);
	ShowWindow(ConRadio24, State);
	ShowWindow(ConRadio28, State);
	//ShowWindow(ConTotal, State);

	ShowWindow(IntRadio4, State);
	ShowWindow(IntRadio8, State);
	ShowWindow(IntRadio12, State);
	ShowWindow(IntRadio16, State);
	ShowWindow(IntRadio20, State);
	ShowWindow(IntRadio24, State);
	ShowWindow(IntRadio28, State);
	//ShowWindow(IntTotal, State);

	ShowWindow(WisRadio4, State);
	ShowWindow(WisRadio8, State);
	ShowWindow(WisRadio12, State);
	ShowWindow(WisRadio16, State);
	ShowWindow(WisRadio20, State);
	ShowWindow(WisRadio24, State);
	ShowWindow(WisRadio28, State);
	//ShowWindow(WisTotal, State);

	ShowWindow(ChaRadio4, State);
	ShowWindow(ChaRadio8, State);
	ShowWindow(ChaRadio12, State);
	ShowWindow(ChaRadio16, State);
	ShowWindow(ChaRadio20, State);
	ShowWindow(ChaRadio24, State);
	ShowWindow(ChaRadio28, State);
	//ShowWindow(ChaTotal, State);

	ShowWindow(CurrentFrame, State);
	ShowWindow(CurrentLabel, State);
	ShowWindow(CurrentStr, State);
	ShowWindow(CurrentDex, State);
	ShowWindow(CurrentCon, State);
	ShowWindow(CurrentInt, State);
	ShowWindow(CurrentWis, State);
	ShowWindow(CurrentCha, State);
	ShowWindow(CurrentStr2, State);
	ShowWindow(CurrentDex2, State);
	ShowWindow(CurrentCon2, State);
	ShowWindow(CurrentInt2, State);
	ShowWindow(CurrentWis2, State);
	ShowWindow(CurrentCha2, State);
	ShowWindow(CurrentValue, State);
	ShowWindow(CurrentMod, State);

	//Center in Window

	int ParentX;
	int ParentY;

	RECT WindowRect;
	RECT ParentRect;
	int WindowX;
	int WindowY;
	HWND ParentWindow;
	ParentWindow = InterfaceManager.ControlWindow.GetControlWindowHandle();
	GetWindowRect(ParentWindow, &ParentRect);
	ParentX = ParentRect.right - ParentRect.left;
	ParentY = ParentRect.bottom - ParentRect.top;

	GetWindowRect(MultiAbilityHandle, &WindowRect);
	WindowX = WindowRect.right - WindowRect.left;
	WindowY = WindowRect.bottom - WindowRect.top;
	SetWindowPos(MultiAbilityHandle, ParentWindow, ParentRect.left + (ParentX / 2) - (WindowX / 2), ParentRect.top + (ParentY / 2) - (WindowY / 2), 0, 0, SWP_NOSIZE);

	//Find RadioButtonIDs
	RadioButtonID[0][0] = MAB_4STR;
	RadioButtonID[0][1] = MAB_8STR;
	RadioButtonID[0][2] = MAB_12STR;
	RadioButtonID[0][3] = MAB_16STR;
	RadioButtonID[0][4] = MAB_20STR;
	RadioButtonID[0][5] = MAB_24STR;
	RadioButtonID[0][6] = MAB_28STR;

	RadioButtonID[1][0] = MAB_4DEX;
	RadioButtonID[1][1] = MAB_8DEX;
	RadioButtonID[1][2] = MAB_12DEX;
	RadioButtonID[1][3] = MAB_16DEX;
	RadioButtonID[1][4] = MAB_20DEX;
	RadioButtonID[1][5] = MAB_24DEX;
	RadioButtonID[1][6] = MAB_28DEX;

	RadioButtonID[2][0] = MAB_4CON;
	RadioButtonID[2][1] = MAB_8CON;
	RadioButtonID[2][2] = MAB_12CON;
	RadioButtonID[2][3] = MAB_16CON;
	RadioButtonID[2][4] = MAB_20CON;
	RadioButtonID[2][5] = MAB_24CON;
	RadioButtonID[2][6] = MAB_28CON;

	RadioButtonID[3][0] = MAB_4INT;
	RadioButtonID[3][1] = MAB_8INT;
	RadioButtonID[3][2] = MAB_12INT;
	RadioButtonID[3][3] = MAB_16INT;
	RadioButtonID[3][4] = MAB_20INT;
	RadioButtonID[3][5] = MAB_24INT;
	RadioButtonID[3][6] = MAB_28INT;

	RadioButtonID[4][0] = MAB_4WIS;
	RadioButtonID[4][1] = MAB_8WIS;
	RadioButtonID[4][2] = MAB_12WIS;
	RadioButtonID[4][3] = MAB_16WIS;
	RadioButtonID[4][4] = MAB_20WIS;
	RadioButtonID[4][5] = MAB_24WIS;
	RadioButtonID[4][6] = MAB_28WIS;

	RadioButtonID[5][0] = MAB_4CHA;
	RadioButtonID[5][1] = MAB_8CHA;
	RadioButtonID[5][2] = MAB_12CHA;
	RadioButtonID[5][3] = MAB_16CHA;
	RadioButtonID[5][4] = MAB_20CHA;
	RadioButtonID[5][5] = MAB_24CHA;
	RadioButtonID[5][6] = MAB_28CHA;

	CurrentLevel = 30;

	DrawCreation();
	DrawLevelUp();
	DrawCurrent();
	DrawLevelBars();
}
//---------------------------------------------------------------------------
void MultiAbilityWindowClass::DrawCreation()
{
	int Ability;
	int Modifier;
	int Cost;
	UIComponentManager *UIManager;
	UIManager = InterfaceManager.GetUIComponents();
	InterfaceGraphicStruct *Graphic;
	ostringstream ss;
	ostringstream vs;
	int X, Y;
	int Width, Height;
	COLORREF OldColor;
	HDC hdc;
	RECT rc;
	hdc = GetWindowDC(MultiAbilityHandle);
	string TextString, EraseString;
	EraseString = "  ";
	SelectObject(hdc, DefaultFont);
	SetBkMode(hdc, TRANSPARENT);
	for (int i = 0; i < 6; i++)
	{
		ss.str("");
		ss << "AbilityDown" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTIABILITYWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		Width = static_cast<int>(Graphic->BaseWidth);
		Height = static_cast<int>(Graphic->BaseHeight);
		//if (SetTotalValue[i] < 1)
			//DrawGraphicGreyscale(hdc, &LeftArrow, X, Y, Width, Height);
		//else
		DrawGraphic(hdc, &Minus, X, Y, Width, Height);

		ss.str("");
		ss << "AbilityUp" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTIABILITYWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		Width = static_cast<int>(Graphic->BaseWidth);
		Height = static_cast<int>(Graphic->BaseHeight);
		//if (SetTotalValue[i] < 1)
		//DrawGraphicGreyscale(hdc, &LeftArrow, X, Y, Width, Height);
		//else
		DrawGraphic(hdc, &Plus, X, Y, Width, Height);

		//Ability Value
		SelectObject(hdc, DefaultFont);
		OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		ss.str("");
		ss << "AbilityValue" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTIABILITYWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		Width = static_cast<int>(Graphic->BaseWidth);
		Height = static_cast<int>(Graphic->BaseHeight);
		rc.left = X;
		rc.top = Y;
		rc.right = X + Width;
		rc.bottom = Y + Height;
		ClearRect(hdc, rc);
		ss.str("");
		Ability = Character.GetAbility(i, 1, false, false, false, false);
		ss << Ability;
		TextString = ss.str();
		if (TextString.size()>1)
			X -= 5;
		TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
		SetTextColor(hdc, OldColor);

		//Ability Cost
		SelectObject(hdc, DefaultFont);
		OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		ss.str("");
		ss << "CurrentCost" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTIABILITYWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		Width = static_cast<int>(Graphic->BaseWidth);
		Height = static_cast<int>(Graphic->BaseHeight);
		rc.left = X;
		rc.top = Y;
		rc.right = X + Width;
		rc.bottom = Y + Height;
		ClearRect(hdc, rc);
		ss.str("");
		Cost = Character.GetAbilityCost(i);
		if (Cost == -1)
			TextString = "MAX";
		else
		{
			ss << Cost;
			TextString = ss.str();
		}
		if (TextString.size()>1)
			X -= 5;
		TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
		SetTextColor(hdc, OldColor);

		//Current Cost
		SelectObject(hdc, DefaultFont);
		OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		ss.str("");
		ss << "CurrentMod" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTIABILITYWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		Width = static_cast<int>(Graphic->BaseWidth);
		Height = static_cast<int>(Graphic->BaseHeight);
		rc.left = X;
		rc.top = Y;
		rc.right = X + Width;
		rc.bottom = Y + Height;
		ClearRect(hdc, rc);
		ss.str("");
		Modifier = Data.CalculateAbilityModifier(Ability);
		if (Modifier > 0)
			ss << "+" << Modifier;
		else
			ss << Modifier;
		TextString = ss.str();
		if (TextString.size()>1)
			X -= 5;
		TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
		SetTextColor(hdc, OldColor);
	}

	ReleaseDC(MultiAbilityHandle, hdc);
}

//---------------------------------------------------------------------------
void MultiAbilityWindowClass::DrawLevelUp()
{
	int Ability;
	int LevelUpTotal;
	UIComponentManager *UIManager;
	UIManager = InterfaceManager.GetUIComponents();
	InterfaceGraphicStruct *Graphic;
	ostringstream ss;
	ostringstream vs;
	int X, Y;
	int Width, Height;
	COLORREF OldColor;
	HDC hdc;
	RECT rc;
	hdc = GetWindowDC(MultiAbilityHandle);
	string TextString;
	SelectObject(hdc, DefaultFont);
	SetBkMode(hdc, TRANSPARENT);
	LRESULT GetState;
	ABILITIES LevelUpAbility;
	//Set Radio Buttons
	int LevelUpLevel[7] = { 4, 8, 12, 16, 20, 24, 28 };
	for (int x = 0; x < 7; x++)
		{
			LevelUpAbility = Character.GetAbilityIncrease(LevelUpLevel[x]);
			if (LevelUpAbility != -1)
			{
				switch (LevelUpAbility)
				{
					case 0:
					{
						switch (x)
						{
						case 0:
						{
							SendMessage(StrRadio4, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 1:
						{
							SendMessage(StrRadio8, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 2:
						{
							SendMessage(StrRadio12, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 3:
						{
							SendMessage(StrRadio16, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 4:
						{
							SendMessage(StrRadio20, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 5:
						{
							SendMessage(StrRadio24, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 6:
						{
							SendMessage(StrRadio28, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
	
						}
					break;
					}
					case 1:
					{
						switch (x)
						{
						case 0:
						{
							SendMessage(DexRadio4, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 1:
						{
							SendMessage(DexRadio8, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 2:
						{
							SendMessage(DexRadio12, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 3:
						{
							SendMessage(DexRadio16, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 4:
						{
							SendMessage(DexRadio20, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 5:
						{
							SendMessage(DexRadio24, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 6:
						{
							SendMessage(DexRadio28, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}

						}
						break;
					}
					case 2:
					{
						switch (x)
						{
						case 0:
						{
							SendMessage(ConRadio4, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 1:
						{
							SendMessage(ConRadio8, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 2:
						{
							SendMessage(ConRadio12, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 3:
						{
							SendMessage(ConRadio16, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 4:
						{
							SendMessage(ConRadio20, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 5:
						{
							SendMessage(ConRadio24, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 6:
						{
							SendMessage(ConRadio28, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}

						}
						break;
					}
					case 3:
					{
						switch (x)
						{
						case 0:
						{
							SendMessage(IntRadio4, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 1:
						{
							SendMessage(IntRadio8, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 2:
						{
							SendMessage(IntRadio12, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 3:
						{
							SendMessage(IntRadio16, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 4:
						{
							SendMessage(IntRadio20, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 5:
						{
							SendMessage(IntRadio24, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 6:
						{
							SendMessage(IntRadio28, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}

						}
						break;
					}
					case 4:
					{
						switch (x)
						{
						case 0:
						{
							SendMessage(WisRadio4, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 1:
						{
							SendMessage(WisRadio8, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 2:
						{
							SendMessage(WisRadio12, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 3:
						{
							SendMessage(WisRadio16, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 4:
						{
							SendMessage(WisRadio20, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 5:
						{
							SendMessage(WisRadio24, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 6:
						{
							SendMessage(WisRadio28, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}

						}
						break;
					}
					case 5:
					{
						switch (x)
						{
						case 0:
						{
							SendMessage(ChaRadio4, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 1:
						{
							SendMessage(ChaRadio8, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 2:
						{
							SendMessage(ChaRadio12, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 3:
						{
							SendMessage(ChaRadio16, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 4:
						{
							SendMessage(ChaRadio20, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 5:
						{
							SendMessage(ChaRadio24, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}
						case 6:
						{
							SendMessage(ChaRadio28, BM_SETCHECK, BST_CHECKED, 1);
							break;
						}

						}
						break;
					}
				}
			}
		}



	for (int i = 0; i < 6; i++)
	{
		//Ability Value
		SelectObject(hdc, DefaultFont);
		OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		ss.str("");
		ss << "LevelUpTotal" << i;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTIABILITYWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		Width = static_cast<int>(Graphic->BaseWidth);
		Height = static_cast<int>(Graphic->BaseHeight);
		rc.left = X;
		rc.top = Y;
		rc.right = X + Width;
		rc.bottom = Y + Height;
		ClearRect(hdc, rc);
		ss.str("");
		if (Character.GetAbilityMod(static_cast<ABILITIES>(i), ABMOD_LEVELUP, 30) > 0)
			ss << "+";
		ss << Character.GetAbilityMod(static_cast<ABILITIES>(i), ABMOD_LEVELUP, 30);
		TextString = ss.str();
		if (TextString.size()>1)
			X -= 5;
		TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
		SetTextColor(hdc, OldColor);
	}
	ReleaseDC(MultiAbilityHandle, hdc);
}
//---------------------------------------------------------------------------
void MultiAbilityWindowClass::DrawCurrent()
{
	int Ability;
	int Modifier;
	int Cost;
	UIComponentManager *UIManager;
	UIManager = InterfaceManager.GetUIComponents();
	InterfaceGraphicStruct *Graphic;
	ostringstream ss;
	ostringstream vs;
	int X, Y;
	int Width, Height;
	COLORREF OldColor;
	HDC hdc;
	RECT rc;
	hdc = GetWindowDC(MultiAbilityHandle);
	string TextString, EraseString;
	EraseString = "  ";
	SelectObject(hdc, DefaultFont);
	SetBkMode(hdc, TRANSPARENT);
	for (int i = 0; i < 6; i++)
	{
	//Current Value
	SelectObject(hdc, DefaultFont);
	OldColor = SetTextColor(hdc, RGB(255, 255, 255));
	ss.str("");
	ss << "CurrentValue" << i;
	Graphic = UIManager->GetGraphicData(ss.str(), MULTIABILITYWINDOW);
	X = static_cast<int>(Graphic->BaseLocationX);
	Y = static_cast<int>(Graphic->BaseLocationY);
	Width = static_cast<int>(Graphic->BaseWidth);
	Height = static_cast<int>(Graphic->BaseHeight);
	rc.left = X;
	rc.top = Y;
	rc.right = X + Width;
	rc.bottom = Y + Height;
	ClearRect(hdc, rc);
	ss.str("");
	Ability = Character.GetAbility(i, CurrentLevel, true, false, false, false);
	ss << Ability;
	TextString = ss.str();
	if (TextString.size()>1)
		X -= 5;
	TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
	SetTextColor(hdc, OldColor);

	//Current Mod
	SelectObject(hdc, DefaultFont);
	OldColor = SetTextColor(hdc, RGB(255, 255, 255));
	ss.str("");
	ss << "ModValue" << i;
	Graphic = UIManager->GetGraphicData(ss.str(), MULTIABILITYWINDOW);
	X = static_cast<int>(Graphic->BaseLocationX);
	Y = static_cast<int>(Graphic->BaseLocationY);
	Width = static_cast<int>(Graphic->BaseWidth);
	Height = static_cast<int>(Graphic->BaseHeight);
	rc.left = X;
	rc.top = Y;
	rc.right = X + Width;
	rc.bottom = Y + Height;
	ClearRect(hdc, rc);
	ss.str("");
	Modifier = Data.CalculateAbilityModifier(Ability);
	if (Modifier > 0)
		ss << "+" << Modifier;
	else
		ss << Modifier;
	TextString = ss.str();
	if (TextString.size()>1)
		X -= 5;
	TextOut(hdc, X, Y, TextString.c_str(), TextString.size());
	SetTextColor(hdc, OldColor);
	}

	ReleaseDC(MultiAbilityHandle, hdc);
}
//---------------------------------------------------------------------------
void MultiAbilityWindowClass::DrawLevelBars()
{
	HDC hdc;

	hdc = GetWindowDC(MultiAbilityHandle);
	COLORREF OldColor;
	ostringstream ss;
	int X, Y;
	int Width, Height;
	//FeatDataClass *Feat;
	UIComponentManager *UIManager;
	InterfaceGraphicStruct *Graphic;
	//RECT Frame;
	int ButtonSpacing = 30;
	int feat;

	SetBkMode(hdc, TRANSPARENT);
	SetTextAlign(hdc, TA_CENTER);
	//InvalidateRect(MultiFeatHandle, NULL, FALSE);
	//UpdateWindow(MultiFeatHandle);
	UIManager = InterfaceManager.GetUIComponents();

	for (unsigned int i = 0; i < 30; i++)
	{
		ss.str("");
		ss << "AbilityLevelBar" << i + 1;
		Graphic = UIManager->GetGraphicData(ss.str(), MULTIABILITYWINDOW);
		X = static_cast<int>(Graphic->BaseLocationX);
		Y = static_cast<int>(Graphic->BaseLocationY);
		Width = static_cast<int>(Graphic->BaseWidth);
		Height = static_cast<int>(Graphic->BaseHeight);

		if (CurrentLevel == i + 1)
			DrawGraphic(hdc, &GreenLevelBox, X, Y, Width, Height);
		else
			DrawGraphic(hdc, &BlueLevelBox, X, Y, Width, Height);

	

		OldColor = SetTextColor(hdc, RGB(255, 255, 255));
		ss.str("");
		ss << "L" << i + 1;
		TextOut(hdc, X + 20, Y + 6, ss.str().c_str(), ss.str().size());
		SetTextColor(hdc, OldColor);
	}
	SetTextAlign(hdc, TA_LEFT);
	ReleaseDC(MultiAbilityHandle, hdc);
}
//---------------------------------------------------------------------------
void MultiAbilityWindowClass::LoadGraphics(HWND Parent)
{
	HDC hdc;

	//palette for halftone work
	hdc = GetDC(Parent);
	Palette = CreateHalftonePalette(hdc);
	ReleaseDC(Parent, hdc);

	//The Plus Minus
	LoadBitmap("MinusBox", "UserInterface", &Minus);
	LoadBitmap("PlusBox", "UserInterface", &Plus);
	LoadBitmap("LevelBoxBlue", "UserInterface", &BlueLevelBox);
	LoadBitmap("LevelBoxGreen", "UserInterface", &GreenLevelBox);


}
//---------------------------------------------------------------------------
long MultiAbilityWindowClass::HandleWindowsMessage(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	int pos;
	POINTS ps;
	POINT ps1;
	pos = GetMessagePos();
	ps = MAKEPOINTS(pos);
	ps1.x = ps.x;
	ps1.y = ps.y;
	ScreenToClient(MultiAbilityHandle, (LPPOINT)&ps1);

	switch (Message)
	{
	case WM_COMMAND:
	{
		if (HIWORD(wParam) == BN_CLICKED)
		{
			//if ((int)LOWORD(wParam) == MAB_ACCEPT)
			//{
			//	InterfaceManager.ShowChild(MULTIABILITYWINDOW, false);
			//	return 0;
			//}
			if ((int)LOWORD(wParam) == MAB_CLOSE)
			{
				InterfaceManager.ShowChild(MULTIABILITYWINDOW, false);
				return 0;
				break;
			}
			if ((int)LOWORD(wParam) == MAB_4STR || (int)LOWORD(wParam) == MAB_4DEX || (int)LOWORD(wParam) == MAB_4CON || (int)LOWORD(wParam) == MAB_4INT ||
				(int)LOWORD(wParam) == MAB_4WIS || (int)LOWORD(wParam) == MAB_4CHA || (int)LOWORD(wParam) == MAB_8STR || (int)LOWORD(wParam) == MAB_8DEX ||
				(int)LOWORD(wParam) == MAB_8CON || (int)LOWORD(wParam) == MAB_8INT || (int)LOWORD(wParam) == MAB_8WIS || (int)LOWORD(wParam) == MAB_8CHA ||
				(int)LOWORD(wParam) == MAB_12STR || (int)LOWORD(wParam) == MAB_12DEX || (int)LOWORD(wParam) == MAB_12CON || (int)LOWORD(wParam) == MAB_12INT ||
				(int)LOWORD(wParam) == MAB_12WIS || (int)LOWORD(wParam) == MAB_12CHA || (int)LOWORD(wParam) == MAB_16STR || (int)LOWORD(wParam) == MAB_16DEX ||
				(int)LOWORD(wParam) == MAB_16CON || (int)LOWORD(wParam) == MAB_16INT || (int)LOWORD(wParam) == MAB_16WIS || (int)LOWORD(wParam) == MAB_16CHA ||
				(int)LOWORD(wParam) == MAB_20STR || (int)LOWORD(wParam) == MAB_20DEX || (int)LOWORD(wParam) == MAB_20CON || (int)LOWORD(wParam) == MAB_20INT ||
				(int)LOWORD(wParam) == MAB_20WIS || (int)LOWORD(wParam) == MAB_20CHA || (int)LOWORD(wParam) == MAB_24STR || (int)LOWORD(wParam) == MAB_24DEX ||
				(int)LOWORD(wParam) == MAB_24CON || (int)LOWORD(wParam) == MAB_24INT || (int)LOWORD(wParam) == MAB_24WIS || (int)LOWORD(wParam) == MAB_24CHA ||
				(int)LOWORD(wParam) == MAB_28STR || (int)LOWORD(wParam) == MAB_28DEX || (int)LOWORD(wParam) == MAB_28CON || (int)LOWORD(wParam) == MAB_28INT ||
				(int)LOWORD(wParam) == MAB_28WIS || (int)LOWORD(wParam) == MAB_28CHA)
			{
				LevelUpAbility(wParam);
				DrawLevelUp();
				DrawCurrent();
				return 0;
				break;
			}

		}
	}
	case WM_CTLCOLORSTATIC:
	{

		SetBkMode((HDC)wParam, TRANSPARENT);
		if ((HWND)lParam == CreationStr || (HWND)lParam == CreationDex || (HWND)lParam == CreationCon ||
			(HWND)lParam == CreationInt || (HWND)lParam == CreationWis || (HWND)lParam == CreationCha ||
			(HWND)lParam == LevelUpStr || (HWND)lParam == LevelUpDex || (HWND)lParam == LevelUpCon ||
			(HWND)lParam == LevelUpInt || (HWND)lParam == LevelUpWis || (HWND)lParam == LevelUpCha ||
			(HWND)lParam == CurrentStr || (HWND)lParam == CurrentDex || (HWND)lParam == CurrentCon ||
			(HWND)lParam == CurrentInt || (HWND)lParam == CurrentWis || (HWND)lParam == CurrentCha)
		{
			SetTextColor((HDC)wParam, RGB(230, 230, 30));
		}
		else
		{
			SetTextColor((HDC)wParam, RGB(255, 255, 255));
		}



		return (long)GetStockObject(DKGRAY_BRUSH);
		break;
	}
	default:
	{
		return DefWindowProc(Wnd, Message, wParam, lParam);
	}
	}
}
//---------------------------------------------------------------------------
void MultiAbilityWindowClass::LevelUpAbility(int Button)
{
	int LevelUpLevel[7] = { 4, 8, 12, 16, 20, 24, 28 };
	int CurrentAbility, CurrentLevel;
	CurrentAbility = -1;
	CurrentLevel = -1;
	for (int i = 0; i < 6; i++)
	{
		for( int x = 0; x < 7; x++)
			{
				if (RadioButtonID[i][x] == Button)
				{
					CurrentAbility = i;
					CurrentLevel = LevelUpLevel[x];
					break;
				}
			}
	}

	if (CurrentAbility != -1 && CurrentLevel != -1)
	{
		Character.SetAbilityIncrease(CurrentLevel, static_cast<ABILITIES>(CurrentAbility));
	}

}
void MultiAbilityWindowClass::ClearRect(HDC hdc, RECT rc)
{

	LOGBRUSH lb;

	GetObject(GetStockObject(DKGRAY_BRUSH), sizeof(LOGBRUSH), &lb);
	HBRUSH hbrBkGnd = CreateSolidBrush(lb.lbColor);
	rc.top -= 3;
	rc.left -= 7;
	rc.right += 7;
	rc.bottom += 3;
	FillRect(hdc, &rc, hbrBkGnd);
	DeleteObject(hbrBkGnd);
}
//---------------------------------------------------------------------------
HWND MultiAbilityWindowClass::GetHandle()
{
	return MultiAbilityHandle;
}
