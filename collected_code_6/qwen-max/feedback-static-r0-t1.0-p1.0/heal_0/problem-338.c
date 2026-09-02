#include <stdio.h>
#include <string.h>

int countSubstringsWithSameFirstLast(char *s) {
    int count = 0;
    int len = strlen(s);
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
    char str[] = "abcab";
    int result = countSubstringsWithSameFirstLast(str);
    printf("%d\n", result);
    return 0;
}