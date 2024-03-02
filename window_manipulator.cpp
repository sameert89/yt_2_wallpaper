#include "window_manipulator.h";

WindowManipulator::WindowManipulator(std::wstring windowTitle) {
    this->data.targetWindowTitle = windowTitle;
    this->data.matchingWindowTitles = std::vector < std::wstring>();
}

BOOL CALLBACK WindowManipulator::EnumWidowsProc(HWND hwnd, LPARAM lParam) {
    EnumWindowData* data = reinterpret_cast<EnumWindowData*>(lParam);

    const DWORD TITLE_SIZE = 1024;
    WCHAR windowTitle[TITLE_SIZE];

    if (GetWindowTextW(hwnd, windowTitle, TITLE_SIZE) && wcslen(windowTitle) > 0)
    {
        std::wstring windowTitleWstr = windowTitle;
        if (windowTitleWstr.find(data->targetWindowTitle) != std::wstring::npos)
        {
            data->matchingWindowTitles.push_back(windowTitleWstr);
        }
    }

    return TRUE; // Continue enumeration
}

void WindowManipulator::lockWindow(HWND hwnd) {
    std::cout << " I worked";
    // Make the window active
    SetForegroundWindow(hwnd);
    // Simulate "F" key press using SendInput
    INPUT input[2] = {};
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = VK_F;  // Virtual-Key code for "F"
    input[0].ki.dwFlags = 0; // 0 for key press

    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = VK_F;                // Virtual-Key code for "F"
    input[1].ki.dwFlags = KEYEVENTF_KEYUP; // Indicate key release

    SendInput(2, input, sizeof(INPUT));

    // Set the window to the bottom of the Z-order
    SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    // Change window style to ignore mouse inputs
    LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);
    SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_TRANSPARENT | WS_EX_LAYERED);

}
void WindowManipulator::unlockWindow(HWND hwnd) {
    // Restore the window to its original position in the Z-order
    SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    // Remove the window styles that were added to ignore mouse inputs
    LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);
    style &= ~(WS_EX_TRANSPARENT | WS_EX_LAYERED);
    SetWindowLong(hwnd, GWL_EXSTYLE, style);
}

std::wstring WindowManipulator::ConvertToWideString(const char* narrowString) {
    // Get the length of the wide string
    int length = MultiByteToWideChar(CP_UTF8, 0, narrowString, -1, NULL, 0);

    // Allocate memory for the wide string
    wchar_t* wideString = new wchar_t[length];

    // Convert the narrow string to wide string
    MultiByteToWideChar(CP_UTF8, 0, narrowString, -1, wideString, length);

    // Construct the wstring from wchar_t*
    std::wstring result(wideString);

    // Clean up allocated memory
    delete[] wideString;

    return result;
}

// Convert wstring to const char *
const char* WindowManipulator::wstring_to_const_char(const std::wstring& wideString) {
    // Use wstring_convert from codecvt
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string narrowString = converter.to_bytes(wideString);

    // Return a const char* pointing to the internal buffer of the string
    return narrowString.c_str();
}
