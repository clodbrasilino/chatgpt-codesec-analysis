#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

int left_rotate(char *str, size_t str_size, size_t d)
{
    size_t len;
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

    temp = malloc(len + 1);
    if (temp == NULL) {
        return -1;
    }

    memcpy(temp, str + d, len - d);
    memcpy(temp + (len - d), str, d);
    temp[len] = '\0';

    memcpy(str, temp, len + 1);
    free(temp);

    return 0;
}

int main(void)
{
    char str[] = "GeeksforGeeks";
    size_t d = 2;

    if (left_rotate(str, sizeof(str), d) != 0) {
        fprintf(stderr, "Rotation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", str) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}