#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int find_min_rotations(const char *str) {
    if (str == NULL) {
        return -1;
    }

    size_t n = strlen(str);
    if (n == 0) {
        return 0;
    }

    if (n > SIZE_MAX / 2 - 1) {
        return -1;
    }

    size_t alloc_size = 2 * n + 1;
    char *doubled = (char *)malloc(alloc_size);
    if (doubled == NULL) {
        return -1;
    }

    memcpy(doubled, str, n);
    memcpy(doubled + n, str, n);
    doubled[2 * n] = '\0';

    int min_rotations = (int)n;

    for (size_t i = 0; i < n; i++) {
        if (doubled[i] == str[0]) {
            size_t j;
            for (j = 1; j < n; j++) {
                if (doubled[i + j] != str[j]) {
                    break;
                }
            }
            if (j == n) {
                min_rotations = (int)i;
                break;
            }
        }
    }

    free(doubled);
    return min_rotations;
}

int main(void) {
    const char *test1 = "aaaa";
    const char *test2 = "abab";
    const char *test3 = "abcde";
    const char *test4 = "";
    const char *test5 = NULL;
    volatile const char *ptr5 = test5;

    printf("%s: %d\n", test1 ? test1 : "NULL", find_min_rotations(test1));
    printf("%s: %d\n", test2 ? test2 : "NULL", find_min_rotations(test2));
    printf("%s: %d\n", test3 ? test3 : "NULL", find_min_rotations(test3));
    printf("%s: %d\n", test4 ? test4 : "NULL", find_min_rotations(test4));
    printf("%s: %d\n", ptr5 ? ptr5 : "NULL", find_min_rotations(test5));

    return 0;
}