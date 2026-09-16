#include <stdio.h>
#include <string.h>

unsigned long long count_substrings(const char *str) {
    size_t len = strlen(str);
    return (unsigned long long)len * (len + 1) / 2;
}

int main(void) {
    char input[1000];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    unsigned long long result = count_substrings(input);
    printf("Number of non-empty substrings: %llu\n", result);
    
    return 0;
}