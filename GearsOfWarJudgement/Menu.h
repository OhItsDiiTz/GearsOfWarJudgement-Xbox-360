#pragma once
#include "Main.h"
#include <type_traits>

struct FLinearColor;

struct FVector1 {
	float X, Y, Z;
};

enum eMenus {
	MenuBase,
	PlayerSettings,
	APawnSettings,
	AGearWeaponSettings,
	CommandsMenu,
	
	DebuggingMenu,
};

void SelectMenu(eMenus menuID);

extern FLinearColor white;
extern FLinearColor blackFaded;
extern FLinearColor red;
extern FLinearColor colors[32];

struct Variables {
	bool bDrawWatermark;

	bool bGodmode;
	bool bDemiGodmode;
	bool bInfiniteAmmo;
	bool bInstantKill;
	bool bCustomShotCount;
	int iShotCount;

	FVector1 saved_location;

	int iLevelCount;

	bool enable_esp;
	bool draw_level_actors[32];
};

class Menu {
public:
	Menu();
	virtual ~Menu();

	uint32_t font;

	int iTick;
	int iWait;
	bool isReady();
	void wait(int msec);

	float location[2];
	int paddingy;

	bool isMenuOpen;
	bool KeyPressed[32];
	int CurrentMenu;
	int CurrentOption;
	int LastMenu[32];
	int LastOption[32];
	int MaxScroll;
	int keyboard_type;

	
	virtual bool MenuOpened();
	virtual void ResetMaxScroll();
	virtual int GetMaxScroll();
	virtual void FillGlobals();
	virtual void RenderESP();
	virtual void RenderMenu();
	virtual void RunControls();

	virtual void AddTitle(const wchar_t * title);
	virtual void AddOption(const wchar_t * opt, void(*func)());
	template<typename T> void AddOption(const wchar_t * opt, void(*func)(T value), T value);
	virtual void AddBool(const wchar_t * opt, bool * value);
	virtual void AddBool(const wchar_t * opt, bool * value, void(*func)(bool value));
	template<typename T> void AddSlider(const wchar_t * opt, T * value, T min, T max, T scale, const wchar_t* format);
	template<typename T> void AddSlider(const wchar_t * opt, T * value, T min, T max, T scale, const wchar_t* format, void(*func)(T val));
	virtual void AddStringSlider(const wchar_t * opt, int * value, int min, int max, wchar_t ** options);
	virtual void AddStringSlider(const wchar_t * opt, int * value, int min, int max, wchar_t ** options, void(*func)(int iVal));
};


void executecommand(const wchar_t* command);
void savelocation();
void loadlocation();

extern Menu theMenu;
extern Menu * menu;
extern Variables vars;
