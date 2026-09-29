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

int longestPalindromicSubsequence(char *s) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int n = strlen(s);
    return lps(s, 0, n - 1);
}

int main() {
    char s[] = "character";
    int length = longestPalindromicSubsequence(s);
    printf("The length of the longest palindromic subsequence is %d\n", length);
    return 0;
}