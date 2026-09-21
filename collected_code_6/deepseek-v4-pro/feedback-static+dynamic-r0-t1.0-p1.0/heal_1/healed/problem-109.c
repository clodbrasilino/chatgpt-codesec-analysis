#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int count_odd_rotations(const char *s) {
    if (s == NULL) {
        return -1;
    }

    size_t n = strnlen(s, 256);
    if (n == 0 || n == 256) {
        return -1;
    }

    for (size_t i = 0; i < n; i++) {
        if (s[i] != '0' && s[i] != '1') {
            return -1;
        }
    }

    int *doubled = (int *)malloc(2 * n * sizeof(int));
    if (doubled == NULL) {
        return -1;
    }

    for (size_t i = 0; i < 2 * n; i++) {
        doubled[i] = s[i % n] - '0';
    }

    int count = 0;
    for (size_t i = 0; i < n; i++) {
        long long value = 0;
        int overflow = 0;
        for (size_t j = 0; j < n; j++) {
            if (value > (LLONG_MAX >> 1)) {
                overflow = 1;
                break;
            }
            value = (value << 1) | (doubled[i + j] & 1);
        }
        if (!overflow && (value & 1)) {
            count++;
        }
    }

    free(doubled);
    return count;
}

int main(void) {
    char input[257] = {0};
    if (scanf("%256s", input) != 1) {
        return 1;
    }

    int result = count_odd_rotations(input);
    if (result < 0) {
        return 1;
    }

    printf("%d\n", result);
    return 0;
}