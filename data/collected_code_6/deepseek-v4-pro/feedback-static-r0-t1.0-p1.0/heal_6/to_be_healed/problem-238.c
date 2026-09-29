#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned long long count_non_empty_substrings(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    size_t len = strnlen(str, SIZE_MAX);
    if (len == SIZE_MAX) {
        return 0;
    }
    
    return (unsigned long long)len * ((unsigned long long)len + 1) / 2;
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
        input[sizeof(input) - 1] = '\0';
        size_t len = strnlen(input, sizeof(input));
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
            len--;
        }
        printf("String: \"%s\", Non-empty substrings: %llu\n", input, count_non_empty_substrings(input));
        (void)len;
    }
    
    return 0;
}