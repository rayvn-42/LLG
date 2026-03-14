#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "LLG/color.h"
#include "LLG/draw.h"
#include "LLG/event.h"
#include "LLG/frame.h"
#include "LLG/image.h"
#include "LLG/llg.h"
#include "LLG/text.h"
#include "LLG/types.h"
#include "LLG/window.h"

extern LLGError lastError;

int LLG__errorHandle(Display *display, XErrorEvent *error);
void LLG__initErrorHandle(void);

typedef void (*LLGErrorCallback)(LLGError err, LLGSeverity severity, const char *msg);
extern LLGErrorCallback LLG__userErrorCallback;

void LLG__dispatchError(LLGError err);

const char *LLG__strCat(char *dest, size_t dest_size, char *m1, const char *m2);

unsigned long LLG__colorToPixel(LLGContext *ctx, LLGColor color);

int LLG__xEventToLLGEvent(LLGContext *ctx, XEvent xevent, LLGEvent *event);

const char *LLG__resolveFont(char *name);

struct LLGContext {
    // XLib core
    Display         *display;
    int             screen;
    Window          root;
    Atom            wmDeleteWindow;

    // User window
    Window          window;
    GC              gc;

    // Window dims
    int             width;
    int             height;
    const char      *title;

    // Peripherals
     // Keyboard
    char            keyState[256];
     // Mouse
    int             mouseButtons[5];
    int             mouseX;
    int             mouseY; 

    // state
    int             running;

    // frame update rate (FPS)
    int             fpsCap;
    double          frameTime;
    double          lastFrameTime;

    // Double screen buffering
    Pixmap          backBuffer;

    // Font
    XFontStruct *font;

    // Draw state
    LLGColor        fgColor;
    LLGColor        bgColor;
    int             lineWidth;
    LLGDrawState    drawState;
};

struct LLGImage {
    // Xlib core
    Pixmap          pmap;
    XImage          *ximage;

    // Image dims
    int             width;
    int             height;

    // Image metadata
    int             depth;
    int             channels;

    // Raw pixel buffer
    uint8_t         *data;
};
