#pragma once

typedef struct LLGContext LLGContext;

void LLG_drawText(LLGContext *ctx, int x, int y, const char *text);
void LLG_setFont(LLGContext *ctx, const char *font_name);
void LLG_textSize(LLGContext *ctx, const char *text, int *width, int *height);