// Esempio di creazione finestra, con controllo (pulsante), ridimensionamento interattivo con scrittura testo e gestione dei messaggi Win32.

#include <stdio.h>
#include <windows.h>

#define BTN_CLICKME_ID 123
#define BTN_CLICKME_WIDTH 100
#define BTN_CLICKME_HEIGHT 30
#define MARGINS 10

LRESULT CALLBACK MyFirstWindowProcedure(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
);

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
) {
    // Register a new window class
    WNDCLASS wc = {0};
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszClassName = "MyFirstWindowClass";
    wc.lpfnWndProc = MyFirstWindowProcedure;

    RegisterClass(&wc);

    // Create and display a simple window
    HWND hwnd = CreateWindow(
        "MyFirstWindowClass", // wc.lpszClassName,
        "My First Window",    // titolo finestra
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL,
        hInstance,
        NULL
    );
    ShowWindow(hwnd, SW_NORMAL);

    // Message pump
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // GetMessage returns 0 when it receives a WM_QUIT message

    return 0;
}

LRESULT CALLBACK MyFirstWindowProcedure(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
) {
    switch (uMsg) {
        case WM_CREATE:
            {
                CreateWindow(
                    "BUTTON", // Predefined window class for buttons (Win32 control)
                    "Click Me", // Window text used as button label
                    WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    0, // X position (temporary, we'll move it later when we handle WM_SIZE)
                    0, // Y position (temporary, we'll move it later when we handle WM_SIZE)
                    100, // Width
                    30, // Height
                    hwnd, // Parent window (must use the WS_CHILD style above as well)
                    (HMENU) BTN_CLICKME_ID, // ID of the button from the POV of the parent
                    GetModuleHandle(NULL),
                    NULL
                );
            }
            return 0;

        case WM_SIZE:
            {
                // Move the button to stay positioned in the bottom-right corner
                HWND buttonHandle = GetDlgItem(hwnd, BTN_CLICKME_ID);
                if (buttonHandle) {
                    RECT clientRect;
                    GetClientRect(hwnd, &clientRect);

                    MoveWindow(
                        buttonHandle,
                        clientRect.right - BTN_CLICKME_WIDTH - MARGINS,
                        clientRect.bottom - BTN_CLICKME_HEIGHT - MARGINS,
                        BTN_CLICKME_WIDTH,
                        BTN_CLICKME_HEIGHT,
                        TRUE
                    );
                }

                // Invalidate the window to trigger a repaint
                // (this forces WM_PAINT to be sent)
                InvalidateRect(hwnd, NULL, TRUE);
            }
            return 0;

        case WM_COMMAND:
            {
                // The low word of wParam contains the control ID that sent the WM_COMMAND message
                int source_id = LOWORD(wParam);

                // The high word of wParam contains the notification code (which indicates the action)
                int code = HIWORD(wParam);

                if (source_id == BTN_CLICKME_ID) {
                    if(code == BN_CLICKED) {
                        MessageBox(hwnd, "You clicked me!", "Button Clicked", MB_OK | MB_ICONINFORMATION);
                    }
                }
            }
            return 0;

        case WM_PAINT:
            {
                // Begin paint operation
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);

                RECT clientRect;
                GetClientRect(hwnd, &clientRect);

                TCHAR szBuffer[100];
                wsprintf(szBuffer, TEXT("Screen area of %d x %d pixels"), clientRect.right, clientRect.bottom);

                DrawText(
                    hdc, // Draw on the window's device context
                    szBuffer, // Text to draw
                    -1, // Draw all the text (null-terminated)
                    &clientRect, // Area in which to draw (full client area)
                    DT_SINGLELINE | DT_CENTER | DT_VCENTER // Center the text both horizontally and vertically, on a single line
                );

                // End paint operation
                EndPaint(hwnd, &ps);
            }
            return 0;

        case WM_LBUTTONUP:
            {
                int x = LOWORD(lParam);
                int y = HIWORD(lParam);

                TCHAR szBuffer[100];
                wsprintf(szBuffer, "You left-clicked at (%d, %d)", x, y);

                MessageBox(hwnd, szBuffer, "You left-clicked me", MB_OK | MB_ICONINFORMATION);
            }
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0); // This posts a WM_QUIT on our message queue, telling us to exit the message pump
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}