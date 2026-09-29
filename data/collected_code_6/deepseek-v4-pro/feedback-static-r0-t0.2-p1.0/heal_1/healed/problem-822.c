#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

bool is_valid_password(const char *password) {
    if (password == NULL) {
        return false;
    }

    size_t length = 0;
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    for (size_t i = 0; i < 65; i++) {
        if (password[i] == '\0') {
            length = i;
            break;
        }
        if (i == 64) {
            return false;
        }

        unsigned char c = (unsigned char)password[i];
        if (isupper(c)) {
            has_upper = true;
        } else if (islower(c)) {
            has_lower = true;
        } else if (isdigit(c)) {
            has_digit = true;
        } else if (ispunct(c)) {
            has_special = true;
        } else if (isspace(c)) {
            return false;
        }
    }

    if (length < 8) {
        return false;
    }

    return has_upper && has_lower && has_digit && has_special;
}

int main(void) {
    const char *test_passwords[] = {
        "Password1!",
        "password1!",
        "PASSWORD1!",
        "Password!",
        "Password1",
        "Pass1!",
        "ValidPass123!@#",
        NULL
    };

    for (int i = 0; test_passwords[i] != NULL; i++) {
        printf("%s: %s\n", test_passwords[i],
               is_valid_password(test_passwords[i]) ? "valid" : "invalid");
    }

    return 0;
}