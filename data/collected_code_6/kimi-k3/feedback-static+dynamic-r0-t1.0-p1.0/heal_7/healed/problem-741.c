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
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strcspn(buffer, "\n");
    buffer[len] = '\0';
    
    if (all_characters_same(buffer)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return 0;
}