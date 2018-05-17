#ifndef TARGETTEMPTEXT_H
#define TARGETTEMPTEXT_H
#include <QPainter>
#include "../mxc-mxcui/MXCUI/ui/uicomponent.h"


class TargetTempText : public UIComponent
{
public:
    TargetTempText() : UIComponent(UI_CONTROL_CHECKBOX)
    {
        pos.setX(0);
        pos.setY(0);
        width = 0;
        height = 0;
        flags = Qt::AlignHCenter|Qt::AlignTop;
        text = "";
    }

    void setData(int x, int y, int w, int h,int f,QString t)
    {
        pos.setX(x);
        pos.setY(y);
        width = w;
        height = h;
        flags = f;
        text = t;
    }


    void draw(QPainter& painter)
    {
        painter.drawText(pos.x(), pos.y(), width, height, flags, text);
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
    QString text;
    int flags;
};
#endif // TARGETTEMPTEXT_H

