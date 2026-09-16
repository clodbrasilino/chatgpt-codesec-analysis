#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_alphabet_position_matches(const char *str) {
    int count = 0;
    int i;
    
    if (str == NULL) {
        return 0;
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            char lower_char = tolower((unsigned char)str[i]);
            int alphabet_pos = lower_char - 'a' + 1;
            int string_pos = i + 1;
            
            if (alphabet_pos == string_pos) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    char input[256];
    
    printf("Enter a string: ");
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        
        int result = count_alphabet_position_matches(input);
        printf("Count: %d\n", result);
    }
    
    return 0;
}