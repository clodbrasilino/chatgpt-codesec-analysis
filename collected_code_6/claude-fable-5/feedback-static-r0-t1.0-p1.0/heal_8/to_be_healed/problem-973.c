#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int left_rotate(char *str, size_t str_size, size_t d)
{
    size_t len;
    size_t suffix_len;
    size_t temp_size;
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

    suffix_len = len - d;

    if (len > SIZE_MAX - 1) {
        return -1;
    }

    temp_size = len + 1;
    if (temp_size > str_size) {
        return -1;
    }

    temp = malloc(temp_size);
    if (temp == NULL) {
        return -1;
    }

    if (suffix_len > temp_size - 1 ||
        d > temp_size - 1 - suffix_len ||
        (d + suffix_len) != len) {
        free(temp);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str + d, suffix_len);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp + suffix_len, str, d);
    temp[len] = '\0';

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str, temp, temp_size);
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