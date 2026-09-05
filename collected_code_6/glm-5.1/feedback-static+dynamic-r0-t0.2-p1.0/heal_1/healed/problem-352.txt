#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool are_chars_unique(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = strlen(str);
    if (len > 256) {
        return false;
    }

    bool *seen = (bool *)calloc(256, sizeof(bool));
    if (seen == NULL) {
        return false;
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            free(seen);
            return false;
        }
        seen[c] = true;
    }

    free(seen);
    return true;
}

int main(void) {
    const char *test1 = "abcdef";
    const char *test2 = "hello";

    if (are_chars_unique(test1)) {
        printf("\"%s\" has all unique characters.\n", test1);
    } else {
        printf("\"%s\" does not have all unique characters.\n", test1);
    }

    if (are_chars_unique(test2)) {
        printf("\"%s\" has all unique characters.\n", test2);
    } else {
        printf("\"%s\" does not have all unique characters.\n", test2);
    }

    const char *test3 = NULL;
    if (test3 != NULL && are_chars_unique(test3)) {
        printf("\"%s\" has all unique characters.\n", test3);
    } else {
        printf("NULL string does not have all unique characters.\n");
    }

    return 0;
}