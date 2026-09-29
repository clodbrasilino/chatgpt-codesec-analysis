#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool areAllCharactersUnique(const char *str) {
    if (str == NULL) {
        return false;
    }

    bool char_set[256] = {false};

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
    const char *test4 = NULL;

    if (areAllCharactersUnique(test1)) {
        printf("test1: Unique\n");
    } else {
        printf("test1: Not Unique\n");
    }

    if (areAllCharactersUnique(test2)) {
        printf("test2: Unique\n");
    } else {
        printf("test2: Not Unique\n");
    }

    if (areAllCharactersUnique(test3)) {
        printf("test3: Unique\n");
    } else {
        printf("test3: Not Unique\n");
    }

    if (areAllCharactersUnique(test4)) {
        printf("test4: Unique\n");
    } else {
        printf("test4: Not Unique\n");
    }

    return 0;
}