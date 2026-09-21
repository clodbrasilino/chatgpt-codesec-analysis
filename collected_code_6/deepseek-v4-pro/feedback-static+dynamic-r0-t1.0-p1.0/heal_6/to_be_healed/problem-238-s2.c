#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

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
    char *input = NULL;
    size_t bufsize = 1024;
    
    input = malloc(bufsize);
    if (input == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter a string: ");
    if (fgets(input, bufsize, stdin) == NULL) {
        printf("Error reading input\n");
        free(input);
        return 1;
    }
    
    input[bufsize - 1] = '\0';
    size_t len = strnlen(input, bufsize);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    } else {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF);
        printf("Input too long\n");
        free(input);
        return 1;
    }
    
    if (len >= 1000) {
        printf("Input too long\n");
        free(input);
        return 1;
    }
    
    unsigned long long result = count_substrings(input);
    printf("Number of non-empty substrings: %llu\n", result);
    
    free(input);
    return 0;
}