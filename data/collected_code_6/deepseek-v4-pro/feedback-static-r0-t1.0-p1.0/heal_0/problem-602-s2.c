#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define NO_REPEATED_CHAR '\0'

char first_repeated_char(const char *str) {
    if (str == NULL) {
        return NO_REPEATED_CHAR;
    }

    bool seen[256] = { false };
    size_t len = strlen(str);

    for (size_t i = 0; i < len; ++i) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return (char)c;
        }
        seen[c] = true;
    }

    return NO_REPEATED_CHAR;
}

int main(void) {
    const char *test_strings[] = {
        "hello",
        "abcdef",
        "aabbcc",
        "",
        "test string",
        NULL
    };

    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        const char *str = test_strings[i];
        char result = first_repeated_char(str);
        if (result == NO_REPEATED_CHAR) {
            printf("No repeated character found\n");
        } else {
            printf("First repeated character: %c\n", result);
        }
    }

    return 0;
}