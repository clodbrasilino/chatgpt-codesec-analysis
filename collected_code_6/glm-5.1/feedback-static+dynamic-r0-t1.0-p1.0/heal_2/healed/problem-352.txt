#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool are_characters_unique(const char *str, size_t maxlen) {
    if (str == NULL) {
        return true;
    }

    size_t len = strnlen(str, maxlen);

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
    const char *test3 = NULL;
    const char *test4 = "";
    const char *test3_str = test3 ? test3 : "NULL";

    printf("%s: %d\n", test1 ? test1 : "NULL", are_characters_unique(test1, 256));
    printf("%s: %d\n", test2 ? test2 : "NULL", are_characters_unique(test2, 256));
    printf("%s: %d\n", test3_str, are_characters_unique(test3, 256));
    printf("%s: %d\n", test4 ? test4 : "NULL", are_characters_unique(test4, 256));

    return 0;
}