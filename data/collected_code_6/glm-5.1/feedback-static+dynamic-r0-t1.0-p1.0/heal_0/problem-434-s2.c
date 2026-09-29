#include <stdio.h>
#include <stdbool.h>

bool match_pattern(const char *str) {
    if (str == NULL) {
        return false;
    }

    bool found_a = false;
    size_t b_count = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == 'a' && !found_a) {
            found_a = true;
        } else if (str[i] == 'b' && found_a) {
            b_count++;
        } else if (found_a) {
            break;
        }
    }

    if (found_a && b_count >= 1) {
        return true;
    }

    return false;
}

int main(void) {
    const char *test_cases[] = {
        "ab",
        "abb",
        "abbb",
        "a",
        "ac",
        "abc",
        "aab",
        "bac",
        NULL
    };

    for (size_t i = 0; test_cases[i] != NULL; i++) {
        bool result = match_pattern(test_cases[i]);
        printf("%s: %s\n", test_cases[i], result ? "Match" : "No Match");
    }

    return 0;
}