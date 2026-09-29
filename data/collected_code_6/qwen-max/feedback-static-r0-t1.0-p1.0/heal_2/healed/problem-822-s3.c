#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_valid_password(const char *password, size_t len) {
    if (len < 8 || len > 20) {
        return false;
    }

    bool has_upper = false, has_lower = false, has_digit = false, has_special = false;

    for (size_t i = 0; i < len; i++) {
        if (password[i] >= 'A' && password[i] <= 'Z') {
            has_upper = true;
        } else if (password[i] >= 'a' && password[i] <= 'z') {
            has_lower = true;
        } else if (password[i] >= '0' && password[i] <= '9') {
            has_digit = true;
        } else if (password[i] == '!' || password[i] == '@' || password[i] == '#' || password[i] == '$') {
            has_special = true;
        }
    }

    return has_upper && has_lower && has_digit && has_special;
}

int main() {
    const char *test_passwords[] = {"P@ssw0rd", "weakpass", "STRONGpassword1!", "Short1!"};
    const size_t num_passwords = sizeof(test_passwords) / sizeof(test_passwords[0]);

    for (size_t i = 0; i < num_passwords; i++) {
        const char *password = test_passwords[i];
        while (*password != '\0') password++;
        size_t len = password - test_passwords[i];
        if (is_valid_password(test_passwords[i], len)) {
            printf("Password '%s' is valid.\n", test_passwords[i]);
        } else {
            printf("Password '%s' is invalid.\n", test_passwords[i]);
        }
    }

    return 0;
}