#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t shortest_common_supersequence_length(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return (size_t)-1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t m = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(str2);

    size_t *prev = (size_t *)calloc(n + 1, sizeof(size_t));
    if (prev == NULL) {
        return (size_t)-1;
    }

    size_t *curr = (size_t *)calloc(n + 1, sizeof(size_t));
    if (curr == NULL) {
        free(prev);
        return (size_t)-1;
    }

    for (size_t i = 1; i <= m; i++) {
        for (size_t j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                curr[j] = prev[j - 1] + 1;
            } else {
                curr[j] = (prev[j] > curr[j - 1]) ? prev[j] : curr[j - 1];
            }
        }
        
        size_t *temp = prev;
        prev = curr;
        curr = temp;
    }

    size_t lcs_length = prev[n];
    
    free(prev);
    free(curr);

    return m + n - lcs_length;
}

int main(void) {
    const char *str1 = "AGGTAB";
    const char *str2 = "GXTXAYB";

    size_t length = shortest_common_supersequence_length(str1, str2);
    
    if (length == (size_t)-1) {
        fprintf(stderr, "Memory allocation failure or invalid input.\n");
        return EXIT_FAILURE;
    }

    printf("%zu\n", length);

    return EXIT_SUCCESS;
}