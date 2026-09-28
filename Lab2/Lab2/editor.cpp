#include "editor.h"

extern Shape* pcshape[116];
extern int shapeCount;

void ShapeEditor::OnLBdown(HWND hWnd) {
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    xstart = xend = pt.x;
    ystart = yend = pt.y;
    isDrawing = true;
}

void ShapeEditor::OnMouseMove(HWND hWnd) {
    if (!isDrawing) return;
    HDC hdc = GetDC(hWnd);
    SetROP2(hdc, R2_NOTXORPEN);
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); 
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    MoveToEx(hdc, xstart, ystart, NULL);
    LineTo(hdc, xend, yend);

    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    xend = pt.x; yend = pt.y;

    MoveToEx(hdc, xstart, ystart, NULL);
    LineTo(hdc, xend, yend);

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
    ReleaseDC(hWnd, hdc);
}

void ShapeEditor::OnLBup(HWND hWnd) {
    isDrawing = false;
}

void RectEditor::OnLBup(HWND hWnd) {
    isDrawing = false;
    if (shapeCount < 116) {
        pcshape[shapeCount] = new RectShape();
        pcshape[shapeCount]->Set(xstart, ystart, xend, yend);
        shapeCount++;
        InvalidateRect(hWnd, NULL, TRUE);
    }
}

void EllipseEditor::OnMouseMove(HWND hWnd) {
    if (!isDrawing) return;
    HDC hdc = GetDC(hWnd);
    SetROP2(hdc, R2_NOTXORPEN);
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    long dx = abs(xstart - xend);
    long dy = abs(ystart - yend);
    Ellipse(hdc, xstart - dx, ystart - dy, xstart + dx, ystart + dy);

    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    xend = pt.x; yend = pt.y;

    dx = abs(xstart - xend);
    dy = abs(ystart - yend);
    Ellipse(hdc, xstart - dx, ystart - dy, xstart + dx, ystart + dy);

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
    ReleaseDC(hWnd, hdc);
}

void EllipseEditor::OnLBup(HWND hWnd) {
    isDrawing = false;
    if (shapeCount < 116) {
        long dx = abs(xstart - xend);
        long dy = abs(ystart - yend);
        pcshape[shapeCount] = new EllipseShape();
        pcshape[shapeCount]->Set(xstart - dx, ystart - dy, xstart + dx, ystart + dy);
        shapeCount++;
        InvalidateRect(hWnd, NULL, TRUE);
    }
}

void PointEditor::OnLBup(HWND hWnd) {
    isDrawing = false;
    if (shapeCount < 116) {
        pcshape[shapeCount] = new PointShape();
        pcshape[shapeCount]->Set(xstart, ystart, xstart, ystart);
        shapeCount++;
        InvalidateRect(hWnd, NULL, TRUE);
    }
}

void LineEditor::OnLBup(HWND hWnd) {
    isDrawing = false;
    if (shapeCount < 116) {
        pcshape[shapeCount] = new LineShape();
        pcshape[shapeCount]->Set(xstart, ystart, xend, yend);
        shapeCount++;
        InvalidateRect(hWnd, NULL, TRUE);
    }
}