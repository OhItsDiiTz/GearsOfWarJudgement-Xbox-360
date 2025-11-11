#include "Main.h"

void* ResolveFunction(const std::string& moduleName, uint32_t ordinal)
{
	HMODULE hModule = GetModuleHandle(moduleName.c_str());

	return (hModule == NULL) ? NULL : GetProcAddress(hModule, reinterpret_cast<const char*>(ordinal));
}
typedef void(*XNOTIFYQUEUEUI)(int type, uint32_t userIndex, unsigned __int64 areas, const wchar_t* displayText, void* pContextData);
static XNOTIFYQUEUEUI XNotifyQueueUI = static_cast<XNOTIFYQUEUEUI>(ResolveFunction("xam.xex", 656));
const std::wstring final_str = L"Join discord.gg/bskh4ZG32J";

wchar_t buffer[0x500];

Detour<void> Draw;
void Draw_Detour(uint32_t ViewPortClient, uint32_t Viewport, uint32_t Canvas) {
	ZeroMemory(&input, sizeof(XINPUT_STATE));
	XInputGetState(0, &input);
	GCanvas = Canvas;
	Draw.CallOriginal(ViewPortClient, Viewport, Canvas);
	uint32_t gengine = *reinterpret_cast<uint32_t*>(GEngine);
	if (gengine)
	{
		uint32_t font = *reinterpret_cast<uint32_t*>(gengine + 0x60);
		if (font) {
			menu->font = font;

			//console.draw(Canvas, 10.f, 40.f, font, &red, DrawShadowedStringZ);

			if (vars.bDrawWatermark) {
				DrawShadowedStringZ(Canvas, 15, 15, va(L"Join discord.gg/bskh4ZG32J | Build %i", BUILD_NUMBER), font, &white);
			}

			menu->FillGlobals();
			menu->RenderESP();
			menu->RenderMenu();
			menu->RunControls();

			//DrawTileZ(Canvas, 20, 20, 1, 20, 20, 0, 0, 0, 0, &blackFaded, 0, 1);
			//DrawShadowedString(Canvas, 20, 20, L"testing string", font, &white);
		}
	}
}

DWORD XamInputGetState_Detour(DWORD dwUserIndex, DWORD dwFlags, PXINPUT_STATE pState) {
	DWORD ret = XInputGetStateEx(dwUserIndex, dwFlags, pState);
	//memcpy(&input, pState, sizeof(XINPUT_STATE));
	if (menu->isMenuOpen) {
		if (pState->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_UP;
		if (pState->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_DOWN;
		if (pState->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_LEFT;
		if (pState->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_RIGHT;
		if (pState->Gamepad.wButtons & XINPUT_GAMEPAD_A) pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_A;
	}
	return ret;
}

namespace APawn {
	Detour<void> TickSpecial;
	void TickSpecial_Detour(uint32_t pawn, float DeltaSeconds) {

		if (pawn != GPawn) {
			if (vars.bInstantKill) {
				*reinterpret_cast<int*>(pawn + 0x2DC) = 1;
			}
		}
		else {
			if (vars.bDemiGodmode) {
				*reinterpret_cast<int*>(pawn + 0x2DC) = 9999999;
			}
		}

		TickSpecial.CallOriginal(pawn, DeltaSeconds);
	}
}

void Start() {
	Sleep(10);

	menu = &theMenu;
	//FSceneView
	//*reinterpret_cast<uint32_t*>(0x820F1488) = (uint32_t)TestFunc;
	menu->location[0] = 85;
	menu->location[1] = 65;
	menu->paddingy = 18;

	vars.iShotCount = 1;
	vars.bDrawWatermark = true;

	GEngine = 0x83544E04;
	GWorld = 0x835455C0;
	
	Draw.SetupDetour(0x82639B48, Draw_Detour);
	PatchInJump((DWORD*)(0x8309DE1C), XamInputGetState_Detour, false);
	APawn::TickSpecial.SetupDetour(0x8259F720, APawn::TickSpecial_Detour);
	
	
	XNotifyQueueUI(14, 0, XNOTIFY_SYSTEM, va(L"Gears Of War Judgement Hook Loaded | Build %i", BUILD_NUMBER), nullptr);
}

BOOL WINAPI DllMain(HANDLE hInstDLL, DWORD fdwReason, LPVOID lpReserved) {
	
	if (fdwReason == DLL_PROCESS_ATTACH) {
		
		printf("Quarantine\n");
		Start();
	}

	if (fdwReason == DLL_PROCESS_DETACH) {

		///DrawFPSCounter_Detour.TakeDownDetour();
		///
		///*(uint32_t*)(0x825339E8) = 0x4810AF79;
		///*(uint32_t*)(0x831457B8) = 0;
		printf("Module UnLoaded!\n");
	}
	return TRUE;
}

void blr(u32 address) {
	*(u32*)(address) = 0x4E800020;
}

void nop(u32 address) {
	*(u32*)(address) = 0x60000000;
}

XINPUT_STATE input;
MiniConsole console;

