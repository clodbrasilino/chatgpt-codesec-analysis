#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool is_valid_password(const char *password) {
    if (password == NULL) {
        return false;
    }

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;
    size_t length = 0;

    while (password[length] != '\0') {
        if (length >= 64) {
            return false;
        }
        if (isupper((unsigned char)password[length])) {
            has_upper = true;
        } else if (islower((unsigned char)password[length])) {
            has_lower = true;
        } else if (isdigit((unsigned char)password[length])) {
            has_digit = true;
        } else if (ispunct((unsigned char)password[length])) {
            has_special = true;
        }
        length++;
    }

    if (length < 8) {
        return false;
    }

    return has_upper && has_lower && has_digit && has_special;
}

int main(void) {
    const char *test_passwords[] = {
        "Valid1Password!",
        "short1!",
        "nousername1!",
        "NOLOWERCASE1!",
        "NoDigitPassword!",
        "NoSpecialPassword1",
        NULL
    };

    for (size_t i = 0; test_passwords[i] != NULL; i++) {
        if (is_valid_password(test_passwords[i])) {
            printf("Password '%s' is valid.\n", test_passwords[i]);
        } else {
            printf("Password '%s' is invalid.\n", test_passwords[i]);
        }
    }

    return 0;
}