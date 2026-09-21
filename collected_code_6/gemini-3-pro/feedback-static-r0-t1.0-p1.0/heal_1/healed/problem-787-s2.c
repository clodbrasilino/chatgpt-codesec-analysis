#include <stdio.h>
#include <stddef.h>

int match_a_three_b(const char *str) {
    if (str == NULL) {
        return 0;
    }

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == 'a') {
            if (str[i + 1] == 'b' && str[i + 2] == 'b' && str[i + 3] == 'b') {
                return 1;
            }
        }
    }
    return 0;
}

int main(void) {
    const char *test_strings[] = {
        "abbb",
        "aabbbc",
        "ab",
        "abb",
        "abbbb",
        "babbb",
        NULL
    };

    for (size_t i = 0; test_strings[i] != NULL; i++) {
        int result = match_a_three_b(test_strings[i]);
        printf("%s: %d\n", test_strings[i], result);
    }

    return 0;
}