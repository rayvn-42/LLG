#include "internal.h"

void LLG_setColor(LLGContext *ctx, LLGColor color) {
    /*
        parameters:
            ctx: window context
            color: color value

        returns:
            none
    */

    // context NULL guard
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}
    // set context and draw state values
    ctx->fgColor = color;
    ctx->drawState.fillColor = color;
    ctx->drawState.strokeColor = color;
    ctx->drawState.fillEnabled = 1;
    ctx->drawState.strokeEnabled = 1;
}

void LLG_setFill(LLGContext *ctx, LLGColor color) {
    /*
        parameters:
            ctx: window context
            color: color value

        returns:
            none
    */

    // context NULL guard
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}
    // set draw state fill values
    ctx->drawState.fillColor = color;
    ctx->drawState.fillEnabled = 1;
}

void LLG_setStroke(LLGContext *ctx, LLGColor color) {
    /*
        parameters:
            ctx: window context
            color: color value

        returns:
            none
    */

    // context NULL guard
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}
    // set draw state stroke values
    ctx->drawState.strokeColor = color;
    ctx->drawState.strokeEnabled = 1;
}

void LLG_noFill(LLGContext *ctx) {
    /*
        parameters:
            ctx: window context

        returns:
            none
    */

    // context NULL guard
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}
    // set draw state fill values
    ctx->drawState.fillEnabled = 0;
}

void LLG_noStroke(LLGContext *ctx) {
    /*
        parameters:
            ctx: window context

        returns:
            none
    */

    // context NULL guard
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}
    // set draw state stroke values
    ctx->drawState.strokeEnabled = 0;
}

void LLG_setStrokeWidth(LLGContext *ctx, int width) {
    /*
        parameters:
            ctx: window context
            width: line width

        returns:
            none
    */

    // context NULL & negative width guard
    if (ctx == NULL || width <= 0) {LLG__dispatchError(LLG_ERR_BADARG); return;}
    ctx->lineWidth = width;
    XSetLineAttributes(ctx->display, ctx->gc, width, LineSolid, CapRound, JoinRound);
}
void LLG_setBackground(LLGContext *ctx, LLGColor color) {
    /*
        parameters:
            ctx: window context
            color: color value

        returns:
            none
    */

    // context NULL guard
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}
    // initialize pixel value variable
    unsigned long pval;
    // set context and draw state values
    ctx->bgColor = color;
    // convert llg colors to xlib pixel values
    pval = LLG__colorToPixel(ctx, color);
    // set background colors
    XSetWindowBackground(ctx->display, ctx->window, pval);
}
