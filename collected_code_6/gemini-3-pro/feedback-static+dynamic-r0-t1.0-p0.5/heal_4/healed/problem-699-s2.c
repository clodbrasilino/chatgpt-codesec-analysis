#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long min_swaps(const char *str1, const char *str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (len1 != len2) {
        return -1;
    }

    size_t ones1 = 0, ones2 = 0;
    for (size_t i = 0; i < len1; i++) {
        if (str1[i] == '1') ones1++;
        if (str2[i] == '1') ones2++;
    }

    if (ones1 != ones2) {
        return -1;
    }

    long long swaps = 0;
    size_t j = 0;
    for (size_t i = 0; i < len1; i++) {
        if (str1[i] == '1') {
            while (str2[j] != '1') {
                j++;
            }
            swaps += abs((long long)i - (long long)j);
            j++;
        }
    }

    return swaps;
}

int main(void) {
    char str1[100005];
    char str2[100005];

    if (scanf("%100004s %100004s", str1, str2) == 2) {
        long long result = min_swaps(str1, str2);

        if (result != -1) {
            printf("%lld\n", result);
        } else {
            printf("Not Possible\n");
        }
    } else {
        printf("Not Possible\n");
    }

    return 0;
}