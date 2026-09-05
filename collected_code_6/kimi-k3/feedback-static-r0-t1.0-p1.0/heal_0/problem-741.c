#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool all_characters_same(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return false;
    }
    
    char first = str[0];
    size_t i = 1;
    
    while (str[i] != '\0') {
        if (str[i] != first) {
            return false;
        }
        i++;
    }
    
    return true;
}

int main(void) {
    char buffer[256];
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    if (all_characters_same(buffer)) {
        printf("All characters are the same\n");
    } else {
        printf("Characters are not all the same\n");
    }
    
    return 0;
}