#include <stdio.h>
#include <windows.h>

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
) {
    // printf("Hello, Windows!\n");

    int selection = MessageBox(
        NULL,
        "Retry or cancel?",
        "Hello!",       // titolo del messagebox
        MB_RETRYCANCEL | MB_ICONERROR
    );
    if(selection == IDRETRY) {
        MessageBox(NULL, "You clicked Retry!", "Info", MB_OK);
    } else if(selection == IDCANCEL) {
        MessageBox(NULL, "You clicked Cancel!", "Info", MB_OK);
    } else {
        // Impossible
    }

    return 0;
}