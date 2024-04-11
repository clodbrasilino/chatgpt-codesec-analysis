#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check_number_at_end(char *str) {
    int len = strlen(str);
    if(isdigit(str[len-1]))
        return 1;
    else
        return 0;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, 100, stdin);
    str[strlen(str) - 1] = '\0';
    if(check_number_at_end(str))
        printf("The string ends with a number.\n");
    else
        printf("The string does not end with a number.\n");
    return 0;
}