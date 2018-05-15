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
    QList<int> layerSta;
signals:

public slots:
    void slotSetLayerSta(QList<int> ls);
    void slotUpdateSta(SearchType st);
};

#endif // PAINTERWIDGET_H
