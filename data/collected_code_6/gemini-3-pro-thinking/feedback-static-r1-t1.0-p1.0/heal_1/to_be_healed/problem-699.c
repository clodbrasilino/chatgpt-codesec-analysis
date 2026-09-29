#include <stdio.h>
#include <string.h>

int min_swaps(const char *str1, const char *str2);

int min_swaps(const char *str1, const char *str2) {
    size_t len1;
    size_t len2;
    size_t i;
    int mismatch_1_to_0 = 0;
    int mismatch_0_to_1 = 0;

    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len2 = strlen(str2);

    if (len1 != len2) {
        return -1;
    }

    for (i = 0; i < len1; i++) {
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
        printf("-1\n");
    }

    return 0;
}