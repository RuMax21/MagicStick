#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->label, SIGNAL(click(QPoint)), this, SLOT(clickAction(QPoint)));

    connect(ui->btnUndo, SIGNAL(clicked()), this, SLOT( undoClick() ));
    connect(ui->btnRedo, SIGNAL(clicked()), this, SLOT( redoClick() ));

    ui->btnRedo->setEnabled(false);
    ui->btnUndo->setEnabled(false);
}

MainWindow::~MainWindow(){ delete ui; }

void MainWindow::setClick(QColor color, QPoint point)
{
    this->colorFromImage = QColor(image.pixel(point));
    this->colorHightLight = color;
    fillPoints(point);

}

void MainWindow::fillPoints(QPoint point)
{
    QColor compareColor = image.pixel(point);
    if (ignore.contains(point)) {
        return;
    }else if ( compare(colorFromImage, compareColor) ){
        ignore.insert(point);
        image.setPixelColor(point.x(), point.y(), colorHightLight);
        QList<QPoint> points = pointMustFill(point);

        for (auto &i : points){
            fillPoints(i);
        }

        ui->label->setPixmap(QPixmap::fromImage(image));
    }else{
        return;
    }
}

bool MainWindow::compare(QColor x, QColor y)
{
    int value_x = x.black();
    int value_y = y.black();
    qDebug() << value_x;
    qDebug() << value_y;
    return qAbs(value_x - value_y) <= rate;
}

bool MainWindow::isSize(QPoint point)
{
    int x = point.x();
    int y = point.y();
    if (x < 0 || x >= image.width()) {
        return false;
    } else if (y < 0 || y >= image.height()) {
        return false;
    } else {
        return true;
    }
}

void MainWindow::redoClick()
{
    undo.push(getLastImage());
    image = redo.pop();
    ui->label->setPixmap(QPixmap::fromImage(image));

    if (redo.size() == 0) {
        ui->btnRedo->setEnabled(false);
    }
    ui->btnUndo->setEnabled(true);
    ignore.clear();
}

void MainWindow::undoClick()
{
    redo.push(getLastImage());
    image = undo.pop();
    ui->label->setPixmap(QPixmap::fromImage(image));

    if (undo.size() == 0) {
        ui->btnUndo->setEnabled(false);
    }
    ui->btnRedo->setEnabled(true);
    ignore.clear();
}



QList<QPoint> MainWindow::pointMustFill(QPoint point)
{
    QList<QPoint> listPoints;
    int x = point.x();
    int y = point.y();
    if (isSize(QPoint(x-1, y-1))) {
        listPoints.append(QPoint(x-1, y-1));
    }
    if (isSize(QPoint(x-1, y))) {
        listPoints.append(QPoint(x-1, y));
    }
    if (isSize(QPoint(x-1, y+1))) {
        listPoints.append(QPoint(x-1, y+1));
    }
    if (isSize(QPoint(x, y+1))) {
        listPoints.append(QPoint(x, y+1));
    }
    if (isSize(QPoint(x, y-1))) {
        listPoints.append(QPoint(x, y-1));
    }
    if (isSize(QPoint(x+1, y))) {
        listPoints.append(QPoint(x+1, y));
    }
    if (isSize(QPoint(x+1, y+1))) {
        listPoints.append(QPoint(x+1, y+1));
    }
    if (isSize(QPoint(x+1, y-1))) {
        listPoints.append(QPoint(x+1, y-1));
    }
    return listPoints;
}

QImage MainWindow::getImage(){ return imageOriginal; }
QImage MainWindow::getLastImage(){ return image; }

void MainWindow::on_btnLoad_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "", "", "*.png *jpg");

    imageOriginal.load(path);
    image = QImage(imageOriginal);
    ui->label->setPixmap(QPixmap::fromImage( image.scaled(ui->label->size())));

    undo.clear();
    redo.clear();
    ignore.clear();

}

void MainWindow::clickAction(QPoint point)
{
    ui->btnRedo->setEnabled(false);
    ui->btnUndo->setEnabled(true);

    undo.push(getLastImage());
    redo.clear();

    setClick(QColor(r, g, b), point);
}


void MainWindow::on_pushButton_clicked()
{
    image = getImage();
    ui->label->setPixmap(QPixmap::fromImage(image));
    ignore.clear();
}


void MainWindow::on_pushButton_2_clicked()
{
    QString filters;
    foreach(QByteArray byte, QImageWriter::supportedImageFormats())
    {
        QString format = byte;
        filters += QString("%1 (%2)\n")
                   .arg(format.toUpper())
                   .arg("*." + format);
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as..."), "", filters);

    if (fileName.isEmpty() || fileName.isNull()){ return; }

    ui->label->pixmap().save(fileName);
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    rate = value;
    ui->valueRate->setText(QString::number(value));
}

