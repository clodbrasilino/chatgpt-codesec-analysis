#include <stdio.h>
#include <string.h>
#include <ctype.h>

char findFirstNonRepeatedChar(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    int count[256] = {0};
    int i;

    for (i = 0; str[i] != '\0'; i++) {
        count[(unsigned char)str[i]]++;
    }

    for (i = 0; str[i] != '\0'; i++) {
        if (count[(unsigned char)str[i]] == 1) {
            return str[i];
        }
    }

    return '\0';
}

int main(void) {
    const char *test_strings[] = {
        "programming",
        "aabbcc",
        "hello",
        "a",
        "",
        NULL
    };

    size_t num_strings = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < num_strings; i++) {
        char result = findFirstNonRepeatedChar(test_strings[i]);
        if (test_strings[i] == NULL) {
            printf("String: NULL -> First non-repeated char: '%c'\n", result);
        } else {
            printf("String: \"%s\" -> First non-repeated char: '%c'\n", test_strings[i], result);
        }
    }

    return 0;
}