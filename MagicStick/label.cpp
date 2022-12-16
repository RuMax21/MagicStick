#include "label.h"

Label::Label(QWidget* parent) : QLabel(parent){}

Label::~Label(){}



void Label::mousePressEvent(QMouseEvent *e)
{
    qDebug() << e->x() << e->y();
    emit click(e->pos());
}
