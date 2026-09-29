#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_swaps(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    size_t len1 = 0;
    while (str1[len1] != '\0' && len1 < 100005) {
        len1++;
    }

    size_t len2 = 0;
    while (str2[len2] != '\0' && len2 < 100005) {
        len2++;
    }

    if (len1 != len2) {
        return -1;
    }

    int mismatches_01 = 0;
    int mismatches_10 = 0;

    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != '0' && str1[i] != '1') return -1;
        if (str2[i] != '0' && str2[i] != '1') return -1;

        if (str1[i] != str2[i]) {
            if (str1[i] == '0') {
                mismatches_01++;
            } else {
                mismatches_10++;
            }
        }
    }

    if (mismatches_01 != mismatches_10) {
        return -1;
    }

    return mismatches_01;
}

int main(void) {
    char *str1 = (char *)malloc(100005 * sizeof(char));
    char *str2 = (char *)malloc(100005 * sizeof(char));

    if (str1 == NULL || str2 == NULL) {
        free(str1);
        free(str2);
        return 1;
    }

    if (scanf("%100004s %100004s", str1, str2) == 2) {
        int result = min_swaps(str1, str2);

        if (result != -1) {
            printf("%d\n", result);
        } else {
            printf("Not Possible\n");
        }
    }

    free(str1);
    free(str2);
    return 0;
}