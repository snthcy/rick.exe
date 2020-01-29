#include "Windows.h"
using namespace std;

int main()
{
	bool truth = true;
	FreeConsole();
	while (truth == true) {
		if (GetAsyncKeyState('E') & 0x8000) {
			ShellExecute(0, 0, "https://www.youtube.com/watch?v=dQw4w9WgXcQ", 0, 0, SW_SHOW);
		}
	}
    return 0;
}
