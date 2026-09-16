#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool is_valid_password(const char *password) {
    if (password == NULL) {
        return false;
    }

    size_t length = strlen(password);
    if (length < 8 || length > 64) {
        return false;
    }

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    for (size_t i = 0; i < length; i++) {
        if (isupper((unsigned char)password[i])) {
            has_upper = true;
        } else if (islower((unsigned char)password[i])) {
            has_lower = true;
        } else if (isdigit((unsigned char)password[i])) {
            has_digit = true;
        } else if (ispunct((unsigned char)password[i])) {
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
        "NoSpecialChar123",
        NULL
    };

    size_t num_tests = sizeof(test_passwords) / sizeof(test_passwords[0]);

    for (size_t i = 0; i < num_tests; i++) {
        bool valid = is_valid_password(test_passwords[i]);
        printf("Password %zu: %s\n", i + 1, valid ? "Valid" : "Invalid");
    }

    return 0;
}