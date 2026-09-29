#include <stdio.h>
#include <stdlib.h>

int min_swaps(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    int count_0_1 = 0;
    int count_1_0 = 0;
    size_t i = 0;

    while (str1[i] != '\0' && str2[i] != '\0') {
        if ((str1[i] != '0' && str1[i] != '1') || 
            (str2[i] != '0' && str2[i] != '1')) {
            return -1;
        }

        if (str1[i] == '0' && str2[i] == '1') {
            count_0_1++;
        } else if (str1[i] == '1' && str2[i] == '0') {
            count_1_0++;
        }
        i++;
    }

    if (str1[i] != '\0' || str2[i] != '\0') {
        return -1;
    }

    if (count_0_1 == count_1_0) {
        return count_0_1;
    }

    return -1;
}

int main(void) {
    const char *str1 = "1100";
    const char *str2 = "1010";

    int result = min_swaps(str1, str2);

    if (result == -1) {
        printf("Conversion not possible or invalid input.\n");
    } else {
        printf("Minimum number of swaps: %d\n", result);
    }

    return 0;
}