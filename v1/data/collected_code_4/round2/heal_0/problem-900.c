#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool starts_with_number(const char* str) {
    if (str == NULL || strlen(str) == 0) {
        return false;
    }
    return isdigit((unsigned char)str[0]);
}

int main() {
    char* test_string1 = "123Hello";
    char* test_string2 = "Hello123";

    if (starts_with_number(test_string1)) {
        printf("'%s' starts with a number.\n", test_string1);
    } else {
        printf("'%s' does not start with a number.\n", test_string1);
    }

    if (starts_with_number(test_string2)) {
        printf("'%s' starts with a number.\n", test_string2);
    } else {
        printf("'%s' does not start with a number.\n", test_string2);
    }

    return 0;
}