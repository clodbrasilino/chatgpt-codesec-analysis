#include <stdio.h>
#include <string.h>

unsigned long long countNonEmptySubstrings(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }
    
    return (unsigned long long)len * (len + 1) / 2;
}

int main(void) {
    char buffer[1024];
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    unsigned long long result = countNonEmptySubstrings(buffer);
    printf("Number of non-empty substrings: %llu\n", result);
    
    return 0;
}