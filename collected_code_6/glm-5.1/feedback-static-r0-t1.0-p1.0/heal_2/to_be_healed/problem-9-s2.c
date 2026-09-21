#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_min_rotations(const char *str) {
    if (str == NULL) {
        return -1;
    }

    size_t len = strnlen(str, 1048576);
    if (len == 0) {
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
    memcpy_s(doubled, 2 * len + 1, str, len);
    memcpy_s(doubled + len, len + 1, str, len);
    doubled[2 * len] = '\0';

    for (size_t i = 1; i < len; i++) {
        if (memcmp(doubled + i, str, len) == 0) {
            free(doubled);
            return (int)i;
        }
    }

    free(doubled);
    return (int)len;
}

int main(void) {
    const char *str1 = "aaaa";
    int res1 = find_min_rotations(str1);
    printf("%d\n", res1);

    const char *str2 = "abab";
    int res2 = find_min_rotations(str2);
    printf("%d\n", res2);

    const char *str3 = "abcd";
    int res3 = find_min_rotations(str3);
    printf("%d\n", res3);

    const char *str4 = "";
    int res4 = find_min_rotations(str4);
    printf("%d\n", res4);

    int res5 = find_min_rotations(NULL);
    printf("%d\n", res5);

    return 0;
}