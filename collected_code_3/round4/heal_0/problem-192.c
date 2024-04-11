#include <stdio.h>
#include <ctype.h>
#include <string.h>

int checkString(char *str) {
    int hasLetter = 0, hasNumber = 0;
    for(int i = 0; i < strlen(str); i++) {
        if(isalpha(str[i])) {
            hasLetter = 1;
        }
        if(isdigit(str[i])) {
            hasNumber = 1;
        }
        if(hasLetter && hasNumber) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, 100, stdin);
    str[strlen(str) - 1] = '\0';
    if(checkString(str)) {
        printf("The string has at least one letter and one number.\n");
    } else {
        printf("The string does not have at least one letter and one number.\n");
    }
    return 0;
}