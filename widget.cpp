#include <QLabel>
#include <QScrollArea>
#include <QPixmap>
#include <QImage>
#include <QMouseEvent>
#include <QApplication>
#include <math.h>

#ifndef QT_NO_WHEELEVENT
#include <QWheelEvent>
#endif

#include <stdio.h>

#include "widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{

}

Widget::~Widget()
{

}


bool Widget::showPicture() {
    imageLabel = new QLabel(this);
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    setWindowTitle(mFilename);
    //resize(500, 400);

    QImage image(mFilename);

    if(image.isNull()) {
        fprintf(stderr, "Can't load %s\n", mFilename.toLocal8Bit().data());
        return false;
    }

    imageLabel->setPixmap(QPixmap::fromImage(image));
    resize(imageLabel->pixmap()->size());
    imageLabel->resize(this->width(), this->height());
    imageLabel->move(0,0);
    return true;
}

void Widget::resizeEvent(QResizeEvent *e) {
    this->QWidget::resizeEvent(e);

    imageLabel->resize(this->width(), this->height());
    imageLabel->move(0,0);
}

void Widget::mousePressEvent(QMouseEvent *e) {
    if(e->modifiers() != 0) {
        if(e->modifiers() == Qt::ControlModifier && e->button() == Qt::LeftButton) {
            this->rememberedPointForPanning = e->pos();
        }
        return;
    }
    switch(e->button()) {
        case Qt::RightButton:
            QApplication::exit(0);
            break;
        case Qt::LeftButton:
            this->printCoordinates(this->coordWindowToPicture( e->pos()));
            break;
        case Qt::MiddleButton:
            this->rememberedPointForPanning = e->pos();
            break;
    }
}

void Widget::mouseMoveEvent(QMouseEvent *e) {
    Qt::MouseButtons buttonSet = e->buttons();
    Qt::KeyboardModifiers modifierSet = e->modifiers();

    if(buttonSet == Qt::MiddleButton ||
            (modifierSet == Qt::ControlModifier && buttonSet == Qt::LeftButton)) {
        imageLabel->move(imageLabel->pos() + e->pos() - this->rememberedPointForPanning);
        this->rememberedPointForPanning = e->pos();
    }
}

QPoint Widget::coordWindowToPicture(QPoint in) {
    int pictureWidth = imageLabel->pixmap()->size().width();
    int pictureHeight = imageLabel->pixmap()->size().height();
    int windowWidth = imageLabel->width();
    int windowHeight = imageLabel->height();

    int xx = (in.x() - imageLabel->x()) * pictureWidth  / windowWidth;
    int yy = (in.y() - imageLabel->y()) * pictureHeight / windowHeight;

    return QPoint(xx, yy);
}

QPoint Widget::coordPictureToWindow(QPoint in) {
    int pictureWidth = imageLabel->pixmap()->size().width();
    int pictureHeight = imageLabel->pixmap()->size().height();
    int windowWidth = imageLabel->width();
    int windowHeight = imageLabel->height();

    int xx = in.x()  * windowWidth / pictureWidth  + imageLabel->x();
    int yy = in.y() * windowHeight / pictureHeight +  imageLabel->y();

    return QPoint(xx, yy);
}


void Widget::printCoordinates(QPoint coords) {
    fprintf(stdout, "%d,%d\n", coords.x(), coords.y());
    fflush(stdout);
}

#ifndef QT_NO_WHEELEVENT
void Widget::wheelEvent(QWheelEvent * e) {
    int d = e->delta();

    double q = exp(0.001*d);

    //fprintf(stderr, "D: %d %g\n", d, q);

    QPoint pictCoords = this->coordWindowToPicture( e->pos());

    imageLabel->resize(imageLabel->size()*q);

    QPoint windowCoords = this->coordPictureToWindow(pictCoords) - imageLabel->pos();

    imageLabel->move(e->pos() - windowCoords );
}
#endif
