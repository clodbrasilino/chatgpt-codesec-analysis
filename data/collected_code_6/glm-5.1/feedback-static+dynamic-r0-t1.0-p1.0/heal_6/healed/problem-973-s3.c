#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    if (len - shift > 0) {
        errno_t err = memcpy_s(temp, len + 1, str + shift, len - shift);
        if (err != 0) {
            free(temp);
            return NULL;
        }
    }

    if (shift > 0) {
        errno_t err = memcpy_s(temp + len - shift, shift + 1, str, shift);
        if (err != 0) {
            free(temp);
            return NULL;
        }
    }

    temp[len] = '\0';

    errno_t err = memcpy_s(str, len + 1, temp, len);
    if (err != 0) {
        free(temp);
        return NULL;
    }

    str[len] = '\0';

    free(temp);

    return str;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <rotate_amount>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t input_len = strlen(argv[1]);
    char *input = (char *)malloc(input_len + 1);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    errno_t err = memcpy_s(input, input_len + 1, argv[1], input_len + 1);
    if (err != 0) {
        fprintf(stderr, "Memory copy failed\n");
        free(input);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || val < 0) {
        fprintf(stderr, "Rotate amount must be a non-negative integer\n");
        free(input);
        return EXIT_FAILURE;
    }

    size_t n = (size_t)val;

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