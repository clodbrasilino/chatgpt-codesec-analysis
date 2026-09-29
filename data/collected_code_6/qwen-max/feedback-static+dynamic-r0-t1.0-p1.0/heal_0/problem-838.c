#include <stdio.h>
#include <string.h>

int minSwaps(char *s1, char *s2) {
    int len = strlen(s1);
    int mismatch[2] = {0, 0};
    for (int i = 0; i < len; ++i) {
        if (s1[i] != s2[i]) {
            mismatch[s1[i] - '0']++;
        }
    }
    int swaps = 0;
    while (mismatch[0] > 0 && mismatch[1] > 0) {
        swaps++;
        mismatch[0]--;
        mismatch[1]--;
    }
    return swaps + (mismatch[0] / 2) * 2 + (mismatch[1] / 2) * 2;
}

int main() {
    char s1[] = "1100";
    char s2[] = "1001";
    printf("Minimum swaps: %d\n", minSwaps(s1, s2));
    return 0;
}