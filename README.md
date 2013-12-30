Simple Qt application that displays picture specified on the command line and 
lets you choose pixels from it. Pixel coordinates are printed to stdout.

For use in conjunction with ImageMagick or similar tools.

http://superuser.com/questions/693732/how-to-display-a-picture-and-print-pixel-coordinates-when-i-click

# Usage

    $ DisplayAndPickPixel /tmp/mm.png
    49,285
    258,290
    256,317

* **Left mouse click** - print coordinated to standard output;
* **Right mouse click** - exit the application;
* **Dragging with middleor Ctrl+left mouse button** - pan image;
* **Mouse wheel** - zooming.

# Known issues

* I don't know how to switch smooth scaling to nearest-neighbour, so zooming in 
and choosing exact pixel is not convenient;
* Memory usage skyrockets and application crashes if zoomed in too much.
