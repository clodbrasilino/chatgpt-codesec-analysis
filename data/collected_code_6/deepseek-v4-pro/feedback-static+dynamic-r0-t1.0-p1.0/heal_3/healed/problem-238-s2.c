#include <stdio.h>
#include <string.h>
#include <stddef.h>

unsigned long long count_substrings(const char *str) {
    size_t len = strnlen(str, 1000);
    if (len == 0) {
        return 0;
    }
    if (len > 1000) {
        len = 1000;
    }
    return (unsigned long long)len * (len + 1) / 2;
}

int main(void) {
    char input[1024];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    if (strnlen(input, sizeof(input)) >= sizeof(input)) {
        printf("Input too long\n");
        return 1;
    }
    
    unsigned long long result = count_substrings(input);
    printf("Number of non-empty substrings: %llu\n", result);
    
    return 0;
}