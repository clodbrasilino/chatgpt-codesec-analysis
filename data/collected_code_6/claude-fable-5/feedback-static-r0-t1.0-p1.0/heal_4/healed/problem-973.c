#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int left_rotate(char *str, size_t str_size, size_t d)
{
    size_t len;
    size_t suffix_len;
    char *temp;

    if (str == NULL || str_size == 0) {
        return -1;
    }

    len = strnlen(str, str_size);
    if (len >= str_size) {
        return -1;
    }

    if (len == 0) {
        return 0;
    }

    d = d % len;
    if (d == 0) {
        return 0;
    }

    if (d >= len || (len + 1) > str_size) {
        return -1;
    }

    suffix_len = len - d;

    temp = malloc(len + 1);
    if (temp == NULL) {
        return -1;
    }

    if (suffix_len > len || d > (len + 1) - suffix_len) {
        free(temp);
        return -1;
    }

    memcpy(temp, str + d, suffix_len);
    memcpy(temp + suffix_len, str, d);
    temp[len] = '\0';

    if ((len + 1) > str_size) {
        free(temp);
        return -1;
    }

    memcpy(str, temp, len + 1);
    free(temp);

    return 0;
}

int main(void)
{
    char str[] = "HelloWorld";
    size_t d = 3;

    printf("Original string: %s\n", str);

    if (left_rotate(str, sizeof(str), d) != 0) {
        fprintf(stderr, "Rotation failed\n");
        return EXIT_FAILURE;
    }

    printf("Rotated string:  %s\n", str);

    return EXIT_SUCCESS;
}