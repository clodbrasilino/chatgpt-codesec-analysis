#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min_swaps(const char *str1, const char *str2) {
    size_t len1;
    size_t len2;
    size_t i;
    int mismatch_1_to_0 = 0;
    int mismatch_0_to_1 = 0;

    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    len1 = strlen(str1);
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

int main(int argc, char *argv[]) {
    if (argc >= 3) {
        int result = min_swaps(argv[1], argv[2]);
        if (result != -1) {
            printf("%d\n", result);
        } else {
            printf("Not Possible\n");
        }
        return 0;
    }

    char *str1 = malloc(2000005);
    char *str2 = malloc(2000005);

    if (str1 == NULL || str2 == NULL) {
        if (str1) free(str1);
        if (str2) free(str2);
        return 1;
    }

    while (scanf("%2000000s %2000000s", str1, str2) == 2) {
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