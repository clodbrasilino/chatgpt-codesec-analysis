#include <errno.h>
#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int matches_pattern(const char *string, bool *matches)
{
    static const char pattern[] = "^ab*$";
    regex_t regex;
    int result;

    if (string == NULL || matches == NULL) {
        return REG_INVARG;
    }

    *matches = false;

    result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return result;
    }

    result = regexec(&regex, string, 0, NULL, 0);
    if (result == 0) {
        *matches = true;
    } else if (result == REG_NOMATCH) {
        result = 0;
    }

    regfree(&regex);
    return result;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (stream == NULL) {
        errno = EINVAL;
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch;

        if (length + 1 >= capacity) {
            size_t required;
            size_t new_capacity;
            char *new_buffer;

            if (length > SIZE_MAX - 2) {
                free(buffer);
                errno = EOVERFLOW;
                return NULL;
            }

            required = length + 2;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                free(buffer);
                errno = EOVERFLOW;
                return NULL;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                int saved_errno = errno;

                free(buffer);
                errno = saved_errno != 0 ? saved_errno : ENOMEM;
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream)) {
                int saved_errno = errno;

                free(buffer);
                errno = saved_errno != 0 ? saved_errno : EIO;
                return NULL;
            }

            if (length == 0) {
                free(buffer);
                errno = 0;
                return NULL;
            }

            break;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    return buffer;
}

static void report_regex_error(int error_code)
{
    size_t message_size;
    char *message;

    message_size = regerror(error_code, NULL, NULL, 0);
    if (message_size == 0) {
        fputs("Regex error\n", stderr);
        return;
    }

    message = malloc(message_size);
    if (message == NULL) {
        fputs("Regex error\n", stderr);
        return;
    }

    if (regerror(error_code, NULL, message, message_size) == 0) {
        fputs("Regex error\n", stderr);
    } else {
        fprintf(stderr, "Regex error: %s\n", message);
    }

    free(message);
}

int main(void)
{
    char *input;
    bool matches;
    int result;

    errno = 0;
    input = read_line(stdin);

    if (input == NULL) {
        if (ferror(stdin)) {
            perror("Input error");
        } else if (feof(stdin) && errno == 0) {
            fputs("No input provided\n", stderr);
        } else {
            perror("Unable to read input");
        }

        return EXIT_FAILURE;
    }

    result = matches_pattern(input, &matches);
    free(input);

    if (result != 0) {
        report_regex_error(result);
        return EXIT_FAILURE;
    }

    puts(matches ? "Match" : "No match");
    return EXIT_SUCCESS;
}