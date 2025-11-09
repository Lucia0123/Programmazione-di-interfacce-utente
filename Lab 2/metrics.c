// Leggiamo le dimensioni dello schermo tramite un'interfaccia Win32.

#include <stdio.h>
#include <windows.h>

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
) {
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    TCHAR buffer[100];
    wsprintf(buffer, TEXT("Screen Resolution: %dx%d"), width, height);

    MessageBox(
        NULL,
        buffer,
        "Screen Resolution",
        MB_OK | MB_ICONINFORMATION
    );

    return 0;
}