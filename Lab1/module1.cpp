#include "framework.h"
#include "module1.h"
#include "module1.rh"

extern WCHAR g_szDisplayText[256];
static WCHAR g_textBuffer[256] = L"";

static INT_PTR CALLBACK DlgProc1(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            GetDlgItemTextW(hDlg, IDC_EDIT1, g_textBuffer, 256);
            EndDialog(hDlg, 1);
            return TRUE;
        }
        if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, 0);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

int Func_MOD1(HWND hWnd) {
    INT_PTR res = DialogBox(
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        MAKEINTRESOURCE(IDD_DIALOG1),
        hWnd,
        DlgProc1
    );

    if (res == 1) {
        swprintf_s(g_szDisplayText, L"Chosen number: %s", g_textBuffer);
        InvalidateRect(hWnd, NULL, TRUE);
    }
    return (int)res;
}