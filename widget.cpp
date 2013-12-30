#include <QLabel>
#include <QScrollArea>
#include <QPixmap>
#include <QImage>
#include <QMouseEvent>
#include <QApplication>

#include <stdio.h>

#include "widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{

}

Widget::~Widget()
{

}


void Widget::showPicture() {
    imageLabel = new QLabel(this);
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);


    setWindowTitle(tr("Image Viewer"));
    //resize(500, 400);

    QImage image(mFilename);
    imageLabel->setPixmap(QPixmap::fromImage(image));
    resize(imageLabel->pixmap()->size());
    imageLabel->resize(this->width(), this->height());
}

void Widget::resizeEvent(QResizeEvent *e) {
    this->QWidget::resizeEvent(e);

    imageLabel->resize(this->width(), this->height());
}

void Widget::mousePressEvent(QMouseEvent *e) {
    switch(e->button()) {
        case Qt::RightButton:
            QApplication::exit(0);
            break;
        case Qt::LeftButton:
            this->printCoordinates(e->x(), e->y());
            break;
    }
}

void Widget::printCoordinates(int x, int y) {
    int pictureWidth = imageLabel->pixmap()->size().width();
    int pictureHeight = imageLabel->pixmap()->size().height();
    int windowWidth = this->width();
    int windowHeight = this->height();

    int xx = x * pictureWidth  / windowWidth;
    int yy = y * pictureHeight / windowHeight;
    fprintf(stdout, "%d,%d\n", xx, yy);
    fflush(stdout);
}
