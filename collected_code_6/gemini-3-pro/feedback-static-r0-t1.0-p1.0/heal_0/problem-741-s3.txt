#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool areAllCharactersSame(const char *str) {
    if (str == NULL) {
        return false;
    }

    if (str[0] == '\0') {
        return true;
    }

    char first_char = str[0];
    const char *current = str + 1;

    while (*current != '\0') {
        if (*current != first_char) {
            return false;
        }
        current++;
    }

    return true;
}

int main(void) {
    const char *test_cases[] = {
        "aaaaa",
        "abcde",
        "",
        "z",
        "zzzzzzzzX",
        NULL
    };
    
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; i++) {
        if (areAllCharactersSame(test_cases[i])) {
            printf("Test %zu: All characters are same\n", i);
        } else {
            printf("Test %zu: Characters are not same or input is invalid\n", i);
        }
    }

    return 0;
}