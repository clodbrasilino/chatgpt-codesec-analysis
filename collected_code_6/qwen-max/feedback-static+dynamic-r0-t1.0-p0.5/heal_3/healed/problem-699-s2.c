#include <stdio.h>
#include <string.h>

int minSwaps(const char *s1, const char *s2, int len) {
    int count[2] = {0, 0};
    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            count[s1[i] - '0']++;
        }
    }
    return (count[0] + count[1]) / 2;
}

int main() {
    const char s1[] = "1100";
    const char s2[] = "1001";
    int len = strlen(s1);
    if (strcmp(s1, s2) != 0 && len == strlen(s2)) {
        int result = minSwaps(s1, s2, len);
        printf("%d\n", result);
    } else {
        printf("Not Possible\n");
    }
    return 0;
}