#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

static bool has_uppercase(const char *password, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)password[i])) {
            return true;
        }
    }
    return false;
}

static bool has_lowercase(const char *password, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (islower((unsigned char)password[i])) {
            return true;
        }
    }
    return false;
}

static bool has_digit(const char *password, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (isdigit((unsigned char)password[i])) {
            return true;
        }
    }
    return false;
}

static bool has_special(const char *password, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (!isalnum((unsigned char)password[i])) {
            return true;
        }
    }
    return false;
}

static bool is_password_valid(const char *password, size_t max_len) {
    size_t len = 0;
    
    if (password == NULL) {
        return false;
    }
    
    while (len < max_len && password[len] != '\0') {
        len++;
    }
    
    if (len == max_len && password[len] != '\0') {
        return false;
    }
    
    if (len < 8 || len > 32) {
        return false;
    }
    
    if (!has_uppercase(password, len)) {
        return false;
    }
    
    if (!has_lowercase(password, len)) {
        return false;
    }
    
    if (!has_digit(password, len)) {
        return false;
    }
    
    if (!has_special(password, len)) {
        return false;
    }
    
    return true;
}

int main(void) {
    const char *test_passwords[] = {
        "Password1!",
        "weak",
        "NoDigits!",
        "nouppercase1!",
        "NOLOWERCASE1!",
        "NoSpecial1",
        NULL
    };
    
    for (int i = 0; test_passwords[i] != NULL; i++) {
        size_t max_check = 33;
        printf("'%s': %s\n", test_passwords[i],
               is_password_valid(test_passwords[i], max_check) ? "valid" : "invalid");
    }
    
    return 0;
}