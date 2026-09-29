#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>

bool is_valid_password(const char *password, size_t max_size) {
    if (password == NULL) {
        return false;
    }

    size_t length = 0;
    while (length < max_size && password[length] != '\0') {
        length++;
    }

    if (length == max_size) {
        return false;
    }

    if (length < 8) {
        return false;
    }

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;

    for (size_t i = 0; i < length; i++) {
        unsigned char ch = (unsigned char)password[i];
        if (isupper(ch)) {
            has_upper = true;
        } else if (islower(ch)) {
            has_lower = true;
        } else if (isdigit(ch)) {
            has_digit = true;
        }
    }

    return has_upper && has_lower && has_digit;
}

int main(void) {
    const char password[] = "ValidPass123";
    if (is_valid_password(password, sizeof(password))) {
        puts("true");
    } else {
        puts("false");
    }
    return 0;
}