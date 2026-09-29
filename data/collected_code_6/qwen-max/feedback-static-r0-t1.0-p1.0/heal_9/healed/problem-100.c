#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

bool isPalindrome(int n) {
    char numStr[22];
    int ret = snprintf(numStr, sizeof(numStr), "%d", n);
    if (ret < 0 || (size_t)ret >= sizeof(numStr)) return false;
    size_t len = strlen(numStr);
    for (size_t i = 0; i < len / 2; ++i) {
        if (numStr[i] != numStr[len - i - 1]) return false;
    }
    return true;
}

int nextPalindromicNumber(int n) {
    n++;
    while (!isPalindrome(n)) {
        n++;
    }
    return n;
}

int main() {
    int n;
    if (scanf("%d", &n) == 1) {
        int result = nextPalindromicNumber(n);
        printf("%d\n", result);
    }
    return 0;
}