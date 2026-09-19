#include <stdio.h>
#include <string.h>

int minSwaps(char* s1, const char* s2) {
    int count[2] = {0};
    int n = strlen(s1);
    int diff_count = 0;

    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            diff_count++;
            if (s1[i] == '0' && s2[i] == '1') {
                count[0]++;
            } else if (s1[i] == '1' && s2[i] == '0') {
                count[1]++;
            }
        }
    }

    if (count[0] != count[1]) {
        return -1;
    }
    return diff_count / 2;
}

int main() {
    char s1[] = "1100";
    const char s2[] = "0011";

    int swaps = minSwaps(s1, s2);
    if (swaps != -1) {
        printf("Minimum number of swaps: %d\n", swaps);
    } else {
        printf("Not Possible\n");
    }

    s1[0] = '1'; s1[1] = '1'; s1[2] = '0'; s1[3] = '1';
    s2[0] = '1'; s2[1] = '0'; s2[2] = '1'; s2[3] = '1';

    swaps = minSwaps(s1, s2);
    if (swaps != -1) {
        printf("Minimum number of swaps: %d\n", swaps);
    } else {
        printf("Not Possible\n");
    }

    s1[0] = '0'; s1[1] = '1'; s1[2] = '0'; s1[3] = '0';
    s2[0] = '1'; s2[1] = '1'; s2[2] = '0'; s2[3] = '0';

    swaps = minSwaps(s1, s2);
    if (swaps != -1) {
        printf("Minimum number of swaps: %d\n", swaps);
    } else {
        printf("Not Possible\n");
    }

    return 0;
}