#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 0
  *  test case 0 failed: expected 1, got 0
  *  test case 2 failed: expected 3, got 0
  */

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
                i += match_count;
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

    int res1 = find_min_rotations(str1);
    int res2 = find_min_rotations(str2);
    int res3 = find_min_rotations(str3);

    printf("Minimum rotations for '%s': %d\n", str1, res1);
    printf("Minimum rotations for '%s': %d\n", str2, res2);
    printf("Minimum rotations for '%s': %d\n", str3, res3);

    return 0;
}