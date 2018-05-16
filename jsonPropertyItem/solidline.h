#ifndef SOLIDLINE_H
#define SOLIDLINE_H
#include <QPainter>
#include "/home/raise3d/workspace/mxc-mxcui/MXCUI/ui/uicomponent.h"

class SolidLine : public UIComponent
{
public:
    SolidLine() : UIComponent(UI_CONTROL_CHECKBOX)
    {
        pos.setX(0);
        pos.setY(0);
        width = 0;
        height = 0;
    }

    void setData(int x, int y, int w, int h)
    {
        pos.setX(x);
        pos.setY(y);
        width = w;
        height = h;
    }

    void draw(QPainter& painter)
    {
        painter.drawLine(pos, QPoint(pos.x() + width, pos.y()));
    }

public:
    QPoint pos;
    int width;
    int height;
};
#endif // SOLIDLINE_H

