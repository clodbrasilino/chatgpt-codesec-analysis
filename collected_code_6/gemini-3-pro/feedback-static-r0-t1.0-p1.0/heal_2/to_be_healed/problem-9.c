#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_minimum_rotations(const char *str) {
    if (str == NULL) {
        return -1;
    }

    size_t n = 0;
    while (str[n] != '\0') {
        n++;
    }

    if (n == 0) {
        return 0;
    }

    char *temp = (char *)malloc((2 * n + 1) * sizeof(char));
    if (temp == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, n);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp + n, str, n);
    temp[2 * n] = '\0';

    int rotations = (int)n;

    for (size_t i = 1; i <= n; i++) {
        if (strncmp(str, temp + i, n) == 0) {
            rotations = (int)i;
            break;
        }
    }

    free(temp);
    return rotations;
}

int main(void) {
    const char *test_str1 = "geeks";
    const char *test_str2 = "aaaa";
    const char *test_str3 = "abc";

    int res1 = find_minimum_rotations(test_str1);
    if (res1 != -1) {
        printf("%d\n", res1);
    }

    int res2 = find_minimum_rotations(test_str2);
    if (res2 != -1) {
        printf("%d\n", res2);
    }

    int res3 = find_minimum_rotations(test_str3);
    if (res3 != -1) {
        printf("%d\n", res3);
    }

    return 0;
}