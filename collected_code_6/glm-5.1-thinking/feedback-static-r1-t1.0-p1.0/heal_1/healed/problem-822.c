#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MIN_PASSWORD_LENGTH 8
#define MAX_PASSWORD_LENGTH 128

bool is_password_valid(const char *password, size_t max_len) {
    if (password == NULL) {
        return false;
    }

    size_t length = 0;
    while (length < max_len && password[length] != '\0') {
        length++;
    }

    if (length < MIN_PASSWORD_LENGTH) {
        return false;
    }

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    for (size_t i = 0; i < length; ++i) {
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
    const char *valid_password = "Password1!";
    const char *short_password = "Pwd1!";
    const char *no_upper = "password1!";
    const char *no_lower = "PASSWORD1!";
    const char *no_digit = "Password!";
    const char *no_special = "Password1";
    const char *null_password = NULL;

    printf("Valid: %d\n", is_password_valid(valid_password, MAX_PASSWORD_LENGTH));
    printf("Short: %d\n", is_password_valid(short_password, MAX_PASSWORD_LENGTH));
    printf("No Upper: %d\n", is_password_valid(no_upper, MAX_PASSWORD_LENGTH));
    printf("No Lower: %d\n", is_password_valid(no_lower, MAX_PASSWORD_LENGTH));
    printf("No Digit: %d\n", is_password_valid(no_digit, MAX_PASSWORD_LENGTH));
    printf("No Special: %d\n", is_password_valid(no_special, MAX_PASSWORD_LENGTH));
    printf("Null: %d\n", is_password_valid(null_password, MAX_PASSWORD_LENGTH));

    return 0;
}