#include <stdio.h>
#include <ctype.h>
#include <string.h>

int checkString(char *str, int length) {
    int hasUpper = 0, hasLower = 0, hasDigit = 0;
    if(strlen(str) != length) {
        return 0;
    }
    while(*str) {
        if(isupper(*str)) {
            hasUpper = 1;
        } else if(islower(*str)) {
            hasLower = 1;
        } else if(isdigit(*str)) {
            hasDigit = 1;
        }
        str++;
    }
    return hasUpper && hasLower && hasDigit;
}

int main() {
    char str[100];
    int length;
    printf("Enter a string: ");
    scanf("%s", str);
    printf("Enter the required length: ");
    scanf("%d", &length);
    if(checkString(str, length)) {
        printf("The string meets the requirements.\n");
    } else {
        printf("The string does not meet the requirements.\n");
    }
    return 0;
}