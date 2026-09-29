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

    int mismatches_0_to_1 = 0;
    int mismatches_1_to_0 = 0;

    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != '0' && str1[i] != '1') return -1;
        if (str2[i] != '0' && str2[i] != '1') return -1;

        if (str1[i] != str2[i]) {
            if (str1[i] == '0') {
                mismatches_0_to_1++;
            } else {
                mismatches_1_to_0++;
            }
        }
    }

    if (mismatches_0_to_1 != mismatches_1_to_0) {
        return -1;
    }

    return mismatches_0_to_1;
}

int main(void) {
    char str1[100005];
    char str2[100005];

    if (scanf("%100004s %100004s", str1, str2) == 2) {
        int result = min_swaps(str1, str2);

        if (result != -1) {
            printf("%d\n", result);
        } else {
            printf("Not Possible\n");
        }
    } else {
        printf("Not Possible\n");
    }

    return 0;
}