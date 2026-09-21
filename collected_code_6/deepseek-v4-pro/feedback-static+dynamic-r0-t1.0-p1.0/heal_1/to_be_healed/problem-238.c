#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned long long count_non_empty_substrings(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    unsigned long long len = (unsigned long long)strlen(str);
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
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        printf("String: \"%s\", Non-empty substrings: %llu\n", input, count_non_empty_substrings(input));
    }
    
    return 0;
}