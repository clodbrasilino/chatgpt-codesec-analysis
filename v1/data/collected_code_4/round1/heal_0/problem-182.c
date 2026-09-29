#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool findUppercase(char* str) {
    for (int i=0; str[i]; i++) {
        if (isupper(str[i])) {
            return true;
        }
    }
    return false;
}

bool findLowercase(char* str) {
    for (int i=0; str[i]; i++) {
        if (islower(str[i])) {
            return true;
        }
    }
    return false;
}

bool findNumeric(char* str) {
    for (int i=0; str[i]; i++) {
        if (isdigit(str[i])) {
            return true;
        }
    }
    return false;
}

bool findSpecialChar(char* str) {
    for (int i=0; str[i]; i++) {
        if(!isdigit(str[i]) && !isalpha(str[i])) {
            return true;
        }
    }
    return false;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, 100, stdin);

    if(findUppercase(str)) {
        printf("The string contains an uppercase character.\n");
    } else {
        printf("The string does not contain an uppercase character.\n");
    }

    if(findLowercase(str)) {
        printf("The string contains a lowercase character.\n");
    } else {
        printf("The string does not contain a lowercase character.\n");
    }
    
    if(findNumeric(str)) {
        printf("The string contains a numeric character.\n");
    } else {
        printf("The string does not contain a numeric character.\n");
    }

    if(findSpecialChar(str)) {
        printf("The string contains a special character.\n");
    } else {
        printf("The string does not contain a special character.\n");
    }
    return 0;
}