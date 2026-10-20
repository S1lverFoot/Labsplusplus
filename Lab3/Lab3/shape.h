#pragma once
#include <windows.h>

class Shape {
protected:
    long x1, y1, x2, y2;
public:
    virtual ~Shape() {}
    void Set(long x1, long y1, long x2, long y2) {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }
    virtual void Show(HDC hdc) = 0;
};

// 1. Крапка
class PointShape : public Shape {
public:
    void Show(HDC hdc) override {
        SetPixel(hdc, x1, y1, RGB(0, 0, 0));
    }
};

// 2. Лінія
class LineShape : public Shape {
public:
    void Show(HDC hdc) override {
        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2, y2);
    }
};

class RectShape : public Shape {
public:
    void Show(HDC hdc) override {
        HBRUSH hBrush = CreateSolidBrush(RGB(192, 192, 192));
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

        Rectangle(hdc, x1, y1, x2, y2);

        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
    }
};

class EllipseShape : public Shape {
public:
    void Show(HDC hdc) override {
        HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hNullBrush);

        Ellipse(hdc, x1, y1, x2, y2);

        SelectObject(hdc, hOldBrush);
    }
};