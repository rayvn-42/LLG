#pragma once

#include <X11/keysym.h>

// Include library files
#include "color.h"
#include "draw.h"
#include "event.h"
#include "frame.h"
#include "image.h"
#include "text.h"
#include "types.h"
#include "window.h"


// Lifecycle
LLGContext *LLG_init(const char *title, int width, int height);
void        LLG_destroy(LLGContext *ctx);
int         LLG_isRunning(const LLGContext *ctx);
double      LLG_time(void);
void        LLG_quit(LLGContext *ctx);
void        LLG_clearError(void);
LLGError    LLG_getError(void);
LLGSeverity LLG_getErrorSeverity(LLGError err);
char       *LLG_errorStr(LLGError err);
