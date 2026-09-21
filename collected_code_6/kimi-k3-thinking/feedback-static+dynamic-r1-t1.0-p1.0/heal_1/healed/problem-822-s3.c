#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MIN_PASSWORD_LENGTH 8
#define MAX_PASSWORD_LENGTH 128
#define INPUT_BUFFER_SIZE (MAX_PASSWORD_LENGTH + 2)

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len = 0;

    if (s == NULL) {
        return 0;
    }

    while (len < max_len && s[len] != '\0') {
        len++;
    }

    return len;
}

bool is_valid_password(const char *password)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;
    size_t length;
    size_t i;

    if (password == NULL) {
        return false;
    }

    length = bounded_strlen(password, MAX_PASSWORD_LENGTH + 1);
    if (length < MIN_PASSWORD_LENGTH || length > MAX_PASSWORD_LENGTH) {
        return false;
    }

    for (i = 0; i < length; i++) {
        unsigned char c = (unsigned char)password[i];

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

int main(void)
{
    char password[INPUT_BUFFER_SIZE];
    size_t len;
    int ch;

    printf("Enter a password: ");

    if (fgets(password, sizeof(password), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    len = bounded_strlen(password, sizeof(password));

    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0';
    } else if (len == sizeof(password) - 1) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        fprintf(stderr, "Error: input exceeds maximum password length.\n");
        return 1;
    }

    if (is_valid_password(password)) {
        printf("Password is valid.\n");
    } else {
        printf("Password is invalid.\n");
    }

    return 0;
}