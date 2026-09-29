#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool is_valid_password(const char *password);

bool is_valid_password(const char *password) {
    if (password == NULL) {
        return false;
    }

    size_t length = 0;
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    while (password[length] != '\0') {
        unsigned char c = (unsigned char)password[length];

        if (isupper(c)) {
            has_upper = true;
        } else if (islower(c)) {
            has_lower = true;
        } else if (isdigit(c)) {
            has_digit = true;
        } else if (ispunct(c)) {
            has_special = true;
        }
        
        length++;
    }

    return (length >= 8 && has_upper && has_lower && has_digit && has_special);
}

int main(void) {
    const char *test_passwords[] = {
        "StrongPass1!",
        "weakpass",
        "NoSpecialChar1",
        "no_uppercase_1!",
        "NO_LOWERCASE_1!",
        "NoDigitsHere!",
        "Sh1!",
        NULL
    };

    for (size_t i = 0; test_passwords[i] != NULL; i++) {
        bool result = is_valid_password(test_passwords[i]);
        if (result) {
            printf("Valid\n");
        } else {
            printf("Invalid\n");
        }
    }

    return 0;
}