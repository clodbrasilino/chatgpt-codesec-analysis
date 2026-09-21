#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MIN_PASSWORD_LENGTH 8
#define MAX_PASSWORD_LENGTH 128

static size_t bounded_strlen(const char *s, size_t max)
{
    size_t n = 0;

    while (n < max && s[n] != '\0') {
        n++;
    }

    return n;
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

static char *read_line(FILE *stream)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer = malloc(capacity);
    int ch;

    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > (SIZE_MAX / 2)) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length] = (char)ch;
        length++;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *password;

    printf("Enter a password: ");

    password = read_line(stdin);
    if (password == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    if (bounded_strlen(password, MAX_PASSWORD_LENGTH + 1) > MAX_PASSWORD_LENGTH) {
        fprintf(stderr, "Error: input exceeds maximum password length.\n");
        free(password);
        return 1;
    }

    if (is_valid_password(password)) {
        printf("Password is valid.\n");
    } else {
        printf("Password is invalid.\n");
    }

    free(password);
    return 0;
}