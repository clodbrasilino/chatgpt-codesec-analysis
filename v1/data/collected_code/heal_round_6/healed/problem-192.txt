#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 101

int checkString(const char *str, size_t length) {
    int hasLetter = 0;
    int hasNumber = 0;

    for(size_t i = 0; i < length && str[i] != '\0'; i++) {
        if(isalpha((unsigned char)str[i])) {
            hasLetter = 1;
        } else if(isdigit((unsigned char)str[i])) {
            hasNumber = 1;
        }

        if(hasLetter && hasNumber) return 1;
    }
    
    return 0;
}

int main() {
    char *str = (char *)malloc(sizeof(char) * MAX_STRING_SIZE);
    if(str == NULL) {
        printf("Failed to allocate memory for string.\n");
        return 1;
    }

    printf("Enter a string: ");
    if(fgets(str, MAX_STRING_SIZE, stdin) != NULL) {
        str[strcspn(str, "\n")] = 0;

        if(checkString(str, strlen(str))) {
            printf("The string has at least one letter and one number.\n");
        } else {
            printf("The string does not have at least one letter and one number.\n");
        }
    }
    else {
        printf("Failed to read the string.\n");
    }

    free(str);
    return 0;
}