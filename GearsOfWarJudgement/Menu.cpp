#include "Menu.h"

FLinearColor white = { 1.0f, 1.0f, 1.0f, 1.0f };
FLinearColor blackFaded = { 0.0f, 0.0f, 0.0f, 0.65f };
FLinearColor red = { 1.0f, 0.0f, 0.0f, 1.0f };

FLinearColor colors[32] = {
	{1.0f, 1.0f, 1.0f, 1.0f},    // White
	{1.0f, 0.0f, 0.0f, 1.0f},    // Red
	{0.0f, 1.0f, 0.0f, 1.0f},    // Green
	{0.0f, 0.0f, 1.0f, 1.0f},    // Blue
	{1.0f, 1.0f, 0.0f, 1.0f},    // Yellow
	{1.0f, 0.0f, 1.0f, 1.0f},    // Magenta
	{0.0f, 1.0f, 1.0f, 1.0f},    // Cyan
	{1.0f, 0.5f, 0.0f, 1.0f},    // Orange
	{0.5f, 0.0f, 0.0f, 1.0f},    // Dark Red
	{0.0f, 0.5f, 0.0f, 1.0f},    // Dark Green
	{0.0f, 0.0f, 0.5f, 1.0f},    // Dark Blue
	{0.5f, 0.5f, 0.0f, 1.0f},    // Olive
	{0.5f, 0.0f, 0.5f, 1.0f},    // Purple
	{0.0f, 0.5f, 0.5f, 1.0f},    // Teal
	{1.0f, 0.75f, 0.8f, 1.0f},   // Pink
	{0.6f, 0.4f, 0.2f, 1.0f},    // Brown
	{0.8f, 0.8f, 0.8f, 1.0f},    // Light Gray
	{0.3f, 0.3f, 0.3f, 1.0f},    // Dark Gray
	{0.0f, 1.0f, 0.5f, 1.0f},    // Spring Green
	{1.0f, 0.4f, 0.7f, 1.0f},    // Coral
	{0.3f, 0.15f, 0.7f, 1.0f},   // Indigo
	{0.5f, 1.0f, 0.0f, 1.0f},    // Chartreuse
	{0.9f, 0.6f, 0.4f, 1.0f},    // Tan
	{0.0f, 0.6f, 1.0f, 1.0f},    // Dodger Blue
	{0.8f, 0.2f, 0.2f, 1.0f},    // Firebrick
	{0.2f, 0.8f, 0.2f, 1.0f},    // Lime Green
	{0.2f, 0.2f, 0.8f, 1.0f},    // Royal Blue
	{1.0f, 0.9f, 0.3f, 1.0f},    // Gold
	{0.4f, 0.0f, 0.4f, 1.0f},    // Dark Violet
	{0.0f, 0.8f, 1.0f, 1.0f},    // Sky Blue
	{0.6f, 0.2f, 0.8f, 1.0f},    // Medium Purple
	{0.9f, 0.3f, 0.8f, 1.0f}     // Orchid
};


Menu::Menu() {
	isMenuOpen = false;
	CurrentMenu = 0;
	CurrentOption = 0;
}

Menu::~Menu() {
	memset(this, 0, sizeof(Menu));
}

bool Menu::isReady() {
	iTick = GetTickCount();
	return iTick > iWait;
}

void Menu::wait(int msec){
	iWait = iTick + msec;
}

bool Menu::MenuOpened() {
	return isMenuOpen;
}

void Menu::ResetMaxScroll() {
	MaxScroll = 0;
}

int Menu::GetMaxScroll() {
	return MaxScroll;
}

void SelectMenu(eMenus menuID) {
	menu->LastOption[menu->CurrentMenu] = menu->CurrentOption;
	menu->CurrentMenu = menuID;
	menu->CurrentOption = menu->LastOption[menuID];
}

void nullsub() {}

void test() {

}

bool test_bool = false;
float float_test = 1.0f;

int slider_val;
wchar_t* slider_string[5] = { 
	L"Test 1",
	L"Test 2",
	L"Test 3",
	L"Test 4",
	L"Test 5"
};

bool testing = false;

void Menu::FillGlobals() {
	uint32_t engine = *reinterpret_cast<uint32_t*>(GEngine);
	if (!engine)
		return;

	uint32_t players = *reinterpret_cast<uint32_t*>(engine + 0x4A4);
	if (!players)
		return;

	uint32_t player = *reinterpret_cast<uint32_t*>(players);
	if (!player)
		return;

	GPlayerController = *reinterpret_cast<uint32_t*>(player + 0x40);

	if (!GPlayerController)
		return;

	GPawn = *reinterpret_cast<uint32_t*>(GPlayerController + 0x1CC);

	if (!GPawn)
		return;

	GGearWeapon = *reinterpret_cast<uint32_t*>(GPawn + 0x4C0);

	if (GGearWeapon) {
		if (vars.bInfiniteAmmo) {
			*reinterpret_cast<uint32_t*>(GGearWeapon + 0x4BC) = 0;
			*reinterpret_cast<uint32_t*>(GGearWeapon + 0x4C4) = 9999;
		}
	}

}

