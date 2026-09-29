#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_valid_password(const char *password) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (password == NULL || strlen(password) < 8) {
        return false;
    }

    bool has_upper = 0, has_lower = 0, has_digit = 0;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    for (size_t i = 0; i < strlen(password); ++i) {
        if (password[i] >= 'A' && password[i] <= 'Z') {
            has_upper = 1;
        } else if (password[i] >= 'a' && password[i] <= 'z') {
            has_lower = 1;
        } else if (password[i] >= '0' && password[i] <= '9') {
            has_digit = 1;
        }
    }

    return has_upper && has_lower && has_digit;
}

int main() {
    const char *password = "TestPass123";
    if (is_valid_password(password)) {
        printf("Password is valid.\n");
    } else {
        printf("Password is invalid.\n");
    }
    return 0;
}