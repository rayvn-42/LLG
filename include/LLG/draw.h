#pragma once

#include "types.h"
typedef struct LLGContext LLGContext;

void LLG_drawPixel(LLGContext *ctx, int x, int y);
void LLG_drawLine(LLGContext *ctx, int x1, int y1, int x2, int y2);
void LLG_drawRect(LLGContext *ctx, LLGRect rect);
void LLG_fillRect(LLGContext *ctx, LLGRect rect);
void LLG_drawEllipse(LLGContext *ctx, LLGEllipse ellipse);
void LLG_fillEllipse(LLGContext *ctx, LLGEllipse ellipse);
void LLG_drawCircle(LLGContext *ctx, int x, int y, int r);
void LLG_fillCircle(LLGContext *ctx, int x, int y, int r);
void LLG_drawPolygon(LLGContext *ctx, LLGPolygon polygon);
void LLG_fillPolygon(LLGContext *ctx, LLGPolygon polygon);
void LLG_drawArc(LLGContext *ctx, LLGEllipse ellipse, int angle1, int angle2);
void LLG_fillArc(LLGContext *ctx, LLGEllipse ellipse, int angle1, int angle2);
void LLG_rect(LLGContext *ctx, LLGRect rect);
void LLG_circle(LLGContext *ctx, int x, int y, int r);
void LLG_ellipse(LLGContext *ctx, LLGEllipse ellipse);
void LLG_polygon(LLGContext *ctx, const LLGPolygon polygon);