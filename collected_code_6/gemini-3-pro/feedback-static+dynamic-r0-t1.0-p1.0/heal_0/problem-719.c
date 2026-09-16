#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool match_pattern(const char *str) {
    if (str == NULL) {
        return false;
    }

    if (*str != 'a') {
        return false;
    }

    str++;

    while (*str != '\0') {
        if (*str != 'b') {
            return false;
        }
        str++;
    }

    return true;
}

int main(void) {
    const char *test_cases[] = {
        "a",
        "ab",
        "abb",
        "b",
        "ba",
        "aab",
        NULL
    };

    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_cases; i++) {
        if (test_cases[i] != NULL) {
            bool result = match_pattern(test_cases[i]);
            printf("Pattern '%s' match: %s\n", test_cases[i], result ? "true" : "false");
        }
    }

    return EXIT_SUCCESS;
}