#include <stdio.h>
#include <stdlib.h>

int min_swaps(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    int mismatches_01 = 0;
    int mismatches_10 = 0;
    size_t i = 0;

    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != '0' && str1[i] != '1') {
            return -1;
        }
        if (str2[i] != '0' && str2[i] != '1') {
            return -1;
        }

        if (str1[i] != str2[i]) {
            if (str1[i] == '0') {
                mismatches_01++;
            } else {
                mismatches_10++;
            }
        }
        i++;
    }

    if (str1[i] != '\0' || str2[i] != '\0') {
        return -1;
    }

    if (mismatches_01 != mismatches_10) {
        return -1;
    }

    return mismatches_01;
}

int main(void) {
    const char *str1 = "1100";
    const char *str2 = "0011";

    int result = min_swaps(str1, str2);

    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Invalid input or conversion not possible\n");
    }

    return 0;
}