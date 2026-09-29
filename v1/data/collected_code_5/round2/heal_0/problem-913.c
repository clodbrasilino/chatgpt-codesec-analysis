#include <stdio.h>
#include <ctype.h>
#include <string.h>

int check_number_at_end(char* str) {
    int len = strlen(str);
    return isdigit(str[len - 1]) ? 1 : 0;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);
    if(check_number_at_end(str)) {
        printf("The string ends with a number\n");
    }
    else {
        printf("The string does not end with a number\n");
    }
    return 0;
}