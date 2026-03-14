#include "internal.h"
#include "LLG/text.h"

void LLG_drawText(LLGContext *ctx, int x, int y, const char *text) {
    if (ctx == NULL || text == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}

    if (ctx->drawState.strokeEnabled == 0) {return;}

    XGCValues gcv;
    XGetGCValues(ctx->display, ctx->gc, GCForeground, &gcv);

    unsigned long pval = LLG__colorToPixel(ctx, ctx->drawState.strokeColor);
    XSetForeground(ctx->display, ctx->gc, pval);

    XDrawString(ctx->display, ctx->backBuffer, ctx->gc, x, y, text, strlen(text));
    XSetForeground(ctx->display, ctx->gc, gcv.foreground);
}

void LLG_setFont(LLGContext *ctx, const char *font_name) {
    if (ctx == NULL || font_name == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}

    const char *xlfd = LLG__resolveFont((char *)font_name);

    XFontStruct *font = XLoadQueryFont(ctx->display, xlfd);

    if (font == NULL) {LLG__dispatchError(LLG_ERR_FONT); return;}

    if (ctx->font != NULL) {
        XFreeFont(ctx->display, ctx->font);
    }

    ctx->font = font;

    XSetFont(ctx->display, ctx->gc, ctx->font->fid);
}

void LLG_textSize(LLGContext *ctx, const char *text, int *width, int *height) {
    if (ctx == NULL || text == NULL) {LLG__dispatchError(LLG_ERR_BADARG); return;}

    if (ctx->font == NULL) {LLG__dispatchError(LLG_ERR_FONT); return;}

    XCharStruct overall;
    int dir, ascent, descent;
    XTextExtents(ctx->font, text, strlen(text), &dir, &ascent, &descent, &overall);

    if (width != NULL) {
        *width = overall.width;
    }
    if (height != NULL) {
        *height = ascent + descent;
    }
}
