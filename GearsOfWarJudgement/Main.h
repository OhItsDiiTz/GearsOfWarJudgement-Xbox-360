#pragma once

#include <xtl.h>
#include <xboxmath.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <fstream>
#include <vector>
#include <xhttp.h>
#include <xbox.h>
#include <rtcapi.h>
#include <algorithm>

#include <cstddef>
#include <array>
#include <cstdint>
#include <cmath>



typedef unsigned __int64 uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

#include "buildnumber.h"

/* Xbox SDK Local Headers */
#include "Kernel.h"
#include "Utilities.h"
#include "GameStructures.h"
#include "Detours.h"
#include "Functions.h"
#include "Menu.h"

extern wchar_t buffer[0x500];

class MiniConsole {
public:
	MiniConsole() {}

	void addLine(const std::wstring& line) {
		if (lines.size() == MAX_CONSOLE_LINES)
			lines.pop_back();
		lines.push_back(line);
	}

	void draw(uint32_t Canvas, float StartX, float StartY, uint32_t Font, FLinearColor *Color,
		void(*DrawShadowedStringZ)(uint32_t, float, float, const wchar_t*, uint32_t, FLinearColor*)) {
		float y = StartY;
		std::vector<std::wstring>::iterator it;
		for (it = lines.begin(); it != lines.end(); ++it) {
			DrawShadowedStringZ(Canvas, StartX, y, it->c_str(), Font, Color);
			y += LINE_SPACING;
		}
	}

public:
	std::vector<std::wstring> lines;
	static const size_t MAX_CONSOLE_LINES = 10;
	static const float LINE_SPACING;
};

// Static member initialization outside the class in C++03
const float MiniConsole::LINE_SPACING = 20.f;



void blr(u32 address);
void nop(u32 address);

extern XINPUT_STATE input;
extern MiniConsole console;

