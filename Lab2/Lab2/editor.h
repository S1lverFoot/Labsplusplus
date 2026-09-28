#pragma once
#include <windows.h>
#include "shape.h"

class Editor {
public:
    virtual void OnLBdown(HWND) = 0;
    virtual void OnLBup(HWND) = 0;
    virtual void OnMouseMove(HWND) = 0;
    virtual void OnPaint(HWND) = 0;
    virtual ~Editor() {}
};

class ShapeEditor : public Editor {
protected:
    POINT pt;
    long xstart, ystart, xend, yend;
    bool isDrawing;
public:
    ShapeEditor() : isDrawing(false), xstart(0), ystart(0), xend(0), yend(0) { pt.x = 0; pt.y = 0; }
    void OnLBdown(HWND hWnd) override;
    void OnLBup(HWND hWnd) override;
    void OnMouseMove(HWND hWnd) override;
    void OnPaint(HWND hWnd) override {}
};

class RectEditor : public ShapeEditor {
public:
    void OnLBup(HWND hWnd) override;
};

class EllipseEditor : public ShapeEditor {
public:
    void OnMouseMove(HWND hWnd) override;
    void OnLBup(HWND hWnd) override;
};

class PointEditor : public ShapeEditor {
public:
    void OnLBup(HWND hWnd) override;
};

class LineEditor : public ShapeEditor {
public:
    void OnLBup(HWND hWnd) override;
};