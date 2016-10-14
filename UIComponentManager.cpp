#include "UIComponentManager.h"
#include "DataClass.h"

//---------------------------------------------------------------------------
UIComponentManager::UIComponentManager()
	{
	}

//---------------------------------------------------------------------------
UIComponentManager::~UIComponentManager()
	{
	}

//---------------------------------------------------------------------------
void UIComponentManager::InitializeUI()
	{
		int currentX = 0;
		int currentY = 0;
	//*************The Main Screen Windows***************

	//Menu Bar
	int MenuBarX = 5;
	int MenuBarY = 2;
	int MenuButtonW = 84;
	int MenuButtonH = 18;
	int MenuButtonIncX = 85;
	string ComponentName;
	string GraphicName;

	InitializeUIComponent("LoadButton", MAINWINDOW, "BUTTON", "Load", WS_CHILD | BS_PUSHBUTTON, MenuBarX + MenuButtonIncX * 0, MenuBarY, MenuButtonW, MenuButtonH, MS_LOADBUTTON);
	InitializeUIComponent("SaveButton", MAINWINDOW, "BUTTON", "Save", WS_CHILD | BS_PUSHBUTTON, MenuBarX + MenuButtonIncX * 1, MenuBarY, MenuButtonW, MenuButtonH, MS_SAVEBUTTON);
	InitializeUIComponent("PrintButton", MAINWINDOW, "BUTTON", "Print", WS_CHILD | BS_PUSHBUTTON, MenuBarX + MenuButtonIncX * 2, MenuBarY, MenuButtonW, MenuButtonH, MS_PRINTBUTTON);
	InitializeUIComponent("ForumExportButton", MAINWINDOW, "BUTTON", "Forum Exp", WS_CHILD | BS_PUSHBUTTON, MenuBarX + MenuButtonIncX * 3, MenuBarY, MenuButtonW, MenuButtonH, MS_FORUMEXPORTBUTTON);
	InitializeUIComponent("ClearButton", MAINWINDOW, "BUTTON", "Clear", WS_CHILD | BS_PUSHBUTTON, MenuBarX + MenuButtonIncX * 4, MenuBarY, MenuButtonW, MenuButtonH, MS_CLEARBUTTON);
	InitializeUIComponent("ItemBuilderButton", MAINWINDOW, "BUTTON", "Item Builder", WS_CHILD | BS_PUSHBUTTON, MenuBarX + MenuButtonIncX * 5, MenuBarY, MenuButtonW, MenuButtonH, MS_ITEMBUILDERBUTTON);
	InitializeUIComponent("EquipmentScreenButton", MAINWINDOW, "BUTTON", "Equipment", WS_CHILD | BS_PUSHBUTTON, MenuBarX + MenuButtonIncX * 6, MenuBarY, MenuButtonW, MenuButtonH, MS_EQUIPMENTSCREENBUTTON);
	InitializeUIComponent("DisplayErrorsButton", MAINWINDOW, "BUTTON", "Show Err", WS_CHILD | BS_PUSHBUTTON | WS_DISABLED, MenuBarX + MenuButtonIncX * 7, MenuBarY, MenuButtonW, MenuButtonH, MS_DISPLAYERRORBUTTON);

	InitializeUIComponent("QuitButton", MAINWINDOW, "BUTTON", "Quit", WS_CHILD | BS_PUSHBUTTON, MenuBarX + MenuButtonIncX * 10, MenuBarY, MenuButtonW, MenuButtonH, MS_QUITBUTTON);
	InitializeUIComponent("AboutButton", MAINWINDOW, "BUTTON", "About", WS_CHILD | BS_PUSHBUTTON, MenuBarX + MenuButtonIncX * 11, MenuBarY, MenuButtonW, MenuButtonH, MS_ABOUTBUTTON);
	InitializeUIComponent("NameLabel", MAINWINDOW, "STATIC", "Name Label", WS_CHILD, MenuBarX, MenuBarY+23, 585, 20, MS_NAMELABEL);
	InitializeUIComponent("RaceClassLabel", MAINWINDOW, "STATIC", "RaceClass Label", WS_CHILD, MenuBarX, MenuBarY+41, 585, 20, MS_RACECLASSLABEL);


	//side Menu
	int sideMenuX = 893;
	int sideMenuY = 305;
	int sideMenuIncX = 130;
	int sideMenuIncY = 24;
	currentX = sideMenuX;
	currentY = sideMenuY;
	int sideMenuButonWidth = 120;
	int sideMenuButtonHt = 20;
	InitializeUIComponent("SideMenuTitle", MAINWINDOW, "STATIC", "Edit Buttons", WS_CHILD | BS_PUSHBUTTON, currentX, currentY, sideMenuButonWidth, sideMenuButtonHt, MS_SIDEMENUTITLE);
	currentY += sideMenuIncY;
	InitializeUIComponent("NameAndAlignmentButton", MAINWINDOW, "BUTTON", "Name and Align", WS_CHILD | BS_PUSHBUTTON, currentX, currentY, sideMenuButonWidth, sideMenuButtonHt, MS_NAMEANDALIGNMENTBUTTON);
	currentY += sideMenuIncY;
	InitializeUIComponent("SideReincarnationButton", MAINWINDOW, "BUTTON", "Past Lives", WS_CHILD | BS_PUSHBUTTON, currentX, currentY, sideMenuButonWidth, sideMenuButtonHt, MS_SIDEREINCARNATION);
	currentY += sideMenuIncY;
	InitializeUIComponent("SideRaceSexButton", MAINWINDOW, "BUTTON", "Race and Sex", WS_CHILD | BS_PUSHBUTTON, currentX, currentY, sideMenuButonWidth, sideMenuButtonHt, MS_SIDERACESEX);
	currentY += sideMenuIncY;
	InitializeUIComponent("SideClassButton", MAINWINDOW, "BUTTON", "Class", WS_CHILD | BS_PUSHBUTTON, currentX, currentY, sideMenuButonWidth, sideMenuButtonHt, MS_SIDECLASS);
	currentY += sideMenuIncY;
	InitializeUIComponent("SideAbilityButton", MAINWINDOW, "BUTTON", "Ability", WS_CHILD | BS_PUSHBUTTON, currentX, currentY, sideMenuButonWidth, sideMenuButtonHt, MS_SIDEABILITY);
	currentY += sideMenuIncY;
	InitializeUIComponent("SideSkillButton", MAINWINDOW, "BUTTON", "Skills", WS_CHILD | BS_PUSHBUTTON, currentX, currentY, sideMenuButonWidth, sideMenuButtonHt, MS_SIDESKILL);
	currentY += sideMenuIncY;
	InitializeUIComponent("SideSpellButton", MAINWINDOW, "BUTTON", "Spells", WS_CHILD | BS_PUSHBUTTON, currentX, currentY, sideMenuButonWidth, sideMenuButtonHt, MS_SIDESPELL);
	currentY += sideMenuIncY;
	InitializeUIComponent("SideFeatsButton", MAINWINDOW, "BUTTON", "Feats", WS_CHILD | BS_PUSHBUTTON, currentX, currentY, sideMenuButonWidth, sideMenuButtonHt, MS_SIDEFEATS);
	currentY += sideMenuIncY;
	InitializeUIComponent("SideEnhancementButton", MAINWINDOW, "BUTTON", "Enhancements", WS_CHILD | BS_PUSHBUTTON, currentX, currentY, sideMenuButonWidth, sideMenuButtonHt, MS_SIDEENHANCEMENTS);
	currentY += sideMenuIncY;
	InitializeUIComponent("SideDestinyButton", MAINWINDOW, "BUTTON", "Destiny", WS_CHILD | BS_PUSHBUTTON, currentX, currentY, sideMenuButonWidth, sideMenuButtonHt, MS_SIDEDESTINY);




    //the ability box
	int abilityboxX = 5;
	int abilityboxY = 68;
	InitializeUIComponent("AbilityBoxFrame", MAINWINDOW, "STATIC", "", WS_CHILD | SS_GRAYFRAME, abilityboxX, abilityboxY, 290, 205, MS_ABILITYBOXFRAME);
	InitializeUIComponent("AbilityLabel", MAINWINDOW, "STATIC", "Ability", WS_CHILD | SS_CENTER, abilityboxX + 85, abilityboxY+5, 70, 20, MS_ABILITYLABEL);
	InitializeUIComponent("AbilityModifierLabel", MAINWINDOW, "STATIC", "Modifier", WS_CHILD | SS_CENTER, abilityboxX + 185, abilityboxY+5, 70, 20, MS_ABILITYMODIFIERLABEL);
	InitializeUIComponent("StrLabel", MAINWINDOW, "STATIC", "STR", WS_CHILD | SS_CENTER, abilityboxX + 5, abilityboxY+20, 60, 20, MS_STRLABEL);
	InitializeUIComponent("StrLabel2", MAINWINDOW, "STATIC", "STRENGTH", WS_CHILD | SS_CENTER, abilityboxX + 5, abilityboxY+37, 60, 10, MS_STRLABEL2);
	InitializeUIComponent("DexLabel", MAINWINDOW, "STATIC", "DEX", WS_CHILD | SS_CENTER, abilityboxX + 5, abilityboxY+50, 60, 20, MS_DEXLABEL);
	InitializeUIComponent("DexLabel2", MAINWINDOW, "STATIC", "DEXTERITY", WS_CHILD | SS_CENTER, abilityboxX + 5, abilityboxY+67, 60, 10, MS_DEXLABEL2);
	InitializeUIComponent("ConLabel", MAINWINDOW, "STATIC", "CON", WS_CHILD | SS_CENTER, abilityboxX + 5, abilityboxY+80, 60, 20, MS_CONLABEL);
	InitializeUIComponent("ConLabel2", MAINWINDOW, "STATIC", "CONSTITUTION", WS_CHILD | SS_CENTER, abilityboxX + 5, abilityboxY+97, 60, 10, MS_CONLABEL2);
	InitializeUIComponent("IntLabel", MAINWINDOW, "STATIC", "INT", WS_CHILD | SS_CENTER, abilityboxX + 5, abilityboxY+110, 60, 20, MS_INTLABEL);
	InitializeUIComponent("IntLabel2", MAINWINDOW, "STATIC", "INTELLIGENCE", WS_CHILD | SS_CENTER, abilityboxX + 5, abilityboxY+127, 60, 10, MS_INTLABEL2);
	InitializeUIComponent("WisLabel", MAINWINDOW, "STATIC", "WIS", WS_CHILD | SS_CENTER, abilityboxX + 5, abilityboxY+140, 60, 20, MS_WISLABEL);
	InitializeUIComponent("WisLabel2", MAINWINDOW, "STATIC", "WISDOM", WS_CHILD | SS_CENTER, abilityboxX + 5, abilityboxY+157, 60, 10, MS_WISLABEL2);
	InitializeUIComponent("ChaLabel", MAINWINDOW, "STATIC", "CHA", WS_CHILD | SS_CENTER, abilityboxX + 5, abilityboxY+170, 60, 20, MS_CHALABEL);
	InitializeUIComponent("ChaLabel2", MAINWINDOW, "STATIC", "CHARISMA", WS_CHILD | SS_CENTER, abilityboxX + 5, abilityboxY+187, 60, 10, MS_CHALABEL2);
	InitializeUIComponent("StrNumber", MAINWINDOW, "STATIC", "8", WS_CHILD | SS_CENTER, abilityboxX + 90, abilityboxY+25, 70, 20, MS_STRNUMBER);
	InitializeUIComponent("DexNumber", MAINWINDOW, "STATIC", "8", WS_CHILD | SS_CENTER, abilityboxX + 90, abilityboxY+55, 70, 20, MS_DEXNUMBER);
	InitializeUIComponent("ConNumber", MAINWINDOW, "STATIC", "8", WS_CHILD | SS_CENTER, abilityboxX + 90, abilityboxY+85, 70, 20, MS_CONNUMBER);
	InitializeUIComponent("IntNumber", MAINWINDOW, "STATIC", "8", WS_CHILD | SS_CENTER, abilityboxX + 90, abilityboxY+115, 70, 20, MS_INTNUMBER);
	InitializeUIComponent("WisNumber", MAINWINDOW, "STATIC", "8", WS_CHILD | SS_CENTER, abilityboxX + 90, abilityboxY+145, 70, 20, MS_WISNUMBER);
	InitializeUIComponent("ChaNumber", MAINWINDOW, "STATIC", "8", WS_CHILD | SS_CENTER, abilityboxX + 90, abilityboxY+175, 70, 20, MS_CHANUMBER);
	InitializeUIComponent("StrModifier", MAINWINDOW, "STATIC", "+8", WS_CHILD | SS_CENTER, abilityboxX + 190, abilityboxY+25, 70, 20, MS_STRMODIFIER);
	InitializeUIComponent("DexModifier", MAINWINDOW, "STATIC", "+8", WS_CHILD | SS_CENTER, abilityboxX + 190, abilityboxY+55, 70, 20, MS_DEXMODIFIER);
	InitializeUIComponent("ConModifier", MAINWINDOW, "STATIC", "+8", WS_CHILD | SS_CENTER, abilityboxX + 190, abilityboxY+85, 70, 20, MS_CONMODIFIER);
	InitializeUIComponent("IntModifier", MAINWINDOW, "STATIC", "+8", WS_CHILD | SS_CENTER, abilityboxX + 190, abilityboxY+115, 70, 20, MS_INTMODIFIER);
	InitializeUIComponent("WisModifier", MAINWINDOW, "STATIC", "+8", WS_CHILD | SS_CENTER, abilityboxX + 190, abilityboxY+145, 70, 20, MS_WISMODIFIER);
	InitializeUIComponent("ChaModifier", MAINWINDOW, "STATIC", "+8", WS_CHILD | SS_CENTER, abilityboxX + 190, abilityboxY+175, 70, 20, MS_CHAMODIFIER);

    //the ability statistics box
	int AbilityStatboxX = 300;
	int AbilityStatboxY = 68;
	InitializeUIComponent("AbilityStatBoxFrame", MAINWINDOW, "STATIC", "", WS_CHILD | SS_GRAYFRAME, AbilityStatboxX, AbilityStatboxY, 290, 205, MS_ABILITYSTATBOXFRAME);
	InitializeUIComponent("AbilityStatBox", MAINWINDOW, "LISTBOX", "Ability Statbox", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS, AbilityStatboxX + 5, AbilityStatboxY + 5, 280, 195, MS_ABILITYSTATBOX);


    //the skill box
	int SkillBoxX = 5;
	int SkillBoxY = 278;
	InitializeUIComponent("SkillBoxFrame", MAINWINDOW, "STATIC", "", WS_CHILD | SS_GRAYFRAME, SkillBoxX, SkillBoxY, 290, 480, MS_SKILLBOXFRAME);
	InitializeUIComponent("SkillTitle", MAINWINDOW, "STATIC", "Skill", WS_CHILD, SkillBoxX + 5, SkillBoxY+5, 90, 25, MS_SKILLTITLE);
	InitializeUIComponent("KeyAbilityTitle", MAINWINDOW, "STATIC", "Mod", WS_CHILD | SS_CENTER, SkillBoxX + 120, SkillBoxY+5, 30, 33, MS_KEYABILITYTITLE);
	InitializeUIComponent("TotalModTitle", MAINWINDOW, "STATIC", "Tot", WS_CHILD | SS_CENTER, SkillBoxX + 162, SkillBoxY+5, 30, 30, MS_TOTALMODTITLE);
	InitializeUIComponent("AbilityModTitle", MAINWINDOW, "STATIC", "Abil", WS_CHILD | SS_CENTER, SkillBoxX + 200, SkillBoxY+5, 30, 30, MS_ABILITYMODTITLE);
	InitializeUIComponent("MiscModTitle", MAINWINDOW, "STATIC", "Misc", WS_CHILD | SS_CENTER, SkillBoxX + 232, SkillBoxY+5, 30, 30, MS_MISCMODTITLE);
	InitializeUIComponent("SkillsList", MAINWINDOW, "LISTBOX", "Skill", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED, SkillBoxX + 5, SkillBoxY+40, 280, 425, MS_SKILLSLIST);

	//Known Item boxs
	int KnownBaseX = 300;
	int KnownBaseY = 278;
	int ButtonSize = 72;
	int ButtonSpacing = 73;
	int CurrentX = KnownBaseX;
	int CurrentY = KnownBaseY;
	int KnownFrameWidth = 290;
	int KnownFrameHight = 457;
	InitializeUIComponent("FeatsPanelButton", MAINWINDOW, "BUTTON", "Feats", WS_CHILD | BS_PUSHBUTTON, CurrentX, CurrentY, ButtonSize, 18, MS_FEATSPANELBUTTON);
	CurrentX += ButtonSpacing;
	InitializeUIComponent("SpellsPanelButton", MAINWINDOW, "BUTTON", "Spells", WS_CHILD | BS_PUSHBUTTON, CurrentX, CurrentY, ButtonSize, 18, MS_SPELLSPANELBUTTON);
	CurrentX += ButtonSpacing;
	InitializeUIComponent("EnhPanelButton", MAINWINDOW, "BUTTON", "Enhncmnt", WS_CHILD | BS_PUSHBUTTON, CurrentX, CurrentY, ButtonSize, 18, MS_ENHPANELBUTTON);
	CurrentX += ButtonSpacing;
	InitializeUIComponent("DestinyPanelButton", MAINWINDOW, "BUTTON", "Destinies", WS_CHILD | BS_PUSHBUTTON, CurrentX, CurrentY, ButtonSize, 18, MS_DESTINYPANELBUTTON);



    //the feat list box
	int FeatBoxX = KnownBaseX;
	int FeatBoxY = KnownBaseY+23;
	InitializeUIComponent("FeatBoxFrame", MAINWINDOW, "STATIC", "", WS_CHILD | SS_GRAYFRAME, FeatBoxX, FeatBoxY, KnownFrameWidth, KnownFrameHight, MS_FEATBOXFRAME);
	InitializeUIComponent("FeatListTitle", MAINWINDOW, "STATIC", "Known Feats", WS_CHILD, FeatBoxX + 5, FeatBoxY+5, 100, 20, MS_FEATLISTLABEL);
	InitializeUIComponent("FeatList", MAINWINDOW, "LISTBOX", "Feat List", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED, FeatBoxX + 5, FeatBoxY + 25, KnownFrameWidth - 10, KnownFrameHight-30, MS_FEATSLIST);

	//the enhancement list box
	int EnhBoxX = KnownBaseX;
	int EnhBoxY = KnownBaseY + 23;
	InitializeUIComponent("EnhancementBoxFrame", MAINWINDOW, "STATIC", "", WS_CHILD | SS_GRAYFRAME, EnhBoxX, EnhBoxY, KnownFrameWidth, KnownFrameHight, MS_ENHANCEMENTBOXFRAME);
	InitializeUIComponent("EnhancementTitle", MAINWINDOW, "STATIC", "Known Enhancements", WS_CHILD, EnhBoxX + 5, EnhBoxY+5, 200, 20, MS_ENHANCEMENTLABEL);
	InitializeUIComponent("EnhancementList", MAINWINDOW, "LISTBOX", "Enhancement List", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED, EnhBoxX + 5, EnhBoxY + 25, KnownFrameWidth - 10, KnownFrameHight - 30, MS_ENHANCEMENTLIST);

	//the spell box
	int SpellBoxX = KnownBaseX;
	int SpellBoxY = KnownBaseY + 23;
	InitializeUIComponent("SpellBoxFrame", MAINWINDOW, "STATIC", "", WS_CHILD | SS_GRAYFRAME, SpellBoxX, SpellBoxY, KnownFrameWidth, KnownFrameHight, MS_SPELLBOXFRAME);
	InitializeUIComponent("SpellBoxTitle", MAINWINDOW, "STATIC", "Known Spells", WS_CHILD, SpellBoxX + 5, SpellBoxY+5, 100, 20, MS_SPELLBOXLABEL);
	InitializeUIComponent("SpellList", MAINWINDOW, "LISTBOX", "Spell List", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED, SpellBoxX + 5, SpellBoxY + 25, KnownFrameWidth - 10, KnownFrameHight - 30, MS_SPELLLIST);

	//the Destiny box
	int DestinyBoxX = KnownBaseX;
	int DestinyBoxY = KnownBaseY + 23;
	InitializeUIComponent("DestinyBoxFrame", MAINWINDOW, "STATIC", "", WS_CHILD | SS_GRAYFRAME, DestinyBoxX, DestinyBoxY, KnownFrameWidth, KnownFrameHight, MS_SPELLBOXFRAME);
	InitializeUIComponent("DestinyBoxTitle", MAINWINDOW, "STATIC", "Current Destiny", WS_CHILD, DestinyBoxX + 5, DestinyBoxY + 5, 100, 20, MS_SPELLBOXLABEL);
	InitializeUIComponent("DestinyList", MAINWINDOW, "LISTBOX", "Destiny List", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED, DestinyBoxX + 5, DestinyBoxY + 25, KnownFrameWidth - 10, KnownFrameHight - 30, MS_SPELLLIST);

	//the instruction list box
	int InstructionBoxX = 595;
	int InstructionBoxY = 68;
	InitializeUIComponent("InstructionWindowFrame", MAINWINDOW, "STATIC", "", WS_CHILD | SS_GRAYFRAME, InstructionBoxX, InstructionBoxY, 290, 165, MS_INSTRUCTIONWINDOWFRAME);
	InitializeUIComponent("InstructionWindowTitle", MAINWINDOW, "STATIC", "Level 1 Human Fighter", WS_CHILD, InstructionBoxX + 5, InstructionBoxY + 5, 280, 20, MS_IW_TITLE);
	InitializeUIComponent("InstructionWindowList", MAINWINDOW, "RichEdit", "RichEdit", WS_CHILD | WS_VSCROLL | ES_MULTILINE | ES_READONLY, InstructionBoxX + 5, InstructionBoxY + 23, 280, 140, MS_IW_LIST);

    //the description box
	int DescBoxX = 595;
	int DescBoxY = 573;
	InitializeUIComponent("DescriptionWindow", MAINWINDOW, "RichEdit", "RichEdit", WS_CHILD | WS_VSCROLL | WS_BORDER | ES_MULTILINE | ES_READONLY, DescBoxX, DescBoxY, 410, 185, MS_DESCRIPTIONWINDOW);

    //equipment select box
    InitializeUIComponent("EquipmentDisplayTitle", MAINWINDOW, "STATIC", "Generic Armor Selection", WS_CHILD, 310, 350, 270, 20, MS_ED_TITLE);
    InitializeUIComponent("EquipmentDisplaySelectList", MAINWINDOW, "LISTBOX", "Armor", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, 310, 370, 270, 155, MS_EQUIPMENTDISPLAYSELECTLIST);
	
	//additional Stats items
	InitializeUIComponent("AdditionalStatsTitle", MAINWINDOW, "STATIC", "Additional Unbuffed Stats", WS_CHILD, 310, 45, 270, 20, MS_AS_TITLE);
    InitializeUIComponent("AdditionalStatsList", MAINWINDOW, "LISTBOX", "Additional Stats List", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED, 305, 65, 280, 270, MS_ASLIST);

	//heroic or epic level select buttons
    InitializeUIComponent("HeroicLevelRadio", MAINWINDOW, "BUTTON", "Heroic", WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 750, 30, 70, 18, MS_HEROICLEVELRADIO);
    InitializeUIComponent("EpicLevelRadio", MAINWINDOW, "BUTTON", "Epic", WS_CHILD | BS_AUTORADIOBUTTON, 880, 30, 70, 18, MS_EPICLEVELRADIO);


	//*************The Main Screen Graphics***************

	//Level Bars

	int LevelBarX = 887;
	int LevelBarY = 25;
	int LevelBarXinc = 46;
	int LevelBarYinc = 28;
	CurrentX = LevelBarX;
	CurrentY = LevelBarY;
	for (int i = 1; i <= 30; i+=1)
	{	
		GraphicName = "LevelBar" + to_string(i);
		InitializeUIGraphic(GraphicName, MAINWINDOW, CurrentX, CurrentY, 40, 25);
		if (i % 10 == 0)
		{
			CurrentX += LevelBarXinc;
			CurrentY = LevelBarY;
		}
		else
		{
			CurrentY += LevelBarYinc;
		}
	}

	//AdvancementBox
	//the advancement box
	int AdvBoxX = 595;
	int AdvBoxY = 238;
	InitializeUIComponent("AdvancementWindowFrame", MAINWINDOW, "STATIC", "", WS_CHILD | SS_GRAYFRAME, AdvBoxX, AdvBoxY, 290, 330, MS_ADVANCEMENTWINDOWFRAME);


	//Race Advancement Box 
	int RaceBaseX = AdvBoxX+5;
	int RaceBaseY = AdvBoxY+5;

	int AdvBoxCurrentX = RaceBaseX;
	int AdvBoxCurrentY = RaceBaseY;
	int AdvBoxShiftY = 40;
	int AdvBoxShiftX = 140;

	InitializeUIComponent("HeroicClassRadio", MAINWINDOW, "BUTTON", "Heroic Class", WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, AdvBoxCurrentX + 17, AdvBoxCurrentY, 110, 18, MS_HEROICCLASS);
	InitializeUIComponent("IconicClassRadio", MAINWINDOW, "BUTTON", "Iconic Class", WS_CHILD | BS_AUTORADIOBUTTON, AdvBoxCurrentX + 158, AdvBoxCurrentY, 110, 18, MS_ICONICCLASS);

	AdvBoxCurrentY += 30;

	InitializeUIGraphic("MaleOn", MAINWINDOW, AdvBoxCurrentX + 22, AdvBoxCurrentY, 90, 40);
	InitializeUIGraphic("MaleOff", MAINWINDOW, AdvBoxCurrentX + 22, AdvBoxCurrentY, 90, 40);
	InitializeUIGraphic("FemaleOn", MAINWINDOW, AdvBoxCurrentX + 162, AdvBoxCurrentY, 90, 40);
	InitializeUIGraphic("FemaleOff", MAINWINDOW, AdvBoxCurrentX + 162, AdvBoxCurrentY, 90, 40);

	AdvBoxCurrentY += 55;

	InitializeUIGraphic("MaleHumanOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("MaleHumanOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("FemaleHumanOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("FemaleHumanOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	
	AdvBoxCurrentY += AdvBoxShiftY;

	InitializeUIGraphic("MaleElfOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("MaleElfOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("FemaleElfOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("FemaleElfOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);

	AdvBoxCurrentY += AdvBoxShiftY;

	InitializeUIGraphic("MaleHalflingOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("MaleHalflingOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("FemaleHalflingOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("FemaleHalflingOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);

	AdvBoxCurrentY += AdvBoxShiftY;

	InitializeUIGraphic("MaleDwarfOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("MaleDwarfOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("FemaleDwarfOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("FemaleDwarfOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);

	AdvBoxCurrentY += AdvBoxShiftY;

	InitializeUIGraphic("MaleWarforgedOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("MaleWarforgedOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("FemaleWarforgedOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("FemaleWarforgedOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);

	AdvBoxCurrentY = RaceBaseY+85;
	AdvBoxCurrentX += AdvBoxShiftX;

	InitializeUIGraphic("MaleHalfelfOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("MaleHalfelfOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("FemaleHalfelfOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("FemaleHalfelfOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);

	AdvBoxCurrentY += AdvBoxShiftY;

	InitializeUIGraphic("MaleDrowOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("MaleDrowOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("FemaleDrowOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("FemaleDrowOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);

	AdvBoxCurrentY += AdvBoxShiftY;

	InitializeUIGraphic("MaleHalforcOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("MaleHalforcOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("FemaleHalforcOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("FemaleHalforcOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);

	AdvBoxCurrentY += AdvBoxShiftY;

	InitializeUIGraphic("MaleGnomeOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("MaleGnomeOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("FemaleGnomeOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);
	InitializeUIGraphic("FemaleGnomeOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 135, 35);


	//iconics Advancement Panel

	AdvBoxCurrentY = RaceBaseY+85;
	AdvBoxCurrentX = RaceBaseX;


	InitializeUIGraphic("MaleBladeforgedOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);
	InitializeUIGraphic("MaleBladeforgedOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);
	InitializeUIGraphic("FemaleBladeforgedOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);
	InitializeUIGraphic("FemaleBladeforgedOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);

	AdvBoxCurrentY += AdvBoxShiftY;

	InitializeUIGraphic("MaleMorninglordOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);
	InitializeUIGraphic("MaleMorninglordOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);
	InitializeUIGraphic("FemaleMorninglordOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);
	InitializeUIGraphic("FemaleMorninglordOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);

	AdvBoxCurrentY += AdvBoxShiftY;

	InitializeUIGraphic("MalePurpleDragonKnightOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);
	InitializeUIGraphic("MalePurpleDragonKnightOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);
	InitializeUIGraphic("FemalePurpleDragonKnightOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);
	InitializeUIGraphic("FemalePurpleDragonKnightOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);

	AdvBoxCurrentY += AdvBoxShiftY;

	InitializeUIGraphic("MaleShadarKaiOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);
	InitializeUIGraphic("MaleShadarKaiOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);
	InitializeUIGraphic("FemaleShadarKaiOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);
	InitializeUIGraphic("FemaleShadarKaiOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);

	AdvBoxCurrentY += AdvBoxShiftY;

	InitializeUIGraphic("MaleDeepGnomeOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);
	InitializeUIGraphic("MaleDeepGnomeOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);
	InitializeUIGraphic("FemaleDeepGnomeOn", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);
	InitializeUIGraphic("FemaleDeepGnomeOff", MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 124, 35);


	//Classes Advancement Panel
	int ClassBaseX = AdvBoxX + 5;
	int ClassBaseY = AdvBoxY + 5;

	AdvBoxCurrentX = ClassBaseX;
	AdvBoxCurrentY = ClassBaseY;
	AdvBoxShiftY = 80;
	AdvBoxShiftX = 70;
	for (int i = 1; i <= NUMCLASSES; i += 1)
	{
		GraphicName = "ClassSlot" + to_string(i);
		InitializeUIGraphic(GraphicName, MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 70, 70);
		if (i % 4 == 0)
		{
			
			AdvBoxCurrentY += AdvBoxShiftY;
			AdvBoxCurrentX = ClassBaseX;
		}
		else
		{
			AdvBoxCurrentX += AdvBoxShiftX;
		}
	}
// Name and Alignment Advancement Panel

	int AlignmentBaseX = AdvBoxX + 10;
	int AlignmentBaseY = AdvBoxY+5;
	InitializeUIGraphic("FirstNameText", MAINWINDOW, AlignmentBaseX, AlignmentBaseY, 0, 0);
	InitializeUIComponent("AdvWinFirstNameInput", MAINWINDOW, "EDIT", "", WS_CHILD | WS_BORDER, AlignmentBaseX + 20, AlignmentBaseY+20, 200, 25, MS_ADVWINFIRSTNAMEINPUT);
	AlignmentBaseY += 50;
	InitializeUIGraphic("SurnameText", MAINWINDOW, AlignmentBaseX, AlignmentBaseY, 0, 0);
	InitializeUIComponent("AdvWinSurnameInput", MAINWINDOW, "EDIT", "", WS_CHILD | WS_BORDER, AlignmentBaseX + 20, AlignmentBaseY+20, 200, 25, MS_ADVWINSURNAMEINPUT);

	AlignmentBaseY += 70;

	AdvBoxCurrentX = AlignmentBaseX;
	AdvBoxCurrentY = AlignmentBaseY;
	AdvBoxShiftY = 30;
	AdvBoxShiftX = 10;
	for (int i = 1; i <= 6; i += 1)
	{
		GraphicName = "AlignmentText" + to_string(i);
		InitializeUIGraphic(GraphicName, MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 70, 25);
		if (i % 6 == 0)
		{
			AdvBoxCurrentX += AdvBoxShiftX;
			AdvBoxCurrentY = AlignmentBaseY;
		}
		else
		{
			AdvBoxCurrentY += AdvBoxShiftY;
		}
	}

	//Reincarnate Advancement Panel
	int ReinCarnateBaseX = AdvBoxX + 5;
	int ReinCarnateBaseY = AdvBoxY -10;

	AdvBoxCurrentX = ReinCarnateBaseX;
	AdvBoxCurrentY = ReinCarnateBaseY;
	InitializeUIComponent("HeroicPastRadioButton", MAINWINDOW, "BUTTON", "Heroic", WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, AdvBoxCurrentX, AdvBoxCurrentY, 75, 18, MS_HERIOCPASTLIFE);
	InitializeUIComponent("IconicPastRadioButton", MAINWINDOW, "BUTTON", "Iconic", WS_CHILD | BS_AUTORADIOBUTTON, AdvBoxCurrentX + 85, AdvBoxCurrentY, 75, 18, MS_ICONICPASTLIFE);
	InitializeUIComponent("EpicPastRadioButton", MAINWINDOW, "BUTTON", "Epic", WS_CHILD | BS_AUTORADIOBUTTON, AdvBoxCurrentX + 165, AdvBoxCurrentY, 75, 18, MS_EPICPASTLIFE);
	AdvBoxCurrentY = ReinCarnateBaseY + 35;


	AdvBoxShiftY = 75;
	AdvBoxShiftX = 70;
	for (int i = 1; i <= 16; i += 1)
	{
		GraphicName = "ReincarnateIcon" + to_string(i);
		InitializeUIGraphic(GraphicName, MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 60, 60);
		GraphicName = "ReincarnateNumText" + to_string(i);
		InitializeUIGraphic(GraphicName, MAINWINDOW, AdvBoxCurrentX+27, AdvBoxCurrentY+58, 0, 0);
		GraphicName = "ReincarnateLA" + to_string(i);
		InitializeUIGraphic(GraphicName, MAINWINDOW, AdvBoxCurrentX + 3, AdvBoxCurrentY + 56, 20, 20);
		GraphicName = "ReincarnateRA" + to_string(i);
		InitializeUIGraphic(GraphicName, MAINWINDOW, AdvBoxCurrentX + 38, AdvBoxCurrentY + 56, 20, 20);
		if (i % 4 == 0)
		{
			AdvBoxCurrentY += AdvBoxShiftY;
			AdvBoxCurrentX = ReinCarnateBaseX;
		}
		else
		{
			AdvBoxCurrentX += AdvBoxShiftX;
		}
	}



//Abiltiy Advancement Panel
	string Abilitytext[] = { "AbilityPointStrengthText", "AbilityPointDexterityText", "AbilityPointConstitutionText", "AbilityPointIntelligenceText", "AbilityPointWisdomText", "AbilityPointCharismaText" };
	int AbilityBaseX = AdvBoxX+10;
	int AbilityBaseY = AdvBoxY + 2;

	AdvBoxCurrentX = AbilityBaseX;
	AdvBoxCurrentY = AbilityBaseY;
	AdvBoxShiftY = 30;
	AdvBoxShiftX = 70;	
	
	InitializeUIGraphic("AbilityPointAbilityText", MAINWINDOW, AbilityBaseX + 10, AbilityBaseY, 0, 0);
	InitializeUIGraphic("AbilityPointValueText", MAINWINDOW, AbilityBaseX + 120, AbilityBaseY, 0, 0);
	InitializeUIGraphic("AbilityPointCostText", MAINWINDOW, AbilityBaseX + 190, AbilityBaseY, 0, 0);
	InitializeUIGraphic("AbilityPointModText", MAINWINDOW, AbilityBaseX + 240, AbilityBaseY, 0, 0);

	AdvBoxCurrentY += AdvBoxShiftY;


	for (int i = 1; i <= 6; i += 1)
	{
		GraphicName = Abilitytext[i-1];
		InitializeUIGraphic(GraphicName, MAINWINDOW, AdvBoxCurrentX, AdvBoxCurrentY, 0, 0);
		GraphicName = "AbilityPointValue" + to_string(i);
		InitializeUIGraphic(GraphicName, MAINWINDOW, AdvBoxCurrentX + 135, AdvBoxCurrentY, 0, 0);
		GraphicName = "AbilityPointLA" + to_string(i);
		InitializeUIGraphic(GraphicName, MAINWINDOW, AdvBoxCurrentX + 105, AdvBoxCurrentY -2, 20, 20);
		GraphicName = "AbilityPointRA" + to_string(i);
		InitializeUIGraphic(GraphicName, MAINWINDOW, AdvBoxCurrentX + 160, AdvBoxCurrentY -2, 20, 20);

		AdvBoxCurrentY += AdvBoxShiftY;
		
	}
	InitializeUIGraphic("AbilityPointSpendRemain", MAINWINDOW, AdvBoxCurrentX + 10, AdvBoxCurrentY, 0, 0);
	AdvBoxCurrentY += AdvBoxShiftY;
	InitializeUIComponent("AdvWinBonusAbilityPointsCheckBox", MAINWINDOW, "BUTTON", "+4 Bonus Points (Requires 1750 Favor)", WS_CHILD | BS_AUTOCHECKBOX, AdvBoxCurrentX, AdvBoxCurrentY, 275, 20, MS_ADVWINBONUSABILITY);


//Skill Advancement Panel

	int SkillBaseX = AdvBoxX + 10;
	int SkillBaseY = AdvBoxY + 2;

	AdvBoxCurrentX = SkillBaseX;
	AdvBoxCurrentY = SkillBaseY;

	InitializeUIGraphic("SkillsSkillText", MAINWINDOW, AdvBoxCurrentX+10, SkillBaseY, 0, 0);
	InitializeUIGraphic("SkillsTotalText", MAINWINDOW, AdvBoxCurrentX+140, SkillBaseY, 0, 0);
	InitializeUIGraphic("SkillsPointsText", MAINWINDOW, AdvBoxCurrentX+203, SkillBaseY, 0, 0);
	SkillBaseY += 15;

	InitializeUIGraphic("SkillsModText", MAINWINDOW, SkillBaseX+145, SkillBaseY, 0, 0);
	InitializeUIGraphic("SkillsSpentText", MAINWINDOW, SkillBaseX+204, SkillBaseY, 0, 0);

	SkillBaseY += 20;
	InitializeUIComponent("AdvSkillPointSpendBox", MAINWINDOW, "LISTBOX", "Skill Point Spend", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, SkillBaseX, SkillBaseY, 280, 250, MS_ADVWINSKILLSPEND);

	SkillBaseY += 260;
	InitializeUIGraphic("SkillsRemainingText", MAINWINDOW, SkillBaseX + 10, SkillBaseY, 0, 0);

//Feat Advancement Panel
	int FeatAdvBaseX = AdvBoxX + 5;
	int FeatAdvBaseY = AdvBoxY + 5;

	InitializeUIComponent("AdvWinFeatList", MAINWINDOW, "LISTBOX", "Feat List", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, FeatAdvBaseX, FeatAdvBaseY, 280, 240, MS_ADVWINFEATSLIST);

	FeatAdvBaseY += 242;
	InitializeUIGraphic("FeatSlot1", MAINWINDOW, AdvBoxX + 20, FeatAdvBaseY, 45, 45);
	InitializeUIGraphic("FeatFilled1", MAINWINDOW, AdvBoxX + 23, FeatAdvBaseY+2, 40, 40); // X and Y are now relative to slot
	

	InitializeUIGraphic("FeatSlot2", MAINWINDOW, AdvBoxX + 120, FeatAdvBaseY, 45, 45);
	InitializeUIGraphic("FeatFilled2", MAINWINDOW, AdvBoxX + 123, FeatAdvBaseY+2, 40, 40); // X and Y are now relative to slot
	

	InitializeUIGraphic("FeatSlot3", MAINWINDOW, AdvBoxX + 220, FeatAdvBaseY, 45, 45);
	InitializeUIGraphic("FeatFilled3", MAINWINDOW, AdvBoxX + 223, FeatAdvBaseY+2, 40, 40); // X and Y are now relative to slot
	
	InitializeUIGraphic("FeatTextLegendary", MAINWINDOW, AdvBoxX + 8, FeatAdvBaseY+45, 0, 0);
	InitializeUIGraphic("FeatTextWarlockPact", MAINWINDOW, AdvBoxX + 14, FeatAdvBaseY + 45, 0, 0);
	InitializeUIGraphic("FeatTextFavored", MAINWINDOW, AdvBoxX + 15, FeatAdvBaseY + 45, 0, 0);
	InitializeUIGraphic("FeatTextHuman", MAINWINDOW, AdvBoxX + 20, FeatAdvBaseY + 45, 0, 0);
	InitializeUIGraphic("FeatTextHalfElf", MAINWINDOW, AdvBoxX + 20, FeatAdvBaseY + 45, 0, 0);
	InitializeUIGraphic("FeatTextDruid", MAINWINDOW, AdvBoxX + 23, FeatAdvBaseY + 45, 0, 0);
	InitializeUIGraphic("FeatTextClass", MAINWINDOW, AdvBoxX + 24, FeatAdvBaseY + 45, 0, 0);
	InitializeUIGraphic("FeatTextMonk", MAINWINDOW, AdvBoxX + 24, FeatAdvBaseY + 45, 0, 0);
	InitializeUIGraphic("FeatTextFeat1", MAINWINDOW, AdvBoxX + 28, FeatAdvBaseY + 45, 0, 0);
	InitializeUIGraphic("FeatTextEpic", MAINWINDOW, AdvBoxX + 28, FeatAdvBaseY + 45, 0, 0);
	
	InitializeUIGraphic("FeatTextLegendaryFeat", MAINWINDOW, AdvBoxX + 20, FeatAdvBaseY + 45, 0, 0);
	InitializeUIGraphic("FeatTextWarlockPact2", MAINWINDOW, AdvBoxX + 20, FeatAdvBaseY + 45, 0, 0);
	InitializeUIGraphic("FeatTextBonusFeat", MAINWINDOW, AdvBoxX + 00, FeatAdvBaseY + 45, 0, 0);
	InitializeUIGraphic("FeatTextWildShape", MAINWINDOW, AdvBoxX + 10, FeatAdvBaseY + 45, 0, 0);
	InitializeUIGraphic("FeatTextDestiny", MAINWINDOW, AdvBoxX + 10, FeatAdvBaseY + 45, 0, 0);
	InitializeUIGraphic("FeatTextDilettante", MAINWINDOW, AdvBoxX + 13, FeatAdvBaseY + 45, 0, 0);
	InitializeUIGraphic("FeatTextEnemy", MAINWINDOW, AdvBoxX + 20, FeatAdvBaseY + 45, 0, 0);
	InitializeUIGraphic("FeatTextFeat2", MAINWINDOW, AdvBoxX + 28, FeatAdvBaseY + 45, 0, 0);
	InitializeUIGraphic("FeatTextPath", MAINWINDOW, AdvBoxX + 28, FeatAdvBaseY + 45, 0, 0);
	
	
	//Spell Advancement Panel
	int SpellAdvBaseX = AdvBoxX + 5;
	int SpellAdvBaseY = AdvBoxY + 5;



	InitializeUIComponent("AdvWinSpellList", MAINWINDOW, "LISTBOX", "Spell List", WS_CHILD | WS_VSCROLL | LBS_NOSEL | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_NOTIFY, SpellAdvBaseX, SpellAdvBaseY, 280, 180, MS_ADVWINSPELLLIST);
	InitializeUIComponent("AdvWinSpellClearButton", MAINWINDOW, "BUTTON", "Clear All Spells", WS_CHILD | BS_PUSHBUTTON, SpellAdvBaseX + 173, SpellAdvBaseY + 303, 110, 20, MS_ES_ADVWINSPELLCLEARBUTTON);

	SpellAdvBaseY += 185;
	InitializeUIGraphic("SpellsSelectText", MAINWINDOW, SpellAdvBaseX + 20, SpellAdvBaseY, 0, 0);
	
	int SpellAdvIncX = 50;
	int SpellAdvIncY = 40;

	CurrentX = SpellAdvBaseX + 20;
	CurrentY = SpellAdvBaseY +20;



	InitializeUIGraphic("SpellsLevelText1", MAINWINDOW, CurrentX, CurrentY+5, 0, 0);
	InitializeUIGraphic("SpellsLevelText2", MAINWINDOW, CurrentX, CurrentY + SpellAdvIncY+5, 0, 0);
	InitializeUIGraphic("SpellsLevelText3", MAINWINDOW, CurrentX, CurrentY + SpellAdvIncY*2+5, 0, 0);

	for (int i = 1; i <= 12; i += 1)
	{

		GraphicName = "SpellsSelectSlot" + to_string(i);
		InitializeUIGraphic(GraphicName, MAINWINDOW, CurrentX, CurrentY, 36, 36);

		if (i % 4 == 0)
		{
			CurrentX = SpellAdvBaseX+20;
			CurrentY += SpellAdvIncY;
		}
		else
		{
			CurrentX += SpellAdvIncX;
		}
		

	}

//Tome Advancement Panel
	int TomeAdvBaseX = AdvBoxX + 5;
	int TomeAdvBaseY = AdvBoxY + 5;
	int TomeAdvIncX = 30;
	int TomeAdvIncY = 30;
	CurrentX = TomeAdvBaseX;
	CurrentY = TomeAdvBaseY;



	InitializeUIGraphic("TomeAbilityText", MAINWINDOW, CurrentX + 5, CurrentY, 0, 0);
	InitializeUIGraphic("TomeValueText", MAINWINDOW, CurrentX + 125, CurrentY, 0, 0);
	InitializeUIGraphic("TomeChangeText", MAINWINDOW, CurrentX + 195, CurrentY, 0, 0);
	
	CurrentY += TomeAdvIncY;

	InitializeUIGraphic("TomeStrengthText", MAINWINDOW, CurrentX, CurrentY, 0, 0);
	CurrentY += TomeAdvIncY;
	InitializeUIGraphic("TomeDexterityText", MAINWINDOW, CurrentX, CurrentY, 0, 0);
	CurrentY += TomeAdvIncY; 
	InitializeUIGraphic("TomeConstitutionText", MAINWINDOW, CurrentX, CurrentY, 0, 0);
	CurrentY += TomeAdvIncY; 
	InitializeUIGraphic("TomeIntelligenceText", MAINWINDOW, CurrentX, CurrentY, 0, 0);
	CurrentY += TomeAdvIncY; 
	InitializeUIGraphic("TomeWisdomText", MAINWINDOW, CurrentX, CurrentY, 0, 0);
	CurrentY += TomeAdvIncY; 
	InitializeUIGraphic("TomeCharismaText", MAINWINDOW, CurrentX, CurrentY, 0, 0);

	CurrentY = TomeAdvBaseY + TomeAdvIncY;
	
	for (int i = 1; i <= 6; i += 1)
	{

		GraphicName = "TomeLeftArrow" + to_string(i);
		InitializeUIGraphic(GraphicName, MAINWINDOW, CurrentX + 110, CurrentY - 2, 20, 20);
		GraphicName = "TomeAbilityLevelText" + to_string(i);
		InitializeUIGraphic(GraphicName, MAINWINDOW, CurrentX + 140, CurrentY, 0, 0);
		GraphicName = "TomeRightArrow" + to_string(i);
		InitializeUIGraphic(GraphicName, MAINWINDOW, CurrentX + 165, CurrentY - 2, 20, 20);
		GraphicName = "TomeAbilityModText" + to_string(i);
		InitializeUIGraphic(GraphicName, MAINWINDOW, CurrentX + 205, CurrentY, 0, 0);

		CurrentY += TomeAdvIncY;



	}

	InitializeUIGraphic("TomeInstructionText1", MAINWINDOW, CurrentX + 5, CurrentY, 0, 0);
	CurrentY += TomeAdvIncY; 
	InitializeUIGraphic("TomeInstructionText2", MAINWINDOW, CurrentX + 5, CurrentY-12, 0, 0);
	CurrentY += TomeAdvIncY; 
	InitializeUIGraphic("TomeInstructionText3", MAINWINDOW, CurrentX + 5, CurrentY-24, 0, 0);
	CurrentY += TomeAdvIncY; 
	InitializeUIGraphic("TomeInstructionText4", MAINWINDOW, CurrentX + 5, CurrentY-36, 0, 0);
	CurrentY += TomeAdvIncY; 
	InitializeUIGraphic("TomeInstructionText5", MAINWINDOW, CurrentX + 5, CurrentY-48, 0, 0);
	CurrentY += TomeAdvIncY;
	InitializeUIGraphic("TomeInstructionText6", MAINWINDOW, CurrentX + 5, CurrentY-60, 0, 0);
	CurrentY += TomeAdvIncY;

	//Advancement Equipement Panel
	int EquipBasX = AdvBoxX + 5;
	int EquipBasY = AdvBoxY + 5;
	InitializeUIGraphic("EquipmentPanel", MAINWINDOW, EquipBasX, EquipBasY, 270, 250);
	InitializeUIGraphic("EquipmentHighlightSlot1", MAINWINDOW, EquipBasX + 7, EquipBasY+20, 45, 47);
	InitializeUIGraphic("EquipmentHighlightSlot2", MAINWINDOW, EquipBasX + 7, EquipBasY+73, 45, 47);
	InitializeUIGraphic("EquipmentHighlightSlot3", MAINWINDOW, EquipBasX + 7, EquipBasY+136, 45, 47);
	InitializeUIGraphic("EquipmentHighlightSlot4", MAINWINDOW, EquipBasX + 7, EquipBasY+179, 45, 47);
	InitializeUIGraphic("EquipmentHighlightSlot5", MAINWINDOW, EquipBasX + 62, EquipBasY+20, 45, 47);
	InitializeUIGraphic("EquipmentHighlightSlot6", MAINWINDOW, EquipBasX + 62, EquipBasY+73, 45, 47);
	InitializeUIGraphic("EquipmentHighlightSlot7", MAINWINDOW, EquipBasX + 62, EquipBasY+130, 45, 47);
	InitializeUIGraphic("EquipmentHighlightSlot8", MAINWINDOW, EquipBasX + 62, EquipBasY+185, 45, 47);
	InitializeUIGraphic("EquipmentHighlightSlot9", MAINWINDOW, EquipBasX + 112, EquipBasY+7, 45, 47);
	InitializeUIGraphic("EquipmentHighlightSlot10", MAINWINDOW, EquipBasX + 112, EquipBasY+200, 45, 47);
	InitializeUIGraphic("EquipmentHighlightSlot11", MAINWINDOW, EquipBasX + 112, EquipBasY+7, 45, 47);
	InitializeUIGraphic("EquipmentHighlightSlot12", MAINWINDOW, EquipBasX + 112, EquipBasY+200, 45, 47);
	InitializeUIGraphic("EquipmentHighlightSlot13", MAINWINDOW, EquipBasX + 220, EquipBasY+20, 45, 47);
	InitializeUIGraphic("EquipmentHighlightSlot14", MAINWINDOW, EquipBasX + 220, EquipBasY+73, 45, 47);
	InitializeUIGraphic("EquipmentHighlightSlot15", MAINWINDOW, EquipBasX + 220, EquipBasY+130, 45, 47);
	InitializeUIGraphic("EquipmentHighlightSlot16", MAINWINDOW, EquipBasX + 220, EquipBasY+185, 45, 47);

	//**************************** MultiFeat Window Graphic *************************

	//Level Bars

	LevelBarX = 880;
	LevelBarY = 50;
	LevelBarXinc = 50;
	LevelBarYinc = 30;
	CurrentX = LevelBarX;
	CurrentY = LevelBarY;
	for (int i = 1; i <= 30; i += 1)
	{
		GraphicName = "FeatLevelBar" + to_string(i);
		InitializeUIGraphic(GraphicName, MULTIFEATWINDOW, CurrentX, CurrentY, 40, 25);
		if (i % 15 == 0)
		{
			CurrentX += LevelBarXinc;
			CurrentY = LevelBarY;
		}
		else
		{
			CurrentY += LevelBarYinc;
		}
	}

	//Select Window
	int X = 570;
	int Y = 305;

	InitializeUIGraphic("FeatSlot1", MULTIFEATWINDOW, X + 20, Y, 45, 45);
	InitializeUIGraphic("FeatFilled1", MULTIFEATWINDOW, X + 23, Y + 2, 40, 40); // X and Y are now relative to slot


	InitializeUIGraphic("FeatSlot2", MULTIFEATWINDOW, X + 120, Y, 45, 45);
	InitializeUIGraphic("FeatFilled2", MULTIFEATWINDOW, X + 123, Y + 2, 40, 40); // X and Y are now relative to slot


	InitializeUIGraphic("FeatSlot3", MULTIFEATWINDOW, X + 220, Y, 45, 45);
	InitializeUIGraphic("FeatFilled3", MULTIFEATWINDOW, X + 223, Y + 2, 40, 40); // X and Y are now relative to slot

	InitializeUIGraphic("FeatTextLegendary", MULTIFEATWINDOW, X + 8, Y + 45, 0, 0);
	InitializeUIGraphic("FeatTextWarlockPact", MULTIFEATWINDOW, X + 14, Y + 45, 0, 0);
	InitializeUIGraphic("FeatTextFavored", MULTIFEATWINDOW, X + 15, Y + 45, 0, 0);
	InitializeUIGraphic("FeatTextHuman", MULTIFEATWINDOW, X + 20, Y + 45, 0, 0);
	InitializeUIGraphic("FeatTextHalfElf", MULTIFEATWINDOW, X + 20, Y + 45, 0, 0);
	InitializeUIGraphic("FeatTextDruid", MULTIFEATWINDOW, X + 23, Y + 45, 0, 0);
	InitializeUIGraphic("FeatTextClass", MULTIFEATWINDOW, X + 24, Y + 45, 0, 0);
	InitializeUIGraphic("FeatTextMonk", MULTIFEATWINDOW, X + 24, Y + 45, 0, 0);
	InitializeUIGraphic("FeatTextFeat1", MULTIFEATWINDOW, X + 28, Y + 45, 0, 0);
	InitializeUIGraphic("FeatTextEpic", MULTIFEATWINDOW, X + 28, Y + 45, 0, 0);

	InitializeUIGraphic("FeatTextLegendaryFeat", MULTIFEATWINDOW, X + 20, Y + 45, 0, 0);
	InitializeUIGraphic("FeatTextWarlockPact2", MULTIFEATWINDOW, X + 20, Y + 45, 0, 0);
	InitializeUIGraphic("FeatTextBonusFeat", MULTIFEATWINDOW, X + 00, Y + 45, 0, 0);
	InitializeUIGraphic("FeatTextWildShape", MULTIFEATWINDOW, X + 10, Y + 45, 0, 0);
	InitializeUIGraphic("FeatTextDestiny", MULTIFEATWINDOW, X + 10, Y + 45, 0, 0);
	InitializeUIGraphic("FeatTextDilettante", MULTIFEATWINDOW, X + 13, Y + 45, 0, 0);
	InitializeUIGraphic("FeatTextEnemy", MULTIFEATWINDOW, X + 20, Y + 45, 0, 0);
	InitializeUIGraphic("FeatTextFeat2", MULTIFEATWINDOW, X + 28, Y + 45, 0, 0);
	InitializeUIGraphic("FeatTextPath", MULTIFEATWINDOW, X + 28, Y + 45, 0, 0);

//*****************************MultiClassWindow*******************************

	//Standard components
	InitializeUIComponent("MultiClassText", MULTICLASSWINDOW, "STATIC", "Add Classes", WS_CHILD, 10, 5, 200, 25, MCL_LABEL);
	InitializeUIComponent("Close", MULTICLASSWINDOW, "BUTTON", "CLose", WS_CHILD | BS_PUSHBUTTON, 1000 - ButtonSize - 10, 5, ButtonSize, 18, MCL_CLOSE);
	InitializeUIComponent("ClassString", MULTICLASSWINDOW, "STATIC", "Class", WS_CHILD, 10, 25, 500, 25, MCL_CLASSSTRING);

	int ClassX, ClassY;
	int BaseX, BaseY;
	int FrameBaseX, FrameBaseY;
	int Width, Height;
	int SpacingX, SpacingY;

	ClassX = 10;
	ClassY = 50;

	Width = 320;
	Height = 250;
	CurrentX = ClassX;
	CurrentY = ClassY;

	//Description Box
	InitializeUIComponent("DescriptionWindow", MULTICLASSWINDOW, "RichEdit", "RichEdit", WS_CHILD | WS_VSCROLL | WS_BORDER | ES_MULTILINE | ES_READONLY, CurrentX, CurrentY, Width, Height, MCL_DESCRIPTION);

	//Class List
	CurrentY += Height + 10;
	Height = 410;
	
	FrameBaseX = CurrentX;
	FrameBaseY = CurrentY;

	InitializeUIComponent("ClassListFrame", MULTICLASSWINDOW, "STATIC", "", WS_CHILD | SS_GRAYFRAME, CurrentX, CurrentY, Width, Height, MCL_CLASSFRAME);
	//Reletive to frame
	CurrentX = 15;
	CurrentY = 10;

	SpacingX = 80;
	SpacingY = 80;


	for (int i = 1; i <= NUMCLASSES; i += 1)
	{
		GraphicName = "ClassIcon" + to_string(i);
		InitializeUIGraphic(GraphicName, MULTICLASSWINDOW, CurrentX + 10, CurrentY, 40, 40);

		GraphicName = "ClassText" + to_string(i);
		InitializeUIGraphic(GraphicName, MULTICLASSWINDOW, CurrentX, CurrentY + 50, 60, 20);

		if (i % 4 == 0)
		{
			CurrentX = 15;
			CurrentY += SpacingY;
		}
		else
		{
			CurrentX += SpacingX;
		}
	}


	//Selection Box
	CurrentY = ClassY;
	CurrentX = ClassX + Width + 10;
	Width = 650;
	Height = 670;

	FrameBaseX = CurrentX;
	FrameBaseY = CurrentY;

	InitializeUIComponent("SelectionFrame", MULTICLASSWINDOW, "STATIC", "", WS_CHILD | SS_GRAYFRAME, CurrentX, CurrentY, Width, Height, MCL_SELECTFRAME);

	CurrentX = FrameBaseX + 15;
	CurrentY = FrameBaseY + 15;
	InitializeUIComponent("LevelLabel", MULTICLASSWINDOW, "STATIC", "Level", WS_CHILD, CurrentX, CurrentY, 40, 20, MCL_LEVELLABEL);
	CurrentX += 60;
	InitializeUIComponent("ClassLabel", MULTICLASSWINDOW, "STATIC", "Class", WS_CHILD, CurrentX, CurrentY, 40, 20, MCL_CLASSLABEL);
	CurrentX += 185;
	InitializeUIComponent("ClassLevelLabel", MULTICLASSWINDOW, "STATIC", "Class Lvl", WS_CHILD, CurrentX, CurrentY-10, 40, 40, MCL_CLASSLEVELLABEL);
	CurrentX += 60;
	InitializeUIGraphic("SelectClassIcon1", MULTICLASSWINDOW, CurrentX - FrameBaseX, CurrentY - FrameBaseY, 30, 30);
	CurrentX += 50;
	InitializeUIGraphic("SelectClassIcon2", MULTICLASSWINDOW, CurrentX - FrameBaseX, CurrentY - FrameBaseY, 30, 30);
	CurrentX += 50;
	InitializeUIGraphic("SelectClassIcon3", MULTICLASSWINDOW, CurrentX - FrameBaseX, CurrentY - FrameBaseY, 30, 30);
	CurrentX += 50;
	InitializeUIComponent("BABLabel", MULTICLASSWINDOW, "STATIC", "BAB", WS_CHILD, CurrentX, CurrentY, 40, 20, MCL_BABLABEL);


	//releative to frame position
	CurrentX = 15;
	CurrentY = 49;
	
	for (int i = 0; i < 20; i++)
	{
		GraphicName = "LevelText" + to_string(i);
		InitializeUIGraphic(GraphicName, MULTICLASSWINDOW, CurrentX, CurrentY, 40, 20);
		CurrentX += 60;
		GraphicName = "ClassTextAtLevel" + to_string(i);
		InitializeUIGraphic(GraphicName, MULTICLASSWINDOW, CurrentX, CurrentY, 165, 20);
		CurrentX += 185;
		GraphicName = "ClassLevelText" + to_string(i);
		InitializeUIGraphic(GraphicName, MULTICLASSWINDOW, CurrentX, CurrentY, 40, 20);
		CurrentX += 62;
		GraphicName = "Class1Icon" + to_string(i);
		InitializeUIGraphic(GraphicName, MULTICLASSWINDOW, CurrentX, CurrentY, 26, 26);
		CurrentX += 50;
		GraphicName = "Class2Icon" + to_string(i);
		InitializeUIGraphic(GraphicName, MULTICLASSWINDOW, CurrentX, CurrentY, 26, 26);
		CurrentX += 50;
		GraphicName = "Class3Icon" + to_string(i);
		InitializeUIGraphic(GraphicName, MULTICLASSWINDOW, CurrentX, CurrentY, 26, 26);
		CurrentX += 48;
		GraphicName = "BABText" + to_string(i);
		InitializeUIGraphic(GraphicName, MULTICLASSWINDOW, CurrentX, CurrentY, 40, 20);

		CurrentX = 15;
		CurrentY += 31;

	}

	//**************************** MULTISKILL WINDOW ***************************************


	CurrentX = 5;
	CurrentY = 5;
	
	
	InitializeUIComponent("MultiSkillText", MULTISKILLSWINDOW, "STATIC", "Select Skills", WS_CHILD, CurrentX, CurrentY, 200, 20, MSK_LABEL);
	InitializeUIComponent("Reset", MULTISKILLSWINDOW, "BUTTON", "Reset", WS_CHILD | BS_PUSHBUTTON, 1000 - 3 * ButtonSize - 20, 5, ButtonSize, 18, MSK_RESET);

	InitializeUIComponent("Accept", MULTISKILLSWINDOW, "BUTTON", "Accept", WS_CHILD | BS_PUSHBUTTON, 1000 - 2 * ButtonSize - 20, 5, ButtonSize, 18, MSK_ACCEPT);
	InitializeUIComponent("Close", MULTISKILLSWINDOW, "BUTTON", "CLose", WS_CHILD | BS_PUSHBUTTON, 1000 - ButtonSize - 10, 5, ButtonSize, 18, MSK_CANCEL);

	CurrentY += 25;
	CurrentX += 5;
	Width = 800;
	Height = 680;
	InitializeUIComponent("MultiSkillFrame", MULTISKILLSWINDOW, "STATIC", "", WS_CHILD | SS_GRAYFRAME, CurrentX, CurrentY, Width, Height, MSK_SKILLFRAME);

	CurrentX += 5;
	CurrentY += 5;
	InitializeUIComponent("SKILLLABEL", MULTISKILLSWINDOW, "STATIC", "Skills", WS_CHILD, CurrentX, CurrentY, 100, 20, MSK_LABEL);
	InitializeUIComponent("TOTALLABEL", MULTISKILLSWINDOW, "STATIC", "Total", WS_CHILD, CurrentX+730, CurrentY, 50, 20, MSK_TOTOALLABEL);
	for (int i = 0; i < HEROICLEVELS; i++)
	{
		GraphicName = "LevelLabel" + to_string(i);
		InitializeUIGraphic(GraphicName, MULTISKILLSWINDOW, CurrentX + (i * 30) + 135, CurrentY+3, 30, 20);
	}
	
	CurrentY += 25;
	CurrentX += 5;
	for (int x = 0; x < NUMSKILLS; x++)
	{
		GraphicName = "SkillLabel" + to_string(x);
		InitializeUIGraphic(GraphicName, MULTISKILLSWINDOW, CurrentX, CurrentY+5, 120, 20);
		for (int i = 0; i < HEROICLEVELS; i++)
		{
			GraphicName = "SkillBox" + to_string(x) + "_" + to_string(i);
			InitializeUIGraphic(GraphicName, MULTISKILLSWINDOW, CurrentX + (i * 30) + 125, CurrentY, 25, 25);
			GraphicName = "SkillValue" + to_string(x) + "_" + to_string(i);
			InitializeUIGraphic(GraphicName, MULTISKILLSWINDOW, CurrentX + (i * 30) + 128, CurrentY+5, 25, 25);
		}
		GraphicName = "SkillTotal" + to_string(x);
		InitializeUIGraphic(GraphicName, MULTISKILLSWINDOW, CurrentX + 740, CurrentY+5, 25, 25);

		CurrentY += 28;
	}

	InitializeUIComponent("SKILLSpentLevel", MULTISKILLSWINDOW, "STATIC", "Spent", WS_CHILD, CurrentX, CurrentY-3, 100, 20, MSK_SPENT);
	InitializeUIComponent("SkillAvalibleLevel", MULTISKILLSWINDOW, "STATIC", "Avalible", WS_CHILD, CurrentX, CurrentY+17, 100, 20, MSK_AVALIBLE);
	for (int i = 0; i < HEROICLEVELS; i++)
	{
		GraphicName = "SkillSpentLevel" + to_string(i);
		InitializeUIGraphic(GraphicName, MULTISKILLSWINDOW, CurrentX + (i * 30) + 130, CurrentY, 25, 20);
		GraphicName = "SkillAvalibleLevel"+ to_string(i);
		InitializeUIGraphic(GraphicName, MULTISKILLSWINDOW, CurrentX + (i * 30) + 130, CurrentY + 20, 25, 20);
	}

	//Skills Auto Rank
	CurrentX = 815;
	CurrentY = 30;
	Width = 175;
	Height = 680;
	InitializeUIComponent("AutoSkillFrame", MULTISKILLSWINDOW, "STATIC", "", WS_CHILD | SS_GRAYFRAME, CurrentX, CurrentY, Width, Height, MSK_AUTOSKILLFRAME);
	
	CurrentX += 5;
	CurrentY += 5;
	InitializeUIComponent("AutoFill", MULTISKILLSWINDOW, "BUTTON", "Auto Fill", WS_CHILD | BS_PUSHBUTTON, CurrentX, CurrentY+675-50, ButtonSize, 18, MSK_AUTOSKILLSET);
	InitializeUIComponent("ResetAuto", MULTISKILLSWINDOW, "BUTTON", "Reset AutoFill", WS_CHILD | BS_PUSHBUTTON, CurrentX + Width - ButtonSize - 30, CurrentY + 675 - 50, ButtonSize+20, 18, MSK_AUTOSKILLRESET);
	InitializeUIComponent("ClassFirstCheckBox", MULTISKILLSWINDOW, "BUTTON", "Fill Class Skills First", WS_CHILD | BS_AUTOCHECKBOX, CurrentX, CurrentY + 675 - 25, 160, 20, MSK_AUTOSKILLCLASSFIRST);
	
	InitializeUIComponent("SetTotal", MULTISKILLSWINDOW, "STATIC", "Set Total", WS_CHILD, CurrentX+10, CurrentY, 60, 20, MSK_AUTOSKILLTEXT);
	InitializeUIComponent("Priority", MULTISKILLSWINDOW, "STATIC", "Priority", WS_CHILD, CurrentX+100, CurrentY, 60, 20, MSKAUTOSKILLRANK);

	CurrentY += 25;
	
	for (int x = 0; x < NUMSKILLS; x++)
	{
		GraphicName = "SkillAutoTextLeftArrow" + to_string(x);
		InitializeUIGraphic(GraphicName, MULTISKILLSWINDOW, CurrentX+10, CurrentY+7, 15, 15);

		GraphicName = "SkillAutoText" + to_string(x);
		InitializeUIGraphic(GraphicName, MULTISKILLSWINDOW, CurrentX+35, CurrentY+5, 30, 25);

		GraphicName = "SkillAutoTextRightArrow" + to_string(x);
		InitializeUIGraphic(GraphicName, MULTISKILLSWINDOW, CurrentX+60, CurrentY+7, 15, 15);

		GraphicName = "SkillAutoRankLeftArrow" + to_string(x);
		InitializeUIGraphic(GraphicName, MULTISKILLSWINDOW, CurrentX+90, CurrentY+7, 15, 15);

		GraphicName = "SkillAutoRank" + to_string(x);
		InitializeUIGraphic(GraphicName, MULTISKILLSWINDOW, CurrentX + 115, CurrentY+5, 30, 25);

		GraphicName = "SkillAutoRankRightArrow" + to_string(x);
		InitializeUIGraphic(GraphicName, MULTISKILLSWINDOW, CurrentX+140, CurrentY+7, 15, 15);

		CurrentY += 28;
	}





//*********************************************** MultiSpellsWindowClass *************************************************

	CurrentX = 5;
	CurrentY = 5;

	InitializeUIComponent("MultiSpellText", MULTISPELLSWINDOW, "STATIC", "Select Spells", WS_CHILD, CurrentX, CurrentY, 200, 20, MSP_LABEL);
	InitializeUIComponent("Close", MULTISPELLSWINDOW, "BUTTON", "CLose", WS_CHILD | BS_PUSHBUTTON, 1000 - ButtonSize - 10, 5, ButtonSize, 18, MSP_CANCEL);

	InitializeUIGraphic("Test", MULTISPELLSWINDOW, CurrentX + 130, CurrentY+100, 25, 20);
	InitializeUIGraphic("Test2", MULTISPELLSWINDOW, CurrentX + 230, CurrentY + 100, 25, 20);
	}

//---------------------------------------------------------------------------
void UIComponentManager::InitializeUIComponent(string ComponentName, CHILDWINDOW Screen, string WindowType, string WindowLabel, DWORD Style, unsigned int BaseLocationX, unsigned int BaseLocationY, unsigned int BaseWidth, unsigned int BaseHeight, WINDOWID WindowID, string TooltipText)
	{
	InterfaceComponentStruct NewUI;

	switch (Screen)
		{
		case MAINWINDOW:
			{
			NewUI.ComponentName = ComponentName;
			NewUI.WindowType = WindowType;
			NewUI.WindowLabel = WindowLabel;
			NewUI.Style = Style;
			NewUI.BaseLocationX = static_cast<double>(BaseLocationX) / DEFAULTWIDTH;
			NewUI.BaseLocationY = static_cast<double>(BaseLocationY) / DEFAULTHEIGHT;
			NewUI.BaseWidth = static_cast<double>(BaseWidth) / DEFAULTWIDTH;
			NewUI.BaseHeight = static_cast<double>(BaseHeight) / DEFAULTHEIGHT;
			NewUI.WindowID = WindowID;
			NewUI.TooltipText = TooltipText;
			InterfaceComponentsMainScreen.emplace(pair<string, InterfaceComponentStruct>(ComponentName,NewUI));
			break;
			}
		case MULTICLASSWINDOW:
		{
			NewUI.ComponentName = ComponentName;
			NewUI.WindowType = WindowType;
			NewUI.WindowLabel = WindowLabel;
			NewUI.Style = Style;
			NewUI.BaseLocationX = static_cast<double>(BaseLocationX);
			NewUI.BaseLocationY = static_cast<double>(BaseLocationY);
			NewUI.BaseWidth = static_cast<double>(BaseWidth);
			NewUI.BaseHeight = static_cast<double>(BaseHeight);
			NewUI.WindowID = WindowID;
			NewUI.TooltipText = TooltipText;
			InterfaceComponentsMultiClassScreen.emplace(pair<string, InterfaceComponentStruct>(ComponentName, NewUI));
			break;
		}
		case MULTISKILLSWINDOW:
		{
			NewUI.ComponentName = ComponentName;
			NewUI.WindowType = WindowType;
			NewUI.WindowLabel = WindowLabel;
			NewUI.Style = Style;
			NewUI.BaseLocationX = static_cast<double>(BaseLocationX);
			NewUI.BaseLocationY = static_cast<double>(BaseLocationY);
			NewUI.BaseWidth = static_cast<double>(BaseWidth);
			NewUI.BaseHeight = static_cast<double>(BaseHeight);
			NewUI.WindowID = WindowID;
			NewUI.TooltipText = TooltipText;
			InterfaceComponentsMultiSkillWindow.emplace(pair<string, InterfaceComponentStruct>(ComponentName, NewUI));
			break;
		}
		case MULTISPELLSWINDOW:
		{
			NewUI.ComponentName = ComponentName;
			NewUI.WindowType = WindowType;
			NewUI.WindowLabel = WindowLabel;
			NewUI.Style = Style;
			NewUI.BaseLocationX = static_cast<double>(BaseLocationX);
			NewUI.BaseLocationY = static_cast<double>(BaseLocationY);
			NewUI.BaseWidth = static_cast<double>(BaseWidth);
			NewUI.BaseHeight = static_cast<double>(BaseHeight);
			NewUI.WindowID = WindowID;
			NewUI.TooltipText = TooltipText;
			InterfaceComponentsMultiSpellsWindow.emplace(pair<string, InterfaceComponentStruct>(ComponentName, NewUI));
			break;
		}
		}
	}

//---------------------------------------------------------------------------
void UIComponentManager::InitializeUIGraphic(string GraphicName, CHILDWINDOW Screen, unsigned int BaseLocationX, unsigned int BaseLocationY, unsigned int BaseWidth, unsigned int BaseHeight)
	{
	InterfaceGraphicStruct NewUI;

	switch (Screen)
		{
		case MAINWINDOW:
			{
			NewUI.GraphicName = GraphicName;
			NewUI.BaseLocationX = static_cast<double>(BaseLocationX) / DEFAULTWIDTH;
			NewUI.BaseLocationY = static_cast<double>(BaseLocationY) / DEFAULTHEIGHT;
			NewUI.BaseWidth = static_cast<double>(BaseWidth) / DEFAULTWIDTH;
			NewUI.BaseHeight = static_cast<double>(BaseHeight) / DEFAULTHEIGHT;
			InterfaceGraphicsMainScreen.emplace(pair<string, InterfaceGraphicStruct>(GraphicName, NewUI));
			break;
			}
		case MULTIFEATWINDOW:
			{
				NewUI.GraphicName = GraphicName;
				NewUI.BaseLocationX = static_cast<double>(BaseLocationX);
				NewUI.BaseLocationY = static_cast<double>(BaseLocationY);
				NewUI.BaseWidth = static_cast<double>(BaseWidth);
				NewUI.BaseHeight = static_cast<double>(BaseHeight);
				InterfaceGraphicsFeatWindow.emplace(pair<string, InterfaceGraphicStruct>(GraphicName, NewUI));
				break;
			}
		case MULTICLASSWINDOW:
		{
			NewUI.GraphicName = GraphicName;
			NewUI.BaseLocationX = static_cast<double>(BaseLocationX);
			NewUI.BaseLocationY = static_cast<double>(BaseLocationY);
			NewUI.BaseWidth = static_cast<double>(BaseWidth);
			NewUI.BaseHeight = static_cast<double>(BaseHeight);
			InterfaceGraphicsMultiClassScreen.emplace(pair<string, InterfaceGraphicStruct>(GraphicName, NewUI));
			break;
		}
		case MULTISKILLSWINDOW:
		{
			NewUI.GraphicName = GraphicName;
			NewUI.BaseLocationX = static_cast<double>(BaseLocationX);
			NewUI.BaseLocationY = static_cast<double>(BaseLocationY);
			NewUI.BaseWidth = static_cast<double>(BaseWidth);
			NewUI.BaseHeight = static_cast<double>(BaseHeight);
			InterfaceGraphicsMultiSkillWindow.emplace(pair<string, InterfaceGraphicStruct>(GraphicName, NewUI));
			break;
		}
		case MULTISPELLSWINDOW:
		{
			NewUI.GraphicName = GraphicName;
			NewUI.BaseLocationX = static_cast<double>(BaseLocationX);
			NewUI.BaseLocationY = static_cast<double>(BaseLocationY);
			NewUI.BaseWidth = static_cast<double>(BaseWidth);
			NewUI.BaseHeight = static_cast<double>(BaseHeight);
			InterfaceGraphicsMultiSpellsWindow.emplace(pair<string, InterfaceGraphicStruct>(GraphicName, NewUI));
			break;
		}
		}
	}
	
//---------------------------------------------------------------------------
InterfaceComponentStruct* UIComponentManager::GetComponentData(string ComponentName, CHILDWINDOW Screen)
	{
	InterfaceComponentStruct ReturnUI;

	switch (Screen)
		{
		case MAINWINDOW:
			{
			return &InterfaceComponentsMainScreen.at(ComponentName);
			}
		case MULTICLASSWINDOW:
			{
			return &InterfaceComponentsMultiClassScreen.at(ComponentName);
			}
		case MULTISKILLSWINDOW:
			{
				return &InterfaceComponentsMultiSkillWindow.at(ComponentName);
			}
		case MULTISPELLSWINDOW:
		{
			return &InterfaceComponentsMultiSpellsWindow.at(ComponentName);
		}
		}

	return nullptr;
	}


//---------------------------------------------------------------------------
InterfaceGraphicStruct* UIComponentManager::GetGraphicData(string GraphicName, CHILDWINDOW Screen)
	{
	InterfaceComponentStruct ReturnUI;

	switch (Screen)
		{
		case MAINWINDOW:
			{
			return &InterfaceGraphicsMainScreen.at(GraphicName);
			}
		case MULTIFEATWINDOW:
			{
				return &InterfaceGraphicsFeatWindow.at(GraphicName);
			}
		case MULTICLASSWINDOW:
			{
				return &InterfaceGraphicsMultiClassScreen.at(GraphicName);
			}
		case MULTISKILLSWINDOW:
			{
				return &InterfaceGraphicsMultiSkillWindow.at(GraphicName);
			}
		case MULTISPELLSWINDOW:
			{
				return &InterfaceGraphicsMultiSpellsWindow.at(GraphicName);
			}			
		}

				


	return nullptr;
	}

//---------------------------------------------------------------------------
string UIComponentManager::GetTooltipText(string ComponentName, CHILDWINDOW Screen)
	{
	switch (Screen)
		{
		case MAINWINDOW:
			{
			return InterfaceComponentsMainScreen.at(ComponentName).TooltipText;
			}
		case MULTICLASSWINDOW:
		{
			return InterfaceComponentsMultiClassScreen.at(ComponentName).TooltipText;
		}
		}

	return "";
	}
