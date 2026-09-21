#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool check_string_requirements(const char *str, size_t min_length) {
    if (str == NULL) {
        return false;
    }

    for (size_t i = 0; i < min_length; i++) {
        if (str[i] == '\0') {
            return false;
        }
    }

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isupper((unsigned char)str[i])) {
            has_upper = true;
        } else if (islower((unsigned char)str[i])) {
            has_lower = true;
        } else if (isdigit((unsigned char)str[i])) {
            has_digit = true;
        }
    }

    return has_upper && has_lower && has_digit;
}

int main(void) {
    const char *test_cases[] = {
        "Password123",
        "pass123",
        "PASS123",
        "Password",
        "P1",
        NULL
    };
    
    size_t required_length = 8;
    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_cases; i++) {
        bool result = check_string_requirements(test_cases[i], required_length);
        if (test_cases[i] != NULL) {
            printf("String: '%s' - Meets requirements: %s\n", test_cases[i], result ? "true" : "false");
        } else {
            printf("String: NULL - Meets requirements: %s\n", result ? "true" : "false");
        }
    }

    return 0;
}