#include "Functions.h"


wchar_t va_buffer[0x1000];
const wchar_t* va(const wchar_t* fmt, ...) {
	memset(va_buffer, 0, 0x1000);

	va_list ap;
	va_start(ap, fmt);
	vswprintf_s(va_buffer, fmt, ap);
	va_end(ap);

	return va_buffer;
}

FString FName::ToString() {
	auto tostring = reinterpret_cast<void(*)(FName*, FString*)>(0x82309EB8);
	FString str;
	tostring(this, &str);
	return str;
}

FVector FRotator::Vector() {
	FVector result;
	auto vector = reinterpret_cast<FVector*(*)(FVector*, FRotator*)>(0x822F71C0);
	vector(&result, this);
	return result;
}

void(*DrawShadowedStringZ)(uint32_t Canvas, float StartX, float StartY, const wchar_t *Text, uint32_t Font, FLinearColor *Color) = (void(*)(uint32_t, float, float, const wchar_t *, uint32_t, FLinearColor *))(0x8275C340);
void(*DrawTileZ)(uint32_t Canvas, float X, float Y, float Z, float SizeX, float SizeY, float SizeU, float SizeV, float, float, FLinearColor *Color, uint32_t Texture, int BlendMode) = (void(*)(uint32_t, float, float, float, float, float, float, float, float, float, FLinearColor *, uint32_t, int))(0x8275B9B0);
void(*DrawLine2D)(uint32_t Canvas, FVector2D *StartPos, FVector2D *EndPos, FLinearColor *Color) = (void(*)(uint32_t, FVector2D *, FVector2D *, FLinearColor *))(0x8275B550);


bool world_to_screen(const float* pos, float* screen, bool flip) {

	if (!GViewProjectionMatrix)
		return false;
	float matrix[16];
	memcpy((void*)(matrix), (const void*)(GViewProjectionMatrix), 16 * 4);

	float clipCoords[4];
	if (flip) {
		clipCoords[0] = pos[0] * matrix[0] + pos[1] * matrix[4] + pos[2] * matrix[8] + matrix[12];
		clipCoords[1] = pos[0] * matrix[1] + pos[1] * matrix[5] + pos[2] * matrix[9] + matrix[13];
		clipCoords[2] = pos[0] * matrix[2] + pos[1] * matrix[6] + pos[2] * matrix[10] + matrix[14];
		clipCoords[3] = pos[0] * matrix[3] + pos[1] * matrix[7] + pos[2] * matrix[11] + matrix[15];
	}
	else {
		clipCoords[0] = pos[0] * matrix[0] + pos[1] * matrix[1] + pos[2] * matrix[2] + matrix[3];
		clipCoords[1] = pos[0] * matrix[4] + pos[1] * matrix[5] + pos[2] * matrix[6] + matrix[7];
		clipCoords[2] = pos[0] * matrix[8] + pos[1] * matrix[9] + pos[2] * matrix[10] + matrix[11];
		clipCoords[3] = pos[0] * matrix[12] + pos[1] * matrix[13] + pos[2] * matrix[14] + matrix[15];
	}

	if (clipCoords[3] < 0.1f)
		return false;

	float NDC[3];
	NDC[0] = clipCoords[0] / clipCoords[3];
	NDC[1] = clipCoords[1] / clipCoords[3];
	NDC[2] = clipCoords[2] / clipCoords[3];

	int w = 1280;
	int h = 720;

	screen[0] = (w / 2 * NDC[0]) + (NDC[0] + w / 2);
	screen[1] = -(h / 2 * NDC[1]) + (NDC[1] + h / 2);
	return true;
}


namespace APlayerController {
	FString* (*ConsoleCommand)(FString*, uint32_t, FString*, unsigned int) = (FString* (*)(FString*, uint32_t, FString*, unsigned int))(0x824C08D0);
}


uint32_t GEngine;
uint32_t GWorld;
uint32_t GCanvas;
uint32_t GUCanvas;
uint32_t GSceneView;
uint32_t GPlayerController;
uint32_t GPawn;
uint32_t GGearWeapon;
uint32_t GViewProjectionMatrix;

