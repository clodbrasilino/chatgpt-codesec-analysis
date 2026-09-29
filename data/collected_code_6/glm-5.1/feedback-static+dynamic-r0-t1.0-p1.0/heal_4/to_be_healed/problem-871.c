#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int are_rotations(const char *s1, const char *s2) {
    size_t len1, len2;
    char *concat;
    int result;

    if (s1 == NULL || s2 == NULL) {
        return 0;
    }

    len1 = strnlen(s1, SIZE_MAX);
    len2 = strnlen(s2, SIZE_MAX);

    if (len1 != len2) {
        return 0;
    }

    if (len1 == 0) {
        return 1;
    }

    concat = (char *)malloc(len1 * 2 + 1);
    if (concat == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
     *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  did you mean 'memcpy'?
     */
    memcpy_s(concat, len1 * 2 + 1, s1, len1);
    memcpy_s(concat + len1, len1 + 1, s1, len1);
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