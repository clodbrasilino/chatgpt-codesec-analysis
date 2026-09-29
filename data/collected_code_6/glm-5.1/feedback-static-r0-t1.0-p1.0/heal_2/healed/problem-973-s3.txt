#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char *left_rotate(char *str, size_t n) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return str;
    }

    size_t shift = n % len;
    if (shift == 0) {
        return str;
    }

    char *temp = (char *)malloc(len + 1);
    if (temp == NULL) {
        return NULL;
    }

    memcpy(temp, str + shift, len - shift);
    memcpy(temp + len - shift, str, shift);
    temp[len] = '\0';

    memcpy(str, temp, len);
    str[len] = '\0';

    free(temp);

    return str;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <rotate_amount>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = strlen(argv[1]);
    char *input = (char *)malloc(len + 1);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(input, argv[1], len + 1);

    char *endptr;
    unsigned long n_ul = strtoul(argv[2], &endptr, 10);
    if (*endptr != '\0' || n_ul > SIZE_MAX) {
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