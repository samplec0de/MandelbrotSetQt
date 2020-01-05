//
// Created by Андрей Москалёв on 12.12.2019.
//

#include <QRubberBand>
#include "mainwindow.h"
#include "Complex.h"

using std::min;
using std::max;

const int ITERATIONS = 480;
int DISPLAY_SIZE = 348;
const double EPS = 1e-7;

std::pair<double, double> leftCorner = {-2.5, -2};
double STEP_COORD = 2.0 / double(DISPLAY_SIZE);
bool rubberBandSelection = false;

QRubberBand * rubberBand;
QImage * image;

QColor colorMap[ITERATIONS];
static QPoint startPoint, releasePoint;


int pointCheck(Complex &point, const int N) {
    Complex z = Complex(0.0, 0.0);
    int i = 0;
    for (i = 0; i < N; ++i) {
        z = z * z + point;
        if (z.pointRadius() > 2.0 + EPS) {
            break;
        }
    }
    return i;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    auto * central = new QWidget(this);
    this->setCentralWidget(central);

    this->setMinimumSize(2 * DISPLAY_SIZE + 1, 2 * DISPLAY_SIZE+1);
    this->setMaximumSize(2 * DISPLAY_SIZE + 1, 2 * DISPLAY_SIZE+1);

    for (int i = 0, j = 0; j <= ITERATIONS; i += 3, ++j)
        colorMap[j] = (i <= 348) ? QColor::fromHsl(i, 200, 148).name() : colorMap[j - 1];

    image = new QImage(2 * DISPLAY_SIZE + 1, 2 * DISPLAY_SIZE + 1, QImage::Format_RGB32);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    rubberBandSelection = true;
    startPoint = event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (!rubberBandSelection)
        return;
    rubberBand->setGeometry(QRect(startPoint, event->pos()).normalized());
    rubberBand->show();
    if (event->pos().x() < 0
    || event->pos().y() < 0
    || event->pos().x() > 2 * DISPLAY_SIZE
    || event->pos().y() > 2 * DISPLAY_SIZE)
        return;
    releasePoint = event->pos();
    repaint();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    rubberBandSelection = false;
    rubberBand->hide();

    if (!(event->pos().x() < 0 
    || event->pos().y() < 0 
    || event->pos().x() > 2 * DISPLAY_SIZE 
    || event->pos().y() > 2 * DISPLAY_SIZE))
        releasePoint = event->pos();

    int xDelta = releasePoint.x() - startPoint.x(), yDelta;
    if (xDelta > 0) {
        yDelta = abs(releasePoint.y() - startPoint.y());
        if (yDelta != 0) {
            leftCorner.first = double(min(releasePoint.x(), startPoint.x())) * STEP_COORD + leftCorner.first;
            leftCorner.second = double(2.0 * DISPLAY_SIZE - max(releasePoint.y(),
                    startPoint.y())) * STEP_COORD + leftCorner.second;
            STEP_COORD = double(max(xDelta, yDelta))/(2.0*double(DISPLAY_SIZE))*STEP_COORD;
            repaint();
        }
    }
    else if (xDelta < 0) {
        yDelta = abs(releasePoint.y() - startPoint.y());
        if (yDelta != 0) {
            STEP_COORD = (2.0 * double(DISPLAY_SIZE)) / double(max(xDelta, yDelta)) * STEP_COORD;
            leftCorner.first -= double(min(releasePoint.x(), startPoint.x())) * STEP_COORD;
            leftCorner.second -= double(2.0 * DISPLAY_SIZE - max(releasePoint.y(), startPoint.y())) * STEP_COORD;
            repaint();
        }
    }
}


void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.translate(DISPLAY_SIZE, DISPLAY_SIZE);
    painter.scale(1,-1);
    if (rubberBandSelection) {
        painter.drawImage(QPoint(-DISPLAY_SIZE, -DISPLAY_SIZE), *image);
        return;
    }
    for (int i = -DISPLAY_SIZE; i <= DISPLAY_SIZE; ++i) {
        for (int j = -DISPLAY_SIZE; j <= DISPLAY_SIZE; ++j) {
            Complex point = Complex((i + DISPLAY_SIZE) * STEP_COORD + leftCorner.first,
                    (DISPLAY_SIZE - j)*STEP_COORD + leftCorner.second);
            int q = pointCheck(point, ITERATIONS);
            image->setPixelColor(i + DISPLAY_SIZE, DISPLAY_SIZE - j, colorMap[q].toRgb());
        }
    }
    painter.drawImage(QPoint(-DISPLAY_SIZE, -DISPLAY_SIZE), *image);
}
