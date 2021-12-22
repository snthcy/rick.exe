#include "Windows.h"
using namespace std;

int main()
{
    FreeConsole();
    while (true) {
        if (GetAsyncKeyState('E') & 0x8000) {
            ShellExecute(0, 0, L"https://www.youtube.com/watch?v=dQw4w9WgXcQ", 0, 0, SW_SHOW);
        }
    }
    return 0;
};
