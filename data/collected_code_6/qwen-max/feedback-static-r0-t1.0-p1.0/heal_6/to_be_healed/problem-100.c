#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

bool isPalindrome(int n) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char numStr[22];  // Adjusted size to accommodate '\0' terminator and INT_MAX
    snprintf(numStr, sizeof(numStr), "%d", n);
    size_t len = strnlen(numStr, sizeof(numStr));
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