#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t shortest_common_supersequence_len(const char *str1, const char *str2) {
    size_t m = strnlen(str1, 1024 * 1024);
    size_t n = strnlen(str2, 1024 * 1024);
    
    size_t *dp = (size_t *)malloc((n + 1) * sizeof(size_t));
    if (dp == NULL) {
        exit(EXIT_FAILURE);
    }
    
    for (size_t j = 0; j <= n; ++j) {
        dp[j] = j;
    }
    
    for (size_t i = 1; i <= m; ++i) {
        size_t prev = dp[0];
        dp[0] = i;
        for (size_t j = 1; j <= n; ++j) {
            size_t temp = dp[j];
            if (str1[i - 1] == str2[j - 1]) {
                dp[j] = prev + 1;
            } else {
                dp[j] = (dp[j] < dp[j - 1]) ? dp[j] + 1 : dp[j - 1] + 1;
            }
            prev = temp;
        }
    }
    
    size_t result = dp[n];
    free(dp);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <str1> <str2>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    if (argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Invalid input strings.\n");
        return EXIT_FAILURE;
    }
    
    size_t length = shortest_common_supersequence_len(argv[1], argv[2]);
    printf("%zu\n", length);
    
    return EXIT_SUCCESS;
}