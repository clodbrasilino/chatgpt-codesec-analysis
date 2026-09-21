#include <stdio.h>
#include <string.h>

unsigned long long countNonEmptySubstrings(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    
    size_t len = strnlen(str, max_len);
    if (len == 0) {
        return 0;
    }
    
    return (unsigned long long)len * (len + 1) / 2;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1025];
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    unsigned long long result = countNonEmptySubstrings(buffer, sizeof(buffer));
    printf("Number of non-empty substrings: %llu\n", result);
    
    return 0;
}