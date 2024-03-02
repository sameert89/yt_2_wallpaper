#ifndef WINDOW_MANIPULATOR_H
#define WINDOW_MAINPULATOR_H
#include<iostream>
#include<vector>
#include<windows.h>
#include <string>
#include <codecvt> // for std::wstring_convert (C++11)
#include <string_view> // for std::string_view (C++17)
#include "constants.h"

class WindowManipulator {
public:
    EnumWindowData data;
    WindowManipulator(std::wstring windowTitle);
    // Helper callback function to enumerate and store matching window titles
    static BOOL CALLBACK EnumWidowsProc(HWND hwnd, LPARAM lParam);
    static std::wstring ConvertToWideString(const char* narrowString);
    static const char* wstring_to_const_char(const std::wstring& wideString);
    static void lockWindow(HWND hwnd);
    static void unlockWindow(HWND hwnd);
};

#endif
