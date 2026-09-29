#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char* to_uppercase(char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    char *ptr = str;
    while (*ptr != '\0') {
        *ptr = (char)toupper((unsigned char)*ptr);
        ptr++;
    }
    
    return str;
}

int main(void) {
    char str[] = "Hello, World!";
    
    printf("Original: %s\n", str);
    
    char *result = to_uppercase(str);
    
    if (result != NULL) {
        printf("Uppercase: %s\n", result);
    } else {
        printf("Error: NULL string provided.\n");
    }
    
    return 0;
}