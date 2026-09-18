#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *rotate_string_left(char *str, size_t n) {
    size_t str_length = strlen(str);
    char *result = (char *)malloc((str_length + 1) * sizeof(char));

    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < str_length; ++i) {
        size_t new_idx = (i + n) % str_length;
        result[i] = str[new_idx];
    }

    result[str_length] = '\0';

    return result;
}

int main(void) {
    char str[] = "Hello, world!";
    size_t n = 2;

    printf("Original string: %s\n", str);

    char *rotated = rotate_string_left(str, n);

    if (rotated == NULL) {
        return 1;
    }

    printf("Rotated string: %s\n", rotated);

    free(rotated);

    return 0;
}