#ifndef CONSTANTS_H
#define CONSTANTS_H

#include<iostream>
#include<vector>


struct EnumWindowData
{
    std::wstring targetWindowTitle;
    std::vector<std::wstring> matchingWindowTitles;
};

// Keycode for key "F"
const int VK_F = 0x46;

#endif
