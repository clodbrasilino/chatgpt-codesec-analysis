#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096

bool are_rotations(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t buf_size;
    char *temp;
    bool result;

    if (s1 == NULL || s2 == NULL) {
        return false;
    }

    len1 = strnlen(s1, MAX_INPUT_LEN);
    len2 = strnlen(s2, MAX_INPUT_LEN);

    if (len1 >= MAX_INPUT_LEN || len2 >= MAX_INPUT_LEN) {
        return false;
    }

    if (len1 != len2) {
        return false;
    }

    if (len1 == 0) {
        return true;
    }

    if (len1 > (SIZE_MAX - 1) / 2) {
        return false;
    }

    buf_size = (2 * len1) + 1;

    temp = malloc(buf_size);
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    if (len1 > buf_size - 1) {
        free(temp);
        return false;
    }
    memcpy(temp, s1, len1);

    if (len1 > buf_size - 1 - len1) {
        free(temp);
        return false;
    }
    memcpy(temp + len1, s1, len1);

    temp[buf_size - 1] = '\0';

    result = (strstr(temp, s2) != NULL);

    free(temp);
    return result;
}

int main(void)
{
    const char *str1 = "ABCD";
    const char *str2 = "CDAB";
    const char *str3 = "ACBD";

    if (are_rotations(str1, str2)) {
        printf("\"%s\" and \"%s\" are rotations of each other\n", str1, str2);
    } else {
        printf("\"%s\" and \"%s\" are not rotations of each other\n", str1, str2);
    }

    if (are_rotations(str1, str3)) {
        printf("\"%s\" and \"%s\" are rotations of each other\n", str1, str3);
    } else {
        printf("\"%s\" and \"%s\" are not rotations of each other\n", str1, str3);
    }

    return EXIT_SUCCESS;
}