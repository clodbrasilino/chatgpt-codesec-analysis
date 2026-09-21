#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int is_undulating(const char *s) {
    if (s == NULL) {
        return 0;
    }

    size_t len = 0;
    while (s[len] != '\0') {
        if (!isdigit((unsigned char)s[len])) {
            return 0;
        }
        len++;
    }

    if (len < 3) {
        return 0;
    }

    if (s[0] == s[1]) {
        return 0;
    }

    for (size_t i = 2; i < len; i++) {
        if (s[i] != s[i - 2]) {
            return 0;
        }
    }

    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (is_undulating(argv[1])) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return EXIT_SUCCESS;
}