#pragma once
#include <windows.h>
#include "editor.h"

class ShapeObjectsEditor {
private:
    ShapeEditor* pse;
    int currentMode; 
public:
    ShapeObjectsEditor();
    ~ShapeObjectsEditor();

    void StartPointEditor();
    void StartLineEditor();
    void StartRectEditor();
    void StartEllipseEditor();

    void OnLBdown(HWND hWnd);
    void OnLBup(HWND hWnd);
    void OnMouseMove(HWND hWnd);
    void OnPaint(HWND hWnd);
    void OnInitMenuPopup(HWND hWnd, WPARAM wParam);
};
