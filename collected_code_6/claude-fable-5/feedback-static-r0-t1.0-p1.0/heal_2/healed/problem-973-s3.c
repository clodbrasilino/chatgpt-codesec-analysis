#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096

char *left_rotate(const char *str, size_t d)
{
    size_t len;
    size_t i;
    char *result;

    if (str == NULL) {
        return NULL;
    }

    len = strnlen(str, MAX_INPUT_LEN);
    if (len == MAX_INPUT_LEN) {
        return NULL;
    }

    result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    if (len == 0) {
        result[0] = '\0';
        return result;
    }

    d = d % len;

    if (d > len || (len - d) > len) {
        free(result);
        return NULL;
    }

    for (i = 0; i < len - d; i++) {
        result[i] = str[d + i];
    }

    for (i = 0; i < d; i++) {
        result[(len - d) + i] = str[i];
    }

    result[len] = '\0';

    return result;
}

int main(void)
{
    const char *original = "HelloWorld";
    size_t shift = 3;
    char *rotated;

    rotated = left_rotate(original, shift);
    if (rotated == NULL) {
        fprintf(stderr, "Error: rotation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: %s\n", original) < 0) {
        free(rotated);
        return EXIT_FAILURE;
    }

    if (printf("Rotated:  %s\n", rotated) < 0) {
        free(rotated);
        return EXIT_FAILURE;
    }

    free(rotated);
    return EXIT_SUCCESS;
}