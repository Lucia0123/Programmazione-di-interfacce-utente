#include <windows.h>            // include le Win32
#include <stdio.h>

// main normale
// int main(int argc, char *argv[]) {
//     printf("Hello world!\n");
// }

LRESULT CALLBACK LaMiaProcedura(
    HWND hwnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
){
    // ignoro i messaggi
    return DefWindowProc(hwnd, message, wParam, lParam);
}

// main specifico per le Win32
int WINAPI WinMain(
    HINSTANCE hInstance,        // istanza specifica dell'applicazione
    HINSTANCE hPrevInstance,    // sempre NULL
    PSTR szCmdLine,             // puntatore a stringa
    int iCmdShow                // quasi sempre 0
) {
    printf("Hello world!\n");

    // creazione dialogo
    MessageBox(NULL,
                TEXT("Questo è un dialogo!"),
                TEXT("Titolo"),
                MB_OK | MB_ICONINFORMATION);
    
    // definisco classe di finestra
    WNDCLASS wndclass;
    wndclass.style = 0;     // stile (insieme di comportamenti) di questa classe di finestre
    wndclass.lpfnWndProc = LaMiaProcedura; // campo più importante; puntatore a funzione
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); // aspetto del puntatore del mouse
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = TEXT("LaMiaClasse");

    RegisterClass(&wndclass); // passaggio per puntatore con &

    // creazione finestra
    // arrivata a video minuti 1:15:00
    HWND hfinestra = CreateWindow(
        TEXT("LaMiaClasse"),
        TEXT("Ciao mondo!"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, // posizione della finestra in pixel
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,  // handle alla finestra madre (in questo caso non esiste)
        NULL,
        hInstance,
        NULL
    );
    ShowWindow(hfinestra, SW_NORMAL);

    // Message pump - ottiene i messaggi dalla coda e li dispatcha
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)) {
        DispatchMessage(&msg);
    }

    return 0;
}