#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_min_rotations(const char *str) {
    if (str == NULL) {
        return -1;
    }

    size_t len = strnlen(str, 1024 * 1024);
    if (len == 0 || len == 1024 * 1024) {
        return 0;
    }

    char *doubled = (char *)malloc(2 * len + 1);
    if (doubled == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
     *  did you mean 'memcpy'?
     */
    errno_t err1 = memcpy_s(doubled, 2 * len + 1, str, len);
    if (err1 != 0) {
        free(doubled);
        return -1;
    }

    errno_t err2 = memcpy_s(doubled + len, len + 1, str, len);
    if (err2 != 0) {
        free(doubled);
        return -1;
    }

    doubled[2 * len] = '\0';

    int min_rotations = -1;

    for (size_t i = 0; i < len; i++) {
        if (memcmp(doubled + i, str, len) == 0) {
            min_rotations = (int)i;
            break;
        }
    }

    free(doubled);
    doubled = NULL;

    return min_rotations;
}

int main(void) {
    char str1[] = "aaaa";
    char str2[] = "abab";
    char str3[] = "abcd";

    int res1 = find_min_rotations(str1);
    int res2 = find_min_rotations(str2);
    int res3 = find_min_rotations(str3);

    printf("Minimum rotations for '%s': %d\n", str1, res1);
    printf("Minimum rotations for '%s': %d\n", str2, res2);
    printf("Minimum rotations for '%s': %d\n", str3, res3);

    return 0;
}