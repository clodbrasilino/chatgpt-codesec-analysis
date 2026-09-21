#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_valid_email(const char *email)
{
    static const char pattern[] =
        "^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@"
        "[A-Za-z0-9]([A-Za-z0-9-]{0,61}[A-Za-z0-9])?"
        "(\\.[A-Za-z0-9]([A-Za-z0-9-]{0,61}[A-Za-z0-9])?)+$";
    regex_t regex;
    int status;

    if (email == NULL || email[0] == '\0' || strlen(email) > 254) {
        return false;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (status != 0) {
        return false;
    }

    status = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    return status == 0;
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        char *new_buffer;
        size_t new_capacity;

        if (ch == '\r') {
            int next = fgetc(stream);

            if (next != '\n' && next != EOF) {
                ungetc(next, stream);
            }
            break;
        }

        if (length == 254) {
            while ((ch = fgetc(stream)) != EOF && ch != '\n') {
                if (ch == '\r') {
                    int next = fgetc(stream);

                    if (next != '\n' && next != EOF) {
                        ungetc(next, stream);
                    }
                    break;
                }
            }
            free(buffer);
            return NULL;
        }

        if (length + 1 >= capacity) {
            new_capacity = capacity == 0 ? 64 : capacity * 2;
            if (new_capacity > 255) {
                new_capacity = 255;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    if (buffer == NULL) {
        buffer = malloc(1);
        if (buffer == NULL) {
            return NULL;
        }
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *email = read_line(stdin);

    if (email == NULL) {
        puts("Invalid email address");
        return ferror(stdin) ? 1 : 0;
    }

    puts(is_valid_email(email)
             ? "Valid email address"
             : "Invalid email address");

    free(email);
    return 0;
}