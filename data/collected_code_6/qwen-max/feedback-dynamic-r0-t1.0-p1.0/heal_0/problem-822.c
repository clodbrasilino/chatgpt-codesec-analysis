#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_valid_password(const char *password) {
    if (password == NULL) return false;

    int length = strlen(password);
    if (length < 8 || length > 20) return false;

    bool has_uppercase = false;
    bool has_lowercase = false;
    bool has_digit = false;

    for (int i = 0; i < length; ++i) {
        if (password[i] >= 'A' && password[i] <= 'Z') has_uppercase = true;
        else if (password[i] >= 'a' && password[i] <= 'z') has_lowercase = true;
        else if (password[i] >= '0' && password[i] <= '9') has_digit = true;
        else return false;
    }

    return has_uppercase && has_lowercase && has_digit;
}

int main() {
    const char *password1 = "Password123";
    const char *password2 = "pass";
    const char *password3 = "PASSWORD123";
    const char *password4 = "Pass1";
    const char *password5 = "Pa$$word123";

    printf("Password1: %s\n", is_valid_password(password1) ? "Valid" : "Invalid");
    printf("Password2: %s\n", is_valid_password(password2) ? "Valid" : "Invalid");
    printf("Password3: %s\n", is_valid_password(password3) ? "Valid" : "Invalid");
    printf("Password4: %s\n", is_valid_password(password4) ? "Valid" : "Invalid");
    printf("Password5: %s\n", is_valid_password(password5) ? "Valid" : "Invalid");

    return 0;
}