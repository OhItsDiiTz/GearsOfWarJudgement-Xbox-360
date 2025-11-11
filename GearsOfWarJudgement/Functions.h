#pragma once
#include "Main.h"


const wchar_t* va(const wchar_t* fmt, ...);

struct FLinearColor
{
	float R;
	float G;
	float B;
	float A;
};

struct FVector2D
{
	float X;
	float Y;
};
struct FVector;
struct FVector
{
	float X;
	float Y;
	float Z;
};

struct FRotator
{
	int Pitch;
	int Yaw;
	int Roll;
	FVector Vector();
};


struct FPlane : FVector
{
	float W;
};

struct FMatrix
{
	float M[4][4];
};

struct FString;
struct FName
{
	int Index;
	int Number;
	FString ToString();
};

template< class T >
struct TArray
{
public:
	T* Data;
	int Count;
	int Max;

public:
	TArray()
	{
		Data = NULL;
		Count = Max = 0;
	};

public:
	int Num()
	{
		return this->Count;
	};

	T& operator() (int i)
	{
		return this->Data[i];
	};

	const T& operator() (int i) const
	{
		return this->Data[i];
	};

	void Add(T InputData)
	{
		Data = (T*)malloc(sizeof(T) * (Count + 1));
		Data[Count++] = InputData;
		Max = Count;
	};

	void Clear()
	{
		free(Data);
		Count = Max = 0;
	};

	inline T GetIndex(int i) const
	{
		T Addr = (T)((unsigned long)Data[i] ^ i);
		return Addr;
	}
};

struct FString : public TArray< wchar_t >
{
	FString() {};
	~FString() {};

	FString(wchar_t* Other)
	{
		this->Max = this->Count = *Other ? (wcslen(Other) + 1) : 0;

		if (this->Count)
			this->Data = Other;
	};

	FString(const wchar_t* Other)
	{
		this->Max = this->Count = *Other ? (wcslen(Other) + 1) : 0;
		if (this->Count)
		{
			this->Data = const_cast<wchar_t*>(Other);
		}
	};

	FString operator = (wchar_t* Other)
	{
		if (this->Data != Other)
		{
			this->Max = this->Count = *Other ? (wcslen(Other) + 1) : 0;

			if (this->Count)
				this->Data = Other;
		}

		return *this;
	};

	inline bool IsValid() const
	{
		return Data != nullptr;
	}

	inline const wchar_t* c_str() const
	{
		return Data;
	}
};

#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif

#ifndef M_PI_F
#define M_PI_F		((float)(M_PI))
#endif

#ifndef DEG2RAD
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#endif

void inline SinCos(float radians, float * sine, float * cosine)
{
	*sine = sinf(radians);
	*cosine = cosf(radians);
}
void AngleVectors(FVector* angles, FVector* forward)
{
	float	sp, sy, cp, cy;

	SinCos(DEG2RAD(angles->X), &sy, &cy);
	SinCos(DEG2RAD(angles->Y), &sp, &cp);

	forward->X = cp * cy;
	forward->Y = cp * sy;
	forward->Z = -sp;
}

struct FTraceHitInfo
{
	uint32_t Material;
	uint32_t PhysMaterial;
	int Item;
	int LevelIndex;
	FName BoneName;
	uint32_t HitComponent;
};


extern void(*DrawShadowedStringZ)(uint32_t Canvas, float StartX, float StartY, const wchar_t *Text, uint32_t Font, FLinearColor *Color);
extern void(*DrawTileZ)(uint32_t Canvas, float X, float Y, float Z, float SizeX, float SizeY, float SizeU, float SizeV, float, float, FLinearColor *Color, uint32_t Texture, int BlendMode);
extern void(*DrawLine2D)(uint32_t Canvas, FVector2D *StartPos, FVector2D *EndPos, FLinearColor *Color);


bool world_to_screen(const float* pos, float* screen, bool flip = false);



namespace APlayerController {
	extern FString* (*ConsoleCommand)(FString*, uint32_t, FString*, unsigned int);
}


extern uint32_t GEngine;
extern uint32_t GWorld;
extern uint32_t GCanvas;
extern uint32_t GUCanvas;
extern uint32_t GSceneView;
extern uint32_t GPlayerController;
extern uint32_t GPawn;
extern uint32_t GGearWeapon;
extern uint32_t GViewProjectionMatrix;

