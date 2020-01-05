//
// Created by Андрей Москалёв on 12.12.2019.
//

#ifndef MANDELBROT_MAINWINDOW_H
#define MANDELBROT_MAINWINDOW_H
#include <QMainWindow>
#include <algorithm>
#include <QPainter>
#include <QDebug>
#include <QColor>
#include <QMouseEvent>
#include <QPoint>
#include <QImage>
#include <cmath>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;
protected:
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
};


#endif //MANDELBROT_MAINWINDOW_H
