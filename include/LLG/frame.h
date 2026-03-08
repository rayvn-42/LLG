#pragma once

typedef struct LLGContext LLGContext;

void    LLG_clear(LLGContext *ctx);
void    LLG_present(LLGContext *ctx);
void    LLG_setFpsCap(LLGContext *ctx, int fps);
double  LLG_deltaTime(const LLGContext *ctx);