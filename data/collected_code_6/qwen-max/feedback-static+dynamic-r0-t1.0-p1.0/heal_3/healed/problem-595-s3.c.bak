#include <stdio.h>
#include <string.h>

int minSwaps(char* s1, const char* s2) {
    int count[2] = {0};
    int n = strlen(s1);
    int diff_count = 0;

    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            count[s1[i] - '0']++;
            count[s2[i] - '0']--;
            diff_count++;
        }
    }

    if (count[0] == 0 && count[1] == 0 && diff_count % 2 == 0) {
        return diff_count / 2;
    } else {
        return -1;
    }
}

int main() {
    char s1[] = "1100";
    const char s2[] = "0011";

    int swaps = minSwaps(s1, s2);
    if (swaps != -1) {
        printf("Minimum number of swaps: %d\n", swaps);
    } else {
        printf("Cannot convert string s1 to s2 with swaps.\n");
    }

    return 0;
}