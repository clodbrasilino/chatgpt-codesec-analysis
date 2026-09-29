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

    if (suffix_len > len || d > len - suffix_len) {
        return -1;
    }

    temp = malloc(len + 1);
    if (temp == NULL) {
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