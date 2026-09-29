#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

char *left_rotate(char *str, size_t n) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
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

    size_t part1_len = len - shift;
    if (part1_len > 0) {
        memcpy(temp, str + shift, part1_len);
    }

    size_t part2_len = shift;
    if (part2_len > 0) {
        memcpy(temp + part1_len, str, part2_len);
    }
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

    size_t len = strnlen(argv[1], SIZE_MAX);
    char *input = (char *)malloc(len + 1);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(input, argv[1], len + 1);

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