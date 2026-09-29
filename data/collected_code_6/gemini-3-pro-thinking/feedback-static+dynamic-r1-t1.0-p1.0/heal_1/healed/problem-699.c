#include <stdio.h>
#include <stddef.h>

int min_swaps(const char *str1, const char *str2);

int min_swaps(const char *str1, const char *str2) {
    size_t i = 0;
    int mismatch_1_to_0 = 0;
    int mismatch_0_to_1 = 0;

    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    while (str1[i] != '\0' && str2[i] != '\0') {
        if ((str1[i] != '0' && str1[i] != '1') || (str2[i] != '0' && str2[i] != '1')) {
            return -1;
        }

        if (str1[i] != str2[i]) {
            if (str1[i] == '1') {
                mismatch_1_to_0++;
            } else {
                mismatch_0_to_1++;
            }
        }
        i++;
    }

    if (str1[i] != '\0' || str2[i] != '\0') {
        return -1;
    }

    if (mismatch_1_to_0 != mismatch_0_to_1) {
        return -1;
    }

    return mismatch_1_to_0;
}

int main(void) {
    const char *str1 = "11001";
    const char *str2 = "10101";
    int result;

    result = min_swaps(str1, str2);

    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Not Possible\n");
    }

    return 0;
}