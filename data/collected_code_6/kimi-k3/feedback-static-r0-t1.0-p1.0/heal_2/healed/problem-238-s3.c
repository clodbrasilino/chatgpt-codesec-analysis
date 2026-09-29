#include <stdio.h>
#include <string.h>
#include <stdint.h>

unsigned long long countNonEmptySubstrings(const char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return 0;
    }
    
    size_t len = strnlen(str, max_len);
    if (len == 0) {
        return 0;
    }
    
    if (len > UINT64_MAX / (len + 1)) {
        return 0;
    }
    
    return (unsigned long long)len * (len + 1) / 2;
}

int main(void) {
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