#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool is_valid_password(const char *password, size_t max_len) {
    if (password == NULL) {
        return false;
    }

    size_t len = strnlen(password, max_len);
    if (len < 8 || len >= max_len) {
        return false;
    }

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    for (size_t i = 0; i < len; ++i) {
        unsigned char c = password[i];
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
        "WeakPass1",
        "StrongPass1!",
        "short1!",
        "NOLOWER1!",
        "noupper1!",
        "NoDigit!!",
        "NoSpecial1",
        NULL
    };

    for (size_t i = 0; test_passwords[i] != NULL; ++i) {
        bool valid = is_valid_password(test_passwords[i], 129);
        printf("Password: %-15s Valid: %s\n", test_passwords[i], valid ? "true" : "false");
    }

    bool null_valid = is_valid_password(NULL, 129);
    printf("Password: NULL             Valid: %s\n", null_valid ? "true" : "false");

    return 0;
}