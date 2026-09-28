#include "shape_editor.h"
#include "Resource.h"

Shape* pcshape[116];
int shapeCount = 0;

ShapeObjectsEditor::ShapeObjectsEditor() : pse(nullptr), currentMode(0) {}

ShapeObjectsEditor::~ShapeObjectsEditor() {
    if (pse) delete pse;
    for (int i = 0; i < shapeCount; i++) {
        delete pcshape[i];
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

void ShapeObjectsEditor::OnLBdown(HWND hWnd) { if (pse) pse->OnLBdown(hWnd); }
void ShapeObjectsEditor::OnLBup(HWND hWnd) { if (pse) pse->OnLBup(hWnd); }
void ShapeObjectsEditor::OnMouseMove(HWND hWnd) { if (pse) pse->OnMouseMove(hWnd); }

void ShapeObjectsEditor::OnPaint(HWND hWnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    for (int i = 0; i < shapeCount; i++) {
        if (pcshape[i]) pcshape[i]->Show(hdc);
    }
    EndPaint(hWnd, &ps);
}

void ShapeObjectsEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam) {
    HMENU hMenu = GetMenu(hWnd);
    HMENU hSubMenu = GetSubMenu(hMenu, 1);
    if ((HMENU)wParam == hSubMenu) {
        CheckMenuItem(hSubMenu, ID_OBJECTS_DOT, MF_UNCHECKED);
        CheckMenuItem(hSubMenu, ID_OBJECTS_LINE, MF_UNCHECKED);
        CheckMenuItem(hSubMenu, ID_OBJECTS_RECTANGLE, MF_UNCHECKED);
        CheckMenuItem(hSubMenu, ID_OBJECTS_ELLIPSE, MF_UNCHECKED);

        if (currentMode != 0) {
            CheckMenuItem(hSubMenu, currentMode, MF_CHECKED);
        }
    }
}