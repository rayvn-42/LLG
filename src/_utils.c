#include "internal.h"

#define CLAMP(value, min, max) ((value) < (min) ? (min) : ((value) > (max) ? (max) : (value)))

unsigned long LLG__colorToPixel(LLGContext *ctx, LLGColor color) {
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return 0;}
    color.r = CLAMP(color.r, 0, 255);
    color.g = CLAMP(color.g, 0, 255);
    color.b = CLAMP(color.b, 0, 255);

    XColor xcolor;
    Colormap cmap;

    cmap = DefaultColormap(ctx->display, ctx->screen);
    xcolor.red = (unsigned short)((color.r * 65535) / 255);
    xcolor.green = (unsigned short)((color.g * 65535) / 255);
    xcolor.blue = (unsigned short)((color.b * 65535) / 255);
    (void)color.a;

    if (!XAllocColor(ctx->display, cmap, &xcolor)) {LLG__dispatchError(LLG_ERR_COLOR); return 0;}

    return xcolor.pixel;
}

int LLG__xEventToLLGEvent(LLGContext *ctx, XEvent xevent, LLGEvent *event) {
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return 0;}

    switch (xevent.type) {
        case KeyPress:
            event->type = LLG_EVENT_KEY_PRESS;
            event->key.key = XLookupKeysym(&xevent.xkey, 0);
            ctx->keyState[xevent.xkey.keycode] = 1;
            return 1;

        case KeyRelease:
            event->type = LLG_EVENT_KEY_RELEASE;
            event->key.key = XLookupKeysym(&xevent.xkey, 0);
            ctx->keyState[xevent.xkey.keycode] = 0;
            return 1;
        
        case ButtonPress:
            event->type = LLG_EVENT_MOUSE_PRESS;
            event->mouse.x = xevent.xbutton.x;
            event->mouse.y = xevent.xbutton.y;
            event->mouse.button = xevent.xbutton.button;
            ctx->mouseButtons[xevent.xbutton.button] = 1;
            return 1;

        case ButtonRelease:
            event->type = LLG_EVENT_MOUSE_RELEASE;
            event->mouse.x = xevent.xbutton.x;
            event->mouse.y = xevent.xbutton.y;
            event->mouse.button = xevent.xbutton.button;
            ctx->mouseButtons[xevent.xbutton.button] = 0;
            return 1;

        case MotionNotify:
            event->type = LLG_EVENT_MOUSE_MOVE;
            event->mouse.x = xevent.xmotion.x;
            ctx->mouseX = xevent.xmotion.x;
            event->mouse.y = xevent.xmotion.y;
            ctx->mouseY = xevent.xmotion.y;
            return 1;

        case ConfigureNotify:
            event->type = LLG_EVENT_RESIZE;
            event->resize.width = xevent.xconfigure.width;
            event->resize.height = xevent.xconfigure.height;
            return 1;

        case ClientMessage:
            if ((long unsigned int)xevent.xclient.data.l[0] == ctx->wmDeleteWindow) {
                event->type = LLG_EVENT_CLOSE;
                return 1;
            }break;

        case Expose:
            event->type = LLG_EVENT_EXPOSE;
            return 1;

        default:
            event->type = LLG_EVENT_NONE;
            return 0;
    }
    return 0;
}

typedef struct {
    const char *alias;
    const char *xlfd;
} LLG__FontAlias;

static LLG__FontAlias LLG__FontAliases[] = {
    {"fixed", "fixed"},
    {"mono-12", "-misc-fixed-medium-r-normal--12-*-*-*-*-*-*-*"},
    {"mono-14", "-misc-fixed-medium-r-normal--14-*-*-*-*-*-*-*"},
    {"mono-bold-14", "-misc-fixed-bold-r-normal--14-*-*-*-*-*-*-*"},
    {"sans-12", "-adobe-helvetica-medium-r-normal--12-*-*-*-*-*-*-*"},
    {"sans-14", "-adobe-helvetica-medium-r-normal--14-*-*-*-*-*-*-*"},
    {"sans-bold-14", "-adobe-helvetica-bold-r-normal--14-*-*-*-*-*-*-*"},
    {NULL, NULL}
};

const char *LLG__resolveFont(char *name) {
    for (LLG__FontAlias *fa = LLG__FontAliases; fa->alias != NULL; fa++) {
        if (strcmp(name, fa->alias)) {
            return fa->xlfd;
        }
    }

    return name;
}
