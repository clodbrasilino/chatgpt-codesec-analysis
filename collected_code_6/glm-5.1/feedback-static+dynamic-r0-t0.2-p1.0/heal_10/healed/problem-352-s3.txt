#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
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
        uint8_t c = (uint8_t)str[i];
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
    const char *test3 = "";
    const char *test4 = NULL;
    const char *test5 = "aabbcc";

    bool res1 = are_characters_unique(test1);
    bool res2 = are_characters_unique(test2);
    bool res3 = are_characters_unique(test3);
    bool res4 = are_characters_unique(test4);
    bool res5 = are_characters_unique(test5);

    printf("\"%s\" %s all unique characters\n", test1, res1 ? "has" : "does not have");
    printf("\"%s\" %s all unique characters\n", test2, res2 ? "has" : "does not have");
    printf("\"%s\" %s all unique characters\n", test3, res3 ? "has" : "does not have");
    printf("\"%s\" %s all unique characters\n", test4 ? test4 : "NULL", res4 ? "has" : "does not have");
    printf("\"%s\" %s all unique characters\n", test5, res5 ? "has" : "does not have");

    return EXIT_SUCCESS;
}