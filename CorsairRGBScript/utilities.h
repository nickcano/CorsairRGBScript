#pragma once

#include <stdint.h>
#include <Windows.h>
#include <string>

uint32_t timeGetHighResTime();

HWND findWindowByPartialTitle(const char* title);

std::wstring getWorkingDirectory();