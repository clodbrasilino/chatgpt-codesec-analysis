#include <stdio.h>
#include <stdbool.h>

bool match_a_followed_by_bs(const char *str) {
    if (str == NULL) {
        return false;
    }

    bool found_a = false;
    bool valid = false;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == 'a') {
            if (!found_a) {
                found_a = true;
                valid = true;
            } else {
                valid = false;
                break;
            }
        } else if (str[i] == 'b') {
            if (found_a) {
                valid = true;
            } else {
                valid = false;
                break;
            }
        } else {
            valid = false;
            break;
        }
    }

    return valid;
}

int main(void) {
    const char *test_cases[] = {
        "a",
        "ab",
        "abb",
        "abbb",
        "b",
        "ba",
        "aa",
        "abc",
        "",
        NULL
    };

    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        bool result = match_a_followed_by_bs(test_cases[i]);
        if (test_cases[i] == NULL) {
            printf("NULL: %s\n", result ? "Match" : "No Match");
        } else {
            printf("\"%s\": %s\n", test_cases[i], result ? "Match" : "No Match");
        }
    }

    return 0;
}