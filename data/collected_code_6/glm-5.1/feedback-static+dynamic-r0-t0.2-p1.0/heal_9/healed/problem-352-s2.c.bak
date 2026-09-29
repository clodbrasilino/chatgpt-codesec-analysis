#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool are_characters_unique(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = strlen(str);
    if (len > 256) {
        return false;
    }

    bool char_set[256] = {false};

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (char_set[c]) {
            return false;
        }
        char_set[c] = true;
    }

    return true;
}

int main(void) {
    const char *test1 = "abcdef";
    const char *test2 = "hello";
    const char *test3 = "world";
    const char *test4 = "aabbc";

    bool result1 = are_characters_unique(test1);
    bool result2 = are_characters_unique(test2);
    bool result3 = are_characters_unique(test3);
    bool result4 = are_characters_unique(test4);

    printf("%s: %s\n", test1 ? test1 : "NULL", result1 ? "Unique" : "Not Unique");
    printf("%s: %s\n", test2 ? test2 : "NULL", result2 ? "Unique" : "Not Unique");
    printf("%s: %s\n", test3 ? test3 : "NULL", result3 ? "Unique" : "Not Unique");
    printf("%s: %s\n", test4 ? test4 : "NULL", result4 ? "Unique" : "Not Unique");

    return 0;
}