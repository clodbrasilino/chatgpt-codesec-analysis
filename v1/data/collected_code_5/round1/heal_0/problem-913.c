#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check_number_end_of_string(char *str) {
    int len = strlen(str);

    if(len > 0 && isdigit(str[len-1])) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char str[100];

    printf("Enter a string: ");
    fgets(str, 100, stdin);

    // Remove newline character from fgets
    str[strlen(str)-1] = '\0';

    if(check_number_end_of_string(str)) {
        printf("The string ends with a number\n");
    } else {
        printf("The string does not end with a number\n");
    }

    return 0;
}