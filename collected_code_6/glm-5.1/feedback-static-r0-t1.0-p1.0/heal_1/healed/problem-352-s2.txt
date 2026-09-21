#include <stdio.h>
#include <stdbool.h>

bool are_chars_unique(const char *str, size_t max_len) {
    if (str == NULL) {
        return false;
    }

    bool char_set[256] = {false};

    size_t i = 0;
    while (i < max_len) {
        unsigned char c = (unsigned char)str[i];
        if (c == '\0') {
            break;
        }
        if (char_set[c]) {
            return false;
        }
        char_set[c] = true;
        i++;
    }

    return true;
}

int main(void) {
    const char *test1 = "abcdef";
    const char *test2 = "hello";
    const char *test3 = NULL;
    const char *test4 = "";
    size_t max_len = 256;

    printf("%d\n", are_chars_unique(test1, max_len));
    printf("%d\n", are_chars_unique(test2, max_len));
    printf("%d\n", are_chars_unique(test3, max_len));
    printf("%d\n", are_chars_unique(test4, max_len));

    return 0;
}