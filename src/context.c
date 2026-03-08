/* Include Libraries */
#include "internal.h"
#include "LLG/llg.h"
#include "LLG/types.h"
#include "LLG/color.h"

LLGContext *LLG_init(const char *title, int width, int height) {
    /*
        parameters:
            title: window title
            width: window width
            height: window height
            err: a pointer error variable

        returns:
            window context
    */

    // args NULL guard
    if (title == NULL || width == None || height == None) {LLG__dispatchError(LLG_ERR_BADARG); return NULL;}
    // prohibit width & height values equal or less than 0
    if (width <= 0 || height <= 0) {LLG__dispatchError(LLG_ERR_BADARG); return NULL;}
    // allocate memory for the context structure
    LLGContext *ctx = malloc(sizeof(LLGContext));
    // initialize xlib error handling
    LLG__initErrorHandle();
    // check if there was a memory allocation error
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_ALLOC); return NULL;}
    ctx->display = XOpenDisplay(NULL);
    // check if there was a display initialization error
    if (ctx->display == NULL) {LLG__dispatchError(LLG_ERR_DISPLAY); free(ctx); return NULL;}
    // get the default screen and setup the root window
    ctx->screen = DefaultScreen(ctx->display);
    ctx->root = RootWindow(ctx->display, ctx->screen);
    // create a simple X server window with given width and height
    ctx->window = XCreateSimpleWindow(ctx->display, ctx->root, 0, 0, width, height, 0, WhitePixel(ctx->display, ctx->screen), BlackPixel(ctx->display, ctx->screen));
    // check if window is none
    if (ctx->window == None) {LLG__dispatchError(LLG_ERR_WINDOW); free(ctx); return NULL;}
    // name the window with given title
    XStoreName(ctx->display, ctx->window, title);
    // initialize input masks
    XSelectInput(ctx->display, ctx->window, KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | ExposureMask | StructureNotifyMask);
    // initialize parameter states on the context
    ctx->width = width;
    ctx->height = height;
    ctx->title = title;
    // create a simple GC (graphics context)
    XGCValues values;
    unsigned long valuemask = 0;
    ctx->gc = XCreateGC(ctx->display, ctx->window, valuemask ,&values);
    // setup a back buffer
    ctx->backBuffer = XCreatePixmap(ctx->display, ctx->window, width, height, DefaultDepth(ctx->display, ctx->screen));
    // handle GC and back buffer errors
    if (ctx->gc == NULL) {LLG__dispatchError(LLG_ERR_GC); XDestroyWindow(ctx->display, ctx->window); XCloseDisplay(ctx->display); free(ctx); return NULL;}
    if (ctx->backBuffer == None) {LLG__dispatchError(LLG_ERR_DRAWABLE); XFreeGC(ctx->display, ctx->gc); XDestroyWindow(ctx->display, ctx->window); XCloseDisplay(ctx->display); free(ctx); return NULL;}
    // register the window manager delete window, so the X button works correctly (triggers event)
    Atom wm_delete_window = XInternAtom(ctx->display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(ctx->display, ctx->window, &wm_delete_window, 1);
    // store it for later use
    ctx->wmDeleteWindow = wm_delete_window;
    // set defaults
    ctx->fpsCap = 0.0;
    ctx->frameTime = 0.0;
    // set defaults
    ctx->fgColor = LLG_HEX(0xffffff);
    ctx->bgColor = LLG_RGB(0, 0, 0);
    ctx->lineWidth = 3;
    // set defaults
    ctx->drawState.fillColor = LLG_RGB(255, 255, 255);
    ctx->drawState.strokeColor = LLG_RGB(0, 0, 0);
    ctx->drawState.fillEnabled = 1;
    ctx->drawState.strokeEnabled = 0;
    // maps window to display, which shows to the user
    XMapWindow(ctx->display, ctx->window);
    XSync(ctx->display, False);
    // set the context running state
    ctx->running = 1;
    // set the last frame time to the current time
    ctx->lastFrameTime = LLG_time();
    // return the context
    return ctx;
}

void LLG_destroy(LLGContext *ctx) {
    /*
        parameters:
            ctx: window context

        returns:
            none
    */
    
    // context NULL guard
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}
    // free the back buffer pixel map
    XFreePixmap(ctx->display, ctx->backBuffer);
    // free the graphics context
    XFreeGC(ctx->display, ctx->gc);
    // destroy the window
    XDestroyWindow(ctx->display, ctx->window);
    // close the display
    XCloseDisplay(ctx->display);
    // clear out context values
    ctx->backBuffer = None;
    ctx->window = None;
    ctx->root = None;
    ctx->screen = 0;
    ctx->gc = NULL;
    ctx->display = NULL;
    // free context
    free(ctx);
}

int LLG_isRunning(const LLGContext *ctx) {
    /*
        parameters:
            ctx: window context
        
        returns:
            running state
    */
   
   // return false if context is null
   if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return 0;}
   // get the running state from the context
   int is_running = ctx->running;
   // return is_running state
   return is_running;
}

double LLG_time(void) {
    /*
        parameters:
            none
        
        returns:
            time in seconds w/ sub-second precision
    */
   
    // create timespec structure to get the time
    struct timespec ts;
    // get the clock time, always moves forward and is immune to NTP sync changes and day light savings
    clock_gettime(CLOCK_MONOTONIC, &ts);
    // return time in seconds + nano second accuracy
    return ts.tv_sec + (ts.tv_nsec / 1000000000.0);
}

void LLG_quit(LLGContext *ctx) {
    /*
        parameters:
            ctx: window context
        
        returns:
            none
    */
   
    // NULL guard
    if (ctx != NULL) {
       // set running field to false
       ctx->running = 0;
    } else {LLG__dispatchError(LLG_ERR_BADARG); return;}
}

void LLG_clearError(void) {
    /*
        parameters:
            ctx: window context

        returns:
            none
    */

    // reset last error value
    lastError = LLG_OK;
    // return from function
    return;
}

LLGError LLG_getError(void) {
    /*
        parameters:
            ctx: window context

        returns:
            error enum
    */

    // get error from global variable
    LLGError err = lastError;
    // return err
    return err;
}

LLGSeverity LLG_getErrorSeverity(LLGError err) {
    /*
        parameters:
            err: error enum

        returns:
            severity enum
    */

    // LLGError bounds
    if (err >= LLG_ERR_UNKNOWN) return LLG_ERR_SEVERITY_RECOVERABLE;
    // return severity
    return LLG__errorSeverity[err];
}

char *LLG_errorStr(LLGError err) {
    /*
        parameters:
            err: error enum

        returns:
            string literal
    */

    // reserve string buffer and concatenate string and return
    char s_buf[50];
    return (char*)LLG__strCat(s_buf, sizeof(s_buf), "[LLG] error ", LLG__errorStrings[err]);
}
