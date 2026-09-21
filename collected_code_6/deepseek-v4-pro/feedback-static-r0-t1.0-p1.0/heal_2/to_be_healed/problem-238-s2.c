#include <stdio.h>
#include <string.h>

unsigned long long count_substrings(const char *str, size_t max_len) {
    size_t len = strnlen(str, max_len);
    return (unsigned long long)len * (len + 1) / 2;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1001];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    unsigned long long result = count_substrings(input, sizeof(input));
    printf("Number of non-empty substrings: %llu\n", result);
    
    return 0;
}