#include <stdio.h>
#include <stdlib.h>
#include "LLG/llg.h"
#include "test_utils.h"

/*
    test_main.c
    Check if the library intializes, runs a simple loop and shut everything down correctly.
    Full module tests are in test_[context|window|color|frame|event].
*/

int main(void) {
    printf(_CYAN "\n[LLG] test_main.c - basic test" _RESET "\n");
    LLGError err = LLG_OK;

    /* ----- */
    TEST_SECTION("basic test - init, loop, destroy");

    LLGContext *ctx = LLG_init("LLG Basic Test", 800, 600);
    err = LLG_getError();
    TEST_ASSERT("LLG_init returns non-NULL", ctx != NULL);
    TEST_ASSERT("no error after LLG_init", err == LLG_OK);
    TEST_ASSERT("LLG_isRunning returns 1", LLG_isRunning(ctx) == 1);

    /* ------- */
    TEST_SECTION("basic test - basic frame loop for 2 secs");

    printf("  " _YELLOW "visual: grey window should appear for 2 secs" _RESET "\n");

    LLG_setBackground(ctx, LLG_RGB(50, 50, 50));
    LLG_setFpsCap(ctx, 60);

    double start = LLG_time();
    int frames = 0;
    LLGEvent event;

    while (LLG_isRunning(ctx)) {
        while (LLG_pollEvent(ctx, &event))
            if (event.type == LLG_EVENT_CLOSE) LLG_quit(ctx);

        LLG_clear(ctx);
        LLG_present(ctx);
        frames++;

        if (LLG_time() - start >= 2.0) break;
    }

    printf("  rendered %d frames in 2 seconds\n", frames);
    TEST_ASSERT("rendered at least 1 frame", frames > 0);
    TEST_ASSERT("no error after frame loop", LLG_getError() == LLG_OK);

    /* ------ */
    TEST_SECTION("basic test - quit & destroy");

    LLG_quit(ctx);
    TEST_ASSERT("LLG_isRunning returns 0 after quit", LLG_isRunning(ctx) == 0);

    LLG_destroy(ctx);
    TEST_ASSERT("LLG_destroy completed", 1);

    TEST_SUMMARY();

    if (_tests_failed > 0) {
        printf(_RED "basic test FAILED - no need to run other tests\n" _RESET);
        return 1;
    }

    printf(_GREEN "basic test PASSED - now we can run individual tests for thorough testing\n" _RESET);
    printf("  make test_[context|window|color|frame|event]\n");

    return 0;
}