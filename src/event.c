#include "internal.h"
#include "LLG/event.h"

int LLG_waitEvent(LLGContext *ctx, LLGEvent *event) {
    /*
        parameters:
            ctx: window context
            event: event enum
        
        returns:
            integer
    */

    // context & event NULL guard
    if (ctx == NULL || event == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return 0;}
    // wait for event
    XEvent xevent;
    XNextEvent(ctx->display, &xevent);
    // return LLG compatible event
    return LLG__xEventToLLGEvent(ctx, xevent, event);
}

int LLG_pollEvent(LLGContext *ctx, LLGEvent *event) {
    /*
        parameters:
            ctx: window context
            event: event enum
        
        returns:
            integer
    */

    // context & event NULL guard
    if (ctx == NULL || event == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return 0;}
    // skip if no events pending
    if (XPending(ctx->display) == 0) {
        return 0;
    }
    // wait for event
    XEvent xevent;
    XNextEvent(ctx->display, &xevent);
    // return LLG compatible event
    return LLG__xEventToLLGEvent(ctx, xevent, event);
}

int LLG_keyDown(const LLGContext *ctx, int key) {
    /*
        parameters:
            ctx: window context
            key: key number
        
        returns:
            integer
    */

    // context NULL guard
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return 0;}
    // key index must within the 256 range
    if (key < 0 || key > 255) {LLG__dispatchError(LLG_ERR_BADARG); return 0;}
    // return the current state for that key
    return ctx->keyState[key];
}

int LLG_mouseDown(const LLGContext *ctx, int button) {
    /*
        parameters:
            ctx: window context
            button: button number
        
        returns:
            integer
    */

    // context NULL guard
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return 0;}
    // button index must within the 1-5 range
    if (button < 1 || button > 5) {LLG__dispatchError(LLG_ERR_BADARG); return 0;}
    // return the current state for that button
    return ctx->mouseButtons[button];
}

void LLG_mousePos(const LLGContext *ctx, int *x, int *y) {
    /*
        parameters:
            ctx: window context
            x, y: mouse coords
        
        returns:
            none
    */

    // context NULL guard
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}
    // guard each coord seperatly, user might only need one
    if (x != NULL) {
        *x = ctx->mouseX;
    }
    if (y != NULL) {
        *y = ctx->mouseY;
    }
}
