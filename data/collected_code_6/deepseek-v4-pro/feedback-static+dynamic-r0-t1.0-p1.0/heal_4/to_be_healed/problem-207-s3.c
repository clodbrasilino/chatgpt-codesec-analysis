#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 3, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  */

int longest_repeating_subsequence(const char *str) {
    if (str == NULL) return -1;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    int n = (int)len;
    if (n == 0) return 0;

    int *dp = (int *)calloc((n + 1) * (n + 1), sizeof(int));
    if (!dp) return -1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[i * (n + 1) + j] = dp[(i - 1) * (n + 1) + (j - 1)] + 1;
            } else {
                int up = dp[(i - 1) * (n + 1) + j];
                int left = dp[i * (n + 1) + (j - 1)];
                dp[i * (n + 1) + j] = (up > left) ? up : left;
            }
        }
    }

    int result = dp[n * (n + 1) + n];
    free(dp);
    return result;
}

int main(void) {
    const char *test1 = "ATACTCGGA";
    const char *test2 = "AABEBCDD";
    const char *test3 = "abcabc";
    const char *test4 = "";
    const char *test5 = "aaaa";

    printf("%d\n", longest_repeating_subsequence(test1));
    printf("%d\n", longest_repeating_subsequence(test2));
    printf("%d\n", longest_repeating_subsequence(test3));
    printf("%d\n", longest_repeating_subsequence(test4));
    printf("%d\n", longest_repeating_subsequence(test5));

    return 0;
}