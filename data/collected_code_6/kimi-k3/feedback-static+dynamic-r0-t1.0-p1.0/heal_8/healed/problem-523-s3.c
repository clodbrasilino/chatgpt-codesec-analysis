#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check_password_strength(const char *str, size_t max_len, size_t min_length) {
    int has_upper = 0;
    int has_lower = 0;
    int has_digit = 0;
    size_t length;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    length = strnlen(str, max_len);

    if (length < min_length) {
        return 0;
    }

    for (i = 0; i < length; i++) {
        if (isupper((unsigned char)str[i])) {
            has_upper = 1;
        } else if (islower((unsigned char)str[i])) {
            has_lower = 1;
        } else if (isdigit((unsigned char)str[i])) {
            has_digit = 1;
        }
    }

    return has_upper && has_lower && has_digit;
}

int main(void) {
    char password[128];
    size_t min_len = 8;
    size_t len;

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    len = strcspn(password, "\n");
    if (len == sizeof(password) - 1 && password[len] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Password too long\n");
        return 1;
    }
    password[len] = '\0';

    if (check_password_strength(password, sizeof(password), min_len)) {
        printf("Password meets requirements\n");
    } else {
        printf("Password does not meet requirements\n");
    }

    return 0;
}