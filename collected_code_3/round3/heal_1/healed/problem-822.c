#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isValidPassword(char* password) {
    int length = strlen(password);

    if(length < 8) {
        return false;
    }

    bool hasUpper = false, hasLower = false, hasDigit = false;

    for(int i = 0; i < length; i++) {
        if(password[i] >= 'A' && password[i] <= 'Z') {
            hasUpper = true;
        }
        else if(password[i] >= 'a' && password[i] <= 'z') {
            hasLower = true;
        }
        else if(password[i] >= '0' && password[i] <= '9') {
            hasDigit = true;
        }
    }

    return hasUpper && hasLower && hasDigit;
}

int main() {
    char password[100];

    printf("Enter your password: ");
    scanf("%s", password);

    if(isValidPassword(password)) {
        printf("Password is valid.\n");
    }
    else {
        printf("Password is not valid.\n");
    }

    return 0;
}