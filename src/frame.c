#include "internal.h"
#include "LLG/frame.h"

void LLG_clear(LLGContext *ctx) {
    /*
        parameters:
            ctx: window context

        returns:
            none
    */

    // context NULL guard
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}
    // translate LLG color to Xlib color value
    unsigned long pval;
    pval = LLG__colorToPixel(ctx, ctx->bgColor);
    // temporarily set the foreground color to the background color
    XSetForeground(ctx->display, ctx->gc, pval);
    // fill the backbuffer with a rectangle the size of the window
    XFillRectangle(ctx->display, ctx->backBuffer, ctx->gc, 0, 0, ctx->width, ctx->height);
    // reset the foreground ground color
    XSetForeground(ctx->display, ctx->gc, LLG__colorToPixel(ctx, ctx->fgColor));
}

void LLG_present(LLGContext *ctx) {
    /*
        parameters:
            ctx: window context

        returns:
            none
    */

    // context NULL guard
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}
    // copy back buffer onto the window
    XCopyArea(ctx->display, ctx->backBuffer, ctx->window, ctx->gc, 0, 0, ctx->width, ctx->height, 0, 0);
    // flush to ensure the copy is immediately visible
    XFlush(ctx->display);
    // check if the fpsCap is set
    if (ctx->fpsCap > 0) {
        // reserve variables
        double now, elapsed;
        // get the current time
        now = LLG_time();
        // get the time since the last frame
        elapsed = now - ctx->lastFrameTime;
        // sleep for rest of set frame time
        if (elapsed < ctx->frameTime) {
            usleep(ctx->frameTime - elapsed);
        }
        // set the last frame time to the current time
        ctx->lastFrameTime = LLG_time();
    }
}

void LLG_setFpsCap(LLGContext *ctx, int fps) {
    /*
        parameters:
            ctx: window context
            fps: set fps cap

        returns:
            none
    */

    // context NULL & fps guard
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}
    if (fps <= 0) {LLG__dispatchError(LLG_ERR_BADARG); return;}
    // store fps cap on the context
    ctx->fpsCap = fps;
    // precompute each frame duration in microseconds
    ctx->frameTime = 1000000 / fps;
}

double LLG_deltaTime(const LLGContext *ctx) {
    /*
        parameters:
            ctx: window context

        returns:
            none
    */

    // context NULL guard
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return 0.0;}
    // reserve variables
    double now, delta;
    // get the current time
    now = LLG_time();
    // compute the elapsed time between now and the last frame
    delta = now - ctx->lastFrameTime;
    // return
    return delta;
}
