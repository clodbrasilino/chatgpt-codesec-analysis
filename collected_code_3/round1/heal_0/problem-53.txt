#include <stdio.h>
#include <string.h>

int checkFirstLastChar(char *str) {
    int len = strlen(str);
    if (str[0] == str[len - 1]) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';
    int result = checkFirstLastChar(str);
    if (result == 1) {
        printf("First and last character are same.\n");
    } else {
        printf("First and last character are not same.\n");
    }
    return 0;
}