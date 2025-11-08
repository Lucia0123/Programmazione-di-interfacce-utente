#include <windows.h>            // include le Win32
#include <stdio.h>
#include <windowsx.h>

int lastX, lastY;
int vertPPI, horPPI;

// main normale
// int main(int argc, char *argv[]) {
//     printf("Hello world!\n");
// }

// funzione per gestire i messaggi
LRESULT CALLBACK LaMiaProcedura(
    HWND hwnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
){
    switch(message) {
        case WM_CREATE: // qui creo le eventuali sottofinestre
            {
                // provo a calcolare PPI (pixel per inch) dello schermo
                HDC hdc = GetDC(hwnd);
                vertPPI = GetDeviceCaps(hdc, LOGPIXELSX);
                horPPI = GetDeviceCaps(hdc, LOGPIXELSY);
            }
            return 0;  // o break;

        case WM_PAINT:  // quando la finestra ritorna in primo piano o viene ingrandita,
                        // deve "ridisegnare" sè stessa
            {
                PAINTSTRUCT ps;     // è la tavolozza dentro cui memorizzo pennello, colore ecc.
                HDC hdc = BeginPaint(hwnd, &ps);  // hdc è la tela
                // BeginPaint() è una specie di semaforo

                // Qui dentro si può disegnare
                RECT clientRect;
                GetClientRect(hwnd, &clientRect);

                RECT miorettangolo;
                miorettangolo.left = clientRect.left + 10;
                miorettangolo.top = clientRect.top + 10;
                miorettangolo.bottom = clientRect.bottom - 10;
                miorettangolo.right = clientRect.right - 10;
                FillRect(hdc, &miorettangolo, (HBRUSH)GetStockObject(WHITE_BRUSH));

                TCHAR buffer[2048];
                wsprintf(buffer, TEXT("Client RECT: %dx%d\nPPI dello schermo: h -> %d, v -> %d\nUltimo click: (%d, %d)"),
                        clientRect.right, clientRect.bottom,
                        horPPI, vertPPI,
                        lastX, lastY);

                RECT misura;
                ZeroMemory(&misura, sizeof(RECT));
                DrawText(hdc, buffer, -1, &misura, DT_CENTER | DT_CALCRECT | DT_END_ELLIPSIS);

                RECT destinazione;
                destinazione.top = 10 + ((miorettangolo.bottom - miorettangolo.top) / 2) - (misura.bottom / 2);
                destinazione.right = miorettangolo.right;
                destinazione.left = miorettangolo.left;
                destinazione.bottom = miorettangolo.bottom;
                DrawText(hdc, buffer, -1, &destinazione, DT_CENTER |  DT_END_ELLIPSIS);

                EndPaint(hwnd, &ps);
            }
            return 0;

        case WM_LBUTTONUP:
            // voglio riconoscere dove è stato cliccato
            {
                lastX = GET_X_LPARAM(lParam);
                lastY = GET_Y_LPARAM(lParam);

                InvalidateRect(hwnd, NULL, TRUE);
            }
            break;
        
        // quando mi arriva un messaggio di distruzione della finestra,
        // l'intera applicazione deve terminare
        case WM_DESTROY:
            PostQuitMessage(0);     // exit code 0
            break;
    }
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
    wndclass.style = CS_HREDRAW | CS_VREDRAW;     // stile (insieme di comportamenti) di questa classe di finestre
    wndclass.lpfnWndProc = LaMiaProcedura; // campo più importante; puntatore a funzione
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); // aspetto del puntatore del mouse
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = TEXT("LaMiaClasse");

    RegisterClass(&wndclass); // passaggio per puntatore con &

    // creazione finestra
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
    // la finestra inizia a ricevere messaggi (es. click, eventi di sistema, ..)

    // Message pump (busy loop/wait) - ottiene i messaggi dalla coda e li dispatcha
    // loop infinito e bloccante per rimanere in attesa di eventuali eventi
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)) {
        DispatchMessage(&msg);
    }

    return msg.wParam;
}