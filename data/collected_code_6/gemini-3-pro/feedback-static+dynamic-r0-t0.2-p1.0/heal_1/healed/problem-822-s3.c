#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool is_valid_password(const char *password) {
    if (password == NULL) {
        return false;
    }

    size_t length = 0;
    while (length <= 64 && password[length] != '\0') {
        length++;
    }

    if (length < 8 || length > 64) {
        return false;
    }

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    for (size_t i = 0; i < length; i++) {
        unsigned char c = (unsigned char)password[i];
        if (isupper(c)) {
            has_upper = true;
        } else if (islower(c)) {
            has_lower = true;
        } else if (isdigit(c)) {
            has_digit = true;
        } else if (ispunct(c)) {
            has_special = true;
        }
    }

    return has_upper && has_lower && has_digit && has_special;
}

int main(void) {
    const char *test_passwords[] = {
        "Valid1Password!",
        "short1!",
        "nouppercase1!",
        "NOLOWERCASE1!",
        "NoDigitPassword!",
        "NoSpecial123",
        NULL
    };

    size_t num_passwords = sizeof(test_passwords) / sizeof(test_passwords[0]);

    for (size_t i = 0; i < num_passwords; i++) {
        if (test_passwords[i] != NULL) {
            bool valid = is_valid_password(test_passwords[i]);
            printf("Password: %s - Valid: %s\n", test_passwords[i], valid ? "true" : "false");
        } else {
            bool valid = is_valid_password(test_passwords[i]);
            printf("Password: NULL - Valid: %s\n", valid ? "true" : "false");
        }
    }

    return 0;
}