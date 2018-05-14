#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H

#include <QWidget>
#include "publicfunc.h"

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);
private:
    int layerSta[3];
signals:

public slots:
    void slotSetLayerSta(bool layer0,bool layer1,bool layer2);
    void slotUpdateSta(SearchType st);
};

#endif // PAINTERWIDGET_H
