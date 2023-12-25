#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

int main(int argc, char *argv[])
{
    Display         *d;
    int              s;
    Window           w;
    Window           ch_w;
    XEvent           e;

    d = XOpenDisplay(NULL);
    if (!d) {
        fprintf(stderr, "Cannot open display.\n");
        return 1;
    }

    s = DefaultScreen(d);

    /* parent window */
    w = XCreateSimpleWindow(d, RootWindow(d, s), 200, 200, 500, 300, 1, BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d, w);

    /* child window */
    ch_w = XCreateSimpleWindow(d, w, 20, 20, 200, 100, 1, BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, ch_w, ExposureMask | KeyPressMask);
    XMapWindow(d, ch_w);

    while (1) {
        XNextEvent(d, &e);
        if (e.xany.window == ch_w) {
            if (e.type == Expose) {
                XDrawLine(d, ch_w, DefaultGC(d, s), 10, 10, 60, 60);
            }
        }
    }
    
    return 0;
}