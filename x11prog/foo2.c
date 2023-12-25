#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

int main(int argc, char *argv[])
{
    Display *d;
    int s;
    Window w;
    Window ch_w;
    Window root_w;
    XEvent e;
    Colormap colormap;
    XColor btn_color;
    XColor light_gray_color, dark_gray_color;
    XGCValues gcv_light_gray, gcv_dark_gray;
    GC gc_light_gray, gc_dark_gray;
    int width, height, x, y, border_width, depth;

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
    colormap = DefaultColormap(d, s);
    XParseColor(d, colormap, "rgb:cc/cc/cc", &btn_color);
    XAllocColor(d, colormap, &btn_color);

    XParseColor(d, colormap, "rgb:ee/ee/ee", &light_gray_color);
    XAllocColor(d, colormap, &light_gray_color);
    gcv_light_gray.foreground = light_gray_color.pixel;
    gcv_light_gray.background = btn_color.pixel;
    gc_light_gray = XCreateGC(d, RootWindow(d, s), GCForeground | GCBackground, &gcv_light_gray);

    XParseColor(d, colormap, "rgb:88/88/88", &dark_gray_color);
    XAllocColor(d, colormap, &dark_gray_color);
    gcv_dark_gray.foreground = dark_gray_color.pixel;
    gcv_dark_gray.background = btn_color.pixel;
    gc_dark_gray = XCreateGC(d, RootWindow(d, s), GCForeground | GCBackground, &gcv_dark_gray);

    ch_w = XCreateSimpleWindow(d, w, 20, 20, 200, 100, 1, BlackPixel(d, s), btn_color.pixel);
    XSelectInput(d, ch_w, ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask);
    XMapWindow(d, ch_w);
    XGetGeometry(d, ch_w, &w, &x, &y, &width, &height, &border_width, &depth);

    while (1) {
        XNextEvent(d, &e);
        if (e.xany.window == ch_w) {
            if (e.type == Expose) {
                XDrawLine(d, ch_w, gc_dark_gray, 0, 0, width - 1, 0);
                XDrawLine(d, ch_w, gc_dark_gray, 0, 0, 0, height - 1);
                XDrawLine(d, ch_w, gc_dark_gray, width - 1, 0, width - 1, height - 1);
                XDrawLine(d, ch_w, gc_dark_gray, 0, height - 1, width - 1, height - 1);
            }
            if (e.type == ButtonPress) {
                if (e.xbutton.button == 1) {
                    XDrawLine(d, ch_w, gc_dark_gray, 0, 0, width - 1, 0);
                    XDrawLine(d, ch_w, gc_dark_gray, 0, 0, 0, height - 1);
                    XDrawLine(d, ch_w, gc_dark_gray, width - 1, 0, width - 1, height - 1);
                    XDrawLine(d, ch_w, gc_dark_gray, 0, height - 1, width - 1, height - 1);
                    printf("Button pressed.\n");
                }
            }
            if (e.type == ButtonRelease) {
                if (e.xbutton.button == 1) {
                    XDrawLine(d, ch_w, gc_light_gray, 0, 0, width - 1, 0);
                    XDrawLine(d, ch_w, gc_light_gray, 0, 0, 0, height - 1);
                    XDrawLine(d, ch_w, gc_light_gray, width - 1, 0, width - 1, height - 1);
                    XDrawLine(d, ch_w, gc_light_gray, 0, height - 1, width - 1, height - 1);
                    printf("Button released.\n");
                }
            }
        }
    }

    return 0;
}