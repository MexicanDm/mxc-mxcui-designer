#ifndef SOLIDLINE_H
#define SOLIDLINE_H

#include <QPainter>
#include "../mxc-mxcui/MXCUI/ui/uicomponent.h"


class RealLine : public UIComponent
{
public:
    RealLine() : UIComponent()
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

    void setVisible(bool flag)
    {
        Q_UNUSED(flag);
    }

    bool isVisible() const
    {
        return false;
    }

    void baseDraw(QPainter& painter)
    {
        Q_UNUSED(painter);
    }

    bool isComponentPressed() const
    {
        return false;
    }
    void clearPressed()
    {

    }

public:
    QPoint pos;
    int width;
    int height;
};
#endif // SOLIDLINE_H

