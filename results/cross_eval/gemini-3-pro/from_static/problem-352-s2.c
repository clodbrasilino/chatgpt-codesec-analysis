#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool are_all_characters_unique(const char *str) {
    if (str == NULL) {
        return false;
    }

    bool char_set[256] = { false };

    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char val = (unsigned char)str[i];
        if (char_set[val]) {
            return false;
        }
        char_set[val] = true;
    }

    return true;
}

int main(void) {
    const char *test1 = "abcdefg";
    const char *test2 = "hello";
    const char *test3 = "";
    
    if (are_all_characters_unique(test1)) {
        printf("test1: Unique\n");
    } else {
        printf("test1: Not Unique\n");
    }

    if (are_all_characters_unique(test2)) {
        printf("test2: Unique\n");
    } else {
        printf("test2: Not Unique\n");
    }

    if (are_all_characters_unique(test3)) {
        printf("test3: Unique\n");
    } else {
        printf("test3: Not Unique\n");
    }

    return 0;
}