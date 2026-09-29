#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_odd_rotations(const char *s) {
    size_t n = strnlen(s, 256);
    if (n == 0 || n >= 256) {
        return -1;
    }

    for (size_t i = 0; i < n; i++) {
        if (s[i] != '0' && s[i] != '1') {
            return -1;
        }
    }

    unsigned char *doubled = (unsigned char *)malloc(2 * n * sizeof(unsigned char));
    if (doubled == NULL) {
        return -1;
    }

    for (size_t i = 0; i < 2 * n; i++) {
        doubled[i] = (unsigned char)(s[i % n] - '0');
    }

    int count = 0;
    for (size_t i = 0; i < n; i++) {
        int value = 0;
        for (size_t j = 0; j < n; j++) {
            value = (value << 1) | doubled[i + j];
        }
        if (value % 2 == 1) {
            count++;
        }
    }

    free(doubled);
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[258] = {0};

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    size_t len = strnlen(input, sizeof(input));
    if (len == 0 || input[0] == '\n') {
        return 1;
    }

    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len == 0 || len >= 256) {
        return 1;
    }

    int result = count_odd_rotations(input);

    if (result < 0) {
        return 1;
    }

    printf("%d\n", result);
    return 0;
}