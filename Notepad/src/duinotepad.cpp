/*
 * Leet.UI.DuiKit.NotePad
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the Simple Classic Theme License as published by Anis
 * Errais (Leet), either version 1.0 of the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the Simple Classic Theme License along
 * with this program. If not, see <https://simpleclassictheme.nl/license.html>.
 *
 * duinotepad.cpp: Main Entry point
 *
 */

#include "stdafx.h"
#include "NotepadWindow.h"
#include "NotepadListener.h"
#include "LineNumEditElement.h"
#define LINENUMEDIT_IMPL
#include "../../LineNumEdit/LineNumEdit.hpp"

using namespace DirectUI;
using namespace Leet::UI::DuiKit::Notepad;

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(nShowCmd);

    HRESULT hRes;

    // Initialize DUI within the process
    hRes = InitProcessPriv(14, NULL, 0, true);

    // Intialize DUI within the thread
    hRes = InitThread(2);
    if (FAILED(hRes))
        exit(hRes);

    // Register DUI control set
    RegisterAllControls();

    // Register LineNumEdit win32 control
    LineNumEdit::SuperclassWindow();
    CLineNumEditElement::Register();

    // Create the main menu
    CNotepadWindow* mainWindow;
    bool shit = CNotepadWindow::Create(&mainWindow, hInstance);

    // Create a listener
    CNotepadListener* listener = new CNotepadListener(mainWindow);

    // Create the menu
    HMENU menu = LoadMenuW(hInstance, MAKEINTRESOURCEW(IDR_MENU1));
    mainWindow->SetMenu(menu);

    // Message loop
    {
        BOOL bRet;
        MSG msg;
        while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
        {
            if (bRet == -1)
            {
                // Handle the error and possibly exit
            }
            else
            {
                TranslateMessage(&msg);
                if (mainWindow->HandleMenuMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam))
                    continue;
                DispatchMessage(&msg);
            }
        }
    }

    // DirectUI uninitialize thread
    UnInitThread();
    // DirectUI uninitialize process
    UnInitProcessPriv(NULL);

    return 0;
}