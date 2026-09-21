#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_pattern(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    if (str[0] != 'a') {
        return false;
    }
    
    if (str[0] == '\0') {
        return false;
    }
    
    const char *ptr = str + 1;
    while (*ptr != '\0') {
        if (*ptr != 'b') {
            return false;
        }
        ptr++;
    }
    
    return true;
}

int main(void) {
    char input[256];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    if (match_pattern(input)) {
        printf("Match\n");
    } else {
        printf("No match\n");
    }
    
    return 0;
}