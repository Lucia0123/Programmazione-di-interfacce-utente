#include <windows.h>            // include le Win32
#include <stdio.h>

// main normale
// int main(int argc, char *argv[]) {
//     printf("Hello world!\n");
// }

// main specifico per le Win32
int WINAPI WinMain(
    HINSTANCE hInstance,        // istanza specifica dell'applicazione
    HINSTANCE hPrevInstance,    // sempre NULL
    PSTR szCmdLine,             // puntatore a stringa
    int iCmdShow                // quasi sempre 0
) {
    printf("Hello world!\n");
    MessageBox(NULL,
                "Questo è un dialogo!",
                "Titolo",
                MB_OK | MB_ICONINFORMATION);

    return 0;
}