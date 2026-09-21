#include <stdio.h>
#include <string.h>

int minSwaps(const char *s1, const char *s2) {
    int count[2] = {0, 0};
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int len = (len1 < len2) ? len1 : len2;

    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            count[s1[i] - '0']++;
            count[s2[i] - '0']--;
        }
    }

    return (count[0] + count[1]) / 2;
}

int main() {
    const char s1[] = "1100";
    const char s2[] = "1001";
    int result = minSwaps(s1, s2);
    printf("Minimum swaps required: %d\n", result);
    return 0;
}