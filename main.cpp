#include <QApplication>
#include <stdio.h>
#include "widget.h"

int main(int argc, char *argv[])
{
    if(argc!=2 || (QString)argv[1] == "--help" || (QString)argv[1] == "--version") {
        printf("DisplayAndPickPixel v0.1\n");
        fprintf(stderr, "Usage: DisplayAndPickPixel path/to/your/file/png\n");
        fprintf(stderr, "   Left click - print this pixel's coordinates to stdout\n");
        fprintf(stderr, "   Right click - exit the application\n");
        fprintf(stderr, "   Middle drag or Ctrl+left drag - pan picture\n");
        fprintf(stderr, "   Scroll up/down - zoom picture\n");
        return 1;
    }

    const char* filename = argv[1];

    QApplication a(argc, argv);
    Widget w;

    w.setFilename(filename);

    int f = w.showPicture();
    if(!f) return 1;
    w.show();
    
    return a.exec();
}
