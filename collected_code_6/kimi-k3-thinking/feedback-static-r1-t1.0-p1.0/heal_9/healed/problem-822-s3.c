#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define MIN_PASSWORD_LENGTH 8
#define MAX_PASSWORD_LENGTH 128
#define READ_BUFFER_SIZE (MAX_PASSWORD_LENGTH + 2)

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

static char *read_line(FILE *stream, bool *line_too_long)
{
    char *buffer;
    size_t length = 0;
    int ch;

    if (stream == NULL || line_too_long == NULL) {
        return NULL;
    }

    *line_too_long = false;

    buffer = malloc(READ_BUFFER_SIZE);
    if (buffer == NULL) {
        return NULL;
    }

    buffer[0] = '\0';

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length + 1 >= READ_BUFFER_SIZE) {
            *line_too_long = true;
            continue;
        }

        buffer[length] = (char)ch;
        length++;
    }

    if (ferror(stream) != 0) {
        free(buffer);
        return NULL;
    }

    if (ch == EOF && length == 0 && !*line_too_long) {
        free(buffer);
        return NULL;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        length--;
    }

    buffer[length] = '\0';

    return buffer;
}

int main(void)
{
    char *password;
    bool line_too_long = false;

    printf("Enter a password: ");
    fflush(stdout);

    password = read_line(stdin, &line_too_long);
    if (password == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    if (line_too_long ||
        bounded_strlen(password, MAX_PASSWORD_LENGTH + 1) > MAX_PASSWORD_LENGTH) {
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