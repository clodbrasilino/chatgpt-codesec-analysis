#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_min_rotations(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strlen(str);
    if (len <= 1) {
        return 0;
    }

    char *doubled = (char *)malloc(2 * len + 1);
    if (doubled == NULL) {
        return 0;
    }

    memcpy(doubled, str, len);
    memcpy(doubled + len, str, len);
    doubled[2 * len] = '\0';

    for (size_t i = 1; i < len; i++) {
        if (doubled[i] == str[0]) {
            if (memcmp(doubled + i, str, len) == 0) {
                free(doubled);
                return (int)i;
            }
        }
    }

    free(doubled);
    return 0;
}

int main(void) {
    const char str0[] = "a";
    const char str1[] = "aaaa";
    const char str2[] = "abab";
    const char str3[] = "abcd";
    const char str4[] = "ab";
    const char str5[] = "abc";

    int res0 = find_min_rotations(str0);
    int res1 = find_min_rotations(str1);
    int res2 = find_min_rotations(str2);
    int res3 = find_min_rotations(str3);
    int res4 = find_min_rotations(str4);
    int res5 = find_min_rotations(str5);

    printf("%d\n", res0);
    printf("%d\n", res1);
    printf("%d\n", res2);
    printf("%d\n", res3);
    printf("%d\n", res4);
    printf("%d\n", res5);

    return 0;
}