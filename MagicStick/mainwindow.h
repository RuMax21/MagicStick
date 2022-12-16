#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>
#include <QPair>
#include <QRgb>
#include <QImageWriter>
#include <QStack>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    QImage getImage();
private:
    QImage imageOriginal;
    QImage image;

private slots:
    void on_btnLoad_clicked();
    void clickAction(QPoint point);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void redoClick();
    void undoClick();
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
private:
    QSet<QPoint> ignore;

    QColor colorFromImage;
    QColor colorHightLight;

    int r = 0, g = 0, b = 0;
    int rate = 5;

    QStack<QImage> redo;
    QStack<QImage> undo;

public:
    void setClick(QColor color, QPoint point);
    void fillPoints(QPoint point);

    bool compare(QColor x, QColor y);
    bool isSize(QPoint point);

    QImage getLastImage();
    QList<QPoint> pointMustFill(QPoint point);
};


#endif // MAINWINDOW_H
