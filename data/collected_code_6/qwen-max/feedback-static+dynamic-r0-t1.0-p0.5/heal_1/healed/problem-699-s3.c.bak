#include <stdio.h>
#include <string.h>

int minSwaps(char *s1, const char *s2) {
    int count[2] = {0, 0};
    int len = strlen(s1);
    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            count[s1[i] - '0']++;
        }
    }
    return (count[0] + count[1]) / 2;
}

int main() {
    char s1[] = "1100";
    char s2[] = "1001";
    int result = minSwaps(s1, s2);
    printf("%d\n", result);
    return 0;
}