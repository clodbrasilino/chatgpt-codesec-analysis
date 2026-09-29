#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool are_characters_unique(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = strnlen(str, 257);
    if (len >= 256) {
        return false;
    }

    int *char_map = calloc(256, sizeof(int));
    if (char_map == NULL) {
        return false;
    }

    for (size_t i = 0; i < len; ++i) {
        if (char_map[(unsigned char)str[i]] > 0) {
            free(char_map);
            return false;
        }
        char_map[(unsigned char)str[i]]++;
    }

    free(char_map);
    return true;
}

int main() {
    const char *test_str1 = "unique";
    const char *test_str2 = "hello";

    printf("Testing if '%s' has all unique characters: %s\n", test_str1, are_characters_unique(test_str1) ? "True" : "False");
    printf("Testing if '%s' has all unique characters: %s\n", test_str2, are_characters_unique(test_str2) ? "True" : "False");

    return 0;
}