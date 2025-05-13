// This file specifically displays a 150*150 square in the center of the screen in a 150*150 area

#include <windows.h>

// Window dimensions
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define SQUARE_SIZE 150

// Window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            // Get window dimensions
            RECT clientRect;
            GetClientRect(hwnd, &clientRect);
            
            // Calculate center position
            int centerX = (clientRect.right - clientRect.left - SQUARE_SIZE) / 2;
            int centerY = (clientRect.bottom - clientRect.top - SQUARE_SIZE) / 2;
            
            // Create solid brush for square
            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // Red square
            HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
            
            // Draw the square
            Rectangle(hdc, centerX, centerY, centerX + SQUARE_SIZE, centerY + SQUARE_SIZE);
            
            // Clean up
            SelectObject(hdc, hOldBrush);
            DeleteObject(hBrush);
            
            EndPaint(hwnd, &ps);
            return 0;
        }
        
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
            
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
            
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

int main() {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int nCmdShow = SW_SHOW;
    // Register window class
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszClassName = L"FlashEYEWindow";
    
    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    // Create window
    HWND hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        L"FlashEYEWindow",
        L"Flash EYE - Square Display",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL, NULL, hInstance, NULL);
        
    if(hwnd == NULL) {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    // Show window
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    // Message loop
    MSG msg = {0};
    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return (int)msg.wParam;
}