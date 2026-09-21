#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_odd_rotations(const char *s) {
    size_t n = strnlen(s, 256);
    if (n == 0 || n >= 256) {
        return -1;
    }

    int *doubled = (int *)malloc(2 * n * sizeof(int));
    if (doubled == NULL) {
        return -1;
    }

    for (size_t i = 0; i < 2 * n; i++) {
        char c = s[i % n];
        if (c != '0' && c != '1') {
            free(doubled);
            return -1;
        }
        doubled[i] = c - '0';
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
    char input[257] = {0};

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    if (input[0] == '\0') {
        return 1;
    }

    size_t len = 0;
    for (size_t i = 0; i < sizeof(input); i++) {
        if (input[i] == '\0') {
            len = i;
            break;
        }
    }

    if (len >= sizeof(input)) {
        return 1;
    }

    if (len > 0 && input[len - 1] == '\n') {
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