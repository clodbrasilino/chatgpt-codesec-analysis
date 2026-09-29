#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_EMAIL_LENGTH = 320 };

static bool is_valid_email(const char *email)
{
    static const char pattern[] =
        "^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@"
        "[A-Za-z0-9]([A-Za-z0-9-]*[A-Za-z0-9])?"
        "(\\.[A-Za-z0-9]([A-Za-z0-9-]*[A-Za-z0-9])?)+$";
    regex_t regex;

    if (email == NULL || email[0] == '\0' ||
        strlen(email) > MAX_EMAIL_LENGTH) {
        return false;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return false;
    }

    int result = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

static char *read_line(size_t max_length)
{
    size_t capacity = 64;
    size_t length = 0;
    char *line = malloc(capacity);

    if (line == NULL) {
        return NULL;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && ferror(stdin)) {
                free(line);
                return NULL;
            }
            break;
        }

        if (length == max_length) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            free(line);
            return NULL;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity = capacity * 2;

            if (new_capacity > max_length + 1) {
                new_capacity = max_length + 1;
            }

            char *resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return NULL;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (length > 0 && line[length - 1] == '\r') {
        --length;
    }

    line[length] = '\0';
    return line;
}

int main(void)
{
    char *email = read_line(MAX_EMAIL_LENGTH);

    if (email == NULL) {
        return 1;
    }

    puts(is_valid_email(email) ? "Valid" : "Invalid");
    free(email);

    return 0;
}