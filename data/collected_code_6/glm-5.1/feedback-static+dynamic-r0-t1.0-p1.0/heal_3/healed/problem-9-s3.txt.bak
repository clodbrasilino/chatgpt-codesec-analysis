#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_min_rotations(const char *str) {
    if (str == NULL) {
        return -1;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    char *doubled = (char *)malloc(2 * len + 1);
    if (doubled == NULL) {
        return -1;
    }

    memcpy(doubled, str, len);
    memcpy(doubled + len, str, len);
    doubled[2 * len] = '\0';

    int min_rotations = -1;

    for (size_t i = 0; i < len; i++) {
        size_t match_count = 0;
        for (size_t j = 0; j < len; j++) {
            if (doubled[i + j] == str[j]) {
                match_count++;
            } else {
                break;
            }
        }
        if (match_count == len) {
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
    
    char str0[] = "a";
    char str4[] = "ab";
    char str5[] = "abc";

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