#pragma once

#include "types.h"
typedef struct LLGContext LLGContext;

// Helpers
#define LLG_RGB(r, g, b) ((LLGColor){r, g, b, 255})
#define LLG_RGBA(r, g, b, a) ((LLGColor){r, g, b, a})
#define LLG_HEX(hex) ((LLGColor){((hex >> 16) & 0xff), ((hex >> 8) & 0xff), ((hex) & 0xff), 0xff})
#define LLG_HEX_ALPHA(hex) ((LLGColor){((hex >> 24) & 0xff), ((hex >> 16) & 0xff), ((hex >> 8) & 0xff), ((hex) & 0xff)})


// Colors
#define LLG_WHITE LLG_RGB(255, 255, 255)
#define LLG_BLACK LLG_RGB(0, 0, 0)
#define LLG_RED LLG_RGB(255, 0, 0)
#define LLG_GREEN LLG_RGB(0, 255, 0)
#define LLG_BLUE LLG_RGB(0, 0, 255)
#define LLG_YELLOW LLG_RGB(255, 255, 0)
#define LLG_CYAN LLG_RGB(0, 255, 255)
#define LLG_MAGENTA LLG_RGB(255, 0, 255)

LLGColor    LLG_colorLerp(LLGColor c1, LLGColor c2, float t);
void        LLG_setColor(LLGContext *ctx, LLGColor color);
void        LLG_setFill(LLGContext *ctx, LLGColor color);
void        LLG_setStroke(LLGContext *ctx, LLGColor color);
void        LLG_noFill(LLGContext *ctx);
void        LLG_noStroke(LLGContext *ctx);
void        LLG_setStrokeWidth(LLGContext *ctx, int width);
void        LLG_setBackground(LLGContext *ctx, LLGColor color);
