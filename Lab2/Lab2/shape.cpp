#include "shape.h"

void Shape::Set(long x1, long y1, long x2, long y2) {
    xs1 = x1; ys1 = y1; xs2 = x2; ys2 = y2;
}

void PointShape::Show(HDC hdc) {
    SetPixel(hdc, xs1, ys1, RGB(0, 0, 0));
}

void LineShape::Show(HDC hdc) {
    MoveToEx(hdc, xs1, ys1, NULL);
    LineTo(hdc, xs2, ys2);
}

void RectShape::Show(HDC hdc) {
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 128, 0));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    Rectangle(hdc, xs1, ys1, xs2, ys2);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);
}

void EllipseShape::Show(HDC hdc) {
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    Ellipse(hdc, xs1, ys1, xs2, ys2);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);
}