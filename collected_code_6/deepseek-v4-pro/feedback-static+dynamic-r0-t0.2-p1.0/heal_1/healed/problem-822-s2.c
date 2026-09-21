#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

bool isValidPassword(const char *password) {
    if (password == NULL) {
        return false;
    }

    size_t length = 0;
    while (length < 65 && password[length] != '\0') {
        length++;
    }

    if (length < 8 || length > 64 || password[length] != '\0') {
        return false;
    }

    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    for (size_t i = 0; i < length; i++) {
        unsigned char c = (unsigned char)password[i];
        if (isupper(c)) {
            hasUpper = true;
        } else if (islower(c)) {
            hasLower = true;
        } else if (isdigit(c)) {
            hasDigit = true;
        } else if (ispunct(c)) {
            hasSpecial = true;
        } else if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            return false;
        }
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}

int main(void) {
    const char *testPasswords[] = {
        "Password1!",
        "weak",
        "NoSpecial1",
        "NoDigit!",
        "NOLOWER1!",
        "noupper1!",
        "Valid123!",
        NULL
    };

    for (int i = 0; testPasswords[i] != NULL; i++) {
        printf("%s: %s\n", testPasswords[i], 
               isValidPassword(testPasswords[i]) ? "valid" : "invalid");
    }

    return 0;
}