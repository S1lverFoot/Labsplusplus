#include "framework.h"
#include <cwchar>
#include "module2.h"
#include "module2.rh"

extern WCHAR g_szDisplayText[256];

static int g_currentPos = 50;

static INT_PTR CALLBACK DlgProc2(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_INITDIALOG:
    {
        HWND hScroll = GetDlgItem(hDlg, IDC_SCROLLBAR);
        SetScrollRange(hScroll, SB_CTL, 1, 100, FALSE);
        SetScrollPos(hScroll, SB_CTL, g_currentPos, TRUE);
        SetDlgItemInt(hDlg, IDC_STATIC_VAL, g_currentPos, FALSE);
        return TRUE;
    }
    case WM_HSCROLL:
    {
        HWND hScroll = (HWND)lParam;
        int action = LOWORD(wParam);

        switch (action) {
        case SB_LINELEFT:        g_currentPos--; break;
        case SB_LINERIGHT:       g_currentPos++; break;
        case SB_PAGELEFT:        g_currentPos -= 10; break;
        case SB_PAGERIGHT:       g_currentPos += 10; break;
        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:      g_currentPos = HIWORD(wParam); break;
        }

        if (g_currentPos < 1) g_currentPos = 1;
        if (g_currentPos > 100) g_currentPos = 100;

        SetScrollPos(hScroll, SB_CTL, g_currentPos, TRUE);
        SetDlgItemInt(hDlg, IDC_STATIC_VAL, g_currentPos, FALSE);
        return TRUE;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
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

int Func_MOD2(HWND hWnd) {
    INT_PTR res = DialogBox(
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        MAKEINTRESOURCE(IDD_DIALOG2),
        hWnd,
        DlgProc2
    );

    if (res == 1) {
        swprintf_s(g_szDisplayText, L"Chosen number: %d", g_currentPos);

        InvalidateRect(hWnd, NULL, TRUE);
    }
    return (int)res;
}