#ifndef QCUSTOMGRAPHICSEFFECT_H
#define QCUSTOMGRAPHICSEFFECT_H

#include <QObject>
#include <QGraphicsEffect>
#include <QPainter>

// 自定义QGraphicsEffect，赋予QGraphicsItem效果
class QCustomGraphicsEffect : public QGraphicsEffect
{
    Q_OBJECT
public:
    explicit QCustomGraphicsEffect(QObject *parent = nullptr);

protected:
    void draw(QPainter *painter);

signals:

public slots:
};

#endif // QCUSTOMGRAPHICSEFFECT_H
