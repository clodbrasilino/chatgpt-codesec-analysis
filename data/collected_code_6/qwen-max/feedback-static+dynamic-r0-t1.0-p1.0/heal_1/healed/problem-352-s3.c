#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool are_characters_unique(const char *str) {
    if (str == NULL) {
        return false;
    }
    int len = 0;
    while (str[len] != '\0') {
        for (int j = 0; j < len; ++j) {
            if (str[len] == str[j]) {
                return false;
            }
        }
        len++;
    }
    return true;
}

int main() {
    const char *test_str1 = "unique";
    const char *test_str2 = "hello";

    printf("Testing if '%s' has all unique characters: %s\n", test_str1, are_characters_unique(test_str1) ? "True" : "False");
    printf("Testing if '%s' has all unique characters: %s\n", test_str2, are_characters_unique(test_str2) ? "True" : "False");

    return 0;
}