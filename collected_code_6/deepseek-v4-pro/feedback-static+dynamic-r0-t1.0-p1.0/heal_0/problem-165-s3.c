#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int count_same_position(const char *str) {
    int count = 0;
    size_t len = strlen(str);
    
    for (size_t i = 0; i < len; i++) {
        if (isalpha((unsigned char)str[i])) {
            char lower = tolower((unsigned char)str[i]);
            if (lower - 'a' == (int)i) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    char *input = NULL;
    size_t len = 0;
    ssize_t read;
    
    printf("Enter a string: ");
    read = getline(&input, &len, stdin);
    
    if (read == -1) {
        free(input);
        return 1;
    }
    
    if (read > 0 && input[read - 1] == '\n') {
        input[read - 1] = '\0';
    }
    
    int result = count_same_position(input);
    printf("Count: %d\n", result);
    
    free(input);
    return 0;
}