#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int are_rotations(const char *s1, const char *s2) {
    size_t len1, len2;
    char *concat;
    int result;
    size_t concat_size;
    errno_t err;

    if (s1 == NULL || s2 == NULL) {
        return 0;
    }

    len1 = strnlen_s(s1, SIZE_MAX);
    len2 = strnlen_s(s2, SIZE_MAX);

    if (len1 != len2) {
        return 0;
    }

    if (len1 == 0) {
        return 1;
    }

    if (len1 > SIZE_MAX / 2) {
        return 0;
    }

    concat_size = len1 * 2 + 1;
    concat = (char *)malloc(concat_size);
    if (concat == NULL) {
        return 0;
    }

    err = memcpy_s(concat, concat_size, s1, len1);
    if (err != 0) {
        free(concat);
        return 0;
    }

    err = memcpy_s(concat + len1, len1 + 1, s1, len1);
    if (err != 0) {
        free(concat);
        return 0;
    }

    concat[len1 * 2] = '\0';

    result = (strstr(concat, s2) != NULL) ? 1 : 0;

    free(concat);

    return result;
}

int main(int argc, char *argv[]) {
    const char *str1 = "abcd";
    const char *str2 = "cdab";
    const char *str3 = "acbd";

    if (are_rotations(str1, str2)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    if (are_rotations(str1, str3)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}