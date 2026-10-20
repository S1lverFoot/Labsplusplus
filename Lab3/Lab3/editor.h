#pragma once
#include <windows.h>
#include <cmath>
#include "shape.h"

class Editor {
public:
    virtual ~Editor() {}
    virtual void OnLBdown(HWND hWnd) = 0;
    virtual void OnMouseMove(HWND hWnd) = 0;
    virtual void OnLBup(HWND hWnd, Shape** pcshape, int& count) = 0;
    virtual void OnPaint(HWND hWnd) = 0;
};

class ShapeEditor : public Editor {
protected:
    BOOL isDrawing = FALSE;
    POINT ptStart = { 0, 0 };
    POINT ptCurrent = { 0, 0 };

    void DrawRubberBand(HWND hWnd) {
        HDC hdc = GetDC(hWnd);
        SetROP2(hdc, R2_NOTXORPEN);

        HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

        MoveToEx(hdc, ptStart.x, ptStart.y, NULL);
        LineTo(hdc, ptCurrent.x, ptCurrent.y);

        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);
        ReleaseDC(hWnd, hdc);
    }

public:
    void OnLBdown(HWND hWnd) override {
        isDrawing = TRUE;
        GetCursorPos(&ptStart);
        ScreenToClient(hWnd, &ptStart);
        ptCurrent = ptStart;
    }

    void OnMouseMove(HWND hWnd) override {
        if (isDrawing) {
            DrawRubberBand(hWnd); 
            GetCursorPos(&ptCurrent);
            ScreenToClient(hWnd, &ptCurrent);
            DrawRubberBand(hWnd); 
        }
    }

    void OnPaint(HWND hWnd) override {}
};

class PointEditor : public ShapeEditor {
public:
    void OnLBup(HWND hWnd, Shape** pcshape, int& count) override {
        if (!isDrawing) return;
        isDrawing = FALSE;

        PointShape* p = new PointShape();
        p->Set(ptCurrent.x, ptCurrent.y, ptCurrent.x, ptCurrent.y);
        pcshape[count++] = p;

        InvalidateRect(hWnd, NULL, TRUE);
    }
};

class LineEditor : public ShapeEditor {
public:
    void OnLBup(HWND hWnd, Shape** pcshape, int& count) override {
        if (!isDrawing) return;
        DrawRubberBand(hWnd);
        isDrawing = FALSE;

        LineShape* p = new LineShape();
        p->Set(ptStart.x, ptStart.y, ptCurrent.x, ptCurrent.y);
        pcshape[count++] = p;

        InvalidateRect(hWnd, NULL, TRUE);
    }
};

class RectEditor : public ShapeEditor {
public:
    void OnLBup(HWND hWnd, Shape** pcshape, int& count) override {
        if (!isDrawing) return;
        DrawRubberBand(hWnd);
        isDrawing = FALSE;

        long dx = std::labs(ptCurrent.x - ptStart.x);
        long dy = std::labs(ptCurrent.y - ptStart.y);

        RectShape* p = new RectShape();
        p->Set(ptStart.x - dx, ptStart.y - dy, ptStart.x + dx, ptStart.y + dy);
        pcshape[count++] = p;

        InvalidateRect(hWnd, NULL, TRUE);
    }
};

class EllipseEditor : public ShapeEditor {
public:
    void OnLBup(HWND hWnd, Shape** pcshape, int& count) override {
        if (!isDrawing) return;
        DrawRubberBand(hWnd);
        isDrawing = FALSE;

        EllipseShape* p = new EllipseShape();
        p->Set(ptStart.x, ptStart.y, ptCurrent.x, ptCurrent.y);
        pcshape[count++] = p;

        InvalidateRect(hWnd, NULL, TRUE);
    }
};