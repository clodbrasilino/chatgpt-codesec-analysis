#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool canRearrangeAlternating(const char *str) {
    int counts[26] = {0};
    int maxCount = 0;
    int strLen = strlen(str);
    for (int i = 0; i < strLen; ++i) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            counts[str[i] - 'a']++;
            if (counts[str[i] - 'a'] > maxCount) {
                maxCount = counts[str[i] - 'a'];
            }
        }
    }

    return maxCount <= (strLen + 1) / 2;
}

int main() {
    const char *testStr1 = "abac";
    const char *testStr2 = "aaabc";
    const char *testStr3 = "abc";

    printf("Can %s be rearranged? %s\n", testStr1, canRearrangeAlternating(testStr1) ? "Yes" : "No");
    printf("Can %s be rearranged? %s\n", testStr2, canRearrangeAlternating(testStr2) ? "Yes" : "No");
    printf("Can %s be rearranged? %s\n", testStr3, canRearrangeAlternating(testStr3) ? "Yes" : "No");

    return 0;
}