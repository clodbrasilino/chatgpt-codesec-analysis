#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool match_pattern(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    size_t len = strnlen(str, 256);
    if (len == 0 || len >= 256) {
        return false;
    }
    
    if (str[0] != 'a') {
        return false;
    }
    
    if (len == 1) {
        return true;
    }
    
    if (len == 2) {
        return str[1] == 'b';
    }
    
    return false;
}

int main(void) {
    char input[257];
    size_t input_len;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input_len = strlen(input);
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    } else if (input_len == sizeof(input) - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 1;
    }
    
    if (input_len >= 256) {
        return 1;
    }
    
    if (match_pattern(input)) {
        printf("Match\n");
    } else {
        printf("No match\n");
    }
    
    return 0;
}