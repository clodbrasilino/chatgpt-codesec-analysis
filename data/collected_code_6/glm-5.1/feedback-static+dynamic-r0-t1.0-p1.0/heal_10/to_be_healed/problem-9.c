#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got 0
  *  test case 1 failed: expected 2, got 0
  *  test case 2 failed: expected 3, got 0
  */

int find_min_rotations(const char *str) {
    if (str == NULL) {
        return -1;
    }

    size_t n = 0;
    while (str[n] != '\0') {
        if (n == SIZE_MAX) {
            return -1;
        }
        n++;
    }

    if (n == 0) {
        return 0;
    }

    if (n > (SIZE_MAX - 1) / 2) {
        return -1;
    }

    size_t total_size = 2 * n + 1;
    char *doubled = (char *)malloc(total_size);
    if (doubled == NULL) {
        return -1;
    }

    if (total_size < n) {
        free(doubled);
        return -1;
    }

    size_t i;
    for (i = 0; i < n; i++) {
        doubled[i] = str[i];
    }

    if (total_size < 2 * n) {
        free(doubled);
        return -1;
    }

    for (i = 0; i < n; i++) {
        doubled[n + i] = str[i];
    }

    doubled[2 * n] = '\0';

    int min_rotations = (int)n;

    for (i = 0; i < n; i++) {
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
    printf("1: %d\n", find_min_rotations("aaaa"));
    printf("2: %d\n", find_min_rotations("aaab"));
    printf("3: %d\n", find_min_rotations("abab"));
    return 0;
}