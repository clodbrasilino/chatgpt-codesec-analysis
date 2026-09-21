#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int lps(char *seq, int i, int j) {
    if (i == j) {
        return 1;
    }
    if (seq[i] == seq[j] && i + 1 == j) {
        return 2;
    }
    if (seq[i] == seq[j]) {
        return lps(seq, i + 1, j - 1) + 2;
    }
    return max(lps(seq, i, j - 1), lps(seq, i + 1, j));
}

int longestPalindromicSubsequence(const char *s, size_t n) {
    return lps(s, 0, n - 1);
}

int main() {
    const char s[] = "character";
    size_t n = sizeof(s) / sizeof(s[0]) - 1;
    int length = longestPalindromicSubsequence(s, n);
    printf("The length of the longest palindromic subsequence is %d\n", length);
    return 0;
}