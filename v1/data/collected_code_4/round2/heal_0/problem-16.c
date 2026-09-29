#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int find_sequence(char* str) {
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        if (!(islower(str[i]) || str[i] == '_')) {
            return -1;
        }
    }

    return 0;
}

int main() {
    char* test_string = "this_is_test_string";
    int result = find_sequence(test_string);

    if (result == -1) {
        printf("The string '%s' does not follow the sequence rules.\n", test_string);
        return -1;
    }

    printf("The string '%s' follows the sequence rules.\n", test_string);

    return 0;
}