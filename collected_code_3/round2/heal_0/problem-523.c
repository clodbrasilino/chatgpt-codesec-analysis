#include <stdio.h>
#include <ctype.h>
#include <string.h>

int checkString(char *str, int len) {
    int hasUpper = 0, hasLower = 0, hasDigit = 0;

    if(strlen(str) != len) {
        return 0;
    }

    for(int i = 0; i < len; i++) {
        if(isupper(str[i])) {
            hasUpper = 1;
        }
        if(islower(str[i])) {
            hasLower = 1;
        }
        if(isdigit(str[i])) {
            hasDigit = 1;
        }
    }

    if(hasUpper && hasLower && hasDigit) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char str[100];
    int len;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';

    printf("Enter the length: ");
    scanf("%d", &len);

    if(checkString(str, len)) {
        printf("The string meets the criteria.\n");
    } else {
        printf("The string does not meet the criteria.\n");
    }

    return 0;
}