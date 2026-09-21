#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool meets_requirements(const char *string, size_t required_length)
{
    if (string == NULL) {
        return false;
    }

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    size_t length = 0;

    for (const unsigned char *p = (const unsigned char *)string;
         *p != '\0';
         ++p) {
        if (length == SIZE_MAX) {
            return false;
        }

        ++length;

        if (isupper(*p)) {
            has_upper = true;
        } else if (islower(*p)) {
            has_lower = true;
        } else if (isdigit(*p)) {
            has_digit = true;
        }
    }

    return length == required_length && has_upper && has_lower && has_digit;
}

static char *read_line(FILE *stream)
{
    if (stream == NULL) {
        errno = EINVAL;
        return NULL;
    }

    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                errno = ENOMEM;
                return NULL;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        size_t available = capacity - length;

        if (fgets(buffer + length, available > (size_t)INT_MAX
                                    ? INT_MAX
                                    : (int)available,
                  stream) == NULL) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }

            break;
        }

        while (buffer[length] != '\0' && buffer[length] != '\n') {
            ++length;
        }

        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            break;
        }

        if (feof(stream)) {
            break;
        }
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    return buffer;
}

static bool parse_size(const char *text, size_t *value)
{
    if (text == NULL || value == NULL) {
        return false;
    }

    while (isspace((unsigned char)*text)) {
        ++text;
    }

    if (*text == '\0' || *text == '-' || *text == '+') {
        return false;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long parsed = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text) {
        return false;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || parsed > SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

int main(void)
{
    if (fputs("Enter the required length: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    char *length_line = read_line(stdin);

    if (length_line == NULL) {
        fputs("Invalid length.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t required_length = 0;
    bool valid_length = parse_size(length_line, &required_length);
    free(length_line);

    if (!valid_length) {
        fputs("Invalid length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputs("Enter the string: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    char *input = read_line(stdin);

    if (input == NULL) {
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    bool valid = meets_requirements(input, required_length);
    free(input);

    const char *message = valid
        ? "The string meets all requirements.\n"
        : "The string does not meet all requirements.\n";

    if (fputs(message, stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}