#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int count_flips(const char *str, size_t maxlen) {
    size_t len = strnlen(str, maxlen);
    if (len == 0) {
        return 0;
    }

    int flip1 = 0;
    int flip2 = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1') {
            exit(EXIT_FAILURE);
        }

        if (i % 2 == 0) {
            if (str[i] != '0') flip1++;
            if (str[i] != '1') flip2++;
        } else {
            if (str[i] != '1') flip1++;
            if (str[i] != '0') flip2++;
        }
    }

    return min(flip1, flip2);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = count_flips(argv[1], 4096);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}