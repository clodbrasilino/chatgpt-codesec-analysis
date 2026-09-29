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
    char *input = NULL;
    size_t bufsize = 0;

    if (getline(&input, &bufsize, stdin) == -1) {
        free(input);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    if (len == 0) {
        free(input);
        return 1;
    }

    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len == 0 || len >= 256) {
        free(input);
        return 1;
    }

    int result = count_odd_rotations(input);
    free(input);

    if (result < 0) {
        return 1;
    }

    printf("%d\n", result);
    return 0;
}