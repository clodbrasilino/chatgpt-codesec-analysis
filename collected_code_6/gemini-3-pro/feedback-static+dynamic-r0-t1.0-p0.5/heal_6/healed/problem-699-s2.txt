#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str1[2000005];
char str2[2000005];
char str3[2000005];

int main(void) {
    int words = 0;
    if (scanf("%2000000s", str1) == 1) words++;
    if (scanf("%2000000s", str2) == 1) words++;
    if (scanf("%2000000s", str3) == 1) words++;

    char *s1, *s2;
    if (words == 3) {
        s1 = str2;
        s2 = str3;
    } else if (words == 2) {
        s1 = str1;
        s2 = str2;
    } else {
        printf("Not Possible\n");
        return 0;
    }

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    if (len1 != len2) {
        printf("Not Possible\n");
        return 0;
    }

    size_t ones1 = 0, ones2 = 0;
    for (size_t i = 0; i < len1; i++) {
        if (s1[i] == '1') ones1++;
        if (s2[i] == '1') ones2++;
    }

    if (ones1 != ones2) {
        printf("Not Possible\n");
        return 0;
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

    printf("%lld\n", swaps);
    return 0;
}