#include <stdio.h>
#include <LLG/llg.h>

int main(void) {
    LLGContext *ctx = LLG_init("LLG Example - Mouse", 800, 600);
    if (ctx == NULL) {
        printf("%s\n", LLG_errorStr(LLG_getError()));
        return 1;
    }

    LLG_setBackground(ctx, LLG_CYAN);
    LLG_setFpsCap(ctx, 60);

    LLGEvent ev;

    while (LLG_isRunning(ctx)) {
        while (LLG_pollEvent(ctx, &ev)) {
            if (ev.type == LLG_EVENT_CLOSE) LLG_quit(ctx);
            if (ev.type == LLG_EVENT_KEY_PRESS)
                if (ev.key.key == XK_Escape) LLG_quit(ctx);
            if (ev.type == LLG_EVENT_RESIZE)
                printf("resized to %dx%d\n", ev.resize.width, ev.resize.height);
        }

        int mouseX, mouseY;
        LLG_mousePos(ctx, &mouseX, &mouseY);
        printf("\rmouse (%d, %d) dt=%.4f\n", mouseX, mouseY, LLG_deltaTime(ctx));
        fflush(stdout);

        LLG_clear(ctx);
        LLG_present(ctx);
    }

    LLG_destroy(ctx);
    return 0;
}