#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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

protected:
    virtual void resizeEvent(QResizeEvent *);
    virtual void mousePressEvent(QMouseEvent *);

    void printCoordinates(int x, int y);
};

#endif // WIDGET_H
