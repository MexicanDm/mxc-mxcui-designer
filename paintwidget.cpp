#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{

}

void PaintWidget::slotGetComProperty(QVector<JsonProperty> jsonPro)
{
    QRectF rectangle;
    for(int i = 0;i < jsonPro.count();i++)
    {
        for(int j = 0;j < jsonPro[i].vCircleProBar.count();j++)
        {
            CircleProgressBar circle;
            CircleProBarProperty circlePro = jsonPro[i].vCircleProBar[j];
            rectangle = QRectF(circlePro.x,circlePro.y,circlePro.width,circlePro.height);
            circle.setData(rectangle,circlePro.color,circlePro.baseColor,circlePro.penWidth,circlePro.minValue,circlePro.maxValue);
            vCircle.append(circle);
        }
    }
    update();
    vPaintJsonPro = jsonPro;
}

void PaintWidget::slotUpdateSta(SearchType st)
{
    for(int i = 0;i < vPaintJsonPro.count();i++)
    {
        if(st.fileName.compare(vPaintJsonPro[i].fileName) == 0)
        {
            if(st.structType.compare(CIRCLE_PROCESS_BAR) == 0)
            {
                for(int j = 0;j < vPaintJsonPro[i].vCircleProBar.count();j++)
                {
                    CircleProBarProperty &circlePro = vPaintJsonPro[i].vCircleProBar[j];
                    if(st.structName.compare(circlePro.name) == 0)
                    {
                        circlePro.setData(st);
                        CircleProgressBar &circleBar = vCircle[j];
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
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.save();
    painter.fillRect(0,0,w,h,QBrush(QColor(0,0,0,255)));
    painter.restore();
    for(int i = 0;i < vCircle.count();i++)
    {

        vCircle[i].draw(painter);
    }
}

