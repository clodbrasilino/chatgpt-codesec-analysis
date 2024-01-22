#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 256

void removeNonAlphanumeric(char* str, size_t size) {
    if (!str || size <=0) {
        return;
    }

    size_t i = 0;
    size_t j = 0;
    while (str[i] && i<size) {
        if (isalnum((unsigned char)str[i])) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int main() {
    char str[MAX_SIZE];

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = strnlen(str, MAX_SIZE);
        
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }
    
        if (str[0] != '\0') {
            removeNonAlphanumeric(str, len);
            printf("String after removing non-alphanumeric characters: %s\n", str);
        }
    }
   
    return 0;
}