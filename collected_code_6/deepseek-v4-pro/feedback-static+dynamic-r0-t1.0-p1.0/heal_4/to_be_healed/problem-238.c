#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

unsigned long long count_non_empty_substrings(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    unsigned long long len = 0;
    while (len < SIZE_MAX && str[len] != '\0') {
        len++;
    }
    
    if (len == SIZE_MAX) {
        return 0;
    }
    
    return len * (len + 1) / 2;
}

int main(void) {
    const char *test1 = "abc";
    const char *test2 = "";
    const char *test3 = "programming";
    const char *test4 = NULL;
    
    printf("String: \"%s\", Non-empty substrings: %llu\n", test1, count_non_empty_substrings(test1));
    printf("String: \"%s\", Non-empty substrings: %llu\n", test2, count_non_empty_substrings(test2));
    printf("String: \"%s\", Non-empty substrings: %llu\n", test3, count_non_empty_substrings(test3));
    printf("String: NULL, Non-empty substrings: %llu\n", count_non_empty_substrings(test4));
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t max_len = sizeof(input);
        size_t len = strnlen(input, max_len);
        
        if (len > 0 && len < max_len && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        } else if (len >= max_len) {
            input[max_len - 1] = '\0';
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF);
        }
        
        printf("String: \"%s\", Non-empty substrings: %llu\n", input, count_non_empty_substrings(input));
    }
    
    return 0;
}