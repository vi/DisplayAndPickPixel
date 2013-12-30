#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPoint>

class QLabel;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void setFilename(QString filename) { mFilename = filename; }
    void showPicture();

private:
    QString mFilename;
    QLabel *imageLabel;
    QPoint rememberedPointForPanning;

protected:
    virtual void resizeEvent(QResizeEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
#ifndef QT_NO_WHEELEVENT
    virtual void wheelEvent(QWheelEvent *);
#endif

    void printCoordinates(QPoint coords);

    QPoint coordWindowToPicture(QPoint in);
    QPoint coordPictureToWindow(QPoint in);
};

#endif // WIDGET_H