void Menu::RenderESP() {
	if (!vars.enable_esp)
		return;
	uint32_t engine = *reinterpret_cast<uint32_t*>(GEngine);
	if (!engine)
		return;

	uint32_t players = *reinterpret_cast<uint32_t*>(engine + 0x4A4);
	if (!players)
		return;

	uint32_t player = *reinterpret_cast<uint32_t*>(players);
	if (!player)
		return;

	//GViewProjectionMatrix = GSceneView + 0x270;

	DrawShadowedStringZ(GCanvas, 200, 220, va(L"ULocalPlayer: 0x%X", player), font, &white);

	uint32_t world = *reinterpret_cast<uint32_t*>(GWorld);
	if (!world)
		return;
	DrawShadowedStringZ(GCanvas, 200, 230, va(L"world: 0x%X", world), font, &white);
	uint32_t persistentlevel = *reinterpret_cast<uint32_t*>(world + 0x50);
	if (!persistentlevel)
		return;
	DrawShadowedStringZ(GCanvas, 200, 240, va(L"persistentlevel: 0x%X", persistentlevel), font, &white);
	

	uint32_t levels = *reinterpret_cast<uint32_t*>(world + 0x44);
	int levels_count = *reinterpret_cast<int*>(world + 0x48);
	vars.iLevelCount = levels_count;
	//uint32_t actors = *reinterpret_cast<uint32_t*>(persistentlevel + 0x3C);
	//int actor_count = *reinterpret_cast<int*>(persistentlevel + 0x40);
	//DrawShadowedString(GCanvas, 200, 250, va(L"actors: 0x%X - %i", actors, actor_count), font, &white);

	float screen[2];
	FVector2D start = { 1280 / 2, 720 / 2 };
	for (int iLevel = 0; iLevel < levels_count;iLevel++) {
		uint32_t level = *reinterpret_cast<uint32_t*>(levels + (iLevel * 4));
		uint32_t actors = *reinterpret_cast<uint32_t*>(level + 0x3C);
		int actor_count = *reinterpret_cast<int*>(level + 0x40);

		if (vars.draw_level_actors[iLevel]) {
			DrawShadowedStringZ(GCanvas, 200, 250 + (iLevel * 18), va(L"Level %i: actors 0x%X - %i", iLevel, actors, actor_count), font, &white);

			for (int iActor = 0; iActor < actor_count; iActor++) {
				uint32_t actor = *reinterpret_cast<uint32_t*>(actors + (4 * iActor));
				if (actor) {
					uint32_t actorvft = *reinterpret_cast<uint32_t*>(actor);
					if (actorvft == 0x8214AA70) {

					}
					else {
						if (world_to_screen((const float*)(actor + 0x54), screen, true)) {
							//DrawLine2D(GCanvas, &start, (FVector2D*)&screen, &colors[iLevel]);
							DrawShadowedStringZ(GCanvas, screen[0], screen[1], va(L"0x%X - 0x%X", actor, actorvft), font, &white);
						}
					}
				}
			}
		}
	}

	//uint32_t tickable_actors = *reinterpret_cast<uint32_t*>(persistentlevel + 0x2A8);
	//int tickable_actor_count = *reinterpret_cast<int*>(persistentlevel + 0x2AC);
	//DrawShadowedString(GCanvas, 200, 260, va(L"tickable_actors: 0x%X - %i", tickable_actors, tickable_actor_count), font, &white);
	//
	//for (int i = 0; i < tickable_actor_count; i++) {
	//	uint32_t actor = *reinterpret_cast<uint32_t*>(tickable_actors + (4 * i));
	//	if (actor) {
	//		if (world_to_screen((const float*)(actor + 0x60), screen, true)) {
	//			DrawLine2D(GCanvas, &start, (FVector2D*)&screen, &red);
	//		}
	//	}
	//}

}

