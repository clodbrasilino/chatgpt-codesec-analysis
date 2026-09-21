#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_alternating(const char *str) {
    if (str == NULL || str[0] == '\0' || str[1] == '\0') {
        return false;
    }
    
    char first = str[0];
    char second = str[1];
    
    if (first == second) {
        return false;
    }
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (i % 2 == 0) {
            if (str[i] != first) {
                return false;
            }
        } else {
            if (str[i] != second) {
                return false;
            }
        }
    }
    
    return true;
}

int main(void) {
    char buffer[256];
    size_t buffer_size = sizeof(buffer);
    
    printf("Enter a string: ");
    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return 1;
    }
    
    size_t len = strcspn(buffer, "\n");
    if (len < buffer_size) {
        buffer[len] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    
    if (is_alternating(buffer)) {
        printf("The string consists of two alternating characters.\n");
    } else {
        printf("The string does not consist of two alternating characters.\n");
    }
    
    return 0;
}