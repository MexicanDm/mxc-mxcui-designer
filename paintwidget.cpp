#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{

}

void PaintWidget::slotGetComProperty()
{
    QVector<JsonProperty> &vJsonPro = PublicFunc::vPublicJsonPro;
    //vCircle.clear();
    for(int i = 0;i < vJsonPro.count();i++)
    {
        for(int j = 0;j < vJsonPro[i].vCircleBarProperty.count();j++)
        {
            CircleProgressBar circle;
            CircleProBarProperty circlePro = vJsonPro[i].vCircleBarProperty[j];
            QRectF rectangle = QRectF(circlePro.x,circlePro.y,circlePro.width,circlePro.height);
            circle.setData(rectangle,circlePro.color,circlePro.baseColor,circlePro.penWidth,circlePro.minValue,circlePro.maxValue);
            vJsonPro[i].vCircleBar.append(circle);
        }
    }
    update();
}

void PaintWidget::slotUpdateSta(SearchType st)
{
    QVector<JsonProperty> &vJsonPro = PublicFunc::vPublicJsonPro;
    for(int i = 0;i < vJsonPro.count();i++)
    {
        if(st.fileName.compare(vJsonPro[i].fileName) == 0)
        {
            if(st.structType.compare(CIRCLE_PROCESS_BAR) == 0)
            {
                for(int j = 0;j < vJsonPro[i].vCircleBarProperty.count();j++)
                {
                    CircleProBarProperty &circlePro = vJsonPro[i].vCircleBarProperty[j];
                    if(st.structName.compare(circlePro.name) == 0)
                    {
                        circlePro.setData(st);
                        CircleProgressBar &circleBar = vJsonPro[i].vCircleBar[j];
                        QRectF rectangle = QRectF(circlePro.x,circlePro.y,circlePro.width,circlePro.height);
                        circleBar.setData(rectangle,circlePro.color,circlePro.baseColor,circlePro.penWidth,circlePro.minValue,circlePro.maxValue);
                        circleBar.setValue(circlePro.currentValue);
                        update();
                    }
                }
            }
        }
    }
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    int w = 600;
    int h = 1024;
    QPainter painter(this);
    QVector<JsonProperty> &vJsonPro = PublicFunc::vPublicJsonPro;
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.save();
    painter.fillRect(0,0,w,h,QBrush(QColor(0,0,0,255)));
    painter.restore();
    for(int i = 0;i < vJsonPro.count();i++)
    {
        for(int j = 0;j < vJsonPro[i].vCircleBar.count();j++)
        {
            vJsonPro[i].vCircleBar[j].draw(painter);
        }
    }
}

