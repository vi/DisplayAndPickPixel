#include <QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setFilename("/tmp/mm.png");
    w.setFilename("/tmp/what-colors-mean-in-different-cultures_50290a647f1f2.png");
    w.showPicture();
    w.show();
    
    return a.exec();
}
