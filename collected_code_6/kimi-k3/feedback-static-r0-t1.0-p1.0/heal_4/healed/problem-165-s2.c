#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int count_alphabet_position_matches(const char *str) {
    int count = 0;
    size_t i;
    
    if (str == NULL) {
        return 0;
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            char lower_char = tolower((unsigned char)str[i]);
            int alphabet_pos = lower_char - 'a' + 1;
            size_t string_pos = i + 1;
            
            if (alphabet_pos == (int)string_pos) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    char *input = NULL;
    size_t size = 0;
    ssize_t len;
    
    printf("Enter a string: ");
    
    len = getline(&input, &size, stdin);
    
    if (len != -1) {
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        
        int result = count_alphabet_position_matches(input);
        printf("Count: %d\n", result);
        
        free(input);
    }
    
    return 0;
}