void Menu::RenderMenu() {

	if (MenuOpened()) {
		//drawRect(location[0] - 7, location[1] - 24, 183, 23 + (12 * MaxScroll), Color(0, 0, 0, 160));
		//drawRect(location[0] - 7, location[1] - 20 + (17 + (12 * CurrentOption)), 183, 12, Color(255, 0, 0, 160));


		DrawTileZ(GCanvas, location[0] - 13, location[1] - 24, 1, 350, 32 + (paddingy * MaxScroll), 0, 0, 0, 0, &blackFaded, 0, 1);
		DrawTileZ(GCanvas, location[0] - 13, location[1] - 14 + (17 + (paddingy * CurrentOption)), 1, 350, 17, 0, 0, 0, 0, &red, 0, 1);
		

		ResetMaxScroll();
		switch (CurrentMenu) {
		case MenuBase:
			menu->LastMenu[menu->CurrentMenu] = MenuBase;
			AddTitle(va(L"Quarantine | Build %i", BUILD_NUMBER));
			AddOption(L"Player Settings", SelectMenu, PlayerSettings);
			if (GPawn) {
				AddOption(L"APawn Settings", SelectMenu, APawnSettings);
			}
			if (GGearWeapon && GPawn) {
				AddOption(L"AGearWeapon Settings", SelectMenu, AGearWeaponSettings);
			}
			AddOption(L"Console Commands", SelectMenu, CommandsMenu);
			AddBool(L"Draw Watermark", &vars.bDrawWatermark);
			//AddOption(L"Debugging", SelectMenu, DebuggingMenu);
			break;
		case PlayerSettings:
			menu->LastMenu[menu->CurrentMenu] = MenuBase;
			AddTitle(L"Player Settings");
			AddBool(L"Demi Godmode", &vars.bDemiGodmode);
			AddBool(L"Infinite Ammo", &vars.bInfiniteAmmo);
			AddBool(L"Instant Kill", &vars.bInstantKill);
			AddOption(L"Save Location", savelocation);
			AddOption(L"Load Location", loadlocation);

			break;
		case APawnSettings:
			menu->LastMenu[menu->CurrentMenu] = MenuBase;
			AddTitle(L"APawn Settings");
			if (GPawn) {
				AddSlider<float>(L"Alertness", (float*)(GPawn + 0x234), 1.0f, 10000000.0f, 1.0f, L"%.2f");
				AddSlider<float>(L"Mass", (float*)(GPawn + 0x244), 1.0f, 10000000.0f, 1.0f, L"%.2f");
				AddSlider<float>(L"Buoyancy", (float*)(GPawn + 0x248), 1.0f, 10000000.0f, 1.0f, L"%.2f");
				AddSlider<float>(L"Ground Speed", (float*)(GPawn + 0x288), 1.0f, 10000000.0f, 1.0f, L"%.2f");
				AddSlider<float>(L"Air Speed", (float*)(GPawn + 0x290), 1.0f, 10000000.0f, 1.0f, L"%.2f");
				AddSlider<float>(L"Ladder Speed", (float*)(GPawn + 0x294), 1.0f, 10000000.0f, 1.0f, L"%.2f");
				AddSlider<float>(L"Accel Rate", (float*)(GPawn + 0x298), 1.0f, 10000000.0f, 1.0f, L"%.2f");
				//AddSlider<float>(L"Jump Z", (float*)(GPawn + 0x298), 1.0f, 10000000.0f, 1.0f, L"%.2f");
			}
			break;
		case AGearWeaponSettings:
			menu->LastMenu[menu->CurrentMenu] = MenuBase;
			AddTitle(L"AGearWeapon Settings");
			if (GGearWeapon) {
				AddSlider<float>(L"WeaponDamage", (float*)(GGearWeapon + 0x418), 0.0f, 10000000.0f, 0.01f, L"%.2f");
				AddSlider<float>(L"WeaponMagSize", (float*)(GGearWeapon + 0x420), 0.0f, 10000000.0f, 1.0f, L"%.2f");
				AddSlider<float>(L"WeaponMaxSpareAmmo", (float*)(GGearWeapon + 0x424), 0.0f, 10000000.0f, 1.0f, L"%.2f");
				AddSlider<float>(L"WeaponRecoil", (float*)(GGearWeapon + 0x428), 0.0f, 10000000.0f, 1.0f, L"%.2f");

				AddSlider<float>(L"WeaponRateOfFire", (float*)(GGearWeapon + 0x434), 0.0f, 10000000.0f, 1.0f, L"%.2f");
				
				AddSlider<int>(L"HordeCost", (int*)(GGearWeapon + 0x444), 0, 10000000, 1, L"%i");
			}
			break;
		case CommandsMenu:
			menu->LastMenu[menu->CurrentMenu] = MenuBase;
			AddTitle(L"Console Commands");
			AddOption(L"Quit Without Saving", executecommand, L"disconnect");
			AddOption(L"Toggle FPS", executecommand, L"stat fps");
			AddOption(L"Toggle LUM", executecommand, L"stat lum");
			AddOption(L"Toggle Hitches", executecommand, L"stat hitches");
			AddOption(L"Toggle Summary", executecommand, L"stat summary");
			AddOption(L"Toggle Named Events", executecommand, L"stat namedevents");
			AddOption(L"Toggle Levels", executecommand, L"stat levels");
			AddOption(L"Toggle Unit Times", executecommand, L"stat unit");
			AddOption(L"Toggle Tiling", executecommand, L"tiling");
			AddOption(L"Toggle Tiling Mode", executecommand, L"tilingmode");
			//AddOption(L"Custom Command", executecommand, (const wchar_t*)buffer);
			break;
		case DebuggingMenu:
			menu->LastMenu[menu->CurrentMenu] = MenuBase;
			AddTitle(L"Debugging");

			AddBool(L"Enable ESP", &vars.enable_esp);

			for (int i = 0; i < vars.iLevelCount;i++) {
				AddBool(va(L"Draw Level %i Actors", i), &vars.draw_level_actors[i]);
			}
			break;
		}
	}
}

