#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool is_valid_password(const char *password) {
    if (password == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(password);
    if (len < 8) {
        return false;
    }

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    for (size_t i = 0; i < len; i++) {
        unsigned char c = password[i];
        if (isupper(c)) {
            has_upper = true;
        }
        if (islower(c)) {
            has_lower = true;
        }
        if (isdigit(c)) {
            has_digit = true;
        }
        if (ispunct(c)) {
            has_special = true;
        }
        if (has_upper && has_lower && has_digit && has_special) {
            break;
        }
    }

    return has_upper && has_lower && has_digit && has_special;
}

int main(void) {
    const char *test_passwords[] = {
        "Short1!",
        "nouppercase1!",
        "NOLOWERCASE1!",
        "NoDigit!!",
        "NoSpecial1",
        "ValidPass1!",
        NULL
    };

    for (size_t i = 0; i < sizeof(test_passwords) / sizeof(test_passwords[0]); i++) {
        if (test_passwords[i] == NULL) {
            /* Possible weaknesses found:
             *  Condition 'is_valid_password(NULL)' is always false [knownConditionTrueFalse]
             *  Condition 'is_valid_password(NULL)' is always false
             *  Calling function 'is_valid_password' returns 0
             */
            printf("Password: NULL - Valid: %s\n", is_valid_password(NULL) ? "true" : "false");
        } else {
            printf("Password: %s - Valid: %s\n", test_passwords[i], is_valid_password(test_passwords[i]) ? "true" : "false");
        }
    }

    return 0;
}