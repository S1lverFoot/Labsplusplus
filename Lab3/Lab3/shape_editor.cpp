#include "shape_editor.h"

#pragma comment(lib, "comctl32.lib")

ShapeObjectsEditor::ShapeObjectsEditor() {
    for (int i = 0; i < MAX_SHAPES; ++i) pcshape[i] = nullptr;
    pse = new PointEditor();
}

ShapeObjectsEditor::~ShapeObjectsEditor() {
    if (pse) delete pse;
    for (int i = 0; i < shapeCount; ++i) {
        if (pcshape[i]) delete pcshape[i];
    }
}

void ShapeObjectsEditor::InitToolbar(HWND hWndParent, HINSTANCE hInst) {
    InitCommonControls();

    TBBUTTON tbb[4];
    ZeroMemory(tbb, sizeof(tbb));

    tbb[0].iBitmap = STD_FILENEW;
    tbb[0].fsState = TBSTATE_ENABLED;
    tbb[0].fsStyle = TBSTYLE_BUTTON;
    tbb[0].idCommand = ID_OBJECTS_DOT;

    tbb[1].iBitmap = STD_FILEOPEN;
    tbb[1].fsState = TBSTATE_ENABLED;
    tbb[1].fsStyle = TBSTYLE_BUTTON;
    tbb[1].idCommand = ID_OBJECTS_LINE;

    tbb[2].iBitmap = STD_FILESAVE;
    tbb[2].fsState = TBSTATE_ENABLED;
    tbb[2].fsStyle = TBSTYLE_BUTTON;
    tbb[2].idCommand = ID_OBJECTS_RECTANGLE;

    tbb[3].iBitmap = STD_PRINT;
    tbb[3].fsState = TBSTATE_ENABLED;
    tbb[3].fsStyle = TBSTYLE_BUTTON;
    tbb[3].idCommand = ID_OBJECTS_ELLIPSE;

    hwndToolBar = CreateToolbarEx(
        hWndParent,
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
        IDC_MY_TOOLBAR,
        4, HINST_COMMCTRL, IDB_STD_SMALL_COLOR,
        tbb, 4, 0, 0, 0, 0,
        sizeof(TBBUTTON)
    );
}

void ShapeObjectsEditor::OnSize(HWND hWnd) {
    if (hwndToolBar) {
        RECT rc, rw;
        GetClientRect(hWnd, &rc);
        GetWindowRect(hwndToolBar, &rw);
        MoveWindow(hwndToolBar, 0, 0, rc.right - rc.left, rw.bottom - rw.top, FALSE);
    }
}

void ShapeObjectsEditor::OnNotify(LPARAM lParam) {
    LPNMHDR pnmh = (LPNMHDR)lParam;
    if (pnmh->code == TTN_NEEDTEXT) {
        LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
        switch (lpttt->hdr.idFrom) {
        case ID_OBJECTS_DOT:       lstrcpy(lpttt->szText, L"Крапка"); break;
        case ID_OBJECTS_LINE:      lstrcpy(lpttt->szText, L"Лінія"); break;
        case ID_OBJECTS_RECTANGLE: lstrcpy(lpttt->szText, L"Прямокутник"); break;
        case ID_OBJECTS_ELLIPSE:   lstrcpy(lpttt->szText, L"Еліпс"); break;
        }
    }
}

void ShapeObjectsEditor::StartPointEditor() {
    if (pse) delete pse;
    pse = new PointEditor();
    currentMode = ID_OBJECTS_DOT;
}

void ShapeObjectsEditor::StartLineEditor() {
    if (pse) delete pse;
    pse = new LineEditor();
    currentMode = ID_OBJECTS_LINE;
}

void ShapeObjectsEditor::StartRectEditor() {
    if (pse) delete pse;
    pse = new RectEditor();
    currentMode = ID_OBJECTS_RECTANGLE;
}

void ShapeObjectsEditor::StartEllipseEditor() {
    if (pse) delete pse;
    pse = new EllipseEditor();
    currentMode = ID_OBJECTS_ELLIPSE;
}

void ShapeObjectsEditor::OnLBdown(HWND hWnd) {
    if (pse) pse->OnLBdown(hWnd);
}

void ShapeObjectsEditor::OnMouseMove(HWND hWnd) {
    if (pse) pse->OnMouseMove(hWnd);
}

void ShapeObjectsEditor::OnLBup(HWND hWnd) {
    if (pse && shapeCount < MAX_SHAPES) {
        pse->OnLBup(hWnd, pcshape, shapeCount);
    }
}

void ShapeObjectsEditor::OnPaint(HWND hWnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    for (int i = 0; i < shapeCount; ++i) {
        if (pcshape[i]) pcshape[i]->Show(hdc);
    }

    EndPaint(hWnd, &ps);
}