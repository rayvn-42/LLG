#include "internal.h"
#include "LLG/draw.h"

void LLG_drawPixel(LLGContext *ctx, int x, int y) {
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}
    if (x < 0 || x > ctx->width) {LLG__dispatchError(LLG_ERR_BADARG); return;}
    if (y < 0 || y > ctx->height) {LLG__dispatchError(LLG_ERR_BADARG); return;}

    if (ctx->drawState.strokeEnabled == 0) {return;}

    XGCValues gcv;
    XGetGCValues(ctx->display, ctx->gc, GCForeground, &gcv);

    unsigned long pval = LLG__colorToPixel(ctx, ctx->drawState.strokeColor);
    XSetForeground(ctx->display, ctx->gc, pval);

    XDrawPoint(ctx->display, ctx->backBuffer, ctx->gc, x, y);
    XSetForeground(ctx->display, ctx->gc, gcv.foreground);
}

void LLG_drawLine(LLGContext *ctx, int x1, int y1, int x2, int y2) {
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}

    if (ctx->drawState.strokeEnabled == 0) {return;}

    XGCValues gcv;
    XGetGCValues(ctx->display, ctx->gc, GCForeground, &gcv);

    unsigned long pval = LLG__colorToPixel(ctx, ctx->drawState.strokeColor);
    XSetForeground(ctx->display, ctx->gc, pval);

    XDrawLine(ctx->display, ctx->backBuffer, ctx->gc, x1, y1, x2, y2);
    XSetForeground(ctx->display, ctx->gc, gcv.foreground);
}

void LLG_drawRect(LLGContext *ctx, LLGRect rect) {
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}

    if (ctx->drawState.strokeEnabled == 0) {return;}

    XGCValues gcv;
    XGetGCValues(ctx->display, ctx->gc, GCForeground, &gcv);

    unsigned long pval = LLG__colorToPixel(ctx, ctx->drawState.strokeColor);
    XSetForeground(ctx->display, ctx->gc, pval);

    XDrawRectangle(ctx->display, ctx->backBuffer, ctx->gc, rect.x, rect.y, rect.width, rect.height);
    XSetForeground(ctx->display, ctx->gc, gcv.foreground);
}

void LLG_fillRect(LLGContext *ctx, LLGRect rect) {
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}

    if (ctx->drawState.fillEnabled == 0) {return;}

    XGCValues gcv;
    XGetGCValues(ctx->display, ctx->gc, GCForeground, &gcv);

    unsigned long pval = LLG__colorToPixel(ctx, ctx->drawState.fillColor);
    XSetForeground(ctx->display, ctx->gc, pval);

    XFillRectangle(ctx->display, ctx->backBuffer, ctx->gc, rect.x, rect.y, rect.width, rect.height);
    XSetForeground(ctx->display, ctx->gc, gcv.foreground);
}

void LLG_drawEllipse(LLGContext *ctx, LLGEllipse ellipse) {
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}

    if (ctx->drawState.strokeEnabled == 0) {return;}

    XGCValues gcv;
    XGetGCValues(ctx->display, ctx->gc, GCForeground, &gcv);

    unsigned long pval = LLG__colorToPixel(ctx, ctx->drawState.strokeColor);
    XSetForeground(ctx->display, ctx->gc, pval);

    XDrawArc(ctx->display, ctx->backBuffer, ctx->gc, ellipse.x, ellipse.y, ellipse.rx, ellipse.ry, 0, 360 * 64);
    XSetForeground(ctx->display, ctx->gc, gcv.foreground);
}

void LLG_fillEllipse(LLGContext *ctx, LLGEllipse ellipse) {
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}

    if (ctx->drawState.fillEnabled == 0) {return;}

    XGCValues gcv;
    XGetGCValues(ctx->display, ctx->gc, GCForeground, &gcv);

    unsigned long pval = LLG__colorToPixel(ctx, ctx->drawState.fillColor);
    XSetForeground(ctx->display, ctx->gc, pval);

    XFillArc(ctx->display, ctx->backBuffer, ctx->gc, ellipse.x, ellipse.y, ellipse.rx, ellipse.ry, 0, 360 * 64);
    XSetForeground(ctx->display, ctx->gc, gcv.foreground);
}

void LLG_drawCircle(LLGContext *ctx, int x, int y, int r) {
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}

    if (ctx->drawState.strokeEnabled == 0) {return;}

    XGCValues gcv;
    XGetGCValues(ctx->display, ctx->gc, GCForeground, &gcv);

    unsigned long pval = LLG__colorToPixel(ctx, ctx->drawState.strokeColor);
    XSetForeground(ctx->display, ctx->gc, pval);

    XDrawArc(ctx->display, ctx->backBuffer, ctx->gc, x, y, r, r, 0, 360 * 64);
    XSetForeground(ctx->display, ctx->gc, gcv.foreground);
}

void LLG_fillCircle(LLGContext *ctx, int x, int y, int r) {
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}

    if (ctx->drawState.fillEnabled == 0) {return;}

    XGCValues gcv;
    XGetGCValues(ctx->display, ctx->gc, GCForeground, &gcv);

    unsigned long pval = LLG__colorToPixel(ctx, ctx->drawState.fillColor);
    XSetForeground(ctx->display, ctx->gc, pval);

    XFillArc(ctx->display, ctx->backBuffer, ctx->gc, x, y, r, r, 0, 360 * 64);
    XSetForeground(ctx->display, ctx->gc, gcv.foreground);
}

