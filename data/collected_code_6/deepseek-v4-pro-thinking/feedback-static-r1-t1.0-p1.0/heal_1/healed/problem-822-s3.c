#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_PASSWORD_LEN 256

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

bool is_valid_password(const char *password) {
    if (password == NULL) {
        return false;
    }

    size_t length = safe_strlen(password, MAX_PASSWORD_LEN);
    if (length == MAX_PASSWORD_LEN) {
        return false;
    }

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