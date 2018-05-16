#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    layerSta << -1 << -1 << -1;
    pw = 1024;
    ph = 600;
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

void PaintWidget::slotSetLayerSta(QList<int> ls)
{
    layerSta = ls;
    update();
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    QList<JsonProperty> &vJsonPro = PublicFunc::vPublicJsonPro;
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.save();
    painter.fillRect(0,0,pw,ph,QBrush(QColor(0,0,0,255)));
    painter.restore();
    for(int i = 0;i < vJsonPro.count();i++)
    {
        JsonProperty jsonpro = vJsonPro[i];
        for(int j = 0;j < jsonpro.vTotalJsonProperty.count();j++)
        {
            bool layerDisb = false;
            for(int k = 0;k < layerSta.count();k++)
            {
                if(jsonpro.vTotalJsonProperty[j]->layer == layerSta[k])
                {
                    layerDisb = true;
                }
            }
            if(layerDisb)
                jsonpro.vTotalJsonProperty[j]->draw(painter);
        }
    }
}

void PaintWidget::slotPaintWidgetRect(int w, int h)
{
    pw = w;
    ph = h;
    update();
}

