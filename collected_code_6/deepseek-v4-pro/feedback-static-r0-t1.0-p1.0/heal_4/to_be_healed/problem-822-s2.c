#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define MIN_PASSWORD_LENGTH 8
#define MAX_PASSWORD_LENGTH 128

static bool has_uppercase(const char *password, size_t length) {
    for (size_t i = 0; i < length; i++) {
        if (isupper((unsigned char)password[i])) {
            return true;
        }
    }
    return false;
}

static bool has_lowercase(const char *password, size_t length) {
    for (size_t i = 0; i < length; i++) {
        if (islower((unsigned char)password[i])) {
            return true;
        }
    }
    return false;
}

static bool has_digit(const char *password, size_t length) {
    for (size_t i = 0; i < length; i++) {
        if (isdigit((unsigned char)password[i])) {
            return true;
        }
    }
    return false;
}

static bool has_special_character(const char *password, size_t length) {
    for (size_t i = 0; i < length; i++) {
        unsigned char c = (unsigned char)password[i];
        if (!isalnum(c)) {
            return true;
        }
    }
    return false;
}

bool is_valid_password(const char *password) {
    if (password == NULL) {
        return false;
    }

    size_t length = 0;
    const char *ptr = password;
    while (length < MAX_PASSWORD_LENGTH + 1 && *ptr != '\0') {
        length++;
        ptr++;
    }

    if (length > MAX_PASSWORD_LENGTH || *ptr != '\0') {
        return false;
    }

    if (length < MIN_PASSWORD_LENGTH) {
        return false;
    }

    for (size_t i = 0; i < length; i++) {
        if (!isprint((unsigned char)password[i])) {
            return false;
        }
    }

    if (!has_uppercase(password, length) ||
        !has_lowercase(password, length) ||
        !has_digit(password, length) ||
        !has_special_character(password, length)) {
        return false;
    }

    return true;
}

int main(void) {
    const char *test_passwords[] = {
        "Password1!",
        "password1!",
        "PASSWORD1!",
        "Password!",
        "Pass1!",
        "Password1",
        "Password1!Password1!Password1!Password1!Password1!Password1!Password1!Password1!Password1!Password1!Password1!Password1!Password1!Password1!Password1!Password1!",
        "Valid123!@#",
        "",
        NULL
    };

    for (int i = 0; test_passwords[i] != NULL; i++) {
        printf("Password: \"%s\" - Valid: %s\n", 
               test_passwords[i],
               is_valid_password(test_passwords[i]) ? "true" : "false");
    }

    printf("NULL password - Valid: %s\n", 
           /* Possible weaknesses found:
            *  Condition 'is_valid_password(NULL)' is always false [knownConditionTrueFalse]
            *  Calling function 'is_valid_password' returns 0
            *  Condition 'is_valid_password(NULL)' is always false
            */
           is_valid_password(NULL) ? "true" : "false");

    return 0;
}