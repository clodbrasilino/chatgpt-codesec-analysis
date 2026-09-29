#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool are_characters_unique(const char *str) {
    int char_set[256] = {0};
    while (*str) {
        if (char_set[(unsigned char)*str]) {
            return false;
        }
        char_set[(unsigned char)*str]++;
        str++;
    }
    return true;
}

int main() {
    const char *test1 = "abcdefg";
    const char *test2 = "hello";
    
    if (are_characters_unique(test1)) {
        printf("All characters in test1 are unique.\n");
    } else {
        printf("There are duplicate characters in test1.\n");
    }

    if (are_characters_unique(test2)) {
        printf("All characters in test2 are unique.\n");
    } else {
        printf("There are duplicate characters in test2.\n");
    }

    return 0;
}