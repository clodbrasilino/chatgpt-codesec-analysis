#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool canRearrangeAlternating(const char *str, size_t strLen) {
    int counts[26] = {0};
    int maxCount = 0;
    for (size_t i = 0; i < strLen; ++i) {
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

    printf("Can %s be rearranged? %s\n", testStr1, canRearrangeAlternating(testStr1, strlen(testStr1)) ? "Yes" : "No");
    printf("Can %s be rearranged? %s\n", testStr2, canRearrangeAlternating(testStr2, strlen(testStr2)) ? "Yes" : "No");
    printf("Can %s be rearranged? %s\n", testStr3, canRearrangeAlternating(testStr3, strlen(testStr3)) ? "Yes" : "No");

    return 0;
}