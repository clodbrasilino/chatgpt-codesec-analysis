#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool is_valid_password(const char *password) {
    if (password == NULL) {
        return false;
    }

    size_t length = strlen(password);
    if (length < 8) {
        return false;
    }

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    for (size_t i = 0; i < length; i++) {
        unsigned char ch = (unsigned char)password[i];

        if (isspace(ch)) {
            return false;
        }

        if (isupper(ch)) {
            has_upper = true;
        } else if (islower(ch)) {
            has_lower = true;
        } else if (isdigit(ch)) {
            has_digit = true;
        } else if (ispunct(ch)) {
            has_special = true;
        } else {
            return false;
        }
    }

    return has_upper && has_lower && has_digit && has_special;
}

int main(void) {
    const char *password = "Passw0rd!";

    if (is_valid_password(password)) {
        printf("Valid password\n");
    } else {
        printf("Invalid password\n");
    }

    return 0;
}