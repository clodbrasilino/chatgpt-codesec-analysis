#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char str1[2000005];
static char str2[2000005];

int min_swaps(const char *s1, const char *s2) {
    size_t len1;
    size_t len2;
    size_t i;
    int mismatch_1_to_0 = 0;
    int mismatch_0_to_1 = 0;

    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    len1 = strlen(s1);
    len2 = strlen(s2);

    if (len1 != len2) {
        return -1;
    }

    for (i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') || (s2[i] != '0' && s2[i] != '1')) {
            return -1;
        }

        if (s1[i] != s2[i]) {
            if (s1[i] == '1') {
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

int main(int argc, const char * const argv[]) {
    if (argc >= 3) {
        int result = min_swaps(argv[1], argv[2]);
        if (result != -1) {
            printf("%d\n", result);
        } else {
            printf("Not Possible\n");
        }
        return 0;
    }

    while (scanf("%2000004s %2000004s", str1, str2) == 2) {
        int result = min_swaps(str1, str2);

        if (result != -1) {
            printf("%d\n", result);
        } else {
            printf("Not Possible\n");
        }
    }

    return 0;
}