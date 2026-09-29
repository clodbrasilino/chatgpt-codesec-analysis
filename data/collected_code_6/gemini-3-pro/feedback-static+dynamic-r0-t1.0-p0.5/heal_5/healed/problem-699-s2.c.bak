#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str1[2000005];
char str2[2000005];

long long min_swaps(const char *s1, const char *s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    if (len1 != len2) {
        return -1;
    }

    size_t ones1 = 0, ones2 = 0;
    for (size_t i = 0; i < len1; i++) {
        if (s1[i] == '1') ones1++;
        if (s2[i] == '1') ones2++;
    }

    if (ones1 != ones2) {
        return -1;
    }

    long long swaps = 0;
    size_t j = 0;
    for (size_t i = 0; i < len1; i++) {
        if (s1[i] == '1') {
            while (s2[j] != '1') {
                j++;
            }
            long long diff = (long long)i - (long long)j;
            if (diff < 0) diff = -diff;
            swaps += diff;
            j++;
        }
    }

    return swaps;
}

int main(void) {
    if (scanf("%2000000s %2000000s", str1, str2) == 2) {
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