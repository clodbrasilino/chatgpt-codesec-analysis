#include <stdio.h>
#include <stdbool.h>

bool match_a_followed_by_b(const char *str) {
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
        "abbb",
        "b",
        "ba",
        "abc",
        "aab",
        "",
        NULL
    };

    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; i++) {
        bool result = match_a_followed_by_b(test_cases[i]);
        if (test_cases[i] != NULL) {
            printf("'%s': %s\n", test_cases[i], result ? "Match" : "No Match");
        } else {
            printf("NULL: %s\n", result ? "Match" : "No Match");
        }
    }

    return 0;
}