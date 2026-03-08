#include <stdio.h>
#include <unistd.h>
#include "LLG/llg.h"
#include "test_utils.h"

int main(void) {
    printf(_CYAN "\n[LLG] test_event.c" _RESET "\n");

    LLGContext *ctx = NULL;
    LLGError err = LLG_OK;

    ctx = LLG_init("test_event", 800, 600);
    if (ctx == NULL) {
        printf(_RED "  FATAL: LLG_init failed, connot run event tests\n" _RESET);
        return 1;
    }

    /* -------- */
    TEST_SECTION("LLG_pollEvent - NULL guards");

    LLGEvent event;
    int result;

    result = LLG_pollEvent(NULL, &event);
    err = LLG_getError();
    TEST_ASSERT("LLG_pollEvent NULL ctx returns 0", result == 0);
    TEST_ASSERT("LLG_pollEvent NULL ctx sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    result = LLG_pollEvent(ctx, NULL);
    err = LLG_getError();
    TEST_ASSERT("LLG_pollEvent NULL event returns 0", result == 0);
    TEST_ASSERT("LLG_pollEvent NULL event sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    /* -------- */
    TEST_SECTION("LLG_waitEvent - NULL guards");

    result = LLG_waitEvent(NULL, &event);
    err = LLG_getError();
    TEST_ASSERT("LLG_waitEvent NULL ctx returns 0", result == 0);
    TEST_ASSERT("LLG_waitEvent NULL ctx sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    result = LLG_pollEvent(ctx, NULL);
    err = LLG_getError();
    TEST_ASSERT("LLG_waitEvent NULL event returns 0", result == 0);
    TEST_ASSERT("LLG_waitEvent NULL event sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    /* ------- */
    TEST_SECTION("LLG_keyDown / LLG_mouseDown / LLG_mousePos - NULL guards");

    result = LLG_keyDown(NULL, XK_a);
    err = LLG_getError();
    TEST_ASSERT("LLG_keyDown NULL ctx returns 0", result == 0);
    TEST_ASSERT("LLG_keyDown NULL ctx sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    result = LLG_mouseDown(NULL, 1);
    err = LLG_getError();
    TEST_ASSERT("LLG_mouseDown NULL ctx returns 0", result == 0);
    TEST_ASSERT("LLG_mouseDown NULL ctx sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    LLG_mousePos(NULL, NULL, NULL);
    err = LLG_getError();
    TEST_ASSERT("LLG_mousePos NULL ctx sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    /* ------ */
    TEST_SECTION("interactive - event loop (close window or press Q to end)");

    printf("  " _YELLOW "interact: move mouse, click, press keys, then press Q or close window\n" _RESET);
    LLG_setBackground(ctx, LLG_RGB(20, 20, 20));

    while (LLG_isRunning(ctx)) {
        while (LLG_pollEvent(ctx, &event)) {
            switch (event.type) {
                case LLG_EVENT_KEY_PRESS:
                    printf("    KEY PRESS  keysym=0x%lx\n", (unsigned long)event.key.key);
                    if (event.key.key == XK_q || event.key.key == XK_Q)
                        LLG_quit(ctx);
                    break;

                case LLG_EVENT_KEY_RELEASE:
                    printf("    KEY RELEASE keysym=0x%lx\n", (unsigned long)event.key.key);
                    break;

                case LLG_EVENT_MOUSE_PRESS:
                    printf("    MOUSE PRESS button=%d at (%d, %d)\n", event.mouse.button, event.mouse.x, event.mouse.y);
                    break;

                case LLG_EVENT_MOUSE_RELEASE:
                    printf("    MOUSE RELEASE button=%d at (%d, %d)\n", event.mouse.button, event.mouse.x, event.mouse.y);
                    break;

                case LLG_EVENT_MOUSE_MOVE:
                    printf("    MOUSE MOVE (%d, %d)\n", event.mouse.x, event.mouse.y);
                    break;

                case LLG_EVENT_RESIZE:
                    printf("    RESIZE %dx%d\n", event.resize.width, event.resize.height);
                    break;

                case LLG_EVENT_CLOSE:
                    printf("   CLOSE EVENT - exiting\n");
                    LLG_quit(ctx);
                    break;

                default:
                    break;
            }
        }

        int mousex, mousey;
        LLG_mousePos(ctx, &mousex, &mousey);

        int left = LLG_mouseDown(ctx, 1);
        int mid = LLG_mouseDown(ctx, 2);
        int right = LLG_mouseDown(ctx, 3);

        printf("\r    mouse (%4d, %4d) L=%d M=%d R=%d    ", mousex, mousey, left, mid, right);
        fflush(stdout);

        LLG_clear(ctx);
        LLG_present(ctx);
    }
    printf("\n");
    TEST_ASSERT("interactive event loop exited cleanly", LLG_getError() == LLG_OK);

    LLG_destroy(ctx);

    TEST_SUMMARY();
    return _tests_failed > 0 ? 1 : 0;
}