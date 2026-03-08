#include <stdio.h>
#include <unistd.h>
#include "LLG/llg.h"
#include "test_utils.h"

int main(void) {
    printf(_CYAN "\n[LLG] test_window.c" _RESET "\n");

    LLGContext *ctx = NULL;
    LLGError err = LLG_OK;

    ctx = LLG_init("test_window", 800, 600);
    if (ctx == NULL) {
        printf(_RED "  FATAL: LLG_init failed, cannot run window tests\n" _RESET);
        return 1;
    }

    /* ------ */
    TEST_SECTION("LLG_getWidth / LLG_getHeight");

    TEST_ASSERT("LLG_getWidth returns 800 after init with 800", LLG_getWidth(ctx) == 800);
    TEST_ASSERT("LLG_getHeight returns 600 after init with 600", LLG_getHeight(ctx) == 600);
    TEST_ASSERT("LLG_getWidth on NULL returns 0", LLG_getWidth(NULL) == 0);
    TEST_ASSERT("LLG_getHeight on NULL returns 0", LLG_getHeight(NULL) == 0);

    err = LLG_getError();
    TEST_ASSERT("NULL getWidth/getHeight sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();
    /* ----- */
    TEST_SECTION("LLG_setTitle");

    printf("  " _YELLOW "visual: title should change to 'New Title for 1 sec" _RESET "\n");
    LLG_setTitle(ctx, "New Title");
    err = LLG_getError();
    TEST_ASSERT("LLG_setTitle on valid args sets no error", err == LLG_OK);
    sleep(1);

    LLG_setTitle(ctx, "test_window");

    LLG_setTitle(NULL, "title");
    err = LLG_getError();
    TEST_ASSERT("LLG_setTile on NULL ctx sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();
    LLG_setTitle(ctx, NULL);
    err = LLG_getError();
    TEST_ASSERT("LLG_setTitle on NULL title sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();
    /* ------- */
    TEST_SECTION("LLG_setResizable");

    printf("  " _YELLOW "visual: resize grip should disappear for 2 secs" _RESET "\n");
    LLG_setResizable(ctx, 0);
    sleep(2);

    printf("  " _YELLOW "visual: resize grip should return now" _RESET "\n");
    LLG_setResizable(ctx, 1);
    sleep(1);

    LLG_setResizable(NULL, 0);
    err = LLG_getError();
    TEST_ASSERT("LLG_setResizable on NULL sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();
    /* ------ */
    TEST_SECTION("LLG_resize");

    printf("  " _YELLOW "visual: window should resize to 400x300 for 1 sec" _RESET "\n");
    LLG_resize(ctx, 400, 300);
    err = LLG_getError();
    TEST_ASSERT("LLG_resize sets no error on valid args", err == LLG_OK);
    TEST_ASSERT("LLG_getWidth returns the new width after resize", LLG_getWidth(ctx) == 400);
    TEST_ASSERT("LLG_getHeight returns the new height after resize", LLG_getHeight(ctx) == 300);
    sleep(1);

    LLG_resize(ctx, 800, 600);

    LLG_resize(ctx, 0, 600);
    err = LLG_getError();
    TEST_ASSERT("LLG_resize on zero width sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();
    LLG_resize(ctx, 800, -1);
    err = LLG_getError();
    TEST_ASSERT("LLG_resize on negative height sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();
    LLG_resize(NULL, 800, 600);
    err = LLG_getError();
    TEST_ASSERT("LLG_resize on NULL ctx sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    LLG_destroy(ctx);

    TEST_SUMMARY();
    return _tests_failed > 0 ? 1 : 0;
}