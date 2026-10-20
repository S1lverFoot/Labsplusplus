#include <windows.h>
#include "Resource.h"
#include "shape_editor.h"

ShapeObjectsEditor ED;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
        ED.InitToolbar(hWnd, ((LPCREATESTRUCT)lParam)->hInstance);
        SetWindowText(hWnd, L"Режим: Крапка");
        break;

    case WM_SIZE:
        ED.OnSize(hWnd);
        break;

    case WM_NOTIFY:
        ED.OnNotify(lParam);
        break;

    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        switch (wmId) {
        case ID_OBJECTS_DOT:
            ED.StartPointEditor();
            SetWindowText(hWnd, L"Режим: Крапка");
            break;
        case ID_OBJECTS_LINE:
            ED.StartLineEditor();
            SetWindowText(hWnd, L"Режим: Лінія");
            break;
        case ID_OBJECTS_RECTANGLE:
            ED.StartRectEditor();
            SetWindowText(hWnd, L"Режим: Прямокутник");
            break;
        case ID_OBJECTS_ELLIPSE:
            ED.StartEllipseEditor();
            SetWindowText(hWnd, L"Режим: Еліпс");
            break;
        case IDM_FILE_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDM_ABOUT:
            MessageBox(hWnd, L"Графічний редактор. Лабораторна №3", L"Про програму", MB_OK | MB_ICONINFORMATION);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    } break;

    case WM_LBUTTONDOWN:
        ED.OnLBdown(hWnd);
        break;

    case WM_MOUSEMOVE:
        ED.OnMouseMove(hWnd);
        break;

    case WM_LBUTTONUP:
        ED.OnLBup(hWnd);
        break;

    case WM_PAINT:
        ED.OnPaint(hWnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEXW wcex = { sizeof(WNDCLASSEX) };
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB3);
    wcex.lpszClassName = L"Lab3Variant17Class";

    RegisterClassExW(&wcex);

    HWND hWnd = CreateWindowW(L"Lab3Variant17Class", L"Режим: Крапка",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd) return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}