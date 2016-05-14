#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <cmath>
#include <math.h>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
        void paintEvent(QPaintEvent* e);
        void mousePressEvent(QMouseEvent * ev);
    ~MainWindow();


public slots:
    void glowna_funkcja();
    
private slots:



    void on_checkBox_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    QTimer* m_timer;
    QPen pen;
      QBrush *brush;

    float x[3];
    float y[3];
    float z[3];



};

#endif // MAINWINDOW_H
