#include <stdio.h>
#include <string.h>

int countSubstringsWithSameFirstLast(const char *s, int len) {
    int count = 0;
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j <= len; ++j) {
            if (s[i] == s[j - 1]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    const char str[] = "abcab";
    int result = countSubstringsWithSameFirstLast(str, (int)strlen(str));
    printf("%d\n", result);
    return 0;
}