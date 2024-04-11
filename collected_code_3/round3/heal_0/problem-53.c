#include <stdio.h>
#include <string.h>

int check_chars(char *str) {
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
    if (check_chars(str)) {
        printf("First and last characters are equal.\n");
    } else {
        printf("First and last characters are not equal.\n");
    }
    return 0;
}