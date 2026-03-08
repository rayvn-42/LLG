#pragma once

#include "types.h"
typedef struct LLGContext LLGContext;
typedef struct LLGImage LLGImage;

LLGImage   *LLG_imageLoad(LLGContext *ctx, const char *path);
LLGImage   *LLG_imageCreate(LLGContext *ctx, int width, int height);
void        LLG_imageDestroy(LLGImage *img);
void        LLG_drawImage(LLGContext *ctx, LLGImage *img, int x, int y);
void        LLG_drawImageScaled(LLGContext *ctx, LLGImage *img, LLGRect dst);
void        LLG_drawImageRegion(LLGContext *ctx, LLGImage *img, LLGRect src, LLGRect dst);