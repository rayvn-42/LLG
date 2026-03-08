/* Include Libraries */
#include "internal.h"
#include "LLG/window.h"

int LLG_getWidth(const LLGContext *ctx) {
    /*
        parameters:
            ctx: window context

        returns:
            window width
    */

    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return 0;}
    // fetch window width from window context
    int width = ctx->width;
    // return window width
    return width;
}

int LLG_getHeight(const LLGContext *ctx) {
    /*
        parameters:
            ctx: window context

        returns:
            window height
    */

    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return 0;}
    // fetch window height from window context
    int height = ctx->height;
    // return window height
    return height;
}

void LLG_setTitle(LLGContext *ctx, const char *title) {
    /*
        parameters:
            ctx: window context
            title: window title

        returns:
            none
    */

    if (ctx == NULL || title == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}
    // Change WM_NAME property (title)
    XStoreName(ctx->display, ctx->window, title);
    // Update context title
    ctx->title = title;
    // Update window
    XFlush(ctx->display);
}

void LLG_setResizable(LLGContext *ctx, int resizable) {
    /*
        parameters:
            ctx: window context
            resizable: is window resizable

        returns:
            none
    */

    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}
    // Define hints & supplied variables for XGetWMNormalHints
    XSizeHints hints;
    long supplied;

    // Get the window manager normal hints (containes min_&max_(width | height))
    XGetWMNormalHints(ctx->display, ctx->window, &hints, &supplied);

    if (!resizable) {
        // set hints struct flags
        hints.flags |= PMinSize | PMaxSize;
        // set min_height = max_height (resize lock)
        hints.min_height = hints.max_height = LLG_getHeight(ctx);
        // set min_width = max_width (resize lock)
        hints.min_width = hints.max_width = LLG_getWidth(ctx);
        // Set the window manager normal hints
        XSetWMNormalHints(ctx->display, ctx->window, &hints);
    }else {
        // Uncheck Size flags (resize unlock)
        hints.flags &= ~(PMinSize | PMaxSize);
        // Set the window manager normal hints
        XSetWMNormalHints(ctx->display, ctx->window, &hints);
    }

    // Update window
    XFlush(ctx->display);
}

void LLG_resize(LLGContext *ctx, int width, int height) {
    /*
        parameters:
            ctx: window context
            resizable: is window resizable

        returns:
            none
    */

    if (ctx == NULL || width <= 0 || height <= 0) {LLG__dispatchError(LLG_ERR_BADARG); return;}
    // Resize window
    XResizeWindow(ctx->display, ctx->window, width, height);
    // Update context dims values
    ctx->width = width;
    ctx->height = height;
    // Free old back buffer
    XFreePixmap(ctx->display, ctx->backBuffer);
    // Create and update back buffer
    ctx->backBuffer = XCreatePixmap(ctx->display, ctx->window, width, height, DefaultDepth(ctx->display, ctx->screen));
    if (ctx->backBuffer == None) {LLG__dispatchError(LLG_ERR_DRAWABLE); return;}
    // Update window
    XFlush(ctx->display);
}
