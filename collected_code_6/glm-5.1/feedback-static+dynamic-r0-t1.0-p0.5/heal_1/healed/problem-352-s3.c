#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

bool are_characters_unique(const char *str, size_t max_len) {
    if (str == NULL) {
        return true;
    }

    const char *end = memchr(str, '\0', max_len);
    if (end == NULL) {
        return false;
    }

    size_t len = (size_t)(end - str);
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
    const char *test3 = NULL;
    const char *test4 = "";

    printf("%d\n", are_characters_unique(test1, 256));
    printf("%d\n", are_characters_unique(test2, 256));
    printf("%d\n", are_characters_unique(test3, 256));
    printf("%d\n", are_characters_unique(test4, 256));

    return 0;
}