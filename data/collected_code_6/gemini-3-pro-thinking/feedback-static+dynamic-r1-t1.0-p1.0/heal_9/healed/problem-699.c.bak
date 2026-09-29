#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char str[2000005];

int min_swaps(const char *s) {
    int count0 = 0;
    int count1 = 0;
    int i;
    int mismatch1 = 0;
    int mismatch0 = 0;

    if (s == NULL) {
        return -1;
    }

    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == '0') {
            count0++;
        } else if (s[i] == '1') {
            count1++;
        } else {
            return -1;
        }
    }

    if (abs(count0 - count1) > 1) {
        return -1;
    }

    for (i = 0; s[i] != '\0'; i++) {
        char expected1 = (i % 2 == 0) ? '1' : '0';
        char expected0 = (i % 2 == 0) ? '0' : '1';

        if (s[i] != expected1) {
            mismatch1++;
        }
        if (s[i] != expected0) {
            mismatch0++;
        }
    }

    int ans = -1;
    
    if (count1 >= count0) {
        ans = mismatch1 / 2;
    }
    
    if (count0 >= count1) {
        int swaps0 = mismatch0 / 2;
        if (ans == -1 || swaps0 < ans) {
            ans = swaps0;
        }
    }

    return ans;
}

int main(int argc, const char * const argv[]) {
    if (argc >= 2) {
        int result = min_swaps(argv[1]);
        if (result != -1) {
            printf("%d\n", result);
        } else {
            printf("Not Possible\n");
        }
        return 0;
    }

    while (scanf("%2000004s", str) == 1) {
        int result = min_swaps(str);

        if (result != -1) {
            printf("%d\n", result);
        } else {
            printf("Not Possible\n");
        }
    }

    return 0;
}