void Menu::RunControls() {
	if (isReady()) {
		if (!MenuOpened()) { //(input.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0
			if (input.Gamepad.bLeftTrigger && (input.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0) {
				isMenuOpen = true;
				wait(250);
			}
		}
		else {
			if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0) {
				if (menu->CurrentMenu == MenuBase) {
					isMenuOpen = false;
				}
				else {
					SelectMenu((eMenus)menu->LastMenu[menu->CurrentMenu]);

				}
				wait(150);
			}
			if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0) {
				CurrentOption -= 1;
				if (CurrentOption < 0) {
					CurrentOption = GetMaxScroll() - 1;
				}
				wait(150);
			}
			if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0) {
				CurrentOption += 1;
				if (CurrentOption > GetMaxScroll() - 1) {
					CurrentOption = 0;
				}
				wait(150);
			}
		}
	}
}

void Menu::AddTitle(const wchar_t * title) {
	DrawShadowedStringZ(GCanvas, this->location[0] - 7, this->location[1] - 18, title, font, &white);
}

void Menu::AddOption(const wchar_t * opt, void(*func)()) {
	DrawShadowedStringZ(GCanvas, this->location[0], this->location[1] + (MaxScroll * paddingy), opt, font, &white);

	if (isReady()) {
		if (CurrentOption == MaxScroll) {
			if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0) {
				func();
				wait(150);
			}
		}
	}
	MaxScroll += 1;
}

template<typename T> void Menu::AddOption(const wchar_t * opt, void(*func)(T value), T value) {
	DrawShadowedStringZ(GCanvas, this->location[0], this->location[1] + (MaxScroll * paddingy), opt, font, &white);

	if (isReady()) {
		if (CurrentOption == MaxScroll) {
			if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0) {
				func(value);
				wait(150);
			}
		}
	}
	MaxScroll += 1;
}

void Menu::AddBool(const wchar_t * opt, bool * value) {
	DrawShadowedStringZ(GCanvas, this->location[0], this->location[1] + (MaxScroll * paddingy), opt, font, &white);

	//float width, height;
	//WrappedStrLenf(GCanvas, font, 1.0f, 1.0f, &width, &height, *value ? L"ON" : L"OFF");

	DrawShadowedStringZ(GCanvas, this->location[0] + 270, this->location[1] + (MaxScroll * paddingy), *value ? L"ON" : L"OFF", font, *value ? &colors[2] : &colors[1]);

	if (isReady()) {
		if (CurrentOption == MaxScroll) {
			if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0) {
				*value = !*value;
				wait(150);
			}
		}
	}

	MaxScroll += 1;
}

void Menu::AddBool(const wchar_t * opt, bool * value, void(*func)(bool value)) {
	DrawShadowedStringZ(GCanvas, this->location[0], this->location[1] + (MaxScroll * paddingy), opt, font, &white);
	DrawShadowedStringZ(GCanvas, this->location[0] + 270, this->location[1] + (MaxScroll * paddingy), *value ? L"ON" : L"OFF", font, &white);

	if (isReady()) {
		if (CurrentOption == MaxScroll) {
			if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0) {
				*value = !*value;
				func(*value);
				wait(20);
			}
		}
	}

	MaxScroll += 1;
}


