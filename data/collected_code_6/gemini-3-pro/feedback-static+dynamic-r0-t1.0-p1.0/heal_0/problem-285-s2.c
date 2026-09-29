#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match_a_2to3_b(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strlen(str);
    size_t i = 0;

    while (i < len) {
        if (str[i] == 'a') {
            size_t b_count = 0;
            i++;

            while (i < len && str[i] == 'b') {
                b_count++;
                i++;
            }

            if (b_count == 2 || b_count == 3) {
                return 1;
            }
        } else {
            i++;
        }
    }

    return 0;
}

int main(void) {
    const char *test_strings[] = {
        "abb",
        "abbb",
        "abbbb",
        "ab",
        "a",
        "b",
        "xabbx",
        "xabbbx",
        NULL
    };

    for (size_t i = 0; test_strings[i] != NULL; i++) {
        if (match_a_2to3_b(test_strings[i])) {
            printf("Match found in: %s\n", test_strings[i]);
        } else {
            printf("No match in: %s\n", test_strings[i]);
        }
    }

    return 0;
}