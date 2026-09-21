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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(str);

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

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(doubled, str, n);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
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
    printf("1: %d\n", find_min_rotations("aaaa"));
    printf("2: %d\n", find_min_rotations("aaab"));
    printf("3: %d\n", find_min_rotations("abab"));
    return 0;
}