template<typename T>
void Menu::AddSlider(const wchar_t * opt, T * value, T min, T max, T scale, const wchar_t* format) {
	DrawShadowedStringZ(GCanvas, this->location[0], this->location[1] + (MaxScroll * paddingy), opt, font, &white);
	DrawShadowedStringZ(GCanvas, this->location[0] + 270, this->location[1] + (MaxScroll * paddingy), va(format, *value), font, &white);

	if (isReady()) {
		if (CurrentOption == MaxScroll) {
			if (min == 0.0f) {
				if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0) {
					if (*value > (min)) {
						*value -= ((input.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0) ? (50 * scale) : scale;
					}
					wait(50);
				}
				if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0) {
					if (*value < (max - scale)) {
						*value += ((input.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0) ? (50 * scale) : scale;
					}
					wait(50);
				}
			}
			else {
				if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0) {
					if (*value >(min)) {
						*value -= ((input.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0) ? (50 * scale) : scale;
					}
					wait(20);
				}
				if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0) {
					if (*value < (max)) {
						*value += ((input.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0) ? (50 * scale) : scale;
					}
					wait(20);
				}
			}
		}
	}

	MaxScroll += 1;
}

template<typename T>
void Menu::AddSlider(const wchar_t * opt, T * value, T min, T max, T scale, const wchar_t* format, void(*func)(T val)) {
	DrawShadowedStringZ(GCanvas, this->location[0], this->location[1] + (MaxScroll * paddingy), opt, font, &white);
	DrawShadowedStringZ(GCanvas, this->location[0] + 270, this->location[1] + (MaxScroll * paddingy), va(format, *value), font, &white);

	if (isReady()) {
		if (CurrentOption == MaxScroll) {
			if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0) {
				func(*value);
				wait(120);
			}
			if (min == 0.0f) {
				if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0) {
					if (*value > (min - min)) {
						*value -= ((input.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0) ? (50 * scale) : scale;
					}
					wait(20);
				}
				if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0) {
					if (*value < (max - scale)) {
						*value += ((input.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0) ? (50 * scale) : scale;
					}
					wait(20);
				}
			}
			else {
				if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0) {
					if (*value >(min)) {
						*value -= ((input.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0) ? (50 * scale) : scale;
					}
					wait(20);
				}
				if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0) {
					if (*value < (max)) {
						*value += (input.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0 ? (50 * scale) : scale;
					}
					wait(20);
				}
			}
		}
	}

	MaxScroll += 1;
}

void Menu::AddStringSlider(const wchar_t * opt, int * value, int min, int max, wchar_t ** options) {
	DrawShadowedStringZ(GCanvas, this->location[0], this->location[1] + (MaxScroll * paddingy), opt, font, &white);
	DrawShadowedStringZ(GCanvas, this->location[0] + 270, this->location[1] + (MaxScroll * paddingy), options[*value], font, &white);

	if (isReady()) {
		if (CurrentOption == MaxScroll) {
			if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0) {
				if (*value > (min)) {
					*value -= 1;
					wait(100);
				}
			}
			if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0) {
				if (*value < (max - 1)) {
					*value += 1;
				}
				wait(100);
			}
		}
	}
	MaxScroll += 1;
}

void Menu::AddStringSlider(const wchar_t * opt, int * value, int min, int max, wchar_t ** options, void(*func)(int iVal)) {
	DrawShadowedStringZ(GCanvas, this->location[0], this->location[1] + (MaxScroll * paddingy), opt, font, &white);
	DrawShadowedStringZ(GCanvas, this->location[0] + 270, this->location[1] + (MaxScroll * paddingy), options[*value], font, &white);

	if (isReady()) {
		if (CurrentOption == MaxScroll) {
			if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0) {
				func(*value);
				wait(150);
			}
			if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0) {
				if (*value > (min)) {
					*value -= 1;
				}
				wait(150);
			}
			if ((input.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0) {
				if (*value < (max - 1)) {
					*value += 1;
				}
				wait(150);
			}
		}
	}
	MaxScroll += 1;
}


void executecommand(const wchar_t* command) {
	if (GPlayerController) {
		if (wcscmp(command, L"disconnect") == 0) {
			menu->isMenuOpen = false;
			menu->CurrentMenu = MenuBase;
			menu->CurrentOption = 0;
		}
		FString result = L"";
		FString cmd = command;
		APlayerController::ConsoleCommand(&result, GPlayerController, &cmd, 0);
	}
}

void savelocation() {
	if (!GPawn)
		return;
	vars.saved_location = *reinterpret_cast<FVector1*>(GPawn + 0x54);
}

void loadlocation() {
	if (!GPawn)
		return;
	
	if (vars.saved_location.X == 0)
		return;

	*reinterpret_cast<FVector1*>(GPawn + 0x54) = vars.saved_location;
}

Menu theMenu;
Menu * menu;
Variables vars;
