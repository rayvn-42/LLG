#pragma once

#include <stdio.h>
#include <string.h>

static int _tests_run = 0;
static int _tests_passed = 0;
static int _tests_failed = 0;

#define _GREEN "\033[0;32m"
#define _RED "\033[0;31m"
#define _YELLOW "\033[0;33m"
#define _CYAN "\033[0;36m"
#define _RESET "\033[0m"

#define TEST_SECTION(name) \
    printf("\n" _CYAN "=== %s ===" _RESET "\n", name)

#define TEST_ASSERT(desc, condition)                            \
    do {                                                        \
        _tests_run++;                                           \
        printf(" [ ] %s ...", desc);                            \
        if (condition) {                                        \
            _tests_passed++;                                    \
            printf(_GREEN "PASS" _RESET "\n");                  \
        } else {                                                \
            _tests_failed++;                                    \
            printf(_RED "FAIL" _RESET " (line %d)\n", __LINE__);\
        }                                                       \
    } while (0)

#define TEST_SUMMARY()                                                      \
    do {                                                                    \
        printf("\n" _CYAN "===============================" _RESET "\n");   \
        printf("  Total : %d\n", _tests_run);                               \
        printf("  " _GREEN "Passed : %d" _RESET "\n", _tests_passed);       \
        printf("  " _RED "Failed : %d" _RESET "\n", _tests_failed);         \
        printf(_CYAN "===============================" _RESET "\n\n");      \
    } while (0)