void LLG_drawPolygon(LLGContext *ctx, LLGPolygon polygon) {
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}

    if (ctx->drawState.strokeEnabled == 0 || polygon.count < 2) {return;}

    XGCValues gcv;
    XGetGCValues(ctx->display, ctx->gc, GCForeground, &gcv);

    unsigned long pval = LLG__colorToPixel(ctx, ctx->drawState.strokeColor);
    XSetForeground(ctx->display, ctx->gc, pval);

    XPoint *xpoints = malloc(sizeof(XPoint) * (polygon.count + 1));
    if (xpoints == NULL) {LLG__dispatchError(LLG_ERR_ALLOC); return;}

    for (int i = 0; i < polygon.count; i++) {
        xpoints[i].x = (short)polygon.points[i].x;
        xpoints[i].y = (short)polygon.points[i].y;
    }

    xpoints[polygon.count].x = (short)polygon.points[0].x;
    xpoints[polygon.count].y = (short)polygon.points[0].y;

    XDrawLines(ctx->display, ctx->backBuffer, ctx->gc, xpoints, (polygon.count + 1), CoordModeOrigin);
    XSetForeground(ctx->display, ctx->gc, gcv.foreground);
    free(xpoints);
}

void LLG_fillPolygon(LLGContext *ctx, LLGPolygon polygon) {
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}

    if (ctx->drawState.fillEnabled == 0 || polygon.count < 2) {return;}

    XGCValues gcv;
    XGetGCValues(ctx->display, ctx->gc, GCForeground, &gcv);

    unsigned long pval = LLG__colorToPixel(ctx, ctx->drawState.fillColor);
    XSetForeground(ctx->display, ctx->gc, pval);

    XPoint *xpoints = malloc(sizeof(XPoint) * (polygon.count + 1));
    if (xpoints == NULL) {LLG__dispatchError(LLG_ERR_ALLOC); return;}

    for (int i = 0; i < polygon.count; i++) {
        xpoints[i].x = (short)polygon.points[i].x;
        xpoints[i].y = (short)polygon.points[i].y;
    }

    XFillPolygon(ctx->display, ctx->backBuffer, ctx->gc, xpoints, polygon.count, Complex, CoordModeOrigin);
    XSetForeground(ctx->display, ctx->gc, gcv.foreground);
    free(xpoints);
}

void LLG_drawArc(LLGContext *ctx, LLGEllipse ellipse, int angle1, int angle2) {
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}

    if (ctx->drawState.strokeEnabled == 0) {return;}

    XGCValues gcv;
    XGetGCValues(ctx->display, ctx->gc, GCForeground, &gcv);

    unsigned long pval = LLG__colorToPixel(ctx, ctx->drawState.strokeColor);
    XSetForeground(ctx->display, ctx->gc, pval);

    XDrawArc(ctx->display, ctx->backBuffer, ctx->gc, ellipse.x, ellipse.y, ellipse.rx, ellipse.ry, angle1 * 64, angle2 * 64);
    XSetForeground(ctx->display, ctx->gc, gcv.foreground);
}

void LLG_fillArc(LLGContext *ctx, LLGEllipse ellipse, int angle1, int angle2) {
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}

    if (ctx->drawState.fillEnabled == 0) {return;}

    XGCValues gcv;
    XGetGCValues(ctx->display, ctx->gc, GCForeground, &gcv);

    unsigned long pval = LLG__colorToPixel(ctx, ctx->drawState.fillColor);
    XSetForeground(ctx->display, ctx->gc, pval);

    XFillArc(ctx->display, ctx->backBuffer, ctx->gc, ellipse.x, ellipse.y, ellipse.rx, ellipse.ry, angle1 * 64, angle2 * 64);
    XSetForeground(ctx->display, ctx->gc, gcv.foreground);
}

void LLG_rect(LLGContext *ctx, LLGRect rect) {
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}

    if (ctx->drawState.fillEnabled) {
        LLG_fillRect(ctx, rect);
    }
    if (ctx->drawState.strokeEnabled) {
        LLG_drawRect(ctx, rect);
    }

    return;
}

void LLG_circle(LLGContext *ctx, int x, int y, int r) {
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}

    if (ctx->drawState.fillEnabled) {
        LLG_fillCircle(ctx, x, y, r);
    }
    if (ctx->drawState.strokeEnabled) {
        LLG_drawCircle(ctx, x, y, r);
    }

    return;
}

void LLG_ellipse(LLGContext *ctx, LLGEllipse ellipse) {
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}

    if (ctx->drawState.fillEnabled) {
        LLG_fillEllipse(ctx, ellipse);
    }
    if (ctx->drawState.strokeEnabled) {
        LLG_drawEllipse(ctx, ellipse);
    }

    return;
}

void LLG_polygon(LLGContext *ctx, const LLGPolygon polygon) {
    if (ctx == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}

    if (ctx->drawState.fillEnabled) {
        LLG_fillPolygon(ctx, polygon);
    }
    if (ctx->drawState.strokeEnabled) {
        LLG_drawPolygon(ctx, polygon);
    }

    return;
}

