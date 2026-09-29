#include <stdio.h>
#include <stdbool.h>

bool are_characters_unique(const char *str) {
    if (str == NULL) {
        return false;
    }

    bool seen[256] = {false};

    for (size_t i = 0; str[i] != '\0'; i++) {
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
    const char *test3 = "test";

    printf("%s: %s\n", test1, are_characters_unique(test1) ? "true" : "false");
    printf("%s: %s\n", test2, are_characters_unique(test2) ? "true" : "false");
    printf("%s: %s\n", test3, are_characters_unique(test3) ? "true" : "false");

    return 0;
}