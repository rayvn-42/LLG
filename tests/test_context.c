#include <stdio.h>
#include "LLG/llg.h"
#include "test_utils.h"

int main(void) {
    printf(_CYAN "\n[LLG] test_context.c" _RESET "\n");

    LLGContext *ctx = NULL;
    LLGError err = LLG_OK;

    /* ------ */
    TEST_SECTION("LLG_init - valid args");

    ctx = LLG_init("test_context", 800, 600);
    TEST_ASSERT("LLG_init returns non-NULL on valid args", ctx != NULL);
    TEST_ASSERT("no error set after successful init", LLG_getError() == LLG_OK);

    LLG_destroy(ctx);
    ctx = NULL;

    /* ------ */
    TEST_SECTION("LLG_init - bad args");

    ctx = LLG_init(NULL, 800, 600);
    err = LLG_getError();
    TEST_ASSERT("LLG_init returns NULL on NULL title", ctx == NULL);
    TEST_ASSERT("error is LLG_ERR_BADARG on NULL title", err == LLG_ERR_BADARG);

    ctx = LLG_init("test", 0, 600);
    err = LLG_getError();
    TEST_ASSERT("LLG_init returns NULL on zero width", ctx == NULL);
    TEST_ASSERT("error is LLG_ERR_BADARG on zero width", err == LLG_ERR_BADARG);

    ctx = LLG_init("test", 800, -1);
    err = LLG_getError();
    TEST_ASSERT("LLG_init returns NULL on negative height", ctx == NULL);
    TEST_ASSERT("error is LLG_ERR_BADARG on negative height", err == LLG_ERR_BADARG);

    /* ---- */
    TEST_SECTION("LLG_isRunning");

    ctx = LLG_init("test_context", 800, 600);
    TEST_ASSERT("LLG_isRunning returns 1 on fresh context", LLG_isRunning(ctx) == 1);
    TEST_ASSERT("LLG_isRunning returns 0 on NULL", LLG_isRunning(NULL) == 0);

    /* ------ */
    TEST_SECTION("LLG_quit");
    
    LLG_quit(ctx);
    TEST_ASSERT("LLG_isRunning returns 0 after LLG_quit", LLG_isRunning(ctx) == 0);

    LLG_quit(NULL);
    err = LLG_getError();
    TEST_ASSERT("LLG_quit on NULL sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);

    /* -------- */
    TEST_SECTION("LLG_destroy");

    LLG_destroy(ctx);
    ctx = NULL;
    TEST_ASSERT("LLG_destroy on valid ctx completes cleanly", 1);

    LLG_destroy(NULL);
    err = LLG_getError();
    TEST_ASSERT("LLG_destroy on NULL sets LLG_ERR_BADARG", err == LLG_ERR_BADARG);

    /* ------ */
    TEST_SECTION("LLG_errorStr");

    TEST_ASSERT("LLG_ERR_BADARG has non-NULL string", LLG_errorStr(LLG_ERR_BADARG) != NULL);
    TEST_ASSERT("LLG_OK has non-NULL string", LLG_errorStr(LLG_OK) != NULL);
    TEST_ASSERT("LLG_ERR_DISPLAY has non-NULL string", LLG_errorStr(LLG_ERR_DISPLAY) != NULL);
    TEST_ASSERT("unknown error code has non-NULL string", LLG_errorStr((LLGError)1) != NULL);

    TEST_SUMMARY();
    return _tests_failed > 0 ? 1 : 0;
}
