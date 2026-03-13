#include <stdio.h>
#include "internal.h"
#include "LLG/llg.h"
#include "test_utils.h"

int main(void) {
    printf(_CYAN "\n[LLG] test_color.c" _RESET "\n");

    LLGContext *ctx = NULL;
    LLGError err = LLG_OK;
    LLGColor color;

    /* ------- */
    TEST_SECTION("LLG_RGB");

    color = LLG_RGB(255, 0, 0);
    TEST_ASSERT("LLG_RGB sets r=255", color.r == 255);
    TEST_ASSERT("LLG_RGB sets g=0", color.g == 0);
    TEST_ASSERT("LLG_RGB sets b=0", color.b == 0);
    TEST_ASSERT("LLG_RGB sets a=255", color.a == 255);

    /* ------ */
    TEST_SECTION("LLG_RGBA");

    color = LLG_RGBA(10, 20, 30, 128);
    TEST_ASSERT("LLG_RGBA sets r=10", color.r == 10);
    TEST_ASSERT("LLG_RGBA sets g=20", color.g == 20);
    TEST_ASSERT("LLG_RGBA sets b=30", color.b == 30);
    TEST_ASSERT("LLG_RGBA sets a=128", color.a == 128);

    /* -------- */
    TEST_SECTION("LLG_HEX");

    color = LLG_HEX(0xf58823);
    TEST_ASSERT("LLG_HEX sets r=245", color.r == 245);
    TEST_ASSERT("LLG_HEX sets g=136", color.g == 136);
    TEST_ASSERT("LLG_HEX sets b=35", color.b == 35);
    TEST_ASSERT("LLG_HEX sets a=255", color.a == 255);

    color = LLG_HEX(0x000000);
    TEST_ASSERT("LLG_HEX sets r=0", color.r == 0);
    TEST_ASSERT("LLG_HEX sets g=0", color.g == 0);
    TEST_ASSERT("LLG_HEX sets b=0", color.b == 0);
    TEST_ASSERT("LLG_HEX sets a=255", color.a == 255);

    color = LLG_HEX(0xffffff);
    TEST_ASSERT("LLG_HEX sets r=255", color.r == 255);
    TEST_ASSERT("LLG_HEX sets g=255", color.g == 255);
    TEST_ASSERT("LLG_HEX sets b=255", color.b == 255);
    TEST_ASSERT("LLG_HEX sets a=255", color.a == 255);

    /* -------- */
    TEST_SECTION("LLG_HEX_ALPHA");

    color = LLG_HEX_ALPHA(0xf58823a4);
    TEST_ASSERT("LLG_HEX sets r=245", color.r == 245);
    TEST_ASSERT("LLG_HEX sets g=136", color.g == 136);
    TEST_ASSERT("LLG_HEX sets b=35", color.b == 35);
    TEST_ASSERT("LLG_HEX sets a=164", color.a == 164);

    color = LLG_HEX_ALPHA(0x00000000);
    TEST_ASSERT("LLG_HEX sets r=0", color.r == 0);
    TEST_ASSERT("LLG_HEX sets g=0", color.g == 0);
    TEST_ASSERT("LLG_HEX sets b=0", color.b == 0);
    TEST_ASSERT("LLG_HEX sets a=0", color.a == 0);

    color = LLG_HEX_ALPHA(0xffffff45);
    TEST_ASSERT("LLG_HEX sets r=255", color.r == 255);
    TEST_ASSERT("LLG_HEX sets g=255", color.g == 255);
    TEST_ASSERT("LLG_HEX sets b=255", color.b == 255);
    TEST_ASSERT("LLG_HEX sets a=45", color.a == 69);

    /* ------- */
    // We will need a context for these next tests
    ctx = LLG_init("test_color", 800, 600);
    // return if context error
    if (ctx == NULL) {
        printf("  " _YELLOW "  FATAL: LLG_init failed, skipping rest of tests\n" _RESET);
        return 1;
    }

    /* ------- */
    TEST_SECTION("LLG_setColor");

    LLG_setColor(ctx, LLG_RGB(255, 0, 0));
    err = LLG_getError();
    TEST_ASSERT("LLG_setColor valid args sets no error", err == LLG_OK);
    TEST_ASSERT("LLG_setColor updates fgColor", ctx->fgColor.r == 255);
    TEST_ASSERT("LLG_setColor updates drawState.fillColor", ctx->drawState.fillColor.r == 255);
    TEST_ASSERT("LLG_setColor updates drawState.strokeColor", ctx->drawState.strokeColor.r == 255);
    TEST_ASSERT("LLG_setColor enables fill", ctx->drawState.fillEnabled == 1);
    TEST_ASSERT("LLG_setColor enables stroke", ctx->drawState.strokeEnabled == 1);

    LLG_setColor(NULL, LLG_RGB(0, 0, 0));
    err = LLG_getError();
    TEST_ASSERT("LLG_setColor NULL ctx sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    /* ------- */
    TEST_SECTION("LLG_setFill");

    LLG_setFill(ctx, LLG_RGB(0, 255, 0));
    err = LLG_getError();
    TEST_ASSERT("LLG_setFill valid args sets no error", err == LLG_OK);
    TEST_ASSERT("LLG_setFill updates drawState.fillColor", ctx->drawState.fillColor.g == 255);
    TEST_ASSERT("LLG_setFill enables fill", ctx->drawState.fillEnabled == 1);

    LLG_setFill(NULL, LLG_RGB(0, 0, 0));
    err = LLG_getError();
    TEST_ASSERT("LLG_setFill NULL ctx sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    /* ------- */
    TEST_SECTION("LLG_setStroke");

    LLG_setStroke(ctx, LLG_RGB(0, 255, 0));
    err = LLG_getError();
    TEST_ASSERT("LLG_setStroke valid args sets no error", err == LLG_OK);
    TEST_ASSERT("LLG_setStroke updates drawState.strokeColor", ctx->drawState.strokeColor.g == 255);
    TEST_ASSERT("LLG_setStroke enables stroke", ctx->drawState.strokeEnabled == 1);

    LLG_setStroke(NULL, LLG_RGB(0, 0, 0));
    err = LLG_getError();
    TEST_ASSERT("LLG_setStroke NULL ctx sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    /* ------- */
    TEST_SECTION("LLG_noFill");

    LLG_noFill(ctx);
    err = LLG_getError();
    TEST_ASSERT("LLG_noFill valid args sets no error", err == LLG_OK);
    TEST_ASSERT("LLG_noFill disables fill", ctx->drawState.fillEnabled == 0);

    LLG_noFill(NULL);
    err = LLG_getError();
    TEST_ASSERT("LLG_noFill NULL ctx sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    /* ------- */
    TEST_SECTION("LLG_noStroke");

    LLG_noStroke(ctx);
    err = LLG_getError();
    TEST_ASSERT("LLG_noStroke valid args sets no error", err == LLG_OK);
    TEST_ASSERT("LLG_noStroke disables stroke", ctx->drawState.strokeEnabled == 0);

    LLG_noStroke(NULL);
    err = LLG_getError();
    TEST_ASSERT("LLG_noStroke NULL ctx sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    /* ------- */
    TEST_SECTION("LLG_setStrokeWidth");

    LLG_setStrokeWidth(ctx, 9);
    err = LLG_getError();
    TEST_ASSERT("LLG_setStrokeWidth valid args sets no error", err == LLG_OK);
    TEST_ASSERT("LLG_setStrokeWidth sets ctx lineWidth", ctx->lineWidth == 9);

    LLG_setStrokeWidth(NULL, 9);
    err = LLG_getError();
    TEST_ASSERT("LLG_setStrokeWidth NULL ctx sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    LLG_setStrokeWidth(ctx, -1);
    err = LLG_getError();
    TEST_ASSERT("LLG_setStrokeWidth negative width sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    /* ---------- */
    TEST_SECTION("LLG_setBackground");

    LLG_setBackground(ctx, LLG_RGB(0, 40, 0));
    err = LLG_getError();
    TEST_ASSERT("LLG_setBackground valid args sets no error", err == LLG_OK);
    TEST_ASSERT("LLG_setBackground updates ctx bgColor", ctx->bgColor.g == 40);

    LLG_setBackground(NULL, LLG_RGB(0, 0, 0));
    err = LLG_getError();
    TEST_ASSERT("LLG_setBackground NULL ctx sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);
    LLG_clearError();

    LLG_destroy(ctx);

    TEST_SUMMARY();

    return _tests_failed > 0 ? 1 : 0;
}