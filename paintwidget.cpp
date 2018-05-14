#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    for(int i =0;i < 3;i++)
    {
        layerSta[i] = -1;
    }
}

void PaintWidget::slotUpdateSta(SearchType st)
{
    QList<JsonProperty> &vJsonPro = PublicFunc::vPublicJsonPro;
    for(int i =0;i < vJsonPro.count();i++)
    {
        JsonProperty &jsonpro = vJsonPro[i];
        for(int j = 0;j < jsonpro.vTotalJsonProperty.count();j++)
       {
             jsonpro.vTotalJsonProperty[j]->setData(st);
       }

    }
    update();
}

void PaintWidget::slotSetLayerSta(bool layer0, bool layer1, bool layer2)
{
    if(layer0) layerSta[0] = 0;
    else layerSta[0] = -1;
    if(layer1) layerSta[1] = 1;
    else layerSta[1] = -1;
    if(layer2)layerSta[2] = 2;
    else layerSta = -1;
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    int w = 600;
    int h = 1024;
    QPainter painter(this);
    QList<JsonProperty> &vJsonPro = PublicFunc::vPublicJsonPro;
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.save();
    painter.fillRect(0,0,w,h,QBrush(QColor(0,0,0,255)));
    painter.restore();
    for(int i = 0;i < vJsonPro.count();i++)
    {
        JsonProperty jsonpro = vJsonPro[i];
        for(int j = 0;j < jsonpro.vTotalJsonProperty.count();j++)
        {
            if(jsonpro.vTotalJsonProperty[j]->layer == )
            jsonpro.vTotalJsonProperty[j]->draw(painter);
        }
    }
}

