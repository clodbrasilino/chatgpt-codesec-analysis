#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min_swaps(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (len1 != len2) {
        return -1;
    }

    int count_0_1 = 0;
    int count_1_0 = 0;

    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != '0' && str1[i] != '1') {
            return -1;
        }
        if (str2[i] != '0' && str2[i] != '1') {
            return -1;
        }

        if (str1[i] == '0' && str2[i] == '1') {
            count_0_1++;
        } else if (str1[i] == '1' && str2[i] == '0') {
            count_1_0++;
        }
    }

    if (count_0_1 == count_1_0) {
        return count_0_1;
    }

    return -1;
}

int main(void) {
    char *str1 = malloc(2000005 * sizeof(char));
    char *str2 = malloc(2000005 * sizeof(char));

    if (str1 == NULL || str2 == NULL) {
        free(str1);
        free(str2);
        return 1;
    }

    if (scanf("%2000000s %2000000s", str1, str2) == 2) {
        int result = min_swaps(str1, str2);

        if (result == -1) {
            printf("Not Possible\n");
        } else {
            printf("%d\n", result);
        }
    }

    free(str1);
    free(str2);

    return 0;
}