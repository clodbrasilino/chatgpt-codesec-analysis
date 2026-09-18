#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool check_first_last_chars_equal(char* str) {
    int len = strlen(str);

    if (len == 0) {
        return false;
    }

    return str[0] == str[len - 1];
}

int main() {
    char* str1 = "HelloH";
    bool result1 = check_first_last_chars_equal(str1);

    if(result1) {
        printf("First and last characters are same in string '%s'.\n", str1);
    } else {
        printf("First and last characters are not same in string '%s'.\n", str1);
    }

    char* str2 = "world";
    bool result2 = check_first_last_chars_equal(str2);

    if(result2) {
        printf("First and last characters are same in string '%s'.\n", str2);
    } else {
        printf("First and last characters are not same in string '%s'.\n", str2);
    }

    return 0;
}