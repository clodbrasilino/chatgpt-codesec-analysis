#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

char *left_rotate(char *str, size_t n) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    if (len == 0) {
        return str;
    }

    size_t shift = n % len;
    if (shift == 0) {
        return str;
    }

    char temp = str[0];
    size_t current = 0;
    for (size_t i = 0; i < len; i++) {
        size_t next = (current + shift) % len;
        char next_temp = str[next];
        str[next] = temp;
        temp = next_temp;
        current = next;
    }

    return str;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <rotate_amount>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = 0;
    while (argv[1][len] != '\0') {
        len++;
    }

    char *input = (char *)malloc(len + 1);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < len; i++) {
        input[i] = argv[1][i];
    }
    input[len] = '\0';

    char *endptr;
    errno = 0;
    unsigned long n_ul = strtoul(argv[2], &endptr, 10);
    if (*endptr != '\0' || errno == ERANGE || n_ul > SIZE_MAX) {
        fprintf(stderr, "Rotate amount must be a valid non-negative integer\n");
        free(input);
        return EXIT_FAILURE;
    }
    size_t n = (size_t)n_ul;

    char *result = left_rotate(input, n);
    if (result == NULL) {
        fprintf(stderr, "Rotation failed\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("%s\n", result);

    free(input);

    return EXIT_SUCCESS;
}