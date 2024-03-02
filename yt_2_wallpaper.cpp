#include <windows.h>

#include <iostream>

#include "yt_2_wallpaper.h";

#include "window_manipulator.h";

#include "constants.h";

namespace Yt2Wallpaper {
    void DrawUI(ImGuiIO &io, ImFont *fontUI, ImFont *fontTitle)
    {
        static WindowManipulator manipulator = WindowManipulator(L"YouTube");
        
        ImGui::Begin("Yt2Wallpaper");
        ImGui::PushFont(fontUI);
        ImGui::Text("Before Starting, I recommend you check the Help Section");
        if (ImGui::Button("Help")) {
            ImGui::OpenPopup("Help");
        }

        if (ImGui::BeginPopup("Help"))
        {
            ImGui::PushFont(fontTitle);
            ImGui::Text("YT2Wallpaper User Documentation");
            ImGui::PopFont();
            ImGui::Separator();
            ImGui::Text("Welcome to YT2Wallpaper! This application allows you \n to set YouTube or YouTube Music videos as live wallpapers \n on your Windows desktop. Created with love by Sameert89, \n this app aims to enhance your \n desktop experience by bringing your favorite videos to life.");
            ImGui::Separator();
            ImGui::Text("Getting Started:");
            ImGui::BulletText("Open the YT2Wallpaper application on your Windows system.");
            ImGui::BulletText("Make sure you have your desired YouTube or YouTube \n Music video open in a separate browser window.");
            ImGui::BulletText("Select the target application (YouTube or YouTube Music) from the menu.");
            ImGui::BulletText("If you have multiple browser windows open, choose \n the appropriate one from the dropdown menu within the YT2Wallpaper application.");
            ImGui::BulletText("Press the 'Set' button to make the selected video your wallpaper.");
            ImGui::Separator();
            ImGui::Text("Removing the Wallpaper:");
            ImGui::BulletText("Open the YT2Wallpaper application again.");
            ImGui::BulletText("Click the 'Unset' button to unlock the window and \n revert to your previous desktop background.");
            ImGui::Separator();
            ImGui::Text("Consider Supporting Development:");
            ImGui::BulletText("YT2Wallpaper is a passion project developed by Sameert89.");
            ImGui::BulletText("Consider donating to support ongoing development efforts.");
            ImGui::BulletText("Your contributions help ensure that YT2Wallpaper \n remains a reliable and innovative tool for enhancing your desktop experience.");
            ImGui::Separator();
            ImGui::Text("Thank you for using YT2Wallpaper! Enjoy your dynamic \n wallpapers and have fun customizing your desktop.");
            ImGui::EndPopup();
        }

        std::vector<const char *> supportedApps = {"YouTube", "YouTube Music"};
        static int itemCurrent = 0;
        ImGui::Text("Target Application -");
        ImGui::SameLine();
        if (ImGui::BeginCombo("##dropdown", supportedApps[itemCurrent]))
        {
            for (int i = 0; i < supportedApps.size(); i++)
            {
                bool isSelected = (itemCurrent == i);

                // Display the current item in the dropdown list
                if (ImGui::Selectable(supportedApps[i], isSelected))
                {
                    itemCurrent = i; // Update the selected item index if it's clicked
                }

                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo(); // End the dropdown
        }
        static HWND hwnd = nullptr;
        static int windowIndex = 0;
        if (ImGui::Button("Search")) {
            manipulator.data.targetWindowTitle = manipulator.ConvertToWideString(supportedApps[itemCurrent]);
            EnumWindows(manipulator.EnumWidowsProc, reinterpret_cast<LPARAM>(&manipulator.data));
            /* ImGui::Text("Found Multiple %s Windows!", std::string(supportedApps[itemCurrent]));
            ImGui::Separator();
            ImGui::Text("Select the window -");
            if (ImGui::BeginCombo("##dropdown", manipulator.wstring_to_const_char(manipulator.data.matchingWindowTitles[windowIndex])))
            {
                for (int i = 0; i < manipulator.data.matchingWindowTitles.size(); i++)
                {
                    bool isSelected = (windowIndex == i);

                    // Display the current item in the dropdown list
                    if (ImGui::Selectable(manipulator.wstring_to_const_char(manipulator.data.matchingWindowTitles[i]), isSelected))
                    {
                        windowIndex = i; // Update the selected item index if it's clicked
                    }

                    if (isSelected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }

                ImGui::EndCombo(); // End the dropdown
            } */
        }

        if (ImGui::Button("Set Wallpaper")) {
            hwnd = FindWindowW(NULL, manipulator.data.matchingWindowTitles[windowIndex].c_str());
            manipulator.lockWindow(hwnd);
        }
        ImGui::SameLine();
        if (ImGui::Button("Unset Wallpaper")) {

            manipulator.unlockWindow(hwnd);
        }
        ImGui::PopFont();
        ImGui::End();
    }
}
