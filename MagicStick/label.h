#ifndef LABEL_H
#define LABEL_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <QtDebug>
#include <QPoint>
#include <QFileDialog>
#include <QColor>

class Label : public QLabel
{
    Q_OBJECT
public:
    explicit Label(QWidget* parent = nullptr);
    virtual ~Label();
protected:
    virtual void mousePressEvent(QMouseEvent *e);
signals:
    void click(QPoint point);

};

#endif // LABEL_H
