#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_alternating(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len < 2) {
        return false;
    }

    char a = str[0];
    char b = str[1];

    if (a == b) {
        return false;
    }

    for (size_t i = 0; i < len; i++) {
        if (i % 2 == 0) {
            if (str[i] != a) {
                return false;
            }
        } else {
            if (str[i] != b) {
                return false;
            }
        }
    }

    return true;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[256];
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%255s", str) == 1) {
        if (is_alternating(str)) {
            printf("true\n");
        } else {
            printf("false\n");
        }
    }
    return 0;
}