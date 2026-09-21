#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min_swaps(const char *str1, const char *str2, size_t max_len) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    size_t len1 = strnlen(str1, max_len);
    size_t len2 = strnlen(str2, max_len);

    if (len1 != len2 || len1 == 0) {
        return -1;
    }

    int count_01 = 0;
    int count_10 = 0;

    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != '0' && str1[i] != '1') return -1;
        if (str2[i] != '0' && str2[i] != '1') return -1;

        if (str1[i] == '0' && str2[i] == '1') {
            count_01++;
        } else if (str1[i] == '1' && str2[i] == '0') {
            count_10++;
        }
    }

    if (count_01 != count_10) {
        return -1;
    }

    return count_01;
}

int main(void) {
    size_t buffer_size = 4096;
    char *str1 = (char *)malloc(buffer_size);
    char *str2 = (char *)malloc(buffer_size);

    if (str1 == NULL || str2 == NULL) {
        free(str1);
        free(str2);
        printf("Not Possible\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%4095s %4095s", str1, str2) == 2) {
        int result = min_swaps(str1, str2, buffer_size);

        if (result != -1) {
            printf("%d\n", result);
        } else {
            printf("Not Possible\n");
        }
    } else {
        printf("Not Possible\n");
    }

    free(str1);
    free(str2);

    return 0;
}