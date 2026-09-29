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
    bool has_punct = false;
    size_t len = 0;

    for (size_t i = 0; i < 256; ++i) {
        if (password[i] == '\0') {
            break;
        }
        len++;
        unsigned char c = password[i];
        if (isupper(c)) {
            has_upper = true;
        } else if (islower(c)) {
            has_lower = true;
        } else if (isdigit(c)) {
            has_digit = true;
        } else if (ispunct(c)) {
            has_punct = true;
        }
    }

    if (len < 8) {
        return false;
    }

    return has_upper && has_lower && has_digit && has_punct;
}

int main(void) {
    const char *password1 = "Password1!";
    const char *password2 = "weak";
    const char *password3 = "NoSpecial1";

    printf("Password 1 valid: %s\n", is_valid_password(password1) ? "true" : "false");
    printf("Password 2 valid: %s\n", is_valid_password(password2) ? "true" : "false");
    printf("Password 3 valid: %s\n", is_valid_password(password3) ? "true" : "false");

    return 0;
}