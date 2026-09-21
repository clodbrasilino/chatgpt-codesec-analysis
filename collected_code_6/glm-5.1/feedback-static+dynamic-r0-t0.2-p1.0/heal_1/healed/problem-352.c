#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool are_chars_unique(const char *str, size_t len) {
    if (str == NULL) {
        return false;
    }

    if (len > 256) {
        return false;
    }

    bool seen[256] = { false };

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return false;
        }
        seen[c] = true;
    }

    return true;
}

int main(void) {
    const char *test1 = "abcdef";
    const char *test2 = "hello";
    const char *test3 = NULL;

    if (are_chars_unique(test1, test1 ? strlen(test1) : 0)) {
        printf("\"%s\" has all unique characters.\n", test1);
    } else {
        printf("\"%s\" does not have all unique characters.\n", test1);
    }

    if (are_chars_unique(test2, test2 ? strlen(test2) : 0)) {
        printf("\"%s\" has all unique characters.\n", test2);
    } else {
        printf("\"%s\" does not have all unique characters.\n", test2);
    }

    if (are_chars_unique(test3, test3 ? strlen(test3) : 0)) {
        printf("NULL string has all unique characters.\n");
    } else {
        printf("NULL string does not have all unique characters.\n");
    }

    return 0;
}