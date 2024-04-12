//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
// THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//*********************************************************

// main.cpp : Defines the entry point for the application.

#include "stdafx.h"
#include "main.h"
#include "WinComp.h"

using namespace winrt;
using namespace Windows::UI;
using namespace Windows::UI::Composition;
using namespace Windows::UI::Composition::Desktop;
using namespace Windows::UI::Input;


#define MAX_LOADSTRING 100
#define CDSSHAREDHANDLE 0x123987

// Global Variables:
HINSTANCE	 hInst;               // current instance
HANDLE       receivedHandle;
HANDLE       parentProccess;
std::wstring szTitle;             // The title bar text
std::wstring szWindowClass;       // the main window class name
HWND         m_childHWnd;
WinComp*     m_winComp;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

bool isSecondary = false;
volatile bool handleReceived = false;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    isSecondary = wcscmp(lpCmdLine, L"SecondaryProcess") == 0;

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    winrt::init_apartment(winrt::apartment_type::single_threaded);

    // Initialize global strings
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //LoadStringW(hInstance, IDC_VIRTUALSURFACES, szWindowClass, MAX_LOADSTRING);
    szTitle = isSecondary ? L"VirtualSurfaces.Secondary" : L"VirtualSurfaces.Primary";
    szWindowClass = isSecondary ? L"CompositionTiles.Secondary" : L"CompositionTiles.Primary";
    MyRegisterClass(hInstance);
    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VIRTUALSURFACES));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (handleReceived)
        {
            handleReceived = false;

            m_winComp->PrepareVisuals(receivedHandle);
            m_winComp->UpdateViewPort(true);
            m_winComp->ConfigureInteraction();
        }
    }
    return (int)msg.wParam;
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VIRTUALSURFACES));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_VIRTUALSURFACES);
    wcex.lpszClassName = szWindowClass.c_str();
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWndParent = CreateWindowW(szWindowClass.c_str(), szTitle.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWndParent)
    {
        return FALSE;
    }

    //Create the child HWND with the same size as the parent HWND, so it fills up the entire space. 

    RECT rect;
    ::GetWindowRect(hWndParent, &rect);

    m_childHWnd = CreateWindowW(szWindowClass.c_str(), szTitle.c_str(), WS_CHILD,
        0, 0, rect.right - rect.left, rect.bottom - rect.top,
        hWndParent, nullptr, hInstance, nullptr);

    if (!m_childHWnd)
    {
        return FALSE;
    }

    // Ensure that the DispatcherQueue is initialized. This is required by the Compositor. 
    auto controller = WinComp::EnsureDispatcherQueue();

    ShowWindow(hWndParent, nCmdShow);
    UpdateWindow(hWndParent);
    ShowWindow(m_childHWnd, nCmdShow);
    UpdateWindow(m_childHWnd);

    if (!isSecondary)
    {
        Visual visual{ nullptr };
        Compositor compositor;
        DesktopWindowTarget target{ nullptr };
        auto interop = compositor.try_as<ABI::Windows::UI::Composition::Desktop::ICompositorDesktopInterop>();
        interop->CreateDesktopWindowTarget(m_childHWnd, true, reinterpret_cast<ABI::Windows::UI::Composition::Desktop::IDesktopWindowTarget **>(winrt::put_abi(target)));
        auto partner = compositor.try_as<ICompositorPartner>();
        partner->CreateSharedVisual(reinterpret_cast<ABI::Windows::UI::Composition::IVisual **>(winrt::put_abi(visual)));

        HANDLE sharedHandle;
        partner->OpenSharedResourceHandle(reinterpret_cast<ABI::Windows::UI::Composition::ICompositionObject *>(winrt::get_abi(visual.as<CompositionObject>())), &sharedHandle);

        STARTUPINFOA cif;
        ZeroMemory(&cif, sizeof(cif));
        cif.cb = sizeof(cif);

        PROCESS_INFORMATION pi;
        ZeroMemory(&pi, sizeof(pi));

        std::string cmd = GetCommandLineA();
        cmd += " SecondaryProcess";
        CreateProcessA(NULL, (LPSTR)cmd.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &cif, &pi);

        target.Root(visual);
        visual.RelativeSizeAdjustment({ 1, 1 });

        HANDLE secondaryHandle;
        DuplicateHandle(GetCurrentProcess(), sharedHandle, pi.hProcess, &secondaryHandle, NULL, FALSE, DUPLICATE_SAME_ACCESS);

        COPYDATASTRUCT CDS;
        CDS.cbData = sizeof(HANDLE);
        CDS.dwData = CDSSHAREDHANDLE;
        CDS.lpData = &secondaryHandle;

        // Wait for the secondary process to spawn its window
        Sleep(500);

        HWND secondaryHwnd = FindWindowW(L"CompositionTiles.Secondary", NULL);
        SendMessage(secondaryHwnd, WM_COPYDATA, (WPARAM)(HWND)hWndParent, (LPARAM)(LPVOID)&CDS);

        MSG msg;
        while (GetMessage(&msg, nullptr, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return (int)msg.wParam;

        CloseHandle(pi.hThread);
        TerminateProcess(pi.hProcess, 0);

        CloseHandle(sharedHandle);
        CloseHandle(secondaryHandle);

        return FALSE;
    }
    else
    {
        m_winComp = winrt::make_self<WinComp>().detach();
        m_winComp->Initialize(m_childHWnd);
    }

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_POINTERDOWN:
    {
        //Redirect input events to the InteractionTracker for input events.
        if (isSecondary)
        {
            PointerPoint pp = PointerPoint::GetCurrentPoint(GET_POINTERID_WPARAM(wParam));
            if (m_winComp != nullptr)
                m_winComp->TryRedirectForManipulation(pp);
        }
        break;
    }


    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_SIZE:
    {
        //Update the child HWND to the new size of the parent HWnd.
        RECT windowRect;
        ::GetWindowRect(hWnd, &windowRect);
        ::SetWindowPos(m_childHWnd, HWND_TOP, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, SWP_NOZORDER);
        if (m_winComp != nullptr)
            m_winComp->UpdateViewPort(true);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_COPYDATA:
    {
        auto CDS = (PCOPYDATASTRUCT)lParam;
        if (isSecondary && CDS->dwData == CDSSHAREDHANDLE)
        {
            receivedHandle = *(HANDLE*)CDS->lpData;
            handleReceived = true;

            DWORD pid;
            GetWindowThreadProcessId((HWND)wParam, &pid);
            parentProccess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
        }
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}