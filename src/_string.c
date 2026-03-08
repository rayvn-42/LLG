#include "internal.h"

const char *LLG__strCat(char *dest, size_t dest_size, char *m1, const char *m2) {
    snprintf(dest, dest_size, "%s%s", m1, m2);
    return dest;
}