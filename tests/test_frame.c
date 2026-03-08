#include <stdio.h>
#include <unistd.h>
#include "LLG/llg.h"
#include "test_utils.h"

/* Helper */
static void runFor(LLGContext *ctx, int seconds) {
    double start = LLG_time();
    LLGEvent event;
    while (LLG_isRunning(ctx)) {
        while (LLG_pollEvent(ctx, &event)) {
            if (event.type == LLG_EVENT_CLOSE) LLG_quit(ctx);
        }
        LLG_clear(ctx);
        LLG_present(ctx);
        if (LLG_time() - start >= seconds) break;
    }
}

int main(void) {
    printf(_CYAN "\n[LLG] test_frame.c" _RESET "\n");
    
    LLGContext *ctx = NULL;
    LLGError err = LLG_OK;

    ctx = LLG_init("test_frame", 800, 600);
    if (ctx == NULL) {
        printf(_RED "  FATAL: LLG_init failed, cannot run frame tests\n" _RESET);
        return 1;
    }

    /* ------- */
    TEST_SECTION("LLG_clear");

    LLG_clear(ctx);
    err = LLG_getError();
    TEST_ASSERT("LLG_clear on valid ctx sets no error", err == LLG_OK);

    LLG_clear(NULL);
    err = LLG_getError();
    TEST_ASSERT("LLG_clear on NULL sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    /* ------- */
    TEST_SECTION("LLG_present");

    LLG_present(ctx);
    err = LLG_getError();
    TEST_ASSERT("LLG_present on valid ctx sets no error", err == LLG_OK);

    LLG_present(NULL);
    err = LLG_getError();
    TEST_ASSERT("LLG_present on NULL sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();
    /* -------- */
    TEST_SECTION("LLG_clear - visual");

    printf("  " _YELLOW "visual: window should be solid red for 1 sec" _RESET "\n");
    LLG_setBackground(ctx, LLG_RGB(255, 0, 0));
    runFor(ctx, 1);
    TEST_ASSERT("red clear ran without error", LLG_getError() == LLG_OK);

    /* ------- */
    TEST_SECTION("LLG_clear - visual");

    printf("  " _YELLOW "visual: window alternates red/blue every 2 secs for 4 secs" _RESET "\n");
    LLGColor colors[2] = {LLG_RGB(255, 0, 0), LLG_RGB(0, 0, 255)};
    int ci = 0;
    double lastSwap = LLG_time();
    double start = LLG_time();
    LLGEvent event;

    while (LLG_isRunning(ctx)) {
        while (LLG_pollEvent(ctx, &event))
            if (event.type == LLG_EVENT_CLOSE) LLG_quit(ctx);

        if (LLG_time() - lastSwap >= 1.0) {
            ci = !ci;
            lastSwap = LLG_time();
            LLG_setBackground(ctx, colors[ci]);
        }

        LLG_clear(ctx);
        LLG_present(ctx);

        if (LLG_time() - start >= 4.0) break;
    }
    TEST_ASSERT("alternating clear ran without error", LLG_getError() == LLG_OK);

    /* ----- */
    TEST_SECTION("LLG_setFpsCap");

    LLG_setFpsCap(ctx, 0);
    err = LLG_getError();
    TEST_ASSERT("LLG_setFpsCap 0 sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    LLG_setFpsCap(ctx, -1);
    err = LLG_getError();
    TEST_ASSERT("LLG_setFpsCap -1 sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    LLG_setFpsCap(NULL, 60);
    err = LLG_getError();
    TEST_ASSERT("LLG_setFpsCap NULL sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    /* --------- */
    TEST_SECTION("LLG_deltaTime - 60fps cap");

    LLG_setBackground(ctx, LLG_RGB(30, 30, 30));
    LLG_setFpsCap(ctx, 60);
    start = LLG_time();
    int frame = 0;
    int badDeltas = 0;

    while (LLG_isRunning(ctx)) {
        while (LLG_pollEvent(ctx, &event))
            if (event.type == LLG_EVENT_CLOSE) LLG_quit(ctx);

        double dt = LLG_deltaTime(ctx);

        if (dt > 0.05 && frame > 5) badDeltas++;

        LLG_clear(ctx);
        LLG_present(ctx);
        frame++;
        if (LLG_time() - start >= 2.0) break;
    }
    TEST_ASSERT("delta time stayed 50ms while capped at 60fps", badDeltas == 0);

    /* ------- */
    TEST_SECTION("LLG_time");
    // implemented in context.c but mainly used in frame control

    double t1 = LLG_time();
    usleep(100000);
    double t2 = LLG_time();
    TEST_ASSERT("LLG_time increases over time", t2 > t1);
    TEST_ASSERT("LLG_time 100ms sleep is ~0.1 sec", (t2 - t1) >= 0.09 && (t2 - t1) <= 0.15);

    LLG_destroy(ctx);

    TEST_SUMMARY();
    return _tests_failed > 0 ? 1 : 0;
}