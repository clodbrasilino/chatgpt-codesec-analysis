#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool are_characters_unique(const char *str, size_t max_len) {
    if (str == NULL) {
        return false;
    }

    bool char_set[256] = {false};

    for (size_t i = 0; i < max_len; i++) {
        if (str[i] == '\0') {
            break;
        }
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

    if (test1 != NULL && are_characters_unique(test1, 256)) {
        printf("\"%s\" has all unique characters\n", test1);
    } else if (test1 != NULL) {
        printf("\"%s\" does not have all unique characters\n", test1);
    }

    if (test2 != NULL && are_characters_unique(test2, 256)) {
        printf("\"%s\" has all unique characters\n", test2);
    } else if (test2 != NULL) {
        printf("\"%s\" does not have all unique characters\n", test2);
    }

    if (test3 != NULL && are_characters_unique(test3, 256)) {
        printf("\"%s\" has all unique characters\n", test3);
    } else if (test3 != NULL) {
        printf("\"%s\" does not have all unique characters\n", test3);
    }

    if (are_characters_unique(test4, 256)) {
        printf("\"(null)\" has all unique characters\n");
    } else {
        printf("\"(null)\" does not have all unique characters\n");
    }

    return 0;
}