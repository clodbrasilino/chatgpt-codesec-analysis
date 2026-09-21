#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

int left_rotate(char *str, size_t buf_size, size_t d)
{
    size_t len;
    size_t temp_size;
    size_t first_part;
    size_t second_part;
    char *temp;

    if (str == NULL || buf_size == 0 || buf_size > MAX_STR_LEN) {
        return -1;
    }

    len = strnlen(str, buf_size);
    if (len == buf_size) {
        return -1;
    }

    if (len == 0) {
        return 0;
    }

    d = d % len;
    if (d == 0) {
        return 0;
    }

    if (len + 1 > buf_size) {
        return -1;
    }

    temp_size = len + 1;
    temp = malloc(temp_size);
    if (temp == NULL) {
        return -1;
    }

    first_part = len - d;
    second_part = d;

    if (first_part > temp_size - 1) {
        free(temp);
        return -1;
    }

    if (second_part > (temp_size - 1) - first_part) {
        free(temp);
        return -1;
    }

    memcpy(temp, str + d, first_part);
    memcpy(temp + first_part, str, second_part);
    temp[len] = '\0';

    if (temp_size > buf_size) {
        free(temp);
        return -1;
    }

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