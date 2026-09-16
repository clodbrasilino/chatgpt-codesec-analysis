#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 1
  *  test case 2 failed: expected 3, got 1
  */

int find_min_rotations(const char *str) {
    if (str == NULL) {
        return -1;
    }

    size_t n = strlen(str);
    if (n == 0) {
        return 0;
    }

    char *doubled = (char *)malloc(2 * n + 1);
    if (doubled == NULL) {
        return -1;
    }

    memcpy(doubled, str, n);
    memcpy(doubled + n, str, n);
    doubled[2 * n] = '\0';

    int min_rotations = (int)n;

    for (size_t i = 1; i < n; i++) {
        if (doubled[i] == str[0]) {
            int match = 1;
            for (size_t j = 1; j < n; j++) {
                if (doubled[i + j] != str[j]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                min_rotations = (int)i;
                break;
            }
        }
    }

    free(doubled);
    return min_rotations != n ? min_rotations : 1;
}

int main(void) {
    const char *test0 = "a";
    const char *test1 = "ab";
    const char *test2 = "abc";
    const char *test3 = "aaaa";
    const char *test4 = "abab";
    const char *test5 = "abcde";
    const char *test6 = "";
    
    printf("%d\n", find_min_rotations(test0));
    printf("%d\n", find_min_rotations(test1));
    printf("%d\n", find_min_rotations(test2));
    printf("%d\n", find_min_rotations(test3));
    printf("%d\n", find_min_rotations(test4));
    printf("%d\n", find_min_rotations(test5));
    printf("%d\n", find_min_rotations(test6));
    printf("%d\n", find_min_rotations(NULL));

    fflush(stdout);

    return 0;
}