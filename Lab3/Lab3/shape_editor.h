#pragma once
#include <windows.h>
#include <commctrl.h>
#include "shape.h"
#include "editor.h"
#include "Resource.h"

#define MAX_SHAPES 117

class ShapeObjectsEditor {
private:
    Shape* pcshape[MAX_SHAPES];
    int shapeCount = 0;

    ShapeEditor* pse = nullptr;
    HWND hwndToolBar = NULL;
    UINT currentMode = ID_OBJECTS_DOT;

public:
    ShapeObjectsEditor();
    ~ShapeObjectsEditor();

    void InitToolbar(HWND hWndParent, HINSTANCE hInst);
    void OnSize(HWND hWnd);
    void OnNotify(LPARAM lParam);

    void StartPointEditor();
    void StartLineEditor();
    void StartRectEditor();
    void StartEllipseEditor();

    void OnLBdown(HWND hWnd);
    void OnMouseMove(HWND hWnd);
    void OnLBup(HWND hWnd);
    void OnPaint(HWND hWnd);
};