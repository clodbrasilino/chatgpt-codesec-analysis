#include <stdio.h>
#include <string.h>
#include <limits.h>

int countSubstrings(const char *str, size_t max_len) {
    int count = 0;
    if (str == NULL) {
        return 0;
    }
    
    size_t n = 0;
    while (n < max_len && str[n] != '\0') {
        n++;
    }
    
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i; j < n; j++) {
            if (str[i] == str[j]) {
                if (count == INT_MAX) {
                    return -1;
                }
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    char str[1002];
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = strcspn(str, "\n");
        str[len] = '\0';
        
        if (len == 0) {
            printf("Number of substrings with same first and last characters: 0\n");
        } else {
            int result = countSubstrings(str, sizeof(str));
            if (result >= 0) {
                printf("Number of substrings with same first and last characters: %d\n", result);
            } else {
                fprintf(stderr, "Error: count overflow\n");
                return 1;
            }
        }
    } else {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    return 0;
}