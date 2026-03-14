#include <LLG/llg.h>

int main(void) {
    LLGContext *ctx = LLG_init("My Window", 800, 600);
    LLGEvent ev;

    LLG_setBackground(ctx, LLG_RGB(20, 20, 20));
    LLG_setFpsCap(ctx, 60);

    while (LLG_isRunning(ctx)) {
        while (LLG_pollEvent(ctx, &ev))
            if (ev.type == LLG_EVENT_CLOSE) LLG_quit(ctx);

        LLG_clear(ctx);

        LLG_setFill(ctx, LLG_RGB(255, 80, 0));
        LLG_setStroke(ctx, LLG_RGB(255, 255, 255));
        LLG_setStrokeWidth(ctx, 2);
        LLG_circle(ctx, 400, 300, 80);

        LLG_present(ctx);
    }

    LLG_destroy(ctx);
    return 0;
}