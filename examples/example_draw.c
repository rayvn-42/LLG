#include <LLG/llg.h>

int main(void) {
    LLGContext *ctx = LLG_init("LLG Example - draw", 800, 600);
    LLGEvent ev;

    LLGEllipse ellipse = (LLGEllipse){600, 100, 70, 40};

    LLG_setBackground(ctx, LLG_RGB(20, 20, 20));
    LLG_setFpsCap(ctx, 60);

    while (LLG_isRunning(ctx)) {
        while (LLG_pollEvent(ctx, &ev))
            if (ev.type == LLG_EVENT_CLOSE) LLG_quit(ctx);

        LLG_clear(ctx);

        LLG_setFill(ctx, LLG_RGB(255, 80, 0));
        LLG_setStroke(ctx, LLG_RGB(255, 255, 255));
        LLG_setStrokeWidth(ctx, 2);
        LLG_circle(ctx, LLG_getWidth(ctx) / 2, LLG_getHeight(ctx) / 2, 80);
        LLG_setFill(ctx, LLG_RGB(255, 80, 255));
        LLG_ellipse(ctx, ellipse);

        LLG_present(ctx);
    }

    LLG_destroy(ctx);
    return 0;
}