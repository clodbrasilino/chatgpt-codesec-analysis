#include <stdio.h>
#include <ctype.h>
#include <string.h>

int checkString(char* str, int len) {
    int hasUpper = 0, hasLower = 0, hasDigit = 0;
    if(strlen(str) != len) return 0;
    for(int i = 0; i < len; i++) {
        if(isupper(str[i])) hasUpper = 1;
        else if(islower(str[i])) hasLower = 1;
        else if(isdigit(str[i])) hasDigit = 1;
    }
    return hasUpper && hasLower && hasDigit;
}

int main() {
    char str[100];
    int len;
    printf("Enter a string: ");
    scanf("%s", str);
    printf("Enter the required length: ");
    scanf("%d", &len);
    if(checkString(str, len)) {
        printf("The string meets the requirements.\n");
    } else {
        printf("The string does not meet the requirements.\n");
    }
    return 0;
}