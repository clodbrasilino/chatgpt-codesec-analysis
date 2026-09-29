#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MIN_PASSWORD_LENGTH 8

bool is_password_valid(const char *password);

bool is_password_valid(const char *password) {
    if (password == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(password);
    if (length < MIN_PASSWORD_LENGTH) {
        return false;
    }

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    for (size_t i = 0; i < length; i++) {
        unsigned char ch = (unsigned char)password[i];
        
        if (isupper(ch)) {
            has_upper = true;
        } else if (islower(ch)) {
            has_lower = true;
        } else if (isdigit(ch)) {
            has_digit = true;
        } else if (ispunct(ch)) {
            has_special = true;
        }
    }

    return has_upper && has_lower && has_digit && has_special;
}

int main(void) {
    const char *test_passwords[] = {
        NULL,
        "short",
        "NoSpecialChar1",
        "noupperchar1!",
        "NOLOWERCHAR1!",
        "NoDigitPass!",
        "ValidPass123!"
    };

    size_t num_tests = sizeof(test_passwords) / sizeof(test_passwords[0]);

    for (size_t i = 0; i < num_tests; i++) {
        if (is_password_valid(test_passwords[i])) {
            printf("Test %zu: Valid\n", i);
        } else {
            printf("Test %zu: Invalid\n", i);
        }
    }

    return 0;
}