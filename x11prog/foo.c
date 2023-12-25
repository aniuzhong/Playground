#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

int main()
{
    Display *d;
    int      s;
    Window   w;
    XEvent   e;

    d = XOpenDisplay(NULL);
    if (!d) {
        fprintf(stderr, "Cannot open display\n");
        return 1;
    }

    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d,s), 100, 100, 500, 300, 1, BlackPixel(d,s), WhitePixel(d,s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d, w);

    while (1) {
        XNextEvent(d, &e);
    }
}