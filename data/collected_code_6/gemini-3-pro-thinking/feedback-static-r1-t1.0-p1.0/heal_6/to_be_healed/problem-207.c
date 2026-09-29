#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 8192

size_t get_longest_repeating_subsequence_length(const char *str);

size_t get_longest_repeating_subsequence_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(str);
    if (n > MAX_STR_LEN) {
        n = MAX_STR_LEN;
    }

    if (n == 0) {
        return 0;
    }

    size_t *prev = (size_t *)calloc(n + 1, sizeof(size_t));
    if (prev == NULL) {
        return 0;
    }

    size_t *curr = (size_t *)calloc(n + 1, sizeof(size_t));
    if (curr == NULL) {
        free(prev);
        return 0;
    }

    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= n; j++) {
            if (str[i - 1] == str[j - 1] && i != j) {
                curr[j] = 1 + prev[j - 1];
            } else {
                curr[j] = (prev[j] > curr[j - 1]) ? prev[j] : curr[j - 1];
            }
        }
        size_t *temp = prev;
        prev = curr;
        curr = temp;
    }

    size_t result = prev[n];

    free(prev);
    free(curr);

    return result;
}

int main(void) {
    const char *test_str = "AABEBCDD";
    size_t lrs_length = get_longest_repeating_subsequence_length(test_str);
    
    printf("%zu\n", lrs_length);
    
    return 0;
}