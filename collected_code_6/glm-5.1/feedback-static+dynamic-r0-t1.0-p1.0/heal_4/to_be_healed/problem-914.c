#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int is_alternating(const char *str, size_t max_len) {
    size_t len;

    if (str == NULL) {
        return 0;
    }

    len = strnlen(str, max_len);
    if (len < 2) {
        return 0;
    }

    char a = str[0];
    char b = str[1];

    if (a == b) {
        return 0;
    }

    for (size_t i = 2; i < len; i++) {
        if (i % 2 == 0) {
            if (str[i] != a) {
                return 0;
            }
        } else {
            if (str[i] != b) {
                return 0;
            }
        }
    }

    return 1;
}

/* Possible weaknesses found:
 *  variable length array must be bound in function definition
 *  syntax error [syntaxError]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  '[*]' not allowed in other than function prototype scope
 */
int main(int argc, char *argv[const restrict *]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t max_len = strlen(argv[1]);
    if (max_len > SIZE_MAX / 2) {
        return EXIT_FAILURE;
    }

    if (is_alternating(argv[1], max_len)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return EXIT_SUCCESS;
}