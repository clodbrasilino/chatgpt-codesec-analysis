#include <stdio.h>
#include <string.h>

int check_first_last_char(char *str) {
    int len = strlen(str);
    if (len == 0) {
        return 0;
    }
    return str[0] == str[len - 1];
}

int main() {
    char str[] = "helloh";
    if (check_first_last_char(str)) {
        printf("First and last characters are equal.\n");
    } else {
        printf("First and last characters are not equal.\n");
    }
    return 0;
}