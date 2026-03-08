#pragma once

typedef struct LLGContext LLGContext;

int     LLG_getWidth(const LLGContext *ctx);
int     LLG_getHeight(const LLGContext *ctx);
void    LLG_setTitle(LLGContext *ctx, const char *title);
void    LLG_setResizable(LLGContext *ctx, int resizable);
void    LLG_resize(LLGContext *ctx, int width, int height);