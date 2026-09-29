#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

bool is_valid_password(const char *password) {
    if (password == NULL) return false;

    size_t len = strlen(password);

    if (len < 8 || len > 20) return false;

    bool has_upper = false, has_lower = false, has_digit = false, has_special = false;

    for (size_t i = 0; i < len; ++i) {
        if (password[i] >= 'A' && password[i] <= 'Z') has_upper = true;
        else if (password[i] >= 'a' && password[i] <= 'z') has_lower = true;
        else if (isdigit((unsigned char)password[i])) has_digit = true;
        else if (strchr("!@#$%^&*()-_=+[]{}|;:',.<>/?", password[i])) has_special = true;
    }

    return has_upper && has_lower && has_digit && has_special;
}

int main() {
    const char *test_passwords[] = {"Password1!", "weak", "StrongP4ssw0rd!"};
    for (size_t i = 0; i < 3; ++i) {
        if (is_valid_password(test_passwords[i])) {
            printf("Password '%s' is valid.\n", test_passwords[i]);
        } else {
            printf("Password '%s' is invalid.\n", test_passwords[i]);
        }
    }
    return 0;
}