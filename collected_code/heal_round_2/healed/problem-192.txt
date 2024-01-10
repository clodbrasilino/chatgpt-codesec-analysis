#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_STRING_SIZE 101

int checkString(const char *str) {
    int hasLetter = 0;
    int hasNumber = 0;

    for(size_t i = 0; str[i] != '\0'; i++) {
        if(isalpha((unsigned char)str[i]))
            hasLetter = 1;
        else if(isdigit((unsigned char)str[i]))
            hasNumber = 1;

        if(hasLetter && hasNumber)
            return 1;
    }
    
    return 0;
}

int main() {
    char str[MAX_STRING_SIZE] = {0};

    printf("Enter a string: ");
    fgets(str, MAX_STRING_SIZE, stdin);
    
    //Remove newline character
    str[strcspn(str, "\n")] = 0;

    if(checkString(str))
        printf("The string has at least one letter and one number.\n");
    else
        printf("The string does not have at least one letter and one number.\n");
    
    return 0;
}