#include "internal.h"

LLGError lastError = LLG_OK;

const LLGSeverity LLG__errorSeverity[] = {
    [LLG_OK] = LLG_ERR_SEVERITY_OK,
    [LLG_ERR_DISPLAY] = LLG_ERR_SEVERITY_FATAL,
    [LLG_ERR_ALLOC] = LLG_ERR_SEVERITY_FATAL,
    [LLG_ERR_WINDOW] = LLG_ERR_SEVERITY_FATAL,
    [LLG_ERR_GC] = LLG_ERR_SEVERITY_FATAL,
    [LLG_ERR_DRAWABLE] = LLG_ERR_SEVERITY_RECOVERABLE,
    [LLG_ERR_COLOR] = LLG_ERR_SEVERITY_RECOVERABLE,
    [LLG_ERR_FONT] = LLG_ERR_SEVERITY_RECOVERABLE,
    [LLG_ERR_BADARG] = LLG_ERR_SEVERITY_RECOVERABLE,
    [LLG_ERR_ATOM] = LLG_ERR_SEVERITY_RECOVERABLE,
    [LLG_ERR_CURSOR] = LLG_ERR_SEVERITY_RECOVERABLE,
    [LLG_ERR_UNKNOWN] = LLG_ERR_SEVERITY_RECOVERABLE,
};

const char *LLG__errorStrings[] = {
    [LLG_OK]           = "LLG_OK: Success",
    [LLG_ERR_DISPLAY]  = "LLG_ERR_DISPLAY: Failed to open display",
    [LLG_ERR_WINDOW]   = "LLG_ERR_WINDOW: Failed to create window",
    [LLG_ERR_GC]       = "LLG_ERR_GC: Failed to create graphics context",
    [LLG_ERR_ALLOC]    = "LLG_ERR_ALLOC: Memory allocation failed",
    [LLG_ERR_COLOR]    = "LLG_ERR_COLOR: Invalid or unavailable color",
    [LLG_ERR_FONT]     = "LLG_ERR_FONT: Failed to load font",
    [LLG_ERR_BADARG]   = "LLG_ERR_BADARG: Bad argument",
    [LLG_ERR_ATOM]     = "LLG_ERR_ATOM: Failed to intern atom",
    [LLG_ERR_CURSOR]   = "LLG_ERR_CURSOR: Failed to create cursor",
    [LLG_ERR_DRAWABLE] = "LLG_ERR_DRAWABLE: Invalid drawable",
    [LLG_ERR_UNKNOWN]  = "LLG_ERR_UNKNOWN: Unknown error",
};

int LLG__errorHandle(Display *display, XErrorEvent *error) {
    (void)display;
    switch (error->error_code) {
        case BadWindow:   LLG__dispatchError(LLG_ERR_WINDOW); break;
        case BadAccess:   LLG__dispatchError(LLG_ERR_BADARG); break;
        case BadAlloc:    LLG__dispatchError(LLG_ERR_ALLOC); break;
        case BadAtom:     LLG__dispatchError(LLG_ERR_ATOM); break;
        case BadColor:    LLG__dispatchError(LLG_ERR_COLOR); break;
        case BadCursor:   LLG__dispatchError(LLG_ERR_CURSOR); break;
        case BadDrawable: LLG__dispatchError(LLG_ERR_DRAWABLE); break;
        case BadFont:     LLG__dispatchError(LLG_ERR_FONT); break;
        case BadGC:       LLG__dispatchError(LLG_ERR_GC); break;
        default:          LLG__dispatchError(LLG_ERR_UNKNOWN); break;
    }

    char msg[256];
    XGetErrorText(display, error->error_code, msg, sizeof(msg));
    fprintf(stderr, "[LLG] Xlib error %d: %s (request: %d)\n", error->error_code, msg, error->request_code);

    return 0;
}

void LLG__initErrorHandle(void) {
    XSetErrorHandler(LLG__errorHandle);
}

LLGErrorCallback LLG__userErrorCallback = NULL;

void LLG__dispatchError(LLGError err) {
    if (err == LLG_OK) return;
    lastError = err;

    LLGSeverity severity = LLG__errorSeverity[err];
    const char *msg = LLG__errorStrings[err];

    if (LLG__userErrorCallback) {
        LLG__userErrorCallback(err, severity, msg);
    }

    if (severity == LLG_ERR_SEVERITY_FATAL) {
        fprintf(stderr, "[LLG] Fatal error: %s\n", msg);
        exit(EXIT_FAILURE);
    }
}
