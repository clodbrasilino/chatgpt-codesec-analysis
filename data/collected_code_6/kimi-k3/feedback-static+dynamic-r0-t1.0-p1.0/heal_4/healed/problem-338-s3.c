#include <stdio.h>
#include <string.h>
#include <stddef.h>

int countSubstrings(const char *str, size_t len) {
    int count = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < len; i++) {
        for (size_t j = i; j < len; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    char str[100];
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = strcspn(str, "\n");
        str[len] = '\0';
        
        int result = countSubstrings(str, len);
        printf("Number of substrings with same first and last characters: %d\n", result);
    } else {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    return 0;
}