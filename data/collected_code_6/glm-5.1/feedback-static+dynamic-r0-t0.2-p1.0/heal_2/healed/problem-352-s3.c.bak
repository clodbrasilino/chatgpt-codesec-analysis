#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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
    const char *test3 = "";
    const char *test4 = NULL;

    printf("\"%s\" %s all unique characters\n", test1, are_characters_unique(test1) ? "has" : "does not have");
    printf("\"%s\" %s all unique characters\n", test2, are_characters_unique(test2) ? "has" : "does not have");
    printf("\"%s\" %s all unique characters\n", test3, are_characters_unique(test3) ? "has" : "does not have");
    printf("\"(null)\" %s all unique characters\n", are_characters_unique(test4) ? "has" : "does not have");

    return 0